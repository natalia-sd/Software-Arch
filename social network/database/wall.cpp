#include "wall.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void Wall::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Wall` (`post_id` INT NOT NULL AUTO_INCREMENT,"
                        << "`user_id` INT NOT NULL,"
                        << "`post_title` VARCHAR(256) NOT NULL,"
                        << "`post_text` VARCHAR(256) NOT NULL,"
                        << "PRIMARY KEY (`post_id`));",
                now;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Wall::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("post_id", _post_id);
        root->set("user_id", _user_id);
        root->set("post_title", _post_title);
        root->set("post_text", _post_text);


        return root;
    }

    Wall Wall::fromJSON(const std::string &str)
    {
        Wall wall;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        wall.post_id() = object->getValue<long>("post_id");
        wall.user_id() = object->getValue<long>("user_id");
        wall.post_title() = object->getValue<std::string>("post_title");
        wall.post_text() = object->getValue<std::string>("post_text");

        return wall;
    }



    std::vector<Wall> Wall::read_posts_by_user(long user_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<Wall> result;
            Wall a;
            select << "SELECT post_id, user_id, post_title, post_text FROM Wall where user_id = ? ",
                into(a._post_id),
                into(a._user_id),
                into(a._post_title),
                into(a._post_text),
                use(user_id),
                range(0, 1); //  iterate over result set one row at a time

            while (!select.done())
            {
                if (select.execute())
                    result.push_back(a);
            }
            return result;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
        }
        return {};
    }

    void Wall::create_post_to_mysql(long user_id)
    {

        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Wall (user_id,  post_title, post_text) VALUES(?, ?, ?)",
                use(user_id),
                use(_post_title),
                use(_post_text);

            insert.execute();
            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_post_id),
                range(0, 1); //  iterate over result set one row at a time
            if (!select.done()) {
                select.execute();
            }
            std::cout << "inserted:" << _post_id << std::endl;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    long Wall::get_post_id() const
    {
        return _post_id;
    }
        long Wall::get_user_id() const
    {
        return _user_id;
    }
    const std::string &Wall::get_post_title() const
    {
        return _post_title;
    }

    const std::string &Wall::get_post_text() const
    {
        return _post_text;
    }
    long &Wall::post_id()
    {
        return _post_id;
    }
    long &Wall::user_id()
    {
        return _user_id;
    }
    std::string &Wall::post_title()
    {
        return _post_title;
    }

    std::string &Wall::post_text()
    {
        return _post_text;
    }

}