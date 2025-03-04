/*

POO - Parte 1 (Introdução)

*/
 
#include <iostream>
using namespace std;

class Caixa {
   public:
      double largura;   
      double altura; 
      double profundidade;    
};

int main() {

   Caixa Box1;        
   Caixa Box2;    
       
   double volume = 0.0;     
 
   // Box 1
   Box1.largura = 4.2; 
   Box1.altura = 5.3; 
   Box1.profundidade = 8.4;

   // Box 2
   Box2.largura = 11.5;
   Box2.altura = 13.9;
   Box2.profundidade = 12.3;
   
   // Calculando o volume da caixa 1
   volume = Box1.largura * Box1.altura * Box1.profundidade;
   cout << "Volume da Box 1 : " << volume << endl;

   // Calculando o volume da caixa 1
   volume = Box2.largura * Box2.altura * Box2.profundidade;
   cout << "Volume da Box 2 : " << volume << endl;

   return 0;
}