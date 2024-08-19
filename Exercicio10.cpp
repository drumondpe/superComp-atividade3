/*
Sistema de Controle de Estoque Simples: Crie um programa que simule um sistema de controle de estoque para uma loja.
O programa deve permitir ao usuário adicionar itens, remover itens, e visualizar o estoque atual. Os dados devem ser
armazenados em vetores.
*/

#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string nome;
    int quantidade;
};

int main() {
    std::vector<Item> estoque;
    int opcao;

    do {
        std::cout << "1. Adicionar item" << std::endl;
        std::cout << "2. Remover item" << std::endl;
        std::cout << "3. Exibir estoque" << std::endl;
        std::cout << "4. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        if(opcao == 1) {
            Item novoItem;
            std::cout << "Nome do item: ";
            std::cin >> novoItem.nome;
            std::cout << "Quantidade: ";
            std::cin >> novoItem.quantidade;
            estoque.push_back(novoItem);
        } else if(opcao == 2) {
            std::string nome;
            std::cout << "Nome do item a ser removido: ";
            std::cin >> nome;

            for(auto it = estoque.begin(); it != estoque.end(); ++it) {
                if(it->nome == nome) {
                    estoque.erase(it);
                    std::cout << "Item removido." << std::endl;
                    break;
                }
            }
        } else if(opcao == 3) {
            std::cout << "Estoque atual:" << std::endl;
            for(const auto& item : estoque) {
                std::cout << item.nome << ": " << item.quantidade << std::endl;
            }
        }
    } while(opcao != 4);

    return 0;
}
