#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mochila(int W, const vector<int>& weights, const vector<int>& values, int n) {
    if (n == 0 || W == 0) {
        return 0;
    }

    if (weights[n-1] > W) {
        return mochila(W, weights, values, n-1);
    } else {
        int include_item = values[n-1] + mochila(W - weights[n-1], weights, values, n-1);
        int exclude_item = mochila(W, weights, values, n-1);
        return max(include_item, exclude_item);
    }
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
    
    // Chama a função recursiva para resolver o problema
    int max_value = mochila(W, weights, values, N);
    
    // Exibe o valor máximo que pode ser carregado na mochila
    cout << "Valor máximo: " << max_value << endl;

    return 0;
}
