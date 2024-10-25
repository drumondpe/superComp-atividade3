#!/bin/bash
#SBATCH --job-name=comunicacao_multipla_mpi  # Nome do Job
#SBATCH --output=output_comunicacao_multipla_mpi.txt  # Nome do arquivo de saída
#SBATCH --ntasks=3  # Número de processos MPI (mínimo 3)
#SBATCH --time=00:01:00  # Tempo máximo de execução (1 minuto)
#SBATCH --mem=512M  # Memória alocada para o job

# Carregar o módulo do MPI (caso necessário no cluster)
# module load mpi/openmpi-x.x.x

# Executar o programa MPI com 3 processos
mpirun -np 3 ./comunicacao_multipla_mpi
