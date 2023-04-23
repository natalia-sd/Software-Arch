// #ifndef WALLHANDLER_H
// #define WALLHANDLER_H

// #include "Poco/Net/HTTPServer.h"
// #include "Poco/Net/HTTPRequestHandler.h"
// #include "Poco/Net/HTTPRequestHandlerFactory.h"
// #include "Poco/Net/HTTPServerParams.h"
// #include "Poco/Net/HTTPServerRequest.h"
// #include "Poco/Net/HTTPServerResponse.h"
// #include "Poco/Net/HTTPServerParams.h"
// #include "Poco/Net/HTMLForm.h"
// #include "Poco/Net/ServerSocket.h"
// #include "Poco/Timestamp.h"
// #include "Poco/DateTimeFormatter.h"
// #include "Poco/DateTimeFormat.h"
// #include "Poco/Exception.h"
// #include "Poco/ThreadPool.h"
// #include "Poco/Util/ServerApplication.h"
// #include "Poco/Util/Option.h"
// #include "Poco/Util/OptionSet.h"
// #include "Poco/Util/HelpFormatter.h"

// #include <Poco/URIStreamFactory.h>
// #include <Poco/URIStreamOpener.h>
// #include <Poco/Net/HTTPSStreamFactory.h>
// #include <Poco/Net/HTTPStreamFactory.h>
// #include <Poco/Base64Encoder.h>
// #include <Poco/Base64Decoder.h>

// #include "Poco/URI.h"
// #include "Poco/Net/HTTPSClientSession.h"

// #include <iostream>
// #include <iostream>
// #include <fstream>

// using Poco::DateTimeFormat;
// using Poco::DateTimeFormatter;
// using Poco::ThreadPool;
// using Poco::Timestamp;
// using Poco::Net::HTMLForm;
// using Poco::Net::HTTPRequestHandler;
// using Poco::Net::HTTPRequestHandlerFactory;
// using Poco::Net::HTTPServer;
// using Poco::Net::HTTPServerParams;
// using Poco::Net::HTTPServerRequest;
// using Poco::Net::HTTPServerResponse;
// using Poco::Net::NameValueCollection;
// using Poco::Net::ServerSocket;
// using Poco::Util::Application;
// using Poco::Util::HelpFormatter;
// using Poco::Util::Option;
// using Poco::Util::OptionCallback;
// using Poco::Util::OptionSet;
// using Poco::Util::ServerApplication;

// #include "../../database/wall.h"
// #include "../../../user_server/database/user.h"
// #include "../../helper.h"

// static bool hasSubstr(const std::string &str, const std::string &substr)
// {
//     if (str.size() < substr.size())
//         return false;
//     for (size_t i = 0; i <= str.size() - substr.size(); ++i)
//     {
//         bool ok{true};
//         for (size_t j = 0; ok && (j < substr.size()); ++j)
//             ok = (str[i + j] == substr[j]);
//         if (ok)
//             return true;
//     }
//     return false;
// }

// class WallHandler : public HTTPRequestHandler
// {
// private:

// public:
//     WallHandler(const std::string &format) : _format(format)
//     {
//     }



//     void handleRequest(HTTPServerRequest &request,
//                        HTTPServerResponse &response)
//     {
//         HTMLForm form(request, request.stream());
        
//         long cur_user_id = TryAuth(request, response);

//         if(cur_user_id == 0){

//             return;
//         }

//         try
//         {

//             if (hasSubstr(request.getURI(), "/show") && (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET))
//             {
//                 long user_id = cur_user_id;

//                 auto results = database::Wall::read_posts_by_user(user_id);
//                 Poco::JSON::Array arr;
//                 for (auto s : results)
//                     arr.add(s.toJSON());
//                 response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
//                 response.setChunkedTransferEncoding(true);
//                 response.setContentType("application/json");
//                 std::ostream &ostr = response.send();
//                 Poco::JSON::Stringifier::stringify(arr, ostr);

