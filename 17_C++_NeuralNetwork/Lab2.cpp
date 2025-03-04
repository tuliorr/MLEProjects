// Lab Deep Learning em C++ com Arquitetura Customizável

// Includes
#include <cstdlib>
#include <random>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

// Classe para o neurônio matemático
class Neuron
{

private:

	// Número de neurônios com ativação que alimenta a função de ativação deste neurônio
	int neuronInputListCount;

	// Matriz de endereços de neurônios de entrada com uma ativação que faz parte da ativação deste neurônio
	Neuron* inputNeurons;

	// O atributo activation receberá o resultado da função de ativação deste neurônio: sumOfproducts(weights, inputActivations) + bias
	// O atributo activationNudgeSum é a medição de como essa ativação afeta a função de custo, encontrada pela equação (dC / da) * (da / da_this) dos neurônios procedentes
	double activation, activationNudgeSum;

	// O atributo weights é a matriz de pesos aprendidos que são usados ​​para modificar o impacto das ativações do neurônio de entrada na ativação deste neurônio
	// O atributo weightMomentum é a quantidade de movimento dos pesos sendo atualizados pelo impulso anterior, o que terá um efeito nos impulsos subsequentes
	double* weights, * weightsMomentum;

	// O atributo bias é o negativo aprendido do limite de ativação que o sumOfProducts precisa superar para ter uma ativação positiva
	// O atributo biasMomentum é o momentum do bias sendo atualizado pelo impulso anterior, o que terá um efeito nos impulsos subsequentes
	double bias, biasMomentum;

	// O atributo momentumRetention é a taxa inversa de decaimento do momentum de um parâmetro (coeficiente) tendo um efeito no próximo deslocamento dos pesos. Se 0, nenhum impacto.
	double momentumRetention;

protected:

	// Calcula o produto de soma do neurônio: (pesos * inputs) + bias
	double getActivationFunctionInput() const
	{
		double sumOfProduct = 0;
		for (auto i = 0; i < neuronInputListCount; i++)
		{
			sumOfProduct += weights[i] * inputNeurons[i].getActivation();
		}

		return sumOfProduct + bias;
	}

	// Retorna o cálculo atual para a derivada da função de custo em relação à ativação deste neurônio
	double getActivationNudgeSum() const
	{
		return activationNudgeSum;
	}

	// Calcula a derivada parcial da função de custo em relação à ativação do neurônio de entrada: dC/da * da/di = dC/di
	virtual double getActivationRespectiveDerivation(const int inputNeuronIndex) const
	{
		assert(inputNeuronIndex < neuronInputListCount&& inputNeuronIndex >= 0);

		return activationNudgeSum * weights[inputNeuronIndex];
	}

	// Calcula a derivada parcial da função de custo em relação ao peso: dC/da * da/dw = dC/dw
	virtual double getWeightRespectiveDerivation(const int inputNeuronIndex) const
	{
		assert(inputNeuronIndex < neuronInputListCount&& inputNeuronIndex >= 0);

		return activationNudgeSum * inputNeurons[inputNeuronIndex].getActivation();
	}

	// Calcula a derivada parcial da função de custo em relação ao bias: dC/da * da/db = dC/db
	virtual double getBiasRespectiveDerivation() const
	{
		assert(neuronInputListCount >= 0);

		return activationNudgeSum * 1.0;
	}

	// Adiciona a mudança desejada no valor de ativação que teria reduzido o erro de treinamento de minibatch: dC/da = completeSum(dC/do * do/da)
	void nudgeActivation(double nudge)
	{
		activationNudgeSum += nudge;
	}

public:

	// Construtor chamado para neurônios de entrada de ativação determinada por entrada
	Neuron() : weights(nullptr), weightsMomentum(nullptr), inputNeurons(nullptr)
	{
		this -> neuronInputListCount = 0;
		this -> momentumRetention = 0;

		bias = biasMomentum = 0.0;

		activation = activationNudgeSum = 0.0;
	}

