#ifndef SERVER_CPP
#define SERVER_CPP
class server{
    public:
        server():serv_sock(0),client_sock(0),client_size(0){};
        server(const server&) = default;
        server(server&& ) = default;

        server& operator=(const server&) = default;
        server& operator=(server&&) = default;

        void start();
    private:
        void init_sock(); //initializes a socket
        void wait_sock(); // listen socket and accepts connection
        void read_sock(); //reads data from socket

        const short port = 8080;
        int serv_sock,client_sock,client_size;

        template<unsigned size>
        void exec_command(char command[size]){ //executes cmd command
            
        }
};
#endif