/*

POO - Parte 4 (Construtor e Polimorfismo)

A palavra polimorfismo significa ter muitas formas. Normalmente, o polimorfismo ocorre quando há uma hierarquia de classes e 
elas estão relacionadas por herança.

O polimorfismo C++ significa que uma chamada a uma função de membro fará com que uma função diferente seja executada, dependendo 
do tipo de objeto que invoca a função.

Considere o exemplo a seguir, onde uma classe base foi derivada por outras duas classes.

*/

#include <iostream> 
using namespace std;
 
// Classe Base
class Formato {

   protected:
      int largura, altura;
      
   public:

      // Um construtor em C ++ é um método especial que é chamado automaticamente quando um objeto de uma classe é criado.
      // Para criar um construtor, usamos o mesmo nome da classe, seguido por parênteses ():
      Formato(int a = 0, int b = 0){
         largura = a;
         altura = b;
      }
};

// Classe Derivada
class Retangulo: public Formato {

   public:

      // Um construtor em C ++ é um método especial que é chamado automaticamente quando um objeto de uma classe é criado.
      // Para criar um construtor, usamos o mesmo nome da classe, seguido por parênteses ():
      Retangulo(int a = 0, int b = 0):Formato(a, b) { }
      
      // Método de cálculo da área
      int area() { 
         cout << "Área do Retangulo: " << (largura * altura) << endl;
         return 0; 
      }
};

// Classe Derivada
class Triangulo: public Formato {

   public:

      // Um construtor em C ++ é um método especial que é chamado automaticamente quando um objeto de uma classe é criado.
      // Para criar um construtor, usamos o mesmo nome da classe, seguido por parênteses ():
      Triangulo(int a = 0, int b = 0):Formato(a, b) { }
      
      // Método de cálculo da área
      int area() { 
         cout << "Área do Triangulo: " << (largura * altura / 2) << endl;
         return 0; 
      }
};

// Main 
int main() {

   // Instâncias da classe
   // O método construtor de cada classe é chamado neste momento
   Retangulo rec(12,5);
   Triangulo tri(14,6);

   // Área do Retangulo
   rec.area();
   
   // Área do Triangulo
   tri.area();
   
   return 0;
}