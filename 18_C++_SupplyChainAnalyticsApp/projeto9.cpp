// Projeto 9 - Aplicação Analítica de Supply Chain

// Includes
// https://www.cplusplus.com/reference/iomanip/
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h> 
#include <fstream>

using namespace std;

// Constantes
#define LR 0.001
#define EPOCHS 1500
#define PRINT_PADDING 4
#define EPOCH_PRINTS 10

// Classe para cada camada
class Layer; 

// Classe para cada Node
class Node {
    public:
        int idInLayer;
        double value;
        double delta;
        std::vector<double> leftWeights;
        std::vector<double> gradients;

        // Construtor
        Node(int leftUnits, int idInLayer) {

            this -> idInLayer = idInLayer;

            for (int i = 0; i < leftUnits; i++)
                leftWeights.push_back(rand()/(double)RAND_MAX);
            
            gradients.resize(leftUnits, 0);
        }

        // Atualização dos pesos
        void updateWeights() {            
            
            // novo valor de peso = valor anterior do peso - LR * gradient
            for (int i = 0; i < leftWeights.size(); i++)
                leftWeights[i] -= LR * gradients[i];

            // Limpa os gradientes
            std::fill(gradients.begin(), gradients.end(), 0);
        }

        // Imprime os pesos
        void printWeights() {
            for (int i = 0; i < leftWeights.size(); i++)
                std::cout << "Node: " << idInLayer << " " << "Peso "<< i << ": " << leftWeights[i] << std::endl;
        }

        // Métodos implementados sob a declaração de classe de camada
        void predict(Layer leftLayer);
        void predictOutput(Layer leftLayer);
        void calculateGradients(Layer leftLayer, double loss);
        void calculateGradients(Layer leftLayer, Layer rightLayer);
};

// Função softmax para saída da rede
std::vector<double> softmax(std::vector<double> values) {
    std::vector<double> result;
    double denominator = 0;

    for (int i = 0; i < values.size(); i++) 
        denominator += exp(values[i]);

    for (int i = 0; i < values.size(); i++) 
        result.push_back(exp(values[i]) / denominator);

    return result;
}

// Função de ativação sigmóide 
double sigmoid(double innerProduct) {
    return 1 / (1 + exp(-innerProduct));
}

// Derivada da função sigmóide
double sigmoidDerivative(double sigmoid) {
    return sigmoid * (1 - sigmoid);
}

// Função de erro com entropia cruzada, usada para calcular deltas para nodes da camada de saída
double lossDerivativeWRTOutput(std::vector<double> outputValues, 
    std::vector<int> labels, int outputIndex) {
    double sum = 0;
    
    for (int i = 0; i < outputValues.size(); i++) { 

        // cross entropy loss = - Sum_over_i pi * log qi
        // derivative wrt qj onde i = j, (- pj / qj) * qj * (1 - qj) = pj * (qj - 1)
        // derivative wrt qj onde i != j, (- pi / qi) * -qi * qj = pi * qj
        if (i == outputIndex) {
            sum += labels[i] * (outputValues[outputIndex] - 1);
        } else {
            sum += labels[i] * outputValues[outputIndex];
        }
    }
    
    return sum;
}

// Produto entre nodes e pesos
double innerProduct(std::vector<Node> v1, std::vector<double> v2) {
    double sum = 0;

    for (int i = 0; i < v1.size(); i++)
        sum += v1[i].value * v2[i];

    return sum;
}

// Classe para cada camada
class Layer {
    public:
        int layerId;
        bool outputLayer;
        std::vector<Node> nodes;
        std::vector<double> outputValues;

        // Construtor
        Layer(int units, int unitsLeft, bool bias, int layerId) {

            this -> layerId = layerId;
            this -> outputLayer = !bias;

            for (int i = 0; i < units; i++) {
                Node *node = new Node(unitsLeft + 1, i);
                nodes.push_back(*node);           
            }

            // Adiciona o bias
            if (bias) {
                Node *node = new Node(0, units);
                node -> value = 1;
                nodes.push_back(*node);
            }  
        }

        // Método para as previsões do modelo
        void predict(Layer layer) {

            // A previsão é diferente para camadas ocultas vs camada de saída devido a diferentes funções de ativação
            if (!outputLayer) {
                for (int i = 0; i < nodes.size(); i++) 
                    nodes[i].predict(layer); 

            } else {
                // Converte valores em nós da camada de saída para valores softmax
                std::vector<double> outputValues; 

                for (int i = 0; i < nodes.size(); i++) {
                    nodes[i].predictOutput(layer);
                    outputValues.push_back(nodes[i].value);
                }

                outputValues = softmax(outputValues);

                this -> outputValues = outputValues;

                for (int i = 0; i < nodes.size(); i++) 
                    nodes[i].value = outputValues[i];
            }

        }

