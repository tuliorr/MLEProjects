/*

POO - Parte 5 (Abstração)

A abstração de dados refere-se a fornecer apenas informações essenciais para o mundo exterior e ocultar seus detalhes de fundo, ou seja, 
para representar as informações necessárias no programa sem apresentar os detalhes.

Abstração de dados é uma técnica de programação (e design) que depende da separação de interface e implementação.

Vamos dar um exemplo da vida real de uma TV, que você pode ligar e desligar, mudar de canal, ajustar o volume e adicionar 
componentes externos, como alto-falantes ou DVD players, mas você não conhece seus detalhes internos, que ou seja, você não sabe 
como a TV recebe sinais pelo cabo, como os traduz e, finalmente, os exibe na tela.

Assim, podemos dizer que uma televisão separa claramente sua implementação interna de sua interface externa e você pode brincar com 
suas interfaces como botão liga / desliga, trocador de canal e controle de volume sem ter nenhum conhecimento de seus componentes internos.

Em C++, as classes fornecem um ótimo nível de abstração de dados. Elas fornecem métodos públicos suficientes para o mundo externo brincar 
com a funcionalidade do objeto e manipular os dados do objeto, ou seja, declarar sem realmente saber como a classe foi implementada internamente.

Por exemplo, seu programa pode fazer uma chamada para a função sort() sem saber qual algoritmo a função realmente usa para classificar 
os valores fornecidos. Na verdade, a implementação subjacente da funcionalidade de classificação pode mudar entre as versões da 
biblioteca e, desde que a interface permaneça a mesma, sua chamada de função ainda funcionará.

Em C++, usamos classes para definir nossos próprios tipos de dados abstratos (ADT). Você pode usar o objeto cout da classe ostream para 
transmitir dados para a saída padrão, por exemplo.

*/

#include <iostream>
using namespace std;

class Calculadora {

   public:

      // Construtor
      Calculadora(int i = 0) {
         total = i;
      }
      
      // Interface para o mundo externo
      void addNum(int number) {
         total += number;
      }
      
      // Interface para o mundo externo
      int getTotal() {
         return total;
      };
      
   private:
   
      // Não é visível para o mundo externo
      int total;
};

int main() {

   Calculadora calc1;
   
   calc1.addNum(10);
   calc1.addNum(20);
   calc1.addNum(30);

   cout << "Total: " << calc1.getTotal() << endl;

   return 0;
}