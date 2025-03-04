/*

Executando Thread em C++

Neste script para criar uma classe, instanciar um objeto e submeter o objeto pra executar em uma thread.

O objeto poderia ser um modelo de Machine Learning.

*/

#include <iostream>
#include <thread>
using namespace std;

// Criamos a classe
class TestaPrograma
{
    public:

    // Construtor
    TestaPrograma() : estado(0) {
        cout << "Objeto executado em uma thread." << endl;
    }

    // Método
    void operator()() {
        estado++;
    }
  
    private:
    int estado;
};

// Bloco main
int main() {

    // Cria um objeto da classe
    TestaPrograma obj1;

    // Cria a thread e submete o objeto
    thread teste_thread(obj1);

    // Aguarda a execução da thread
    teste_thread.join();
} 