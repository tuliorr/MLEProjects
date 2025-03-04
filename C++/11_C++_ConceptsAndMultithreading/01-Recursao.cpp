/* 

Recursão

Em ciência da computação, recursão é a definição de uma sub-rotina (função ou método) que pode invocar a si mesma. 

Um exemplo de aplicação da recursividade pode ser encontrado nos analisadores sintáticos recursivos para linguagens de programação e em
algoritmos de Machine Learning. 

A grande vantagem da recursão está na possibilidade de usar um programa de computador finito para definir, analisar ou produzir um estoque 
potencialmente infinito de sentenças, designs ou outros dados.

Um exemplo de recursão é o cálculo do fatorial de um número.

Calcular o fatorial de um número só faz sentido quando estamos trabalhando com números naturais. 

Essa operação é bastante comum na análise combinatória, facilitando o cálculo de arranjos, permutações, combinações e demais 
problemas envolvendo contagem. 

O fatorial é representado pelo símbolo “!”. Definimos como n! (n fatorial) a multiplicação de n por todos os seus antecessores 
até chegar em 1. 

n! = n · (n – 1)· (n – 2) · … · 3 · 2 · 1

Cálculo do fatorial

Para encontrar o fatorial de um número, basta calcular o produto. Note também que o fatorial é uma operação que, ao aumentar o valor de n, 
o resultado também aumentará muito.

Exemplos:

4! = 4 · 3 · 2 · 1 = 24
5! = 5 · 4 · 3 · 2 · 1 = 120
6! = 6 · 5 · 4 · 3 · 2 · 1 = 720
7! = 7· 6 · 5 · 4 · 3 · 2 · 1 = 5040

Por definição, temos:

0! = 1
1! = 1

*/

#include <iostream>
using namespace std;

int fatorial(int n) {

    if (n > 1) 
    {    
        return n * fatorial(n - 1);
    } 
    else 
    {
        return 1;
    }

}

int main() {

    int n, resultado;

    cout << "Digite um número não-negativo: ";
    cin >> n;

    resultado = fatorial(n);

    cout << "Fatorial de " << n << " = " << resultado << endl;

    return 0;
}
