#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric> // Para std::accumulate
#include <cstdlib> // Para srand() e rand()

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    const int array_size = 100; // Tamanho total do array
    int local_size = array_size / size; // Tamanho do pedaço para cada processo
    std::vector<int> array; // Array no processo raiz
    std::vector<int> local_array(local_size); // Array local para cada processo

    if (rank == 0) {
        // Inicializa o array com valores aleatórios no processo raiz
        array.resize(array_size);
        srand(42); // Seed para gerar números aleatórios (fixo para reprodutibilidade)
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100; // Valores aleatórios entre 0 e 99
        }

        // Exibe o array gerado no processo raiz
        std::cout << "Array original no processo raiz: ";
        for (int i = 0; i < array_size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    // Distribui partes do array para todos os processos
    MPI_Scatter(array.data(), local_size, MPI_INT, local_array.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula a média local
    double local_sum = std::accumulate(local_array.begin(), local_array.end(), 0);
    double local_avg = local_sum / local_size;

    // Coleta as médias locais no processo raiz
    std::vector<double> local_averages(size);
    MPI_Gather(&local_avg, 1, MPI_DOUBLE, local_averages.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // O processo raiz calcula a média global
    if (rank == 0) {
        double global_sum = std::accumulate(local_averages.begin(), local_averages.end(), 0.0);
        double global_avg = global_sum / size;
        std::cout << "Média global: " << global_avg << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
