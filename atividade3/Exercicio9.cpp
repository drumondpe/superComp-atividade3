/*
Manipulação de Strings: Palíndromo: Escreva um programa que verifique se uma string inserida pelo usuário é um
palíndromo (lê-se da mesma forma de trás para frente).
*/

#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string texto;

    std::cout << "Insira uma string: ";
    std::getline(std::cin, texto);

    std::string invertido = texto;
    std::reverse(invertido.begin(), invertido.end());

    if(texto == invertido) {
        std::cout << "A string é um palíndromo." << std::endl;
    } else {
        std::cout << "A string não é um palíndromo." << std::endl;
    }

    return 0;
}
