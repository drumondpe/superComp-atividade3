#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

pair<int, int> heuristic_probabilistic_selection(int W, const vector<int>& weights, const vector<int>& values, int n, double threshold = 0.5) {
    int current_weight = 0;
    int max_value = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        double prob = dis(gen);
        if (prob > threshold && current_weight + weights[i] <= W) {
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

    // Executa a heurística de seleção probabilística 5 vezes
    for (int i = 0; i < 5; i++) {
        auto start = chrono::high_resolution_clock::now();
        pair<int, int> result = heuristic_probabilistic_selection(W, weights, values, N);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        
        cout << "Execução " << i+1 << ": Valor máximo: " << result.first 
             << ", Peso ocupado: " << result.second << " Kg em " << elapsed.count() << " segundos" << endl;
    }

    return 0;
}
