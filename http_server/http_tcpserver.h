#ifndef INCLUDED_HTTP_TCPSERVER
    #define INCLUDED_HTTP_TCPSERVER

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

namespace http {
    class TCPServer {
        public:
            TCPServer(std::string ip_address, int port);
            ~TCPServer();

            int startServer();
            void closeServer();

        private:
            int m_port;
            int m_socket;
            int m_new_socket;
            long m_incomingMessage;
            struct sockaddr_in m_socketAddress;
            unsigned int m_socketAddress_len;
            std::string m_serverMessage;
    };
}

#endif