	// Construtor chamado para neurônios ocultos durante a criação da rede, com parâmetro de momentum de aprendizagem opcionais
	Neuron(int neuronInputListCount, Neuron* inputNeurons, double momentumRetention = 0.0)
	{
		this -> neuronInputListCount = neuronInputListCount;
		this -> inputNeurons = inputNeurons;
		this -> momentumRetention = momentumRetention;

		// Inicializa funções para gerar números aleatoriamente que seguem uma distribuição gaussiana
		std::random_device randomDevice{};
		std::mt19937 generator{ randomDevice() };
		std::normal_distribution<double> randomGaussianDistributor{ 0.0, std::sqrt(2 / (double)neuronInputListCount) };

		// Inicializa pesos usando o método He-et-al
		// https://arxiv.org/pdf/1511.06422.pdf
		weights = new double[neuronInputListCount];
		if (weights == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
		{
			weights[i] = randomGaussianDistributor(generator);
		}

		weightsMomentum = new double[neuronInputListCount]();
		if (weightsMomentum == nullptr) throw std::bad_alloc();

		bias = biasMomentum = 0.0;

		activation = activationNudgeSum = 0.0;
	}

	// Construtor chamado para neurônios ocultos durante o carregamento da rede, com pesos armazenados e valores de bias passados
	Neuron(int neuronInputListCount, Neuron* inputNeurons, std::vector<double> weightValues, double biasValue, double momentumRetention = 0.0)
	{
		this -> neuronInputListCount = neuronInputListCount;
		this -> inputNeurons = inputNeurons;
		this -> momentumRetention = momentumRetention;

		// Inicializa pesos usando o método He-et-al
		weights = new double[neuronInputListCount];
		if (weights == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
			weights[i] = weightValues[i];

		weightsMomentum = new double[neuronInputListCount]();
		if (weightsMomentum == nullptr) throw std::bad_alloc();

		bias = biasValue;
		biasMomentum = 0.0;

		activation = activationNudgeSum = 0.0;
	}

	// Construtor de cópia para neurônios
	Neuron(const Neuron& original)
	{
		neuronInputListCount = original.neuronInputListCount;
		inputNeurons = original.inputNeurons;
		activation = original.activation;
		activationNudgeSum = original.activationNudgeSum;
		bias = original.bias;
		biasMomentum = original.biasMomentum;
		momentumRetention = original.momentumRetention;

		weights = new double[neuronInputListCount];
		if (weights == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
			weights[i] = original.weights[i];

		weightsMomentum = new double[neuronInputListCount];
		if (weightsMomentum == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
			weightsMomentum[i] = original.weightsMomentum[i];
	}

	// Operador = sobrecarregando para atribuições legíveis, resultando em cópias profundas
	Neuron& operator=(const Neuron& original)
	{
		neuronInputListCount = original.neuronInputListCount;
		inputNeurons = original.inputNeurons;
		activation = original.activation;
		activationNudgeSum = original.activationNudgeSum;
		bias = original.bias;
		biasMomentum = original.biasMomentum;
		momentumRetention = original.momentumRetention;

		weights = new double[neuronInputListCount];
		if (weights == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
			weights[i] = original.weights[i];

		weightsMomentum = new double[neuronInputListCount];
		if (weightsMomentum == nullptr) throw std::bad_alloc();
		for (auto i = 0; i < neuronInputListCount; i++)
			weightsMomentum[i] = original.weightsMomentum[i];

		return *this;
	}

	// "Destruidor" personalizado para neurônios
	~Neuron()
	{
		inputNeurons = nullptr;

		delete[] weights;
		delete[] weightsMomentum;
	}

	// Define a função de ativação externa vazia do neurônio, uma função linear sumOfProducts(weights, inputActivations) + bias
	virtual void activate(const double input = 0.0)
	{
		if (neuronInputListCount > 0)
		{
			activation = getActivationFunctionInput();
		}
		else
		{
			activation = input;
		}

	}

	// Injeta derivada dC/da no neurônio
	void setError(double cost)
	{
		activationNudgeSum = cost;
	}

	// Injeta derivada correspondente nos neurônios de entrada devido à ativação: dC/di = sum(all(dC/dh * dh/di)) 
	void injectInputRespectiveCostDerivation() const
	{
		for (auto i = 0; i < neuronInputListCount; i++)
		{
			inputNeurons[i].nudgeActivation(getActivationRespectiveDerivation(i));
		}
	}

	// Aplica alterações aos pesos que reduziriam o custo do lote anterior
	// Usa impulsos de ativação reservados para dimensionar a mudança proporcionalmente
	void updateWeights(int batchSize, double learningRate)
	{
		for (auto i = 0; i < neuronInputListCount; i++)
		{
			weightsMomentum[i] = momentumRetention * weightsMomentum[i] - (getWeightRespectiveDerivation(i) / batchSize) * learningRate;
			weights[i] += weightsMomentum[i];
		}
	}

	// Aplica a mudança ao bias que reduziria a função de custo para o lote anterior
	// Usa a ativação reservadaNudges para dimensionar a mudança proporcionalmente
	void updateBias(int batchSize, double learningRate)
	{
		biasMomentum = momentumRetention * biasMomentum - (getBiasRespectiveDerivation() / batchSize) * learningRate;
		bias += biasMomentum;
	}

	// Redefine a derivada parcial do custo em relação à ativação deste neurônio do lote anterior
	void resetNudges()
	{
		activationNudgeSum = 0.0;
	}

	// Retorna o número de neurônios de entrada
	int getInputCount() const
	{
		return neuronInputListCount;
	}

	// Retorna o valor de ativação do neurônio
	double getActivation() const
	{
		return activation;
	}

	// Retorna o peso deste neurônio para um neurônio de entrada especificado
	double getWeight(int inputNeuronIndex) const
	{
		assert(inputNeuronIndex < neuronInputListCount&& inputNeuronIndex >= 0);

		return weights[inputNeuronIndex];
	}

	// Retorna o viés deste neurônio
	double getBias() const
	{
		return bias;
	}

	// Retorna o tipo de ativação do neurônio
	virtual std::string getNeuronType()
	{
		return getInputCount() == 0 ? "Input" : "Linear";
	}

};

// Classe para uma camada do modelo
class NeuralLayer
{

protected:

    // O atributo neuronArrayLength é o número de neurônios contidos em cada coluna de uma camada
	// O atributo neuronArrayWidth é o número de neurônios contidos em cada linha de uma camada
	int neuronArrayLength, neuronArrayWidth;

	// O atributo neurons é a matriz de neurônios contidos na camada
	Neuron* neurons;

	// O atributo previousLayer é um ponteiro para o NeuralLayer que deve alimentar esta camada - nullptr se esta for a primeira camada
	NeuralLayer* previousLayer;

	// Definir erro de neurônios com ativações usadas diretamente para calcular o custo dC/da
	void setError(double costArray[])
	{
		if (costArray != nullptr)
		{
			for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
				neurons[i].setError(costArray[i]);
		}
	}

	// Impulsiona as ativações da camada de entrada com as derivadas apropriadas da função de custo dC/da * da/di
	void injectErrorBackwards()
	{
		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
			neurons[i].injectInputRespectiveCostDerivation();
	}

	// Aplica pesos aprendidos e atualizações de bias
	void updateParameters(int batchSize, double learningRate)
	{
		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i].updateWeights(batchSize, learningRate);

			neurons[i].updateBias(batchSize, learningRate);
		}
	}

	// Limpa todos os impulsos armazenados para os parâmetros do neurônio
	void clearNudges()
	{
		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
			neurons[i].resetNudges();
	}

public:
	
	// Construtor padrão para classe de camada
	NeuralLayer()
	{
		neurons = nullptr;
		neuronArrayLength = 0;
		neuronArrayWidth = 0;
		previousLayer = nullptr;
	}

	// Construtor chamado para camadas de entrada
	NeuralLayer(int inputLength, int inputWidth) : neuronArrayLength(inputLength), neuronArrayWidth(inputWidth), previousLayer(nullptr)
	{
		neurons = new Neuron[inputLength * inputWidth];
		if (neurons == nullptr) throw std::bad_alloc();

		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i] = Neuron();
		}
	}

	// Construtor chamado para camadas ocultas durante a criação da rede, com parâmetro de momentum opcional
	NeuralLayer(int neuronCount, NeuralLayer* inputLayer, double momentumRetention = 0.0)
	{
		neuronArrayLength = neuronCount;
		neuronArrayWidth = 1;
		previousLayer = inputLayer;

		int inputNeuronCount = previousLayer->getNeuronArrayCount();
		Neuron* inputNeurons = previousLayer->getNeurons();
		neurons = new Neuron[neuronCount];
		if (neurons == nullptr) throw std::bad_alloc();

		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i] = Neuron(inputNeuronCount, inputNeurons, momentumRetention);
		}

	}

	// Construtor chamado para camadas ocultas durante o carregamento da rede, com pesos armazenados e valores de bias
	NeuralLayer(int neuronCount, NeuralLayer* inputLayer, double momentumRetention, std::vector<std::vector<double>> weightValues, std::vector<double> biasValues)
	{
		neuronArrayLength = neuronCount;
		neuronArrayWidth = 1;
		previousLayer = inputLayer;

		int inputNeuronCount = previousLayer->getNeuronArrayCount();
		Neuron* inputNeurons = previousLayer->getNeurons();
		neurons = new Neuron[neuronCount];
		if (neurons == nullptr) throw std::bad_alloc();

		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i] = Neuron(inputNeuronCount, inputNeurons, weightValues[i], biasValues[i], momentumRetention);
		}

	}

	// Construtor de cópia para camadas
	NeuralLayer(const NeuralLayer& original)
	{
		neuronArrayLength = original.neuronArrayLength;
		neuronArrayWidth = original.neuronArrayWidth;
		previousLayer = original.previousLayer;

		neurons = new Neuron[neuronArrayLength * neuronArrayWidth];
		if (neurons == nullptr) throw std::bad_alloc();

		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i] = Neuron(original.neurons[i]);
		}
	}

	// Operador = sobrecarregando para atribuições legíveis, resultando em cópias profundas
	NeuralLayer& operator=(const NeuralLayer& original)
	{
		neuronArrayLength = original.neuronArrayLength;
		neuronArrayWidth = original.neuronArrayWidth;
		previousLayer = original.previousLayer;

		neurons = new Neuron[neuronArrayLength * neuronArrayWidth];
		if (neurons == nullptr) throw std::bad_alloc();

		for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
		{
			neurons[i] = Neuron(original.neurons[i]);
		}

		return (*this);
	}

	// Destruidor personalizado para objetos NeuralLayer
	~NeuralLayer()
	{
		delete[] neurons;

		previousLayer = nullptr;
	}

	// Ativa todos os neurônios na camada e redefine os impulsos da iteração de aprendizagem anterior
	void propagateForward(double inputValues[] = nullptr)
	{
		if (previousLayer == nullptr)
		{
			for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
			{
				neurons[i].activate(inputValues[i]);
			}
		}

		else
		{
			for (auto i = 0; i < neuronArrayLength * neuronArrayWidth; i++)
			{
				neurons[i].activate();
			}
		}

		clearNudges();
	}

	// Transmite derivada aos neurônios de entrada e aplica atualizações de parâmetros aprendidos
	void propagateBackward(int batchSize, double learningRate, double* costArray = nullptr)
	{
		setError(costArray);

		injectErrorBackwards();

		updateParameters(batchSize, learningRate);
	}

	// Retorna o número de neurônios contidos em uma coluna da camada
	int getNeuronArrayLength() const
	{
		return neuronArrayLength;
	}

	// Retorna o número de neurônios contidos em uma linha da camada
	int getNeuronArrayWidth() const
	{
		return neuronArrayWidth;
	}

	// Retorna o número de neurônios contidos na camada
	int getNeuronArrayCount() const
	{
		return getNeuronArrayLength() * getNeuronArrayWidth();
	}

	// Retorna uma matriz de ponteiros para os neurônios contidos na camada
	Neuron* getNeurons() const
	{
		return neurons;
	}

	// Retorna o ponteiro para a camada que está alimentando esta camada
	NeuralLayer* getPreviousLayer() const
	{
		return previousLayer;
	}

	std::vector<double> getNeuronActivations() const
	{
		std::vector<double> neuronActivations;

		for (auto i = 0; i < getNeuronArrayCount(); i++)
		{
			neuronActivations.push_back(getNeurons()[i].getActivation());
		}

		return neuronActivations;
	}

	// Retorna o tipo de ativação dos neurônios contidos na camada
	virtual std::string getNeuralLayerType() const
	{
		return previousLayer == nullptr ? "Input" : neurons[0].getNeuronType();
	}
};

