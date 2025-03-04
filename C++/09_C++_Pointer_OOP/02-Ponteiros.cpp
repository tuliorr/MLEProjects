#include <iostream>
using namespace std;
 
int main()
{
    // Declara a variável num
    int num = 10;

    // Inicializa ptr com o endereço da variável num
    // Esta variável aponta para um endereço de memória que armazena valor inteiro
    int *ptr = &num; 

    // Imprime o valor da variável num
    cout << num << "\n";
 
    // Imprime o endereço da variável num
    cout << &num << "\n";

    // Imprime o valor da variável ptr (que é o endereço da variável num)
    cout << ptr << "\n"; 
 
    return 0;
}