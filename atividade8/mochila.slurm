#!/bin/bash
#SBATCH --job-name=mochila                      # Nome do job
#SBATCH --output=resultado_%j.txt               # Nome do arquivo de saída (usar %j para o ID do job)
#SBATCH --ntasks=1                              # Número de tarefas (1 processo)
#SBATCH --cpus-per-task=1                       # Número de threads por tarefa (1 thread por processo)
#SBATCH --mem=512M                              # Memória total alocada (512 MB)
#SBATCH --time=00:10:00                         # Tempo máximo de execução (10 minutos)
#SBATCH --partition=espec                       # Fila do cluster a ser utilizada

# Exporta a variável de ambiente para configurar o número de threads OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Executa o programa
./mochila < Entrada1.txt
