/*

C++ não permite passar um array inteiro como um argumento para uma função. No entanto, você pode passar um ponteiro 
para um array especificando o nome do array sem um índice.

*/

#include <iostream>
using namespace std;
 
void imprimeArray1(int *array, int size)
{
    // Imprime os valores do array
    cout << "Os valores no array são: ";
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }

    cout << "\n";
}

void imprimeArray2(int array[], int size)
{
    // Imprime os valores do array
    cout << "Os valores no array são: ";
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    
    cout << "\n";
}

void imprimeArray3(int array[5], int size)
{
    // Imprime os valores do array
    cout << "Os valores no array são: ";
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    
    cout << "\n";
}
 
int main()
{
    // Declara o array
    int lista[] = { 1, 2, 3, 4, 5 };
    int size = 5;

    cout << "\n";

    // Chama a função e passa o array como argumento
    imprimeArray1(lista, size); 
    imprimeArray2(lista, size); 
    imprimeArray3(lista, size); 
 
     return 0;
}