/*

Dada a string "A string". Crie um programa C++ para imprimir em uma linha a letra do índice 0, a letra na 
primeira posição do ponteiro e a letra t. Então mova o ponteiro para a posição +2. Então, em outra linha imprima a 
letra na posição do ponteiro e as letras r e g da string (usando o ponteiro).

*/

#include <iostream>
using namespace std;

int main(void) {

   char str[] = "A string.";
   char *pc = str;

   // A A t
   cout << str[0] << ' ' << *pc << ' ' << pc[3] << "\n";
   pc += 2;

   // s r g
   cout << *pc << ' ' << pc[2] << ' ' << pc[5];
   cout << "\n";

   return 0;
}