#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <numeric> // Para std::accumulate
#include <cmath>   // Para operações matemáticas

#define VECTOR_SIZE 100000

int main(int argc, char** argv) {
    int rank, size;

    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calcula o tamanho do subvetor para cada processo
    int elements_per_proc = VECTOR_SIZE / size;

    // Vetor principal (apenas no processo raiz)
    std::vector<int> main_vector;
    if (rank == 0) {
        main_vector.resize(VECTOR_SIZE);
        // Preenche o vetor com números de 1 a VECTOR_SIZE
        std::iota(main_vector.begin(), main_vector.end(), 1);
    }

    // Subvetor para cada processo
    std::vector<int> sub_vector(elements_per_proc);

    // Distribui partes do vetor principal para todos os processos
    MPI_Scatter(main_vector.data(), elements_per_proc, MPI_INT,
                sub_vector.data(), elements_per_proc, MPI_INT,
                0, MPI_COMM_WORLD);

    // Cada processo calcula a soma dos quadrados usando OpenMP
    double local_sum = 0.0;
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < elements_per_proc; i++) {
        local_sum += std::pow(sub_vector[i], 2);
    }

    // Reduz os resultados parciais para o processo raiz
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // O processo raiz imprime o resultado final
    if (rank == 0) {
        std::cout << "A soma total dos quadrados é: " << global_sum << std::endl;
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();

    return 0;
}
