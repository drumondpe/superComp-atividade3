#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <omp.h>

int main() {
    int N = 100000; // Número de pontos
    int points_inside_circle = 0;
    unsigned int seed;

    // Inicia a medição do tempo
    double start_time = omp_get_wtime();

    // Paralelização com OpenMP
    #pragma omp parallel private(seed) reduction(+:points_inside_circle)
    {
        seed = time(NULL) ^ omp_get_thread_num(); // Seed única para cada thread
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            // Gera dois números aleatórios entre 0 e 1
            double x = static_cast<double>(rand_r(&seed)) / RAND_MAX;
            double y = static_cast<double>(rand_r(&seed)) / RAND_MAX;

            // Verifica se o ponto (x, y) está dentro do círculo de raio 1
            if (sqrt(x * x + y * y) <= 1.0) {
                points_inside_circle++;
            }
        }
    }

    // Estimação de Pi
    double pi_estimate = 4.0 * points_inside_circle / N;

    // Finaliza a medição do tempo
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Imprime o valor estimado de Pi e o tempo de execução
    std::cout << "Valor estimado de Pi (versão paralela): " << std::setprecision(15) << pi_estimate << std::endl;
    std::cout << "Tempo de execução (versão paralela): " << elapsed_time << " segundos" << std::endl;

    return 0;
}
