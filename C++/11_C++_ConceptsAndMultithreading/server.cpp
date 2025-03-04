/*

Executando Thread em C++

Este programa é para o lado servidor (que recebe a conexão) via socket de rede.

*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 3000

// Função main
int main(int argc, char const *argv[])
{
    // Variáveis de trabalho
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char* hello = "Conexão Recebida no Lado Servidor.";
       
    // Criando o descritor do socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket falhou");
        exit(EXIT_FAILURE);
    }
       
    // Associando o socket a porta 3000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Associando o socket a porta 3000
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind falhou");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    // Lendo o socket
    valread = read( new_socket , buffer, 1024);

    // Print
    printf("%s\n",buffer );

    // Envia resposta a conexão do socket
    send(new_socket , hello , strlen(hello) , 0 );

    // Print
    printf("Resposta Enviada ao Cliente. Encerrando a Conexão.\n");
    
    return 0;
}