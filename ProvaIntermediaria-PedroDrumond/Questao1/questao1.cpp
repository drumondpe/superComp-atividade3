#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool subconjuntoSoma(const vector<int>& conjunto, int alvo, vector<int>& subconjunto) {

    int soma_atual = 0;
    
    // cópia do conjunto 
    vector<int> conjunto_ordenado = conjunto;
    sort(conjunto_ordenado.rbegin(), conjunto_ordenado.rend()); // ordem decrescente

    for (int numero : conjunto_ordenado) { // percorre

        if (soma_atual + numero <= alvo) { // compara

            soma_atual += numero; // se não exceder o alvo, inclui
            subconjunto.push_back(numero);
        }
    
        if (soma_atual == alvo) {

            return true;
        }
    }

    return false;
}

int main() {

    vector<int> conjunto = {10, 20, 30, 40, 50, 60};
    int alvo = 100;

    vector<int> subconjunto;

    if (subconjuntoSoma(conjunto, alvo, subconjunto)) {

        cout << "Existe um subconjunto! (" << alvo << ")." << endl;
        cout << "Números usados na soma: ";

        for (int numero : subconjunto) {

            cout << numero << " ";
        }

        cout << endl;

    } else {
        
        cout << "Não existe um subconjunto!" << endl;
    }

    return 0;
}
