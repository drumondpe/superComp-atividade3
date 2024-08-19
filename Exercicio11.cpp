/*
Leitura e Escrita em Arquivo: Estatísticas de Texto: Escreva um programa que leia um arquivo de texto e calcule as seguintes
estatísticas: número total de palavras, número total de linhas, número médio de palavras por linha e a palavra mais frequente.
Em seguida, grave essas estatísticas em um novo arquivo de texto.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

int main() {
    std::ifstream arquivoEntrada("entrada.txt");
    std::ofstream arquivoSaida("estatisticas.txt");

    if(!arquivoEntrada.is_open() || !arquivoSaida.is_open()) {
        std::cout << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::string linha;
    int totalLinhas = 0;
    int totalPalavras = 0;
    std::map<std::string, int> frequenciaPalavras;

    while(std::getline(arquivoEntrada, linha)) {
        totalLinhas++;
        std::istringstream stream(linha);
        std::string palavra;

        while(stream >> palavra) {
            totalPalavras++;
            frequenciaPalavras[palavra]++;
        }
    }

    int palavraMaisFrequente = 0;
    std::string palavraFrequente;
    for(const auto& par : frequenciaPalavras) {
        if(par.second > palavraMaisFrequente) {
            palavraMaisFrequente = par.second;
            palavraFrequente = par.first;
        }
    }

    arquivoSaida << "Número total de linhas: " << totalLinhas << std::endl;
    arquivoSaida << "Número total de palavras: " << totalPalavras << std::endl;
    arquivoSaida << "Palavra mais frequente: " << palavraFrequente << " (" << palavraMaisFrequente << " vezes)" << std::endl;
    arquivoSaida << "Número médio de palavras por linha: " << static_cast<double>(totalPalavras) / totalLinhas << std::endl;

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}
