// Projeto 7 - Previsão do Custo de Vida em Áreas Urbanas com Regressão Linear em C++

// Include e namespace
#include<bits/stdc++.h>
using namespace std;

// https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html

// Classe para carga e manipulação de dados
class CarregaCsv {
	
	protected:
		
        // Vetores
		vector <pair<string,vector<float> > >data;
		vector <float>x, y, yp, y_gra, x_test, y_test;

        // Nome do arquivo csv
		string file_name;

        // Demais variáveis
		float x_factor, y_factor;
		int n;

    public:
		
        // Método de leitura dos dados
		void read(string file)
		{
			file_name = file;
			cout << "Arquivo csv: "  << file_name << endl;
			
            // Stream
			fstream fo;
			
            // Abre o arquivo
			fo.open(file_name.c_str(), ios::in);
			
            // Variáveis de controle
			string line, colname;
			
            // Leitura do arquivo
			if(fo.good())
            {
				
                // Obtém uma linha
                getline(fo,line);
				
                // Stream de string
                stringstream s(line);
				
                // Obtém os nomes das colunas
                while(getline(s,colname,','))
                {
					data.push_back({colname,vector<float> {}});
				}
				
                // Variável de controle
                int temp1;
				
                // Leitura de cada linha de dados
                while(getline(fo,line))
                {
				
                    // Índice de coluna
                	int col = 0;
				
                    // Stream
                	stringstream s1(line);
				
                    // Loop para leitura das linhas
                	while(s1 >> temp1)
                    {
				
                        // Carrega o vetor data
                		data.at(col).second.push_back(temp1);
				
                		col++;
				
                		if(s1.peek() == ',')
                        {
							s1.ignore();
						}
					}
				}
				
                // A primeira variável (coluna) é x
                for(int i = 0;i < data[0].second.size();i++)
                {
					x.push_back(data[0].second.at(i));
				}
				
                // A segunda variável (coluna) é y
                for(int i = 0;i < data[1].second.size();i++)
                {
					y.push_back(data[1].second.at(i));
				}
			}
			else
            {
				cout << "Erro no arquivo";
			}
			
            // Fecha o strem
            fo.close();
			
            // Chama os demais métodos
            check();
			data_normalization();
			spilt_data();
			
		}

        // Método para checar os dados
        void check()
        {
			int i = 0;
			
            // Checa se x foi carregado corretamente
            while(i < data[0].second.size())
            {
				if(x.at(i) != data[0].second.at(i))
                {
					cout << "Erro em x" << endl;
					break;
				}
			
            i++;
			
            }
			
			i = 0;
			
            // Checa se y foi carregado corretamente
			while(i < data[1].second.size())
            {
				if(y.at(i) != data[1].second.at(i))
                {
					cout << "Erro em y"  << endl;
					break;
				}
			
            i++;
			
            }
		}

        // Método de normalização dos dados
        void data_normalization(int normal_level = 7, int type = 0)
        {
            // Variáveis de controle
    	    long double x_sum = 0, y_sum = 0;
    	
            // Loop pelos valores de x
    	    for(int i = 0; i < x.size();i++)
    	    {
    		    x_sum += x[i];
    		    y_sum += y[i];
		    }
		
            // Cria fatores para a normalização
		    x_factor = x_sum / (normal_level * x.size());
		    y_factor = y_sum / (normal_level * y.size());
		
            // Normalização
		    for(int i = 0; i < x.size();i++)
    	    {
    		    x[i] = x[i] / x_factor;
    		    y[i] = y[i] / y_factor;
		    }
		
	    }

        // Método para divisão dos dados em treino e teste
        void spilt_data(int debug = 0)
        {
            // Fator de split (70/30)
    	    int total = 0.3 * x.size();
    	    srand(time(0));
    	
    	    if(debug)
    	    {
    		    cout << "Índices" << endl;
		    }
    	
            for (int i = 0; i < total; i++)
    	    {
                // Tamanho de x e y
    		    int x_mod = x.size();
	    	    int y_mod = y.size();
	    	 
                // Índice de separação dos dados
	    	    int temp = rand();
	    	    int x_index = temp % x_mod;
	    	    int y_index = temp % y_mod;
	    	    
                if(debug)
			    {
				    cout << x_index << endl;
			    }

                // Carrega os dados de teste
	    	    x_test.push_back(x[x_index]);
			    y_test.push_back(y[y_index]);
			
                // Remove os dados de teste dos dados originais que então serão usados para treino
			    x.erase(x.begin() + x_index);
			    y.erase(y.begin() + y_index);
		    }
		
            if(debug)
		    {
			    cout << "X_test" << endl;
		    }
		
		    if(debug)
		    {
			    for (int i = 0; i < x_test.size(); i++)
	    	    {
	    		    cout << x_test[i] << endl;
	    	    }
		    }
    	
    	    cout << endl;
	    }

