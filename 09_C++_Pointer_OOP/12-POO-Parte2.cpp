/*

POO - Parte 2 (Herança)

*/
 
#include <iostream>
using namespace std;

// Classe Base
class Formato {

   public:

      void setLargura(int l) {
         largura = l;
      }
      
      void setAltura(int a) {
         altura = a;
      }
      
   protected:

      int largura;
      int altura;
};

// Classe Derivada
class Retangulo: public Formato {

   public:

      int getArea() { 
         return (largura * altura); 
      }
};

int main(void) {

    // Instância da classe
    Retangulo Ret1;
 
    // Métodos da classe
    Ret1.setLargura(4);
    Ret1.setAltura(7);

    // Imprime a area
    cout << "Área do Retângulo: " << Ret1.getArea() << endl;

    return 0;
}
