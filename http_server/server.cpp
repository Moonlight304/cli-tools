#include <http_tcpserver.h>

int main () {
    using namespace http;

    TCPServer server = TCPServer("0.0.0.0", 8080);
    server.startServer();

    return 0;
}