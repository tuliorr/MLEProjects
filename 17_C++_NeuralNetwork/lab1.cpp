// Lab Rede Neural Simples em C++

// Objetivo: criar uma rede neural simples

// https://www.cplusplus.com/reference/cstdlib/
// https://www.cplusplus.com/reference/cassert/
// https://www.cplusplus.com/reference/sstream/

// Includes
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

// Classe para os dados de treino
class TrainingData
{
public:
	
	TrainingData(const string filename);
	
	bool isEof(void)
	{
		return m_trainingDataFile.eof();
	}
	
	void getTopology(vector<unsigned> &topology);

	// Retorna o número de valores de entrada lidos do arquivo:
	unsigned getNextInputs(vector<double> &inputVals);
	unsigned getTargetOutputs(vector<double> &targetOutputVals);

private:
	ifstream m_trainingDataFile;
};

void TrainingData::getTopology(vector<unsigned> &topology)
{
	string line;
	string label;

	getline(m_trainingDataFile, line);
	
	stringstream ss(line);
	
	ss >> label;
	
	if(this -> isEof() || label.compare("topology:") != 0)
	{
		abort();
	}

	while(!ss.eof())
	{
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}
	return;
}

TrainingData::TrainingData(const string filename)
{
	m_trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals)
{
    inputVals.clear();

    string line;
    
	getline(m_trainingDataFile, line);
    
	stringstream ss(line);

    string label;
    
	ss >> label;
    
	if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
    targetOutputVals.clear();

    string line;
    
	getline(m_trainingDataFile, line);
    
	stringstream ss(line);

    string label;
    
	ss >> label;
    
	if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron;

typedef vector<Neuron> Layer;

// Classe para o neurônio com as propriedades do neurônio para serem usadas na rede
class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVals);
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);
private:
	static double eta; 
	static double alpha; 
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer &nextLayer) const;
	double m_outputVal;
	vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};

double Neuron::eta = 0.15; 
double Neuron::alpha = 0.5; 

void Neuron::updateInputWeights(Layer &prevLayer)
{
	// Os pesos a serem atualizados estão no contêiner de conexão nos neurônios da camada anterior
	for(unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		// Entrada individual, ampliada pelo gradiente e taxa de treino
		// Adicione também momentum = uma fração do peso delta anterior
		double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;
		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}
double Neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	// Soma os erros nos nós que alimentamos
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVals)
{
	double delta = targetVals - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
	// tanh - faixa de saída [-1,0..1,0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	// derivada tanh
	return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	// Soma as saídas da camada anterior e inclui o nó de polarização (bias)
	for(unsigned n = 0 ; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for(unsigned c = 0; c < numOutputs; ++c)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

// Classe para a rede neural
class Net
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; }

private:
	vector<Layer> m_layers; 
	double m_error;
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
};

double Net::m_recentAverageSmoothingFactor = 100.0; 

void Net::getResults(vector<double> &resultVals) const
{
	resultVals.clear();

	for(unsigned n = 0; n < m_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}

void Net::backProp(const std::vector<double> &targetVals)
{
	// Calcular o erro geral
	Layer &outputLayer = m_layers.back();
	
	m_error = 0.0;

	for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta *delta;
	}
	
	m_error /= outputLayer.size() - 1; 
	
	// RMSE
	m_error = sqrt(m_error);

	// Erro médio
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);
	
	// Calcula gradientes da camada de saída
	for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}
	
	// Calcula gradientes em camadas ocultas
	for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for(unsigned n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// Para todas as camadas, desde as saídas até a primeira camada oculta, atualiza os pesos
	for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for(unsigned n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

void Net::feedForward(const vector<double> &inputVals)
{
	// Verifica o número de entradas 
	assert(inputVals.size() == m_layers[0].size() - 1);

	// Atribui os valores de entrada para os neurônios de entrada
	for(unsigned i = 0; i < inputVals.size(); ++i)
	{
		m_layers[0][i].setOutputVal(inputVals[i]); 
	}

	// Propagação para frente
	for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
	{
		Layer &prevLayer = m_layers[layerNum - 1];

		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n)
		{
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

Net::Net(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());
		
		// numOutputs da camada [i] é o numInputs da camada [i + 1]
		// numOutputs da última camada é 0
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 :topology[layerNum + 1];

		// Fizemos uma nova camada, agora a preenchemos com neurônios e adicionamos um neurônio de bias à camada:
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Força o valor de saída do nó de bias para 1,0. É o último neurônio criado acima
		m_layers.back().back().setOutputVal(1.0);
	}
}

void showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for(unsigned i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

// Função main
int main()
{
	TrainingData trainData("dados.txt");
	
	vector<unsigned> topology;

	trainData.getTopology(topology);
	
	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	
	int trainingPass = 0;
	
	while(!trainData.isEof())
	{
		++trainingPass;
		
		cout << endl << "Step" << trainingPass;

		// Obtém novos dados de entrada
		if(trainData.getNextInputs(inputVals) != topology[0])
			break;
		
		showVectorVals(": Input :", inputVals);
		
		myNet.feedForward(inputVals);

		// Coleta as previsões do modelo
		myNet.getResults(resultVals);
		
		showVectorVals("Output:", resultVals);

		// Treina a rede e obtém os valores reais
		trainData.getTargetOutputs(targetVals);
		
		showVectorVals("Target:", targetVals);
		
		assert(targetVals.size() == topology.back());
		
		myNet.backProp(targetVals);

		// Erro do modelo
		cout << "Erro da Rede: " << myNet.getRecentAverageError() << endl;
	}

	cout << endl << "Fim" << endl;

}
