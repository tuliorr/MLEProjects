/* 

Solução do Exercício do Capítulo 8

Código do Programa

*/

#include <iostream>
#include "Livro.h"
using namespace std;
 

Livro::Livro(string nome, Autor autor, double valor, int quantidadeEstoque): nome(nome), autor(autor) {  

   setValor(valor);
   setquantidadeEstoque(quantidadeEstoque);
}
 
string Livro::getNome()  {
   return nome;
}
 
Autor Livro::getAutor()  {
   return autor;
}
 
double Livro::getValor()  {
   return valor;
}
 
void Livro::setValor(double valor) {
   if (valor > 0) {
      this -> valor = valor;
   } else {
      cout << "O valor não pode ser negativo! Colocando 0." << endl;
      this -> valor = 0;
   }
}
 
int Livro::getquantidadeEstoque()  {
   return quantidadeEstoque;
}
 
void Livro::setquantidadeEstoque(int quantidadeEstoque) {
   if (quantidadeEstoque >= 0) {
      this -> quantidadeEstoque = quantidadeEstoque;
   } else {
      cout << "A quantidade não pode ser negativa! Colocando 0." << endl;
      this -> quantidadeEstoque = 0;
   }
}
 
void Livro::print()  {
   cout << "'" << nome << "' por ";
   autor.print();
}
 
string Livro::getAutorNome()  {
   return autor.getNome();  
}
