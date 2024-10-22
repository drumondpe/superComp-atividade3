#!/bin/bash
#SBATCH --job-name=comunicacao_mpi  # Nome do Job
#SBATCH --output=output_comunicacao_mpi.txt  # Nome do arquivo de saída
#SBATCH --ntasks=2  # Número de processos MPI
#SBATCH --time=00:01:00  # Tempo máximo de execução (1 minuto)
#SBATCH --mem=512M  # Memória alocada para o job

# Executar o programa MPI com 2 processos
mpirun -np 2 ./comunicacao_mpi
