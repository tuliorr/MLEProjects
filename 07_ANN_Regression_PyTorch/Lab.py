# Lab Bônus - Rede Neural Artificial de Regressão com PyTorch

# Import
import torch
import time

# Marca o tempo de início da execução do script
start_time = time.time()

# Classe
class Modelo(torch.nn.Module):

    # Construtor
    def __init__(self, D_in, H, D_out):
        super(Modelo, self).__init__()
        self.linear1 = torch.nn.Linear(D_in, H)
        self.linear2 = torch.nn.Linear(H, D_out)

    # Método
    def forward(self, x):
        h_relu = self.linear1(x).clamp(min=0)
        y_pred = self.linear2(h_relu)
        return y_pred

# N é o batch size
# D_in é a camada de entrada
# H é a camada oculta
# D_out é a camada de saída
N, D_in, H, D_out = 64, 1000, 100, 10

# Criamnos dados de entrada e saída aleatórios
x = torch.randn(N, D_in)
y = torch.randn(N, D_out)

# Definimos o modelo (instância da classe)
modelo = Modelo(D_in, H, D_out)

# Função de erro
loss_fn = torch.nn.MSELoss(reduction = 'sum')

# Taxa de aprendizado
learning_rate = 1e-4

# Otimizados SGD
optimizer = torch.optim.SGD(modelo.parameters(), lr = learning_rate)

# Loop de treinamento
for t in range(500):
    
    # Forward pass: faz a previsão de y
    y_pred = modelo(x)

    # Calcula e imprime o erro do modelo
    loss = loss_fn(y_pred, y)

    if t%100 == 99:
        print("Epoch = {}, Erro = {}".format(t, loss.item()))

    # Zera os gradientes antes do backward pass
    optimizer.zero_grad()

    # Backpropagation
    loss.backward()

    # Atualiza os pesos
    optimizer.step()


print("\n--- Executado em %s Segundos ---\n" % (time.time() - start_time))


