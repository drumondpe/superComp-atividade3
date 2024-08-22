/*
Contagem de Letras em uma String: Escreva um programa que peça ao usuário para inserir uma string e exiba o número de
caracteres na string.
*/

#include <iostream>
#include <string>

int main() {
    std::string texto;

    std::cout << "Insira uma string: ";
    std::getline(std::cin, texto);

    std::cout << "Número de caracteres: " << texto.length() << std::endl;

    return 0;
}
