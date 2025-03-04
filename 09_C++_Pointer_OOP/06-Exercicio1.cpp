#include <iostream>
using namespace std;

int main(){

   int a;
   
   cout << "Digite um Número:";
   cin >> a;

   int *b = &a;

    cout << "O valor do ponteiro é " << *b << " neste endereço de memória: " <<  b;
    cout << "\n";

    return 0;
}