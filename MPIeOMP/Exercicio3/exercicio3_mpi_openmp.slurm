#!/bin/bash
#SBATCH --job-name=exercicio3_mpi_openmp   # Nome do job
#SBATCH --output=output_exercicio3_mpi_openmp.txt  # Nome do arquivo de saída
#SBATCH --ntasks=4                         # Número de processos MPI
#SBATCH --cpus-per-task=4                  # Número de threads OpenMP por processo MPI
#SBATCH --time=00:05:00                    # Tempo máximo de execução (5 minutos)
#SBATCH --mem=1G                           # Memória total disponível para o job

# Executar o programa com MPI e OpenMP
mpirun -np 4 ./exercicio3_mpi_openmp
