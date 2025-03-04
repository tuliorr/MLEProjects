# Bônus - Previsão de Churn com Inteligência Artificial e Deploy do Modelo - Deploy

# Imports
import pickle
import pandas as pd
import numpy as np

# Carregar o scaler salvo em disco
with open('modelos/scaler.pkl', 'rb') as model_file:
    loaded_scaler = pickle.load(model_file)

# Carregar o modelo salvo em disco
with open('modelos/modelo.pkl', 'rb') as model_file:
    loaded_model = pickle.load(model_file)

# Criar dados de exemplo de 1 cliente para as variáveis preditoras (usaremos para fazer previsão da variável alvo)
Idade = 25
Tempo_Assinatura_Servico = 12
Valor_Pago_Mes = 55.0
Itens_Acessados = 8

# Montar o array de novos dados de 1 cliente
novos_dados = np.array([[Idade, Tempo_Assinatura_Servico, Valor_Pago_Mes, Itens_Acessados]])

# Aplicar a padronização aos novos dados
novos_dados_scaled = loaded_scaler.transform(novos_dados)

# Fazer previsão com os novos dados e o modelo
previsao = loaded_model.predict(novos_dados_scaled)

# Imprimir resultado de acordo com a previsão
if previsao[0] == False:
    print("\nEste Cliente Não Tem Churn Previsto! Ou seja, não deve cancelar a assinatura!\n")
else:
    print("\nEste Cliente Tem Churn Previsto! Ou seja, deve cancelar a assinatura!\n")
