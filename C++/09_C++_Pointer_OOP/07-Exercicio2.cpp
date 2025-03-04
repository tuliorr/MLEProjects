#include <iostream>
using namespace std;

int main(){

   int  a; int b;
   
   cout << "Digite o valor de A: ";
   cin >> a;

   cout << "Digite o valor de B: ";
   cin >> b;

   int *ptrA = &a;
   int *ptrB = &b;

   cout << "O Valor do ponteiro ptrA é " << *ptrA << " armazenado no endereço " << ptrA <<"\n";
    
   cout << "O Valor do ponteiro ptrB é " << *ptrB << " armazenado no endereço " << ptrB <<"\n";

   return 0;
}
