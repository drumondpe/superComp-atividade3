#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <cstdlib>
#include <iostream>

// Definindo o functor Saxpy
struct saxpy
{
    int a;  // Constante
    saxpy(int a_) : a(a_) {}  // Construtor

    // Operador sobrecarregado para a operação a*x + y
    __host__ __device__
    double operator()(const int& x, const int& y) const {
        return a * x + y;
    }
};

int main()
{
    // Tamanho dos vetores
    int N = 1000;

    // Inicializar vetores de entrada no host (CPU)
    thrust::host_vector<int> h_a(N);
    thrust::host_vector<int> h_b(N);

    // Preencher os vetores com números aleatórios
    for (int i = 0; i < N; i++) {
        h_a[i] = rand() % 100;
        h_b[i] = rand() % 100;
    }

    // Copiar vetores para a GPU (device)
    thrust::device_vector<int> d_a = h_a;
    thrust::device_vector<int> d_b = h_b;
    thrust::device_vector<double> d_c(N);  // Vetor de saída

    // Definir o valor da constante 'a'
    int a = 2;

    // Aplicar Saxpy (a*x + y) usando a função transform e o functor saxpy
    thrust::transform(d_a.begin(), d_a.end(), d_b.begin(), d_c.begin(), saxpy(a));

    // Copiar o resultado de volta para o host (CPU)
    thrust::host_vector<double> h_c = d_c;

    // Exibir os primeiros 10 resultados
    std::cout << "Resultados (primeiros 10 elementos): " << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "a * " << h_a[i] << " + " << h_b[i] << " = " << h_c[i] << std::endl;
    }

    return 0;
}
