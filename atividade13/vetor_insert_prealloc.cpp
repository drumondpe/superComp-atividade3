#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000;
    std::vector<double> vec(N); // Pré-alocação de memória

    double start_time = omp_get_wtime(); // Inicia a medição do tempo

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i);
    }

    double end_time = omp_get_wtime(); // Finaliza a medição do tempo
    double elapsed_time = end_time - start_time;

    std::cout << "Tempo com pré-alocação: " << elapsed_time << " segundos" << std::endl;

    return 0;
}
