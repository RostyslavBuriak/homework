#ifndef SERVER_CPP
#define SERVER_CPP

#include <string>

class server{
    public:
        server():serv_sock(0),client_sock(0),client_size(0){};
        server(const server&) = delete;
        server(server&& ) = delete;

        server& operator=(const server&) = delete;
        server& operator=(server&&) = delete;

        ~server(){close(serv_sock);close(client_sock);}

        void start();
    private:
        void init_sock(); //initializes a socket
        void wait_sock(); // listen socket and accepts connection
        void read_sock(); //reads data from socket

        const short port = 4444;
        int serv_sock,client_sock,client_size;

        std::string exec_command(std::string&&); //executes cmd command
};
#endif