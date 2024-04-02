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
    Poly(int n); // Construtor espec�fico
    Poly(const Poly& other); // Construtor de c�pia
    Poly(Poly&& other) noexcept; // Construtor de movimento
    Poly(std::initializer_list<double> coeffs); // Construtor que aceita uma lista de inicializadores

    ~Poly(); // Destrutor

    Poly& operator=(const Poly& other); // Operador de atribui��o por c�pia
    Poly& operator=(Poly&& other) noexcept; // Operador de atribui��o por movimento

    bool operator!=(const Poly& other) const; // Operador de compara��o !=
    bool operator==(const Poly& other) const; // Operador de compara��o ==

    int getGrau() const; // M�todo de consulta para obter o grau do polin�mio
    double getCoef(int i) const; // M�todo de consulta para obter o i-�simo coeficiente
    void setCoef(int i, double novoCoeficiente); // M�todo para alterar o valor do i-�simo coeficiente
    void reduceDegree(); // M�todo para reduzir o grau do polin�mio

    bool empty() const; // M�todo para verificar se o polin�mio � vazio
    bool isZero() const; // M�todo para verificar se o polin�mio � nulo (todos os coeficientes s�o zero)

    Poly operator-() const; // Sobrecarga do operador de nega��o un�rio
    Poly operator+(const Poly& other) const; // Sobrecarga do operador de adi��o de polin�mios
    Poly operator-(const Poly& other) const; // Sobrecarga do operador de subtra��o de polin�mios
    Poly operator*(const Poly& other) const; // Sobrecarga do operador de multiplica��o de polin�mios
    std::pair<Poly, Poly> operator/(const Poly& divisor) const; // Sobrecarga do operador de divis�o de polin�mios

    double operator()(double x) const; // Operador de chamada de fun��o para calcular o valor do polin�mio para um dado valor de x

    void ler(const std::string& arquivo); // M�todo para ler um polin�mio de um arquivo
    void salvar(const std::string& arquivo) const; // M�todo para salvar um polin�mio em um arquivo

    void recriar(int novoGrau); // Fun��o para recriar o polin�mio com um novo grau

    // Declara��o da fun��o Poly::power(double, int)
    double power(double base, int exponent);
};

std::ostream& operator<<(std::ostream& os, const Poly& p); // Operador de inser��o
std::istream& operator>>(std::istream& is, Poly& p); // Operador de extra��o

#endif // POLY_H
