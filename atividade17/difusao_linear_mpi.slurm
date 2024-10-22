#!/bin/bash
#SBATCH --job-name=difusao_linear_mpi  # Nome do Job
#SBATCH --output=output_difusao_linear_mpi.txt  # Nome do arquivo de saída
#SBATCH --ntasks=3  # Número de processos MPI (mínimo 3)
#SBATCH --time=00:01:00  # Tempo máximo de execução (1 minuto)
#SBATCH --mem=512M  # Memória alocada para o job

# Executar o programa MPI com 3 processos
mpirun -np 3 ./difusao_linear_mpi
