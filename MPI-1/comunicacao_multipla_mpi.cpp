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
        // Processo 0 envia mensagens exclusivas para cada processo
        for (int i = 1; i < size; ++i) {
            // Cria uma mensagem exclusiva para cada processo
            snprintf(message, bufferSize, "Mensagem para o processo %d", i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, i, MPI_COMM_WORLD);
            std::cout << "Processo 0 enviou para processo " << i << ": " << message << std::endl;
        }
    } else {
        // Cada processo (exceto 0) recebe sua mensagem
        MPI_Recv(message, bufferSize, MPI_CHAR, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << message << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
