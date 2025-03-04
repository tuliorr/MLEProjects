# Modelo XGBoost em Python

# pip install xgboost

# Imports
import os
import sys
import os.path
import argparse
import traceback
import numpy as np
import pandas as pd
import xgboost as xgb
import warnings
warnings.filterwarnings("ignore")

# Argumentos
def parse_args():
    parser = argparse.ArgumentParser(description = "XGBoost Para Regressão em Python")
    parser.add_argument("--modelo", type = str, metavar = "arg", required = True, help = "Modelo XGBoost Pré-Treinado")
    parser.add_argument("--dados", type = str, metavar = "arg", required = True, help = "Dados no Formato CSV")
    parser.add_argument("--resultado", type = str, metavar = "arg", required = True, help = "Arquivo Para Salvar os Resultados")
    args = parser.parse_args()

    return args

# Função Main
def main():
    try:

    	# Carrega os argumentos
        args = parse_args()

        # Carrega os dados
        df = pd.read_csv(args.dados, dtype = np.float32)

        # Carrega o modelo
        regressor = xgb.XGBRegressor()
        regressor.load_model(args.modelo)

        # Previsões com o modelo
        preds = regressor.predict(df)

        # Dataframe com as previsões
        result = pd.DataFrame({"previsoes": preds})

        # Salva o dataframe em csv
        result.to_csv(args.resultado, float_format = "%.3f", index = False, header = False)
        
    except Exception as exc:
        print(exc, file = sys.stderr)
        print("===", file = sys.stderr)
        print(traceback.format_exc(), file = sys.stderr)
        sys.exit(-1)

# Executa a função main
if __name__ == "__main__":
    main()
    print("\nModelo Executado com Sucesso!\n")


