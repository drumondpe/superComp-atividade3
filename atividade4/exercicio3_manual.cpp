/*
Exercício: Implemente uma função que aloca dinamicamente uma matriz de 
inteiros de tamanho N x N e realiza uma soma simples de todos os seus elementos.
*/

#include <iostream>
#include <chrono>

int main() {
    int N = 1000;

    auto inicio = std::chrono::high_resolution_clock::now();

    // Alocação dinâmica de memória para uma matriz N x N.
    // Primeiro, aloca um array de ponteiros, onde cada ponteiro irá apontar para uma linha da matriz.
    int** matriz = new int*[N];
    for (int i = 0; i < N; ++i) {
        matriz[i] = new int[N];
    }

    // Para cada linha da matriz, aloca um array de inteiros de tamanho N.
    // Aqui você pode inicializar e somar os elementos da matriz.
    // Por exemplo, você pode preencher a matriz com valores e calcular a soma total.
    long long soma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;
            soma += matriz[i][j];
        }
    }
    
    std::cout << "Soma dos elementos (alocação dinâmica manual): " << soma << std::endl;

    // Liberação da memória alocada dinamicamente.
    // Primeiro, libera a memória alocada para cada linha (os arrays de inteiros).
    for (int i = 0; i < N; ++i) {
        delete[] matriz[i];
    }
    // Finalmente, libera a memória alocada para o array de ponteiros.
    delete[] matriz;

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
    std::cout << "Tempo de execução (alocação dinâmica manual): " << duracao << " ms" << std::endl;

    return 0;
}
