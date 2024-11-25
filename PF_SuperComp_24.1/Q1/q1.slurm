#!/bin/bash
#SBATCH --job-name=questao1_prova          # Nome do job
#SBATCH --output=output_%j.txt             # Arquivo de saída (%j será substituído pelo ID do job)
#SBATCH --nodes=2                          # Solicita 2 máquinas (nós)
#SBATCH --ntasks-per-node=1                # Número de tarefas por nó (1 por nó)
#SBATCH --cpus-per-task=5                  # Solicita 5 cores por máquina
#SBATCH --mem=3G                           # Solicita 3 GB de memória por nó
#SBATCH --partition=prova                  # Partição chamada "prova"
#SBATCH --time=00:30:00                    # Tempo máximo de execução: 30 minutos (ajustável)

# Exporta a variável de ambiente para usar 10 threads
export OMP_NUM_THREADS=10

# Executa o código fictício denominado "./executavel"
./executavel