        // Executa atualização para cada nó na camada de saída
        void calculateGradients(Layer leftLayer, std::vector<int> labels) {
            for (int i = 0; i < nodes.size(); i++)
                nodes[i].calculateGradients(leftLayer, lossDerivativeWRTOutput(this -> outputValues, labels, i));
        }

        // Executa funções de atualização para cada nó na camada
        void calculateGradients(Layer leftLayer, Layer rightLayer) {
            for (int i = 0; i < nodes.size(); i++)
                nodes[i].calculateGradients(leftLayer, rightLayer);
        }

        // Executa atualização para cada nó na camada
        void updateWeights() {
            for (int i = 0; i < nodes.size(); i++)
                nodes[i].updateWeights();
        }

        // Imprime os pesos
        void printWeights() {
            std::cout << "layerId: " << layerId << std::endl;

            for (int i = 0; i < nodes.size(); i++)
                nodes[i].printWeights();
        }

};

// Calcula gradientes cumulativamente para camadas ocultas.
// Este é o algoritmo de retropropagação
void Node::calculateGradients(Layer leftLayer, Layer rightLayer) {

    if (leftWeights.size() > 0) {
        delta = sigmoidDerivative(value);

        double nodeError = 0;

        for (int i = 0; i < rightLayer.nodes.size(); i++) {
            if (rightLayer.nodes[rightLayer.nodes.size()-1].leftWeights.size() > 0)
                nodeError += rightLayer.nodes[i].delta * rightLayer.nodes[i].leftWeights[idInLayer];
        }

        delta *= nodeError;

        for (int i = 0; i < gradients.size(); i++)
            gradients[i] += leftLayer.nodes[i].value * delta;
    }
}

// Calcula gradientes cumulativamente para a camada de saída, a perda é calculada na função lossDerivativeWRTOutput
void Node::calculateGradients(Layer leftLayer, double loss) {
    delta = loss;
    
    for (int i = 0; i < leftWeights.size(); i++)
        gradients[i] += leftLayer.nodes[i].value * delta;
}

// Calcula o valor do nó tomando o sigmóide do produto interno de pesos e valores conectados da camada anterior
void Node::predict(Layer leftLayer) {
    if (leftWeights.size() > 0)
        value = sigmoid(innerProduct(leftLayer.nodes, leftWeights));
}

// Calcula o valor dos nós na camada de saída, sem sigmóide, pois o softmax é obtido no nível da camada 
void Node::predictOutput(Layer leftLayer) {
    value = innerProduct(leftLayer.nodes, leftWeights);
}

// Modelo
class NeuralNet {
    public:
        std::vector<Layer> layers;

        // Construtor      
        NeuralNet(std::vector<int> layerSizes) {

            // Adiciona camada de unidade de entrada, -1 porque não há camada anterior
            Layer *l0 = new Layer(layerSizes[0], -1, true, 0);
            layers.push_back(*l0);

            // Adiciona outras camadas
            for (int i = 0; i < layerSizes.size()-1; i++) {
                Layer *l;

                // Se a camada é de saída, então não há nenhum nó de bias adicionado
                if (i+1==layerSizes.size()-1) {
                    l = new Layer(layerSizes[i+1],layerSizes[i], false, i+1);
                } else {
                    l = new Layer(layerSizes[i+1],layerSizes[i], true, i+1);
                }

                layers.push_back(*l);
            }
        }

        // Prevê a saída para cada linha de dados na matriz de entrada e retorna as previsões de saída na linha equivalente da Matriz
        std::vector<std::vector<double>> predict(std::vector<std::vector<double>> m) {
            int outputUnits = layers[layers.size()-1].nodes.size();
            
            std::vector<std::vector<double>> result;

            result.resize(m.size(), std::vector<double>(outputUnits));
            
            // Calcula a previsão para cada instância (cada registro)
            for (int i = 0; i < m.size(); i++) {
            
                predictInstance(m, i);
                
                // Transfere os valores da camada final para o resultado
                for (int j =  0; j < outputUnits; j++) 
                    result[i][j] = layers[layers.size()-1].nodes[j].value;
            }

            return result;
        }

        // Para uma única instância irá calcular unidades através de uma rede de passagem direta
        void predictInstance(std::vector<std::vector<double>> m, int row) {
            
            // Inicializa a camada de entrada
            for (int i = 0; i < m[0].size(); i++) {
                layers[0].nodes[i].value = m[row][i];
            }      
            
            // Calcula os valores para todas as unidades no passe para frente
            for (int i = 1; i < layers.size(); i++) {
                layers[i].predict(layers[i-1]);
            }            
        }


