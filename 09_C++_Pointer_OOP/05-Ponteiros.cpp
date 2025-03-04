#include <iostream>
using namespace std;
 
int main () 
{

   int  num;
   int  *ptr;
   int  **pptr;

   num = 100;

   // Endereço da variável num
   ptr = &num;

   // Obtém o endereço de ptr usando o endereço com o operador &
   pptr = &ptr;

   // Print
   cout << "Valor de num: " << num << endl;
   cout << "Endereço de num: " << &num << endl;
   cout << "Endereço armazenado em ptr: " << ptr << endl;
   cout << "Valor para o qual *ptr aponta: " << *ptr << endl;
   cout << "Endereço de pptr: " << pptr << endl;
   cout << "Valor para o qual **pptr aponta: " << **pptr << endl;

   return 0;
}
