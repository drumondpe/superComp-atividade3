#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric>  // Para std::accumulate
#include <cmath>    // Para sqrt
#include <cstdlib>  // Para srand() e rand()

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    const int array_size = 100; // Tamanho total do array
    int local_size = array_size / size; // Tamanho do segmento para cada processo

    std::vector<double> array; // Array completo no processo raiz
    std::vector<double> local_array(local_size); // Array local em cada processo

    double local_sum = 0.0;
    double local_variance_sum = 0.0;

    if (rank == 0) {
        // Processo raiz cria um array com valores aleatórios
        array.resize(array_size);
        srand(42); // Seed para gerar números aleatórios
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100 + 1; // Valores aleatórios entre 1 e 100
        }

        // Exibe o array gerado no processo raiz
        std::cout << "Array original no processo raiz: ";
        for (int i = 0; i < array_size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    // Distribui partes do array para todos os processos
    MPI_Scatter(array.data(), local_size, MPI_DOUBLE, local_array.data(), local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Cada processo calcula a média local
    local_sum = std::accumulate(local_array.begin(), local_array.end(), 0.0);
    double local_mean = local_sum / local_size;

    // Calcula a soma da variação local
    for (double val : local_array) {
        local_variance_sum += (val - local_mean) * (val - local_mean);
    }

    // Coleta todas as médias e somas de variação no processo raiz
    std::vector<double> local_means(size);
    std::vector<double> local_variances(size);
    MPI_Gather(&local_mean, 1, MPI_DOUBLE, local_means.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&local_variance_sum, 1, MPI_DOUBLE, local_variances.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Processo raiz calcula o desvio padrão global
    if (rank == 0) {
        double global_sum = std::accumulate(local_means.begin(), local_means.end(), 0.0) * local_size;
        double global_mean = global_sum / array_size;

        double global_variance_sum = std::accumulate(local_variances.begin(), local_variances.end(), 0.0);
        double global_variance = global_variance_sum / array_size;
        double global_standard_deviation = std::sqrt(global_variance);

        std::cout << "Desvio padrão global: " << global_standard_deviation << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
