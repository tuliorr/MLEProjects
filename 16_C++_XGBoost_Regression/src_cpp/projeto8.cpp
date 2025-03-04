// Implementando XGBoost em C++ 

// Includes
#include <ios>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <cxxopts.hpp>
#include <xgboost/c_api.h>

// Call para checar se o XGBoost foi carregado
#define check_xgboost(call)                                                                                            \
    {                                                                                                                  \
        auto err = (call);                                                                                             \
        if (err != 0) {                                                                                                \
            std::fprintf(stderr, "%s:%d: erro em %s: %s\n", __FILE__, __LINE__, #call, XGBGetLastError());            \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
    }

// Verifica se o stream de dados está disponível
#define check_stream_open(stream, fname)                                                                               \
    {                                                                                                                  \
        if (!stream) {                                                                                                 \
            std::cerr << __FILE__ << ":" << __LINE__ << " falha ao abrir o arquivo '" << fname << "'" << std::endl;         \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
    }

// Struct para os argumentos
struct Args {
    std::string model_file;
    std::string data_file;
    std::string result_file;
};

// Parse dos argumentos
Args
parse_args(int argc, char** argv)
{
    cxxopts::Options args("predict", "Modelo XGBoost de Regressão");

    args.add_options()
        ("h,help", "mostra o help")
        ("m,model", "arquivo do modelo", cxxopts::value<std::string>())
        ("d,data", "arquivo dos dados", cxxopts::value<std::string>())
        ("r,result", "arquivo para salvar as previsões", cxxopts::value<std::string>())
        ;

    Args opts;

    try {
        auto parsed_opts = args.parse(argc, argv);
        if (parsed_opts.count("help")) {
            std::cout << args.help() << std::endl;
            exit(EXIT_SUCCESS);
        }

        if (parsed_opts.count("model") == 0 || parsed_opts.count("data") == 0 || parsed_opts.count("result") == 0) {
            std::cerr << "Nem todas as opções obrigatórias foram especificadas! Execute com -h para as opções disponíveis." << std::endl;
            exit(EXIT_FAILURE);
        }

        opts.model_file = parsed_opts["model"].as<std::string>();
        opts.data_file = parsed_opts["data"].as<std::string>();
        opts.result_file = parsed_opts["result"].as<std::string>();
    } catch (std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return opts;
}

// Limpa espaços em branco
std::string
trim(const std::string& s, const std::string& whitespace = " \t")
{
    const auto start = s.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return std::string();
    }

    const auto end = s.find_last_not_of(whitespace);
    const auto range = end - start + 1;

    return s.substr(start, range);
}

// Separa as colunas do vetor de dados
std::vector<float>
tokenize(const std::string& line, char separator)
{
    std::vector<float> tokens;
    std::vector<int> marks;
    std::string s;

    marks.push_back(-1);

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == separator) {
            marks.push_back(i);
        }
    }

    size_t count = marks.size();
    char* end = nullptr;

    marks.push_back(line.size());

    for (size_t idx = 0; idx < count; idx++) {
        s.clear();
        s.append(line, marks[idx] + 1, marks[idx + 1] - marks[idx] - 1);
        auto trimmed = trim(s);
        auto str = trimmed.c_str();
        auto v = std::strtof(str, &end);
        if (v == 0 && end == str) {
            std::cerr << "erro de conversão em float'" << s << "'" << std::endl;
            exit(EXIT_FAILURE);
        }
        tokens.push_back(v);
    }

    return tokens;
}

// Bloco main
int
main(int argc, char** argv)
{
    // Argumentos
    auto args = parse_args(argc, argv);

    // Variável para o modelo
    BoosterHandle booster;
    
    // Matriz de dados
    DMatrixHandle dtest = nullptr;
    
    // Variáveis de controle
    bst_ulong out_len = 0;
    
    // Resultado
    const float* out_result = nullptr;

    // Variável para o stream de dados
    std::fstream input;

    // Abre o arquivo
    input.open(args.data_file, std::ios::in);
    
    // Checa os dados
    check_stream_open(input, args.data_file);

    // Vetor de dados
    std::vector<float> data;
    
    // Variável para cada linha sendo tratada como string
    std::string line;
    
    // Variáveis de controle
    bst_ulong nrow = 0, ncol = 0;

    // Carrega e processa os dados
    if (std::getline(input, line)) { 
        while (std::getline(input, line)) {
            auto values = tokenize(line, ',');
            if (ncol == 0) {
                ncol = values.size();
            } else {
                if (values.size() != ncol) {
                    std::cerr << "erro: " << values.size() << "!=" << ncol << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            std::copy(std::begin(values), std::end(values), std::back_inserter(data));
            nrow++;
        }
    }

    // Cria o objeto
    check_xgboost(XGBoosterCreate(nullptr, 0, &booster));
    
    // Carrega o modelo
    check_xgboost(XGBoosterLoadModel(booster, args.model_file.c_str()));
    
    // Prepara os dados
    check_xgboost(XGDMatrixCreateFromMat(data.data(), nrow, ncol, NAN, &dtest));
    
    // Previsões com o modelo treinado
    check_xgboost(XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &out_result));

    if (out_len != nrow) {
        std::cerr << "número inesperado de resultados" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Resultado
    std::ofstream result(args.result_file, std::ios::trunc);
    
    check_stream_open(result, args.result_file);

    for (bst_ulong i = 0; i < out_len; i++) {
        result << i << "," << std::fixed << std::setprecision(3) << out_result[i] << std::endl;
    }

    result.close();

    // Libera a memória
    check_xgboost(XGDMatrixFree(dtest));
    check_xgboost(XGBoosterFree(booster));

    return EXIT_SUCCESS;
}
