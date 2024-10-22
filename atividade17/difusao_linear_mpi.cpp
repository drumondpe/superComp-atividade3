#include <mpi.h>
#include <iostream>
#include <cstring> // Para usar a função strcpy

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    const int bufferSize = 100;
    char message[bufferSize];

    if (rank == 0) {
        // Processo 0 inicia a mensagem
        strcpy(message, "Mensagem inicial do processo 0");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo 0 enviou para processo " << rank + 1 << ": " << message << std::endl;
    } else {
        // Cada processo recebe a mensagem do processo anterior
        MPI_Recv(message, bufferSize, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu de processo " << rank - 1 << ": " << message << std::endl;

        // Se não for o último processo, envia para o próximo
        if (rank < size - 1) {
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
            std::cout << "Processo " << rank << " enviou para processo " << rank + 1 << ": " << message << std::endl;
        }
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
