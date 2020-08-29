#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include<string.h>

#include "s.hpp"

void server::init_sock(){
    sockaddr_in serv_addr;

    serv_sock = socket(AF_INET, SOCK_STREAM, 0); //create socket

    if (serv_sock < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   bzero(reinterpret_cast<char*>(&serv_addr), sizeof(serv_addr)); //clear memory

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port);

   if (bind(serv_sock,reinterpret_cast<sockaddr*>(&serv_addr) , sizeof(serv_addr)) < 0) { //bind socket
      perror("ERROR on binding");
      exit(1);
   }
}

std::string server::exec_command(std::string && command){
    command[0] = '.'; //create correct command to run 
    command[1] = '/'; //script from local directory with "./" at the start
    FILE* pipe = popen(command.c_str(),"r");
    if (!pipe) return "ERROR";
        char buffer[128];
        std::string result;
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
        }
    pclose(pipe);
    return std::move(result);
}


void server::read_sock(){
    char command[1024]{}; //create buffer for command

    if(read(client_sock,command,1024 ) < 0) {
      perror("ERROR reading from socket");
      exit(1);
    }
    std::string result;
    if(command[0] == 'e'){
        result = exec_command(command);
    }
    if (write( client_sock,result.c_str(),result.length()) < 0) {
      perror("ERROR reading from socket");
      exit(1);
    }

    close(client_sock);
}


void server::wait_sock(){
    sockaddr_in cli_addr;
    listen(serv_sock,1000); //listen server socket with max queue 1000

    client_size = sizeof(cli_addr);

    client_sock = accept(serv_sock, reinterpret_cast<sockaddr*>(&cli_addr), reinterpret_cast<socklen_t*>(&client_size));
    
    if (client_sock < 0) {
      perror("ERROR on accept");
      exit(1);
   }

   read_sock();
}

void server::start(){
     init_sock();
     while(true)
         wait_sock();
}

int main(){
    server s;
    s.start();
}