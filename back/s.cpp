#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>

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

void server::read_sock(){
    char command[1024]{}; //create buffer for command

    if (read( serv_sock,command,1024 )) {
      perror("ERROR reading from socket");
      exit(1);
   }

    if(command[0] == 'e'){
        
    }
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
}

int main(){
    server s;
    s.start();
}