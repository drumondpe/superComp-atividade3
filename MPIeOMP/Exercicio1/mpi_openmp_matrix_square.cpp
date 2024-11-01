#include <iostream>
#include <mpi.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 10; // Tamanho da matriz (alterar para testes)
    int data[N][N]; // Matriz original
    int chunk_size = N / size; // Número de linhas por processo
    int local_data[chunk_size][N]; // Dados locais para cada processo

    // Inicialização da matriz no processo raiz
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                data[i][j] = i + j;
            }
        }
    }

    // Distribuição das linhas da matriz para os processos
    MPI_Scatter(data, chunk_size * N, MPI_INT, local_data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Paralelização com OpenMP para calcular o quadrado dos elementos
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < chunk_size; i++) {
        for (int j = 0; j < N; j++) {
            local_data[i][j] *= local_data[i][j];
        }
    }

    // Reúne os resultados no processo raiz
    MPI_Gather(local_data, chunk_size * N, MPI_INT, data, chunk_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Exibição do resultado no processo raiz
    if (rank == 0) {
        std::cout << "Matriz com os elementos ao quadrado:" << std::endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