        // Método para definir o tamanho da amostra de dados de entrada
        void set_size()
        {
            n = x.size();
        }

};

// Classe para o algoritmo de Regressão Linear
class LinearRegression:public CarregaCsv
{

	protected:
    
		float m, c, xbar, ybar;
    	float slope, intercept;
	
	public:

        // Construtor
    	LinearRegression()
    	{
        	m = 0;
        	c = 0;
        	xbar = 0;
        	ybar = 0;
    	}

        // Método para os cálculos da Regressão Linear
        void calculate()
    	{
            // Variáveis
       		float z, q, s = 0, d = 0;
	   		float siz = y.size();
       		
            // Cálculo acumulado
            xbar = accumulate(x.begin(), x.end(),0) / siz;
       		ybar = accumulate(y.begin(), y.end(),0) / siz;
       		
            // Loop de cálculo
			for(int i = 0;i < n;i++)
       		{
           		z = (x[i] - xbar);
           		q = (y[i] - ybar);
           		s = s + (z * q);
           		d = d + z * z;
       		}
       
            // Calcula os coeficientes
        	m = (s/d);
        	c = ybar - m * xbar;
    	}
    
        // Método para mostrar os resultados
		void show()
    	{
        	cout << "Slope da Linha de Regressão: " << m << endl;
        	cout << "Intercepto da Linha de Regressão: "  << c << endl;
    	}

        // Método para a previsão do modelo
        void predicted()
    	{
        	int i;
        	
            for(i = 0;i < y_test.size();i++)
    		{
          		float z;
                
                // Fórmula de regressão
          		z = m * x_test[i] + c;

                // Armazena os resultados
          		yp.push_back(z);
       		}
       
    	}

        // Algoritmo de aprendizado
        void gradient_descent()
    	{	
			// Array para armazenar os valores dos erros
        	vector<float>error;            
        	float err = 0;

			// Inicializa b0
        	float b0 = 0;     

			// Inicializa b1              
        	float b1 = 0;          

			// Inicializa a taxa de aprendizagem       
        	float alpha = 0.00019;       

            // Total de loops de treinamento      
        	int max_learning_loops = 4500;
	    
	    	for (int j = 0; j < max_learning_loops; j++)
	    	{
	    		for (int i = 0; i < n; i ++)
		    	{
                    // Fórmula de regressão
			    	float p = b0 + b1 * x[i];

                    // Erro da previsão
			    	err += (p - y[i]) * (p - y[i]);
		    	}
		    
                // Armazena o erro
		    	error.push_back(err);
			
                // Altera o valor do coeficiente
		    	b0 = b0 - (alpha * err);

                // A partir daqui faremos um ajuste fino

                // Para armazenar o erro
		    	float err1 = 0;
			
                // Nova rodada de treinamento
				for (int i = 0; i < n; i ++)
		    	{
                    // Fórmula de regressão
			    	float p = b0 + b1 * x[i];

                    // Erro da previsão
			    	err1 += (p - y[i]) * (p - y[i]);
		    	}
		    
                // Altera o valor do coeficiente
		    	b0 = b0 + (2 * alpha * err);

                // Para armazenar o erro
		    	float err2 = 0;
		    
                // Nova rodada de treinamento
		    	for (int i = 0; i < n; i ++)
		    	{
                    // Fórmula de regressão
			    	float p = b0 + b1 * x[i];

                    // Erro da previsão
			    	err2 += (p - y[i])* (p - y[i]);
		    	}
		    
                // Verifica os erros e aumenta a taxa de aprendizado
		    	if(err1 < err2)
		    	{
		    		b0 = b0 - (2 * alpha * err);
				}
			
                // Atualiza b1
				b1 = b1 - (alpha * err);

                // Armazena o erro
		    	err1 = 0;
		    
                // Nova rodada de treinamento
		    	for (int i = 0; i < n; i ++)
		    	{
                    // Fórmula de regressão
			    	float p = b0 + b1 * x[i];

                    // Erro da previsão
			    	err1 += (p - y[i]) * (p - y[i]);
		    	}
		    
                // Atualiza b1
		    	b1 = b1 + (2 * alpha * err);

                // Armazena o erro
		    	err2 = 0;
		    
                // Nova rodada de treinamento
		    	for (int i = 0; i < n; i ++)
		    	{
                    // Fórmula de regressão
			    	float p = b0 + b1 * x[i];

                    // Erro da previsão
			    	err2 += (p - y[i]) * (p - y[i]);
		    	}
		    
                // Verifica os erros e aumenta a taxa de aprendizado
		    	if(err1 < err2)
		    	{
		    		b1 = b1 - (2 * alpha * err);
				}
			
				err = 0;
			
			}
		
	    	cout << "Valores Finais do Gradiente Descente: " << "c (intercepto) = " << b0 << " " << "m (slope) = " << b1 << " " << endl;
	    	slope = b1;
	    	intercept = b0;
    	}

