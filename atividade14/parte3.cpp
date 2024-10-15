#include <iostream>
#include <random>    // Para usar o std::mt19937 e std::uniform_real_distribution
#include <ctime>     // Para o tempo
#include <cmath>     // Para sqrt()
#include <iomanip>   // Para setprecision()
#include <omp.h>     // Para paralelização com OpenMP

int main() {
    int N = 100000; // Número de pontos
    int points_inside_circle = 0;

    // Inicia a medição do tempo
    double start_time = omp_get_wtime();

    // Paralelização com OpenMP
    #pragma omp parallel reduction(+:points_inside_circle)
    {
        // Cada thread terá seu próprio gerador de números aleatórios
        std::random_device rd; // Seed
        std::mt19937 gen(rd() ^ omp_get_thread_num()); // Mersenne Twister para cada thread
        std::uniform_real_distribution<> dis(0.0, 1.0); // Distribuição entre 0 e 1

        #pragma omp for
        for (int i = 0; i < N; ++i) {
            // Gera dois números aleatórios (x, y) entre 0 e 1
            double x = dis(gen);
            double y = dis(gen);

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
    std::cout << "Valor estimado de Pi (versão melhorada): " << std::setprecision(15) << pi_estimate << std::endl;
    std::cout << "Tempo de execução (versão melhorada): " << elapsed_time << " segundos" << std::endl;

    return 0;
}
