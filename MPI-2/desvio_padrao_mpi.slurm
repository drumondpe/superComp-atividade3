#!/bin/bash
#SBATCH --job-name=desvio_padrao_mpi  # Nome do Job
#SBATCH --output=output_desvio_padrao_mpi.txt  # Nome do arquivo de saída
#SBATCH --ntasks=4  # Número de processos MPI
#SBATCH --time=00:02:00  # Tempo máximo de execução (2 minutos)
#SBATCH --mem=512M  # Memória alocada para o job

# Executar o programa MPI com 4 processos
mpirun -np 4 ./desvio_padrao_mpi
