#include <iostream>
using namespace std;
 
int main()
{
    cout << "\n";

    // Declara um array de inteiros
    int array[5] = { 9, 7, 5, 3, 1 };

    cout << "\n";

    // Imprime o array. ATENÇÃO!
    cout << "Conteúdo do array: " << array << "\n"; 

    cout << "\n";

    // Imprime cada elemento do array
    cout << "Os valores no array são: ";
    for(int i = 0; i < 5; i++) {
        cout << array[i] << " ";
    }

    cout << "\n";

    // Imprime o primeiro e terceiro elemento do array. ATENÇÃO!
    cout << "Primeiro elemento do array: " << array[0] << "\n";
    cout << "Terceiro elemento do array: " << array[2] << "\n";

    cout << "\n";

    // Imprime o endereço do array. ATENÇÃO!
    cout << "Endereço do array: " << &array << "\n"; 

    cout << "\n";
 
    // Imprime o endereço do primeiro e terceiro elemento do array. ATENÇÃO!
    cout << "Endereço do primeiro elemento do array: " << &array[0] << "\n";
    cout << "Endereço do terceiro elemento do array: " << &array[2] << "\n";

    cout << "\n";

    // Declara a variável do tipo ponteiro e inicializa com o array (não com o endereço). ATENÇÃO!
    int *ptr = array;

    cout << "\n";

    // Imprime o valor da variável ponteiro. ATENÇÃO!
    cout << "Valor do ponteiro: " << ptr << "\n"; 

    cout << "\n";
    
    // Imprime o valor para o qual o ponteiro aponta. ATENÇÃO!
    cout << "Valor para o qual o ponteiro aponta: " << *ptr << "\n"; 

    cout << "\n";

    // Imprime cada valor doo array para o qual o ponteiro aponta. ATENÇÃO!
    cout << "Os valores no array são: ";
    for(int i = 0; i < 5; i++) {
        cout << *ptr << " ";
        ptr++;
    }

    cout << "\n";
    cout << "\n";
 
    return 0;
}