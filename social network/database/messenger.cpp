#include "messenger.h"
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

    void Message::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Message` (`message_id` INT NOT NULL AUTO_INCREMENT,"
                        << " `sender_id` INT NOT NULL,"
                        << "`receiver_id` INT NOT NULL,"
                        << "`text_message` VARCHAR(256) NULL,"
                        << "PRIMARY KEY (`message_id`));",
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

    Poco::JSON::Object::Ptr Message::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("message_id", _message_id);
        root->set("sender_id", _sender_id);
        root->set("receiver_id", _receiver_id);
        root->set("text_message", _text_message);



        return root;
    }

    Message Message::fromJSON(const std::string &str)
    {
        Message message;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        message.message_id() = object->getValue<long>("message_id");
        message.sender_id() = object->getValue<long>("sender_id");
        message.receiver_id() = object->getValue<long>("receiver_id");
        message.text_message() = object->getValue<std::string>("text_message");

        return message;
    }

    std::vector<Message> Message::read_all(long sender_id)
    {   

        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            std::vector<Message> result;
            Message a;
            select << "SELECT message_id, sender_id, receiver_id, text_message FROM Message where sender_id = ? ",
                into(a._message_id),
                into(a._sender_id),
                into(a._receiver_id),
                into(a._text_message),
                use(sender_id),
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

    void Message::post_message_to_mysql(long sender_id)
    {

        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Message (sender_id, receiver_id, text_message) VALUES(?, ?, ?)",
                use(sender_id),
                use(_receiver_id),
                use(_text_message);

            insert.execute();
            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_message_id),
                range(0, 1); //  iterate over result set one row at a time
            if (!select.done()) {
                select.execute();
            }
            std::cout << "inserted:" << _message_id << std::endl;
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


    long Message::get_message_id() const
    {
        return _message_id;
    }

    long Message::get_sender_id() const
    {
        return _sender_id;
    }

    long Message::get_receiver_id() const
    {
        return _receiver_id;
    }

    const std::string &Message::get_text_message() const
    {
        return _text_message;
    }

    long &Message::message_id()
    {
        return _message_id;
    }

    long &Message::sender_id()
    {
        return _sender_id;
    }

    long &Message::receiver_id()
    {
        return _receiver_id;
    }

    std::string &Message::text_message()
    {
        return _text_message;
    }

}