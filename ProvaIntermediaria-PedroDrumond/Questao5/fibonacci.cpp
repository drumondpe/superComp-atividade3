#include <iostream>
#include <chrono> 

int fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

int main() {
    int n = 50; // Valor de n para calcular Fibonacci

    auto inicio = std::chrono::high_resolution_clock::now();

    int result = fib(n);

    auto fim = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duracao = fim - inicio;

    std::cout << "Fibonacci de " << n << " é " << result << std::endl;
    std::cout << "Tempo de execução: " << duracao.count() << " ms" << std::endl;

    return 0;
}
