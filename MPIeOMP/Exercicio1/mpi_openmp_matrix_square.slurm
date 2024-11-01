#!/bin/bash
#SBATCH --job-name=mpi_openmp_matrix_square
#SBATCH --output=output_mpi_openmp_matrix_square.txt
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4  # Número de threads para OpenMP
#SBATCH --time=00:02:00
#SBATCH --mem=1G

# Executar o programa com MPI e OpenMP
mpirun -np 4 ./mpi_openmp_matrix_square
