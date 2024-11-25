#!/bin/bash
#SBATCH --job-name=matrix_openmp_4cores   # Nome do job
#SBATCH --output=output_%j.txt            # Arquivo de saída (%j será substituído pelo ID do job)
#SBATCH --nodes=1                         # Número de nós
#SBATCH --ntasks=1                        # Número de tarefas MPI (apenas 1 neste caso)
#SBATCH --cpus-per-task=4                 # Número de cores alocados
#SBATCH --mem=8G                          # Memória alocada (ajuste conforme necessário)
#SBATCH --partition=prova                 # Partição a ser usada
#SBATCH --time=00:10:00                   # Tempo máximo de execução

# Define o número de threads para OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Executa o programa
./matrix_openmp
