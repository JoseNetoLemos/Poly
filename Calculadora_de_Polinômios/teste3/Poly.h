#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Poly {
private:
    int grau;       // Grau do polinomio
    double *a;      // Coeficientes
    vector<double> coeficientes;

public:
    void definirGrau(int grau);
    friend istream& operator>>(istream& in, Poly& polinomio);

    // Declara��o da fun��o imprimir
    friend void imprimir(const std::string& Nome, const Poly& P);

    // Construtores
    Poly();
    explicit Poly(int n);
    Poly(const Poly& other);
    Poly(Poly&& other) noexcept;

    // Destrutor
    ~Poly();

    // Operadores de atribui��o
    Poly& operator=(const Poly& other);
    Poly& operator=(Poly&& other) noexcept;

    // M�todos de consulta
    int getGrau() const;
    double getCoef(int i) const;

    // M�todo para alterar o valor do i-�simo coeficiente
    void setCoef(int i, double novoCoeficiente);

    // Operador de indexa��o
    double operator[](int i) const;

    // ---------------------------------------- TESTE 2 ----------------------------------- //

    // Fun��o power modificada para const
    double power(double base, int exponent) const;

    // M�todo para redefinir o grau e os coeficientes do polin�mio
    void recriar(int novoGrau);

    // Operadores de compara��o
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;

    // M�todo para verificar se o polin�mio � vazio
    bool empty() const;

    // M�todo para verificar se o polin�mio � de grau zero e seu �nico coeficiente � zero
    bool isZero() const;

    // M�todo para obter o valor do polin�mio para um dado valor real de x
    double getValor(double x) const;

    // Sobrecarga do operador de chamada de fun��o para calcular o valor do polin�mio para um dado valor real de x
    double operator()(double x);

    // Declara��o do operador de inser��o
    friend std::ostream& operator<<(std::ostream& os, const Poly& p);
    friend std::istream& operator>>(std::istream& is, Poly& p);

    // M�todo para salvar o polin�mio em um arquivo
    bool salvar(const std::string& nomeArquivo) const;
};

#endif // POLY_H
