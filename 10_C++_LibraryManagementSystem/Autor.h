/* 

Solução do Exercício do Capítulo 8

Biblioteca da Classe Autor 

*/
 
#include <string>
using namespace std;
 
class Autor {

private:
   string nome;
   string email;
   char genero; 
 
public:

   // Construtor
   Autor(string nome, string email, char genero);
   
   // Métodos
   string getNome() const;
   string getEmail() const;
   void setEmail(string email);
   char getGenero() const;
   void print() const;
};
