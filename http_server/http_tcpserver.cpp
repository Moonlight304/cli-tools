#include <http_tcpserver.h>

#include <iostream>
#include <sstream>
#include <unistd.h>

namespace {
    void log(const std::string &message) {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &errorMessage) {
        log("Error: " + errorMessage);
        exit(1);
    }
}

namespace http
{
    TCPServer::TCPServer(std::string ip_address, int port) 
        : m_ip_address(ip_address), m_port(port), m_socket(),
            m_new_socket(), m_incomingMessage(), m_socketAddress(),
            m_socketAddress_len(sizeof(m_socketAddress)),
            m_serverMessage(buildResponse())
    {
    }

    TCPServer::~TCPServer()
    {
        closeServer();
    }

    int TCPServer::startServer() {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0) {
            exitWithError("Cannot create socket");
            return 1;
        }

        return 0;
    }

    void TCPServer::closeServer() {
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }
}

