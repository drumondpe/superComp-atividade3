#include <iostream>
#include <vector>
#include <chrono>

int main() {
    int N = 1000;

    auto inicio = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> matriz(N, std::vector<int>(N));

    long long soma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;
            soma += matriz[i][j];
        }
    }

    std::cout << "Soma dos elementos (std::vector): " << soma << std::endl;

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
    std::cout << "Tempo de execução (std::vector): " << duracao << " ms" << std::endl;

    return 0;
}
 