// Struct para info de criação da camada
struct layerCreationInfo
{
	std::string type;
	int neuronCount;
	double momentumRetention;
};

// Struct para info de carregamento da camada
struct layerLoadInfo
{
	std::string type;
	int neuronCount;
	double momentumRetention;
	std::vector<std::vector<double>> weightsOfNeurons;
	std::vector<double> biasOfNeurons;
};

// Classe para a rede neural
class NeuralNetwork
{

private:

    // O atributo layerCount é o número de camadas neurais mantidas dentro da rede neural (também define a profundidade da rede)
	int layerCount;

	// O atributo inputLength é a primeira dimensão definindo o tamanho da matriz de entrada, atualmente assumindo uma grade de entrada 2D
	// O atributo inputWidth é a segunda dimensão definindo o tamanho da matriz de entrada, atualmente assumindo uma grade de entrada 2D
	int inputLength, inputWidth;

	// O atributo outputCount é o número de saídas que se espera que a rede neural produza, atualmente assumindo uma saída vetorial
	int outputCount;

	// O atributo neuralLayers é uma matriz contendo todas as camadas neurais que compõem a rede
	NeuralLayer* neuralLayers;

	// A taxa de Aprendizagem é o coeficiente que descreve a magnitude dos ajustes aos parâmetros de peso e bias após uma iteração de treinamento
	double learningRate;

