/*
Exercício: - Implemente uma função que inicializa um vetor com valores específicos 
e realiza operações matemáticas básicas, como multiplicação por um escalar. 
- Crie uma classe Vector que encapsule a lógica de manipulação de vetores, incluindo 
métodos para adicionar, remover e acessar elementos. Garanta que a classe seja eficiente 
usando alocação dinâmica e funções inline.
*/

#include <iostream>

class Vector {
public:
    // Construtor que inicializa o vetor com um tamanho específico
    Vector(int tamanho) : tam(tamanho), capacidade(tamanho) {
        dados = new int[capacidade];
    }

    // Destrutor para liberar a memória alocada dinamicamente
    ~Vector() {
        delete[] dados;
    }

    void inicializa(int valor) {
        for (int i = 0; i < tam; ++i) {
            dados[i] = valor;
        }
    }

    int get(int index) const {
        if (index >= 0 && index < tam) {
            return dados[index];
        }
        std::cerr << "Índice fora dos limites" << std::endl;
        return -1; // Valor de erro
    }

    void set(int index, int valor) {
        if (index >= 0 && index < tam) {
            dados[index] = valor;
        } else {
            std::cerr << "Índice fora dos limites" << std::endl;
        }
    }

    void inserir(int index, int valor) {
        if (index >= 0 && index <= tam) {
            if (tam == capacidade) {
                redimensiona(capacidade * 2); // Redimensiona a capacidade se necessário
            }
            for (int i = tam; i > index; --i) {
                dados[i] = dados[i - 1];
            }
            dados[index] = valor;
            ++tam;
        } else {
            std::cerr << "Índice fora dos limites" << std::endl;
        }
    }

    void remover(int index) {
        if (index >= 0 && index < tam) {
            for (int i = index; i < tam - 1; ++i) {
                dados[i] = dados[i + 1];
            }
            --tam;
        } else {
            std::cerr << "Índice fora dos limites" << std::endl;
        }
    }

    void imprime() const {
        for (int i = 0; i < tam; ++i) {
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int* dados;       
    int tam;          
    int capacidade;   

    // Redimensiona o vetor para uma nova capacidade
    void redimensiona(int novaCapacidade) {
        int* novosDados = new int[novaCapacidade];
        for (int i = 0; i < tam; ++i) {
            novosDados[i] = dados[i];
        }
        delete[] dados;
        dados = novosDados;
        capacidade = novaCapacidade;
    }
};

int main() {
    Vector vec(5);
    vec.inicializa(0);
    vec.imprime();

    // Testando a função de set
    vec.set(2, 10);
    vec.imprime();

    // Inserindo um novo valor
    vec.inserir(2, 20);
    vec.imprime();

    // Removendo um valor
    vec.remover(3);
    vec.imprime();

    return 0;
}
