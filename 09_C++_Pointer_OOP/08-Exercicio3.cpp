#include<iostream>
using namespace std;

int main(){

  int n;
  int i; 
  int max  = 0;

  cout << "Digite o Tamanho do Array:";
  cin >> n;

  cout << "Digite os Valores Para o Array:\n";

  int arr[n];
  
  // Loop para gravar as entradas do usuário no array
  for(i = 0; i < n; i++) {

   cin >> arr[i];
  }

  // Loop para buscar o maior valor
  for(int u = 0; u <= n; u++){
   if (arr[u] > max)
     max = arr[u];
  }

  // Atribui um ponteiro apontando para o maior valor
  int *pointer = &max;

  cout << "Este é o maior valor do aray: " << *pointer;

  cout << "\n";
  return 0;
}