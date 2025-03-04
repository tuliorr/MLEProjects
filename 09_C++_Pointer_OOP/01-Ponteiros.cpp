#include <iostream>
 
int main()
{
    int x = 5;

    // Imprime o valor da variável x
    std::cout << x << "\n"; 

    // Imprime o endereço de memória do valor da variável x
    std::cout << &x << "\n"; 

    // Imprime o valor no endereço de memória da variavel x
    // Os parenteses não são necessários, mas ajudam na legibilidade do código abaixo
    std::cout << *(&x) << "\n"; 
 
    return 0;
}