	// O tamanho do batch é o número de amostras de treinamento de um conjunto de dados que serão alimentados pela rede antes que o aprendizado ocorra
	int batchSize;

public:
	
	// Construtor para a criação da rede neural
	NeuralNetwork(int layerCount, int inputLength, int inputWidth, int outputCount, double learningRate, int batchSize, layerCreationInfo* layerDetails)
	{
		this -> layerCount = layerCount;
		this -> inputLength = inputLength;
		this -> inputWidth = inputWidth;
		this -> outputCount = outputCount;
		this -> learningRate = learningRate;
		this -> batchSize = batchSize;

		neuralLayers = new NeuralLayer[layerCount];
		if (neuralLayers == nullptr) throw std::bad_alloc();
		neuralLayers[0] = NeuralLayer(inputLength, inputWidth);

		for (auto i = 1; i < layerCount; i++)
		{

			if (false)
			{
				// Aqui podemos implementar outros tipos de camadas como convolucional ou recorrente
			}
			else
			{
				neuralLayers[i] = NeuralLayer(layerDetails[i].neuronCount, &neuralLayers[i - 1], layerDetails[i].momentumRetention);
			}
		}
	}

	// Retorna um vetor dos valores de ativação da camada final da rede
	std::vector<double> getOutputs()
	{
		return neuralLayers[layerCount - 1].getNeuronActivations();
	}

