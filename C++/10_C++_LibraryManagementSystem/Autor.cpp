/*

Solução do Exercício do Capítulo 8

Código do Programa

*/

#include <iostream>
#include "Autor.h"
using namespace std;
 
// Construtor
Autor::Autor(string nome, string email, char genero) {
   
   this -> nome = nome;
   
   setEmail(email); 
   
   if (genero == 'm' || genero == 'f') {
      this -> genero = genero;
   } else {
      cout << "Gênero Inválido!" << endl;
   }
}
 
string Autor::getNome() const {
   return nome;
}
 
string Autor::getEmail() const {
   return email;
}
 
void Autor::setEmail(string email) {

   size_t atIndex = email.find('@');
   
   // Verifica a posição do caracter @
   if (atIndex != string::npos && atIndex != 0 && atIndex != email.length()-1) {
      this -> email = email;
   } else {
      cout << "Email Inválido! Colocando NA." << endl;
      this -> email = "NA";
   }
}
 
char Autor::getGenero() const {
   return genero;
}
 
void Autor::print() const {
   cout << nome << " (" << genero << ") e e-mail: " << email << endl;
}
