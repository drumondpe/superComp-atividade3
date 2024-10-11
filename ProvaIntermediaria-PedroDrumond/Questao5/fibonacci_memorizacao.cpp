#include <iostream>
#include <vector>
#include <chrono> 


int fib(int n, std::vector<int>& memo) {

    if (n <= 1) {

        return n; 
    }

    if (memo[n] != -1) {

        return memo[n];
    }

    // calcula e armazena p/ usar dps
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

int main() {
    
    int n;

    std::cout << "Digite o valor de N: ";
    std::cin >> n;
    std::vector<int> memo(n + 1, -1);

    auto start = std::chrono::high_resolution_clock::now();

    int resultado = fib(n, memo);

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;

    std::cout << "Fibonacci de " << n << " é " << resultado << std::endl;
    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;


    return 0;
}
