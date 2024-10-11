#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;
using namespace std::chrono;

bool subconjuntoSomaOtima(const vector<int>& conjunto, int n, int soma) {
    
    
    if (soma == 0) {
        return true;
    }
    
    if (n == 0 || soma < 0) {
        return false;
    }
    
    // exclui o ultimo item e verifica se encontrou com ou sem ele
    return subconjuntoSomaOtima(conjunto, n - 1, soma) || subconjuntoSomaOtima(conjunto, n - 1, soma - conjunto[n - 1]);
}

int main(int argc, char* argv[]) {

    if (argc != 2) {

        cout << "Uso: " << argv[0] << " <arquivo de entrada>" << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);

    if (!arquivo) {

        cout << "Erro ao abrir" << argv[1] << endl;
        return 1;
    }

    // lendo o arquivo
    int n, alvo;
    arquivo >> n >> alvo;
    vector<int> conjunto(n);
    
    for (int i = 0; i < n; ++i) {

        arquivo >> conjunto[i];
    }

    arquivo.close();

    // inicia medicao de tempo
    auto inicio = high_resolution_clock::now();

    // busca exaustiva 
    bool resultado = subconjuntoSomaOtima(conjunto, n, alvo);

    // termina medicao de tempo
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<microseconds>(fim - inicio);

    if (resultado) {

        cout << "Existe um subconjunto cuja soma é " << alvo << endl;
    
    } else {
        
        cout << "Não existe um subconjunto cuja soma seja " << alvo << endl;
    }

    cout << "Tempo de execução: " << duracao.count() << " microssegundos" << endl;

    return 0;
}