        // Método de treinamento para os pesos de cada nó usando descida do gradiente,
        // calculados para cada instância de dados antes que os pesos sejam atualizados
        void fit(std::vector<std::vector<double>> m, std::vector<std::vector<int>> labels) {

            // Descida do Gradiente
            for (int epoch = 0; epoch < EPOCHS; epoch++) {

                // Imprimimos o erro do modelo
                if (epoch % ((EPOCHS + EPOCH_PRINTS -  1) / EPOCH_PRINTS) == 0) {
                    std::cout << "Epoch: " << std::setfill(' ') <<  std::setw(PRINT_PADDING) << epoch << " | "; loss(m, labels);
                }

                // Loop pelos registros do dataset
                for (int i = 0; i < m.size(); i++) {
                    
                    // Forward pass
                    predictInstance(m, i);

                    // Backward pass

                    // Calcula os gradientes na camada de saída
                    layers[layers.size()-1].calculateGradients(
                        layers[layers.size()-2], labels[i]);

                    // Calcula os gradiente nas outras camadas
                    for (int j = layers.size()-2; j > 0; j--) {
                        layers[j].calculateGradients(layers[j-1], layers[j+1]);
                    } 
                }

                // Atualiza os pesos
                for (int i = 0; i < layers.size(); i++) {
                        layers[i].updateWeights();
                } 
            }

            // Imprime o erro final
            std::cout << "Epoch: " << std::setfill(' ') << std::setw(PRINT_PADDING) << EPOCHS << " | "; loss(m, labels);

            // Imprime o valor final dos pesos
            std::cout << "Valor dos Pesos:" << std::endl;
            for (int i = 0; i < layers.size(); i++) {
                    layers[i].printWeights();
            } 
        }

        // Calcula o valor da função de perda e a precisão de todos os dados
        void loss(std::vector<std::vector<double>> m, std::vector<std::vector<int>> labels) {
            
            std::vector<std::vector<double>> result = predict(m);

            double loss = 0, rowMax;
            float accuracy = 0;
            int labelIndex, rowMaxIndex;

            // Iteração pelas instâncias
            for (int i = 0; i < labels.size(); i++) {

                rowMax = 0;
                rowMaxIndex = -1;
                labelIndex = -1;

                for (int j=0;j<labels[0].size();j++) {

                    // Calcula o erro (cross entropy)
                    loss -= labels[i][j] * log2(result[i][j]);

                    // Obtém o índice do label
                    if (labels[i][j] == 1) labelIndex = j;
                    
                    // Obtém o índice de maior probabilidade
                    if (result[i][j] > rowMax) {
                        rowMax = result[i][j];
                        rowMaxIndex = j;  
                    }
                }
                
                // Se o label previsto estiver correto aumenta a acurácia
                if (labelIndex == rowMaxIndex) accuracy++;
            }

            loss /= labels.size();

            accuracy /= labels.size();

            std::cout << "Erro: "<< loss << " - Acurácia: " << accuracy << std::endl;
        }
};


// Executa a app
int main(int argc, char **argv){
    
    // Cria o modelo
    std::vector<int> layerSizes = {4,4,3};
    NeuralNet nnet(layerSizes);

    // Carrega o dataset
    std::string line;
    std::ifstream infile("dados/dataset.txt");
    std::vector<std::vector<double>> m;
    std::vector<std::vector<int>> labels;

    // Obtém cada linha do dataset
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string in_line;
        std::vector<double> row;

        // Labels da variável alvo
        std::vector<int> label(3, 0);

        while (getline(ss, in_line, ',')) {
            row.push_back(std::stod(in_line, 0));
        }

        // O último elemento da linha é o rótulo
        
        label[row.back()] = 1;
        labels.push_back(label);
        row.pop_back();

        m.push_back(row);
    }

    // Treina o modelo
    std::cout << "Curva de Aprendizado:" << std::endl;
    nnet.fit(m, labels);

    // Forward pass
    std::vector<std::vector<double>> out = nnet.predict(m);

    // Previsões
    std::cout << "Previsões do Modelo:" << std::endl;
    for (int i = 0; i < out.size(); i++) {
        std::cout << "[" << labels[i][0] << ", " << labels[i][1] << ", " << labels[i][2] << "] -> ";
        std::cout << "[" << out[i][0] << ", " << out[i][1] << ", " << out[i][2] << "]";
        std::cout << std::endl;
    }
 
    return 0;
}

// Poderíamos calcular o cut-off e entregar apenas previsão de classe

// Fim
