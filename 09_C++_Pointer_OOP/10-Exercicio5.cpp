#include <iostream>
using namespace std;

int contaOcorrencias(const int arr1[10], int numero){

 int cont = 0;
   
   for (int u = 0; u < 10; u++){

    if (arr1[u] == numero)
     cont = cont + 1;
   }
   
 return cont;
 }

int main(){   

    int arr[10];
    int num;

    cout << "Digite 10 valores para o array: \n";

    for(int i = 0; i < 10; i++)
      cin >> arr[i];

    cout << "Valores no array:";

    for(int i = 0; i < 10; i++)
      cout << " " << arr[i];

    cout << "\n" << "Digite o valor que deseja pesquisar: ";
    cin >> num;

	  cout << "O valor " << num << " foi encontrado esse número de vezes: " << contaOcorrencias(arr, num);
    cout << "\n";

	return 0;
}