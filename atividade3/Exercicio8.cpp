/*
Matriz e Soma de Elementos Diagonais: Crie um programa que peça ao usuário para inserir uma matriz 3x3 e depois exiba a
soma dos elementos na diagonal principal.
*/

#include <iostream>

int main() {
    int matriz[3][3];
    int soma = 0;

    std::cout << "Insira os elementos da matriz 3x3:" << std::endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            std::cin >> matriz[i][j];
            if(i == j) {
                soma += matriz[i][j];
            }
        }
    }

    std::cout << "A soma dos elementos da diagonal principal é: " << soma << std::endl;

    return 0;
}
