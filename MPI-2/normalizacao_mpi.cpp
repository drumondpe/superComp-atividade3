#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm> // Para std::max_element
#include <cstdlib>   // Para srand() e rand()

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    const int array_size = 100; // Tamanho total do array
    int local_size = array_size / size; // Tamanho do segmento para cada processo

    std::vector<double> array; // Array completo no processo raiz
    std::vector<double> local_array(local_size); // Array local em cada processo
    double max_value = 0.0;

    if (rank == 0) {
        // Processo raiz cria um array com valores aleatórios
        array.resize(array_size);
        srand(42); // Seed para gerar números aleatórios
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100 + 1; // Valores aleatórios entre 1 e 100
        }

        // Encontra o valor máximo no processo raiz
        max_value = *std::max_element(array.begin(), array.end());
        std::cout << "Valor máximo encontrado pelo processo raiz: " << max_value << std::endl;
    }

    // Transmite o valor máximo para todos os processos
    MPI_Bcast(&max_value, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Divide o array entre os processos
    MPI_Scatter(array.data(), local_size, MPI_DOUBLE, local_array.data(), local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Cada processo normaliza sua parte do array
    for (int i = 0; i < local_size; i++) {
        local_array[i] /= max_value;
    }

    // Reúne os resultados normalizados no processo raiz
    MPI_Gather(local_array.data(), local_size, MPI_DOUBLE, array.data(), local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Processo raiz imprime o array normalizado final
    if (rank == 0) {
        std::cout << "Array normalizado: ";
        for (int i = 0; i < array_size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
