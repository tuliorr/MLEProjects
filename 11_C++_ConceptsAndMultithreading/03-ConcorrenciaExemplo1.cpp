/*

Executando Thread em C++

Quando o programa C++ é iniciado, ou seja, a função main() inicia sua execução, você pode criar e lançar novas threads 
que serão executadas simultaneamente a thread principal. Para iniciar uma thread em C++, você deve declarar um objeto thread 
e passar a função que deseja executar simultaneamente para a thread principal. 

O código a seguir demonstra a declaração e o início de uma thread definido em #include <thread>

*/

#include <iostream>
#include <thread>
using namespace std;

// Função que imprime mensagem no termninal
void func() {
  cout << "Testando Concorrência com Thread em C++" << endl;
}

// Função main
int main() {

    // Aqui declaramos uma thread para executar a função criada acima 
    thread teste_thread(func);

    // Executamos a thread e agurdamos sua execução com o método join
    teste_thread.join();

}
