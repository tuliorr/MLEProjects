/*

POO - Parte 6 (Encapsulamento)

O significado de Encapsulamento é garantir que dados "confidenciais" sejam ocultados dos usuários. 

Para conseguir isso, você deve declarar variáveis / atributos de classe como privados (não podem ser acessados de fora da classe). 

Se quiser que outras pessoas leiam ou modifiquem o valor de um membro privado, você pode fornecer os métodos get e set públicos.

É considerada uma boa prática declarar seus atributos de classe como privados (sempre que possível). 

O encapsulamento garante melhor controle de seus dados, porque você (ou outra pessoa) pode alterar uma parte do código sem afetar outras partes.

*/

#include <iostream>
using namespace std;

class Funcionario {

  private:
    // Atributo privado
    int salario;

  public:
    
    // Setter
    void setSalario(int s) {
      salario = s;
    }
    
    // Getter
    int getSalario() {
      return salario;
    }
};

int main() {
  
  Funcionario bob;
  
  bob.setSalario(12000);
  
  cout << bob.getSalario() << endl;
  
  return 0;
}