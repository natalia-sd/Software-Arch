// #ifndef WALL_H
// #define WALL_H

// #include <string>
// #include <vector>
// #include "Poco/JSON/Object.h"
// #include <optional>

// namespace database
// {
//     class Wall {
//         private:
//             long _post_id;
//             long _user_id;
//             std::string _post_title;
//             std::string _post_text;

//     public:
//         static Wall fromJSON(const std::string & str);

//         long get_post_id() const;
//         long get_user_id() const;
//         const std::string& get_post_title() const;
//         const std::string& get_post_text() const;

//         long& post_id();
//         long& user_id();
//         std::string& post_title();
//         std::string& post_text();

//         static void init();
//         void create_post_to_mysql(long user_id);
//         /*static std::vector<Wall> read_post_by_id(long post_id);*/
//         static std::vector<Wall> read_posts_by_user(long user_id);
//         /*void update_post(long post_id);*/
//         /*static std::optional<Wall> delete_post(long post_id);*/



//         Poco::JSON::Object::Ptr toJSON() const;
//     };
// }
// #endif

#ifndef WALL_H
#define WALL_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Wall{
        private:
            long _post_id;
            long _user_id;
            std::string _post_title;
            std::string _post_text;

        public:

            static Wall fromJSON(const std::string & str);
        long get_post_id() const;
        long get_user_id() const;
        const std::string& get_post_title() const;
        const std::string& get_post_text() const;

        long& post_id();
        long& user_id();
        std::string& post_title();
        std::string& post_text();

            static void init();
            static std::vector<Wall> read_by_user_id(long user_id);
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif