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
        // Processo 0 inicia a comunicação com cada processo sequencialmente
        for (int i = 1; i < size; ++i) {
            // Envia mensagem para o processo i
            snprintf(message, bufferSize, "Olá processo %d, sou o processo 0", i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo 0 enviou para processo " << i << ": " << message << std::endl;

            // Recebe resposta do processo i
            MPI_Recv(message, bufferSize, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Processo 0 recebeu do processo " << i << ": " << message << std::endl;
        }
    } else {
        // Cada processo responde ao processo 0
        MPI_Recv(message, bufferSize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu do processo 0: " << message << std::endl;

        // Responde ao processo 0
        snprintf(message, bufferSize, "Olá processo 0, sou o processo %d", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou para o processo 0: " << message << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
