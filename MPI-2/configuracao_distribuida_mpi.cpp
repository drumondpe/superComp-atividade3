#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa o MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtém o tamanho total de processos

    // Variável de configuração definida no processo raiz
    int num_iteracoes = 0;

    if (rank == 0) {
        // Processo raiz define a configuração
        num_iteracoes = 10000; // Defina o número de iterações para o cálculo
        std::cout << "Processo raiz configurou o número de iterações para: " << num_iteracoes << std::endl;
    }

    // Transmite a configuração para todos os processos
    MPI_Bcast(&num_iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo executa o cálculo com o número especificado de iterações
    double resultado_local = 0.0;
    for (int i = 0; i < num_iteracoes; i++) {
        resultado_local += i * 0.5; // Cálculo simples para ilustrar
    }

    // Cada processo imprime seu resultado local
    std::cout << "Processo " << rank << " - Resultado local: " << resultado_local << std::endl;

    MPI_Finalize(); // Finaliza o MPI
    return 0;
}