//                 return;
//             } 
//             else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
//             {
//                 long user_id = cur_user_id;
                
//                 if (form.has("post_title")&& form.has("post_text"))
//                 {
//                     database::Wall wall;
//                     wall.post_title() = form.get("post_title");
//                     wall.post_text() = form.get("post_text");                    
//                     std::string reason;

                    
//                     wall.create_post_to_mysql(user_id);
//                     response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
//                     response.setChunkedTransferEncoding(true);
//                     response.setContentType("application/json");
//                     std::ostream &ostr = response.send();
//                     ostr << wall.get_post_id();
//                     return;
//                 }
//             }
            
//         }
//         catch (...)
//         {
//         }

//         response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
//         response.setChunkedTransferEncoding(true);
//         response.setContentType("application/json");
//         Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
//         root->set("type", "/errors/not_found");
//         root->set("title", "Internal exception");
//         root->set("status", Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
//         root->set("detail", "request not found");
//         root->set("instance", "/wall");
//         std::ostream &ostr = response.send();
//         Poco::JSON::Stringifier::stringify(root, ostr);
//     }

// private:
//     std::string _format;
// };
// #endif


#ifndef WALLHANDLER_H
#define WALLHANDLER_H

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"

#include <Poco/URIStreamFactory.h>
#include <Poco/URIStreamOpener.h>
#include <Poco/Net/HTTPSStreamFactory.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Base64Encoder.h>
#include <Poco/Base64Decoder.h>

#include "Poco/URI.h"
#include "Poco/Net/HTTPSClientSession.h"

#include <iostream>
#include <iostream>
#include <fstream>


using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::ThreadPool;
using Poco::Timestamp;
using Poco::Net::HTMLForm;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::NameValueCollection;
using Poco::Net::ServerSocket;
using Poco::Util::Application;
using Poco::Util::HelpFormatter;
using Poco::Util::Option;
using Poco::Util::OptionCallback;
using Poco::Util::OptionSet;
using Poco::Util::ServerApplication;

#include "../../database/wall.h"
#include "../../../messenger_server/database/messenger.h"
#include "../../../user_server/database/user.h"
#include "../../../helper.h"


class WallHandler : public HTTPRequestHandler
{
private:


public:
    WallHandler(const std::string &format) : _format(format)
    {
    }

    void handleRequest(HTTPServerRequest &request,
                       HTTPServerResponse &response)
    {
        HTMLForm form(request, request.stream());

        try
        {
            std::cout << "try started \n";
            if ((request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET))
            { 
                std::cout << "search started \n";
                long user_id = atol(form.get("user_id").c_str());

                auto results = database::Wall::read_by_user_id(user_id);
                Poco::JSON::Array arr;
                for (auto s : results)
                    arr.add(s.toJSON());
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                response.setChunkedTransferEncoding(true);
                response.setContentType("application/json");
                std::ostream &ostr = response.send();
                Poco::JSON::Stringifier::stringify(arr, ostr);
            }

            else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
            {
                if (form.has("user_id") && form.has("post_title")&& form.has("post_text"))
                {
                    database::Wall wall;
                    wall.post_title() = form.get("post_title");
                    wall.post_text() = form.get("post_text");
                    wall.user_id() = atol(form.get("user_id").c_str());
                    std::string message;
                    std::string reason;

                    
                    wall.save_to_mysql();
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    response.setChunkedTransferEncoding(true);
                    response.setContentType("application/json");
                    std::ostream &ostr = response.send();
                    ostr << wall.get_post_id();
                    return;
                }
            }
        }
        catch (...)
        {
        }

        response.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
        root->set("type", "/errors/not_found");
        root->set("title", "Internal exception");
        root->set("status", Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
        root->set("detail", "request not found");
        root->set("instance", "/wall");
        std::ostream &ostr = response.send();
        Poco::JSON::Stringifier::stringify(root, ostr);
    }

private:
    std::string _format;
};
#endif