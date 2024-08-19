/*
Encontrar o Maior Número em um Vetor: Escreva um programa que peça ao usuário para inserir 10 números em um vetor e
determine qual é o maior número.
*/

#include <iostream>

int main() {
    int numeros[10];
    int maior;

    std::cout << "Insira 10 números:" << std::endl;
    for(int i = 0; i < 10; i++) {
        std::cin >> numeros[i];
    }

    maior = numeros[0];
    for(int i = 1; i < 10; i++) {
        if(numeros[i] > maior) {
            maior = numeros[i];
        }
    }

    std::cout << "O maior número é: " << maior << std::endl;

    return 0;
}
