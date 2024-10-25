#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    int valor = rank + 1; // Cada processo recebe um valor exclusivo (por exemplo, seu rank + 1)
    int soma = 0;

    if (rank == 0) {
        // Processo 0 inicia com seu valor exclusivo
        soma = valor;
        // Envia a soma inicial para o processo 1
        MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo 0 iniciou com valor: " << valor << std::endl;

    } else {
        // Cada processo recebe a soma do processo anterior
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        soma += valor; // Adiciona seu valor à soma

        // Se não for o último processo, envia a soma para o próximo
        if (rank < size - 1) {
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Último processo exibe a soma total
            std::cout << "Processo " << rank << " exibiu a soma total: " << soma << std::endl;
        }

        std::cout << "Processo " << rank << " somou seu valor: " << valor << " -> Soma atual: " << soma << std::endl;
    }

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
