#include <mpi.h>
#include <iostream>
#include <cstring> // Para usar a função strcpy

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    if (size < 3) {
        if (rank == 0) {
            std::cerr << "O número de processos deve ser maior que 2 para formar um anel." << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    const int bufferSize = 100;
    char message[bufferSize];

    if (rank == 0) {
        // Processo 0 começa o envio
        strcpy(message, "Mensagem do processo 0");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo 0 enviou para processo " << rank + 1 << ": " << message << std::endl;

        // Recebe a mensagem do último processo
        MPI_Recv(message, bufferSize, MPI_CHAR, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo 0 recebeu de processo " << size - 1 << ": " << message << std::endl;

    } else {
        // Recebe a mensagem do processo anterior
        MPI_Recv(message, bufferSize, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu de processo " << rank - 1 << ": " << message << std::endl;

        // Modifica a mensagem
        std::string newMessage = std::string(message) + " -> Processo " + std::to_string(rank);

        // Envia para o próximo processo ou volta para o processo 0 se for o último
        int nextRank = (rank + 1) % size;
        MPI_Send(newMessage.c_str(), newMessage.size() + 1, MPI_CHAR, nextRank, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou para processo " << nextRank << ": " << newMessage << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
