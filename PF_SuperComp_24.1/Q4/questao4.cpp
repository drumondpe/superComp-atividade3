%%writefile gpu.cu
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/random.h>
#include <iostream>
#include <cmath>

// Função para gerar números aleatórios
struct prg
{
    float a, b;

    __host__ __device__
    prg(float _a=0.f, float _b=1.f) : a(_a), b(_b) {};

    __host__ __device__
    float operator()(const unsigned int n) const
    {
        thrust::default_random_engine rng;
        thrust::uniform_real_distribution<float> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

int main() {
    const int N = 1000000; // Tamanho do vetor
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);
    thrust::host_vector<float> h_vec(N);

    // Preencher o vetor com números aleatórios entre 1.0 e 2.0
    thrust::transform(index_sequence_begin,
                      index_sequence_begin + N,
                      h_vec.begin(),
                      prg(1.f, 2.f));

    // Imprime alguns valores do vetor criado para verificação
    std::cout << "Exibindo os primeiros 20 elementos do vetor original:" << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "Elemento original " << i << ": " << h_vec[i] << std::endl;
    }

    // Copiar o vetor do host para o dispositivo
    thrust::device_vector<float> d_vec = h_vec;

    // Calcular a norma L2 do vetor
    float norm = std::sqrt(thrust::transform_reduce(d_vec.begin(), 
                                                    d_vec.end(), 
                                                    thrust::square<float>(), 
                                                    0.0f, 
                                                    thrust::plus<float>()));

    // Imprime a norma calculada
    std::cout << "Norma calculada: " << norm << std::endl;

    // Normalize o vetor dividindo cada elemento pela norma L2
    thrust::transform(d_vec.begin(), d_vec.end(), d_vec.begin(), 
                      [norm] __device__ (float x) { return x / norm; });

    // Imprime alguns valores do vetor normalizado para verificação
    std::cout << "Exibindo os primeiros 20 elementos do vetor normalizado:" << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "Elemento normalizado " << i << ": " << d_vec[i] << std::endl;
    }

    return 0;
}