	// Ativa todas as camadas em ordem de entrada para camadas de saída
	void propagateForwards(double* inputMatrix)
	{
		neuralLayers[0].propagateForward(inputMatrix);

		for (auto i = 1; i < layerCount; i++)
		{
			neuralLayers[i].propagateForward();
		}
	}

	// Atualiza os parâmetros em todas as camadas, da saída às camadas de entrada
	void propagateBackwards(double* costArray)
	{
		neuralLayers[layerCount - 1].propagateBackward(batchSize, learningRate, costArray);

		for (auto i = layerCount - 2; i > 0; i--)
		{
			neuralLayers[i].propagateBackward(batchSize, learningRate);
		}
	}

	// Altera o número de amostras que a rede espera processar antes de ser instruída a aprender
	void updateBatchSize(int newBatchSize)
	{
		batchSize = newBatchSize;
	}

	// Atualiza a magnitude das mudanças de parâmetro durante a aprendizagem
	void updateLearningRate(int newLearningRate)
	{
		learningRate = newLearningRate;
	}

};

// Função Main
int main()
{
	
	int numberOfLayers, inputLength, inputWidth, outputCount, batchSize;

	std::cout << "Qual o comprimento das entradas que essa rede neural aceitará? ";
	std::cin >> inputLength;
	std::cout << std::endl;

	// Para a largura vamos usar sempre 1, caso contrário  teríamos que implementar o tratamento da matriz de entrada
	// Desta forma teremos um vetor de dads
	inputWidth = 1;

	std::cout << "Qual o número de outputs que essa rede neural vai produzir? ";
	std::cin >> outputCount;
	std::cout << std::endl;

	std::cout << "Quantas camadas essa rede neural vai conter? ";
	std::cin >> numberOfLayers;
	layerCreationInfo* layerDetails = new layerCreationInfo[numberOfLayers];
	std::cout << std::endl;

	// Como o volume de dados será baixo, usaremos sempre batchsize de 1
	batchSize = 1;

	// Camada de entrada
	layerDetails[0].type = "1";
	layerDetails[0].neuronCount = inputLength * inputWidth;

	// Hiperparâmetro momentumRetention
	layerDetails[0].momentumRetention = 0;

	// Loop pelo número de camadas
	for (int i = 1; i < numberOfLayers; i++)
	{
		std::cout << std::endl << "Definir camada neural " << i + 1 << ":\n";

		std::cout << "\tTipo de ativação: ";
		std::cin >> layerDetails[i].type;
		std::cout << std::endl;

		if (i + 1 < numberOfLayers)
		{
			std::cout << "\tContagem de neurônios: ";
			std::cin >> layerDetails[i].neuronCount;
			std::cout << std::endl;
		}
		else
		{
			layerDetails[i].neuronCount = outputCount;
		}

		std::cout << "\tMomentum retention: ";
		std::cin >> layerDetails[i].momentumRetention;
		layerDetails[i].momentumRetention = 0;
		std::cout << std::endl;
	}

	// Cria a rede
	NeuralNetwork network = NeuralNetwork(numberOfLayers, inputLength, inputWidth, outputCount, 0.0001, batchSize, layerDetails);

	// Gera dados fictícios como dados de entrada
	double* inputGrid = new double[inputLength * inputWidth];
	for (auto i = 0; i < inputLength * inputWidth; i++)
	{
		inputGrid[i] = 15;
	}

	// Forward propagate para calcular o erro
	network.propagateForwards(inputGrid);

	// Obtém os outputs (previsões do modelo)
	auto outputVector = network.getOutputs();
	for (std::vector<double>::iterator it = outputVector.begin(); it < outputVector.end(); it++)
	{
		std::cout << (*it) << " ";
	}

	// Calcula o vetor de erro
	double* errorVector = new double[outputCount];
	for (auto i = 0; i < outputCount; i++)
	{
		errorVector[i] = (2 / outputCount) * (20 - network.getOutputs()[i]) * (-1);
	}

	// Backward propagate 
	network.propagateBackwards(errorVector);

	// Forward propagate para as previsões
	network.propagateForwards(inputGrid);

	// Obtém os outputs finais
	outputVector = network.getOutputs();
	for (std::vector<double>::iterator it = outputVector.begin(); it < outputVector.end(); it++)
	{
		std::cout << (*it) << " ";
	}

	return 0;
}

// Fim