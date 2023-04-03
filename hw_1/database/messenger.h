#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Message{
        private:
            long _message_id;
            long _sender_id;
            long _receiver_id;
            std::string _text_message;

        public:

            static Message fromJSON(const std::string & str);

            long             get_message_id() const;
            long             get_sender_id() const;
            long             get_receiver_id() const;
            const std::string &get_text_message() const;
            
            long&        message_id();
            long&        sender_id();
            long&        receiver_id();
            std::string &text_message();


            static void init();
            /* static std::vector<Message> get_messages(long sender_id, long receiver_id, std::string  &date_message);*/
            /* static std::optional<Message> delete_messages(long message_id);*/
            static std::vector<Message> read_all(long sender_id);
            /* void update_messages(long message_id);*/ 
            void post_message_to_mysql(long sender_id);
            
            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif