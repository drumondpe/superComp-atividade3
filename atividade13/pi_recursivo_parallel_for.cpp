#include <omp.h>
#include <iostream>
#include <iomanip>
#include <cstdlib> // Para usar atoi

static long num_steps = 1024l * 1024 * 1024 * 2;
long MIN_BLK = 1024 * 1024 * 256;

double sum = 0;

void pi_r(long Nstart, long Nfinish, double step) {
    long i, iblk;
    if (Nfinish - Nstart < MIN_BLK) {
        #pragma omp parallel for reduction(+:sum)
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    } else {
        iblk = Nfinish - Nstart;
        pi_r(Nstart, Nfinish - iblk / 2, step);
        pi_r(Nfinish - iblk / 2, Nfinish, step);
    }
}

int main(int argc, char* argv[]) {
    // Se um valor de MIN_BLK for passado como argumento, ele será usado
    if (argc > 1) {
        MIN_BLK = std::atol(argv[1]);
    }

    long i;
    double step, pi;
    double init_time, final_time;
    step = 1.0 / (double) num_steps;
    init_time = omp_get_wtime();
    pi_r(0, num_steps, step);
    pi = step * sum;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15)
              << pi << " in " << final_time << " secs (MIN_BLK=" << MIN_BLK << ")\n";
}
