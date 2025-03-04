/* 

Projeto 5 - Implementando um Sistema de Busca em C++

Este sistema implementa a busca a através do algoritmo Binary Search Tree (usado em muitos modelos de Machine Learning)

Para usar o sistema:

1- No terminal, compile o programa usando seu compilador, por exemplo: g++ -o projeto5  projeto5.cpp

2- Execute o programa com o comando: ./projeto5

3- Escolha o primeiro item do menu para carregar o arquivo

4- Execute a busca selecionando a opção do menu.

5- Altere o programa e experimente outras opções

*/

// Includes
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Estrutura para a busca binária
// Cada elemento será um node dentro da árvore de busca, que será percorrida da esquerda para a direita na lista de elementos do conjunto de dados
struct node {
    node * left;
    node * right;
    int value;
};

// Inicializamos os atributos e definimos os métodos
node * initialize(node * head, int arrayValue);
void print(node * head, int space);
node * search(node * head, int serachValue, bool & in);
node * deleteNode(node * head, int deleteValue);
node * minValueNode(node * head);

// Função main
int main () {
    
    // Cria um objeto para um elmento
    node * head = new node;
    
    // Inicializa as variáveis
    int space = 0;
    char * input = new char[999];
    int * array = new int[999];
    bool running = true;
    
    // Loop
    while (running) {
        
        cout << "\nEscolha Uma Opção do Menu (Digite a Letra em Maiúsculo):" << endl;
        
        cout << "(C)arregar, (I)mprimir, (D)eletar, (B)uscar, (E)ncerrar" << endl;
        
        cin >> input;
        
        if (strcmp("C", input) == 0) {
            
            cout << "(T)erminal, (A)rquivo" << endl;
            
            cin >> input;
            
            if(strcmp("T", input) == 0) {
                
                int arrayIndex = 0;
                
                cout << "Digite números separados com espaço, por exemplo: 1 2 3 4 5" << endl;
                
                char * numInput = new char[999];
                
                cin.ignore(999,'\n');
                
                cin.getline(numInput, 999);
                
                char * token = strtok(numInput, " ");
                
                while(token != NULL) {
                    array[arrayIndex] = atoi(token);
                    token = strtok(NULL, " ");
                    arrayIndex++;
                }
                for(int i = 0; i < arrayIndex + 1; i++) {
                    if(array[i] != 0) {
                        initialize(head, array[i]);
                    }
                    array[i] = 0;
                }
            }
            
            if(strcmp("A", input) == 0) {
                
                int arrayIndex = 0;
                
                cout << "Digite o nome do arquivo:" << endl;
                
                cin >> input;
                
                int num = 0;
                
                ifstream numFile (input);
                
                while(numFile >> num) {
                    initialize(head, num);
                }
                cout << "Arquivo carregado na memória!" << endl;
            }
        }
        
        else if(strcmp("D", input) == 0) {
            
            cout << "Digite o valor que você deseja deletar:" << endl;
            
            int deleteValue; 
            
            cin >> deleteValue;
            
            deleteNode(head, deleteValue);
        }
         else if(strcmp("I", input) == 0) {
            print(head, space);
        }
        
        else if(strcmp("B", input) == 0) {
            
            cout << "Digite o valor que você deseja buscar:" << endl;
            
            int searchValue;
            
            cin >> searchValue;
            
            bool in = false;
            
            search(head, searchValue, in);
            
            if(in) {
                cout << "SUCESSO! O valor foi encontrado no conjunto de dados!" << endl;
            }
            else {
                cout << "O valor não foi encontrado no conjunto de dados!" << endl;
            }
        }
        else if(strcmp("E", input) == 0) {
            running = false;
        }
    } 

    return 0;
}

// Função para carregar o conjunto de dados
node * initialize(node * head, int arrayValue) {
    
    if(head -> value == 0) {
        head -> value = arrayValue;
        return head;
    }
    
    node * temp = new node;
    
    temp -> value = arrayValue;
    
    if(arrayValue > head -> value && head -> right != NULL) {
        head -> right = initialize(head -> right, arrayValue);
    }
    else if(arrayValue <= head -> value && head -> left != NULL){
        head -> left = initialize(head -> left, arrayValue);
    }
    else if(arrayValue > head -> value) {
        head -> right = temp;
    }
    else if(arrayValue <= head -> value) {
        head -> left = temp;
    }
    
    return head;
}

// Função para imprimir o conteúdo do conjunto de dados
void print(node * head, int space) {
    
    if(head == NULL) {
        return;
    }
    
    space += 10;
    
    print(head -> right, space);
    
    cout << " " << endl;
    
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    
    cout << head -> value << endl;
    
    print(head -> left, space);

}

// Função para buscar um elemento no conjunto de dados
node * search(node * head, int searchValue, bool & in) {
    
    if(head == NULL) {
        return head;
    }
    
    if(searchValue > head -> value) {
        head -> right = search(head -> right, searchValue, in);
    }
    else if(searchValue < head -> value) {
        head -> left  = search(head -> left, searchValue, in);
    }
    else if(searchValue == head -> value) {
        in = true;
        return head;
    }
    
    return head;
}

// Função para deletar um elemento do conjunto de dados
node * deleteNode(node * head, int deleteValue) {
    
    if(head == NULL) {
        return head;
    }
    
    if(deleteValue > head -> value) {
        head -> right = deleteNode(head -> right, deleteValue);
    }
    else if(deleteValue < head -> value) {
        head -> left  = deleteNode(head -> left, deleteValue);
    }
    else {
        if(head -> left == NULL) {
            node * temp = head -> right;
            delete head;
            return temp;
        }
        else if(head -> right == NULL) {
            node * temp = head -> left;
            delete head;
            return temp;
        }
        node * temp = minValueNode(head -> right);
        head -> value = temp -> value;
        head -> right = deleteNode(head -> right, temp -> value);
    }
    
    return head;
}

// Função auxiliar para buscar o menor valor no conjunto de dados
node * minValueNode(node * head) {
    
    node * current = head;
    
    while(current != NULL && current -> left != NULL) {
        current = current -> left;
    }
    
    return current;
}

