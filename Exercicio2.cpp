/*
Calculadora Simples: Crie um programa que peça ao usuário para inserir dois números e uma operação (adição, subtração,
multiplicação ou divisão). O programa deve exibir o resultado da operação.
*/

#include <iostream>

int main() {
    double num1, num2;
    char operacao;

    std::cout << "Insira o primeiro número: ";
    std::cin >> num1;
    std::cout << "Insira a operação (+, -, *, /): ";
    std::cin >> operacao;
    std::cout << "Insira o segundo número: ";
    std::cin >> num2;

    switch(operacao) {
        case '+':
            std::cout << "Resultado: " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << "Resultado: " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << "Resultado: " << num1 * num2 << std::endl;
            break;
        case '/':
            if(num2 != 0)
                std::cout << "Resultado: " << num1 / num2 << std::endl;
            else
                std::cout << "Erro: Divisão por zero!" << std::endl;
            break;
        default:
            std::cout << "Operação inválida!" << std::endl;
    }

    return 0;
}
