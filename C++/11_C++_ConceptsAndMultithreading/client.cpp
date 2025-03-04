/*

Executando Thread em C++

Este programa é para o lado cliente (que inicia a conexão) via socket de rede.

*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 3000
   
// Função main
int main(int argc, char const *argv[])
{
    // Variáveis
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Cliente Estabelecendo Conexão com o Servidor.";
    char buffer[1024] = {0};
    
    // Testa conexão via Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Erro na criação do Socket \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Converte endereço ipv4 ou ipv6 de texto para formato binário
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nEndereço inválido ou não suportado \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConexão falhou \n");
        return -1;
    }
    
    // Envia o pedido de conexão
    send(sock , hello , strlen(hello) , 0 );

    // Print
    printf("Pedido de Conexão Enviado ao Servidor.\n");

    // Recebe a resposta
    valread = read( sock , buffer, 1024);

    // Print
    printf("%s\n", buffer );
    
    return 0;
}
