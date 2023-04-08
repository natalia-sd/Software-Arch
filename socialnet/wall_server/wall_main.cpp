#include <optional>
#include "web_server/http_wall_server.h"

int main(int argc, char*argv[]) 
{
    HTTPWallServer app;
    return app.run(argc, argv);
}