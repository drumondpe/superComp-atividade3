#include <mpi.h>
#include <iostream>
#include <cstring> // Para usar a função strcpy

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo

    const int bufferSize = 100;
    char message[bufferSize];

    if (rank == 0) {
        // Processo 0 envia "Olá" para o processo 1
        strcpy(message, "Olá");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo 0 enviou: " << message << std::endl;

        // Recebe resposta do processo 1
        MPI_Recv(message, bufferSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo 0 recebeu: " << message << std::endl;

    } else if (rank == 1) {
        // Processo 1 recebe "Olá" do processo 0
        MPI_Recv(message, bufferSize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo 1 recebeu: " << message << std::endl;

        // Responde com "Oi" para o processo 0
        strcpy(message, "Oi");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        std::cout << "Processo 1 enviou: " << message << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
