# Bônus - Previsão de Churn com Inteligência Artificial e Deploy do Modelo - Modelagem

# Imports dos Pacotes
import pickle
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# Carregar os dados
df = pd.read_csv('dados/dataset.csv')

# Definição da variável alvo e das variáveis de entrada
# Divisão dos dados em X (entrada) e y (saída)
X = df.drop('Churn', axis = 1)
y = df['Churn']

# Divisão em Dados em Treino e Teste com proporção 80/20
X_treino, X_teste, y_treino, y_teste = train_test_split(X, y, test_size = 0.2, random_state = 42)

# Padronização dos dados de treino e teste
scaler = StandardScaler()
X_treino_scaled = scaler.fit_transform(X_treino.values)
X_teste_scaled = scaler.transform(X_teste.values)

# Criação do Modelo
modelo_dsa = RandomForestClassifier(n_estimators = 100, random_state = 42)

# Treinanento do modelo
modelo_dsa.fit(X_treino_scaled, y_treino)

# Avaliação do Modelo
y_pred = modelo_dsa.predict(X_teste_scaled)

# Métricas
print("Acurácia:", accuracy_score(y_teste, y_pred))
print("Confusion Matrix:")
print(confusion_matrix(y_teste, y_pred))
print("Classification Report:")
print(classification_report(y_teste, y_pred))

# Salvar o modelo para uso no deploy
with open('modelos/modelo.pkl', 'wb') as model_file:
    pickle.dump(modelo_dsa, model_file)

# Salvar o scaler para uso no deploy
with open('modelos/scaler.pkl', 'wb') as scaler_file:
    pickle.dump(scaler, scaler_file)
