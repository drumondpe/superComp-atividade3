/*
Ordenação de Vetor (Bubble Sort): Implemente o algoritmo de ordenação Bubble Sort para organizar um vetor de números
em ordem crescente.
*/

#include <iostream>

int main() {
    int numeros[10];

    std::cout << "Insira 10 números:" << std::endl;
    for(int i = 0; i < 10; i++) {
        std::cin >> numeros[i];
    }

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9 - i; j++) {
            if(numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    std::cout << "Números ordenados: ";
    for(int i = 0; i < 10; i++) {
        std::cout << numeros[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
