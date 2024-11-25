#!/bin/bash
#SBATCH --job-name=mpi_openmp_hybrid       # Nome do job
#SBATCH --output=output_%j.txt             # Arquivo de saída (%j será substituído pelo ID do job)
#SBATCH --nodes=1                          # Número de nós
#SBATCH --ntasks=4                         # Número de processos MPI
#SBATCH --cpus-per-task=5                  # Número de cores por processo MPI
#SBATCH --mem=4G                           # Memória total por nó
#SBATCH --partition=prova                  # Nome da partição
#SBATCH --time=00:30:00                    # Tempo máximo de execução

# Exporta o número de threads OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Executa o programa usando MPI
mpirun ./mpi_openmp
