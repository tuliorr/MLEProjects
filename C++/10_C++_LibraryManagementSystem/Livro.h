/* 

Solução do Exercício do Capítulo 8

Biblioteca da Classe Livro 

*/

#include <string>
#include "Autor.h"  
using namespace std;
 
class Livro {

private:
   string nome;
   Autor autor; 
   double valor;
   int quantidadeEstoque;
 
public:

   Livro(string nome, Autor autor, double valor, int quantidadeEstoque = 0);
   string getNome() ;
   Autor getAutor() ;  
   double getValor() ;
   void setValor(double valor);
   int getquantidadeEstoque() ;
   void setquantidadeEstoque(int quantidadeEstoque);
   void print() ;
   string getAutorNome() ;
};
 