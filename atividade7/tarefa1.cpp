#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

pair<int, int> heuristic_shuffle_fill(int W, vector<int> weights, vector<int> values, int n) {
    // Embaralha os itens
    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0); // Cria um vetor de 0 a n-1
    shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device()()));
    
    int current_weight = 0;
    int max_value = 0;

    for (int i : indices) {
        if (current_weight + weights[i] <= W) {
            current_weight += weights[i];
            max_value += values[i];
        }
    }

    return {max_value, current_weight};
}

int main() {
    int N, W;
    
    // Lê o número de itens e a capacidade da mochila
    cin >> N >> W;
    
    vector<int> weights(N);
    vector<int> values(N);
    
    // Lê os pesos e valores dos itens
    for (int i = 0; i < N; i++) {
        cin >> weights[i] >> values[i];
    }

    // Executa a heurística de embaralhar e preencher a mochila 5 vezes
    for (int i = 0; i < 5; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int, int> result = heuristic_shuffle_fill(W, weights, values, N);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        
        cout << "Execução " << i+1 << ": Valor máximo: " << result.first 
             << ", Peso ocupado: " << result.second << " Kg em " << elapsed.count() << " segundos" << endl;
    }

    return 0;
}
