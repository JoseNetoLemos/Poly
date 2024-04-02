#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <initializer_list>

class Poly {
private:
    int grau;
    double* a;

public:
    Poly(); // Construtor default
    Poly(int n); // Construtor específico
    Poly(const Poly& other); // Construtor de cópia
    Poly(Poly&& other) noexcept; // Construtor de movimento
    Poly(std::initializer_list<double> coeffs); // Construtor que aceita uma lista de inicializadores

    ~Poly(); // Destrutor

    Poly& operator=(const Poly& other); // Operador de atribuição por cópia
    Poly& operator=(Poly&& other) noexcept; // Operador de atribuição por movimento

    bool operator!=(const Poly& other) const; // Operador de comparação !=
    bool operator==(const Poly& other) const; // Operador de comparação ==

    int getGrau() const; // Método de consulta para obter o grau do polinômio
    double getCoef(int i) const; // Método de consulta para obter o i-ésimo coeficiente
    void setCoef(int i, double novoCoeficiente); // Método para alterar o valor do i-ésimo coeficiente
    void reduceDegree(); // Método para reduzir o grau do polinômio

    bool empty() const; // Método para verificar se o polinômio é vazio
    bool isZero() const; // Método para verificar se o polinômio é nulo (todos os coeficientes são zero)

    Poly operator-() const; // Sobrecarga do operador de negação unário
    Poly operator+(const Poly& other) const; // Sobrecarga do operador de adição de polinômios
    Poly operator-(const Poly& other) const; // Sobrecarga do operador de subtração de polinômios
    Poly operator*(const Poly& other) const; // Sobrecarga do operador de multiplicação de polinômios
    std::pair<Poly, Poly> operator/(const Poly& divisor) const; // Sobrecarga do operador de divisão de polinômios

    double operator()(double x) const; // Operador de chamada de função para calcular o valor do polinômio para um dado valor de x

    void ler(const std::string& arquivo); // Método para ler um polinômio de um arquivo
    void salvar(const std::string& arquivo) const; // Método para salvar um polinômio em um arquivo

    void recriar(int novoGrau); // Função para recriar o polinômio com um novo grau

    // Declaração da função Poly::power(double, int)
    double power(double base, int exponent);
};

std::ostream& operator<<(std::ostream& os, const Poly& p); // Operador de inserção
std::istream& operator>>(std::istream& is, Poly& p); // Operador de extração

#endif // POLY_H
