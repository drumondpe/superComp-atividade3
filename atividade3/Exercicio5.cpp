/*
Soma de Números em um Vetor: Crie um programa que solicite ao usuário para inserir 5 números em um vetor e depois
exiba a soma desses números.
*/

#include <iostream>

int main() {
    int numeros[5];
    int soma = 0;

    std::cout << "Insira 5 números:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cin >> numeros[i];
        soma += numeros[i];
    }

    std::cout << "A soma dos números é: " << soma << std::endl;

    return 0;
}
