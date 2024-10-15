#include <iostream>
#include <cstdlib>  // Para rand() e srand()
#include <ctime>    // Para time() e medir o tempo de execução
#include <cmath>    // Para sqrt()
#include <iomanip>  // Para setprecision()

int main() {
    int N = 100000; // Número de pontos
    int points_inside_circle = 0; // Contador para os pontos dentro do círculo
    double x, y;

    // Inicializa o gerador de números aleatórios com uma seed baseada no tempo
    srand(static_cast<unsigned int>(time(0)));

    // Inicia a medição do tempo
    clock_t start_time = clock();

    // Geração dos pontos e cálculo
    for (int i = 0; i < N; ++i) {
        // Gera dois números aleatórios entre 0 e 1
        x = static_cast<double>(rand()) / RAND_MAX;
        y = static_cast<double>(rand()) / RAND_MAX;

        // Verifica se o ponto (x, y) está dentro do círculo de raio 1
        if (sqrt(x * x + y * y) <= 1.0) {
            points_inside_circle++;
        }
    }

    // Estimação de Pi
    double pi_estimate = 4.0 * points_inside_circle / N;

    // Finaliza a medição do tempo
    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprime o valor estimado de Pi e o tempo de execução
    std::cout << "Valor estimado de Pi: " << std::setprecision(15) << pi_estimate << std::endl;
    std::cout << "Tempo de execução: " << elapsed_time << " segundos" << std::endl;

    return 0;
}
