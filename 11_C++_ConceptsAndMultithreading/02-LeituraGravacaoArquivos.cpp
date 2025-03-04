/*

Leitura e Gravação de Arquivos em C++

Em qualquer programa de computador pode ser necessário a manipulação de arquivos para leitura e gravação.

C++ oferece uma biblioteca para esse fim, a fstream.

Referência: http://www.cplusplus.com/reference/fstream/fstream/

Neste script vamos realizar as seguintes tarefas:

1- Criar um novo arquivo e abrir em modo de gravação
2- Gravar uma frase nesse arquivo
3- Fechar o arquivo
4- Abrir o arquivo em modo de leitura
5- Fazer a leitura do arquivo linha a linha
6- Imprimir o conteúdo do arquivo no termninal
7- Fechar o arquivo

*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
  
  // 1- Criar um novo arquivo e abrir em modo de gravação
  ofstream meuArquivo("teste.txt");

  // 2- Gravar uma frase nesse arquivo
  meuArquivo << "Teste de gravação e leitura de arquivos em C++!";

  // 3- Fechar o arquivo
  meuArquivo.close();

  // 4- Abrir o arquivo em modo de leitura
  ifstream meuArquivoLeitura("teste.txt");

  // Criar uma variável do tipo string para receber o texto do arquivo
  string meuTexto;

  // 5- Fazer a leitura do arquivo linha a linha
  while (getline (meuArquivoLeitura, meuTexto)) {
    
    // 6- Imprimir o conteúdo do arquivo no termninal
    cout << meuTexto << endl;
  }

  // 7- Fechar o arquivo
  meuArquivoLeitura.close();

}