        // Previsão do gradiente
    	void predict_gradient()
    	{
        	for(int i = 0;i < x_test.size();i++)
        	{
            	y_gra.push_back((x_test[i] * slope) + intercept);
        	}
    	}
};

// Classe para avaliação do modelo
class Acuracia:public LinearRegression
{
	protected:
    
		float r2f, r2g, r;

	public:

        // Construtor
    	Acuracia()
    	{
            r = 0;
        	r2f = 0;
        	r2g = 0;
    	}
    
        // Calcula a correlação
		void correlation()
    	{
       		float z, q, s = 0, d = 0, siz = n, b = 0, sq;

            // Calcula variância e co-variância
       		for(int i = 0;i < y.size();i++)
       		{
           		z = (x[i] - xbar);
           		q = (y[i] - ybar);
           		s = s + (z * q);
           		d = d + z * z;
           		b += (q * q);
       		}
       
	   		sq = sqrtf(d * b);

            // Calcula o coeficiente de correlação
       		r = (s / sq);

       		cout << "Correlação = " << r << endl;
       
	   		if(r > -0.5 && r < -1.0)
       		{
           		cout << "Forte Relacionamento Negativo." << endl;
           		cout << "Slope é negativo'." << endl;
       		}
       		else if(r >= -0.5 && r <= 0.5)
       		{
           		cout << "Não há relacionamento entre as variáveis." << endl;
           		cout << "Esses dados não devem ser usados para Regressão Linear." << endl;
       		}
       		else if(r > 0.5 && r <= 1.0)
       		{
           		cout << "Forte Relacionamento Positivo." << endl;
           		cout << "Slope é positivo." << endl;
       		}
       		
			cout << endl;
    	}

        // Coeficiente R2 do modelo
    	void rsquare_for_formula()
    	{
    		float ytbar = accumulate(y_test.begin(), y_test.end(),0) / y_test.size();
        	float z = 0, s = 0;

        	for(int i = 0;i < y_test.size();i++)
        	{
              	z += ((yp[i] - y_test[i]) * (yp[i] - y_test[i]));
              	s += ((y[i] - ytbar) * (y[i] - ytbar));
        	}
        	
            r2f = 1 - (z / s);
        	
            cout << "Coeficiente R2 do Modelo:" << r2f << endl;
    	}
    
        // Coeficiente R2 do gradiente
		void rsquare_for_gradient()
    	{
        	float numg, deng = 0;
        	float y_t_bar = accumulate(y_test.begin(), y_test.end(),0) / y_test.size();
        	
            for(int i = 0; i < x_test.size(); i++)
        	{
            	float temp = (x_test[i] * slope) + intercept;
            	numg += ((temp - y_test[i]) * (temp - y_test[i]));
            	deng += ((y_test[i] - y_t_bar) * (y_test[i] - y_t_bar));
        	}
        	cout << "Coeficiente R2 do Gradiente: " << 1 - (numg/deng) << endl << endl;
    	}
};

// Bloco main
int main()
{
    Acuracia acc;
    acc.read("dados/dataset.csv");
    acc.set_size();
    acc.gradient_descent();
    acc.predict_gradient();
    acc.rsquare_for_gradient();
    acc.correlation();
    acc.calculate();
    acc.show();
    acc.predicted();
    acc.rsquare_for_formula();
}

// Fim