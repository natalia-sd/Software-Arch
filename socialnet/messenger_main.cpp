#include <optional>
#include "messenger_server/http_messenger_server.h"

int main(int argc, char*argv[]) 
{
    HTTPMessengerServer app;
    return app.run(argc, argv);
}