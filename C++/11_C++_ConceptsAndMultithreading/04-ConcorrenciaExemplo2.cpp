
/*

Executando Thread em C++

Neste script vamos enviar uma função contendo um loop, para ser executada em uma thread que criaremos, enquanto outro 
loop será executado pela thread principal.

*/

#include <iostream>
#include <thread>
using namespace std;

// Função para imprimir números no terminal
// Isso será executado em background através de uma thread que nós criaremos
void imprime_numeros_background() 
{
    // Declara variável para usar como contador e inicializa com zero
    int contador1(0);

    // O código abaixo cria um loop que será executado em uma thread criada por nós
    while (true) {
        cout << "Executado pela nossa thread: " << contador1++ << endl;

        if (contador1 > 50000) {
            break;
        }
    }
}

// Função main
int main()
{
    // Cria a thread e submete a função
    thread background(imprime_numeros_background);

    // Declara variável para usar como contador e inicializa com zero
    int contador2(0);
    
    // O código abaixo cria um loop que será executado na thread principal criada pelo nosso programa C++
    while (true) {
        cout << "Executado pela thread principal: " << contador2++ << endl;

        if (contador2 > 50000) {
            break;
        }
    }
}
 