#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // Para a função max()

using namespace std;

class Poly {
private:
    int grau;               // Grau do polinomio
    double *a;              // Coeficientes
    vector<double> coeficientes;

public:
    void definirGrau(int grau);
    friend istream& operator>>(istream& in, Poly& polinomio);

    // Declaração da função imprimir
    friend void imprimir(const std::string& Nome, const Poly& P);

    // Construtores
    Poly();
    Poly(const Poly& other);
    Poly(Poly&& other) noexcept;


    // Construtor que aceita um inteiro para inicializar o polinômio com um grau específico
    Poly(int _grau);
     // Construtor que aceita uma lista de inicializadores para inicializar os coeficientes do polinômio
    Poly(std::initializer_list<double> coeffs);

    // Destrutor
    ~Poly();

    // Operadores de atribuição
    Poly& operator=(const Poly& other);
    Poly& operator=(Poly&& other) noexcept;

    // Métodos de consulta
    int getGrau() const;
    double getCoef(int i) const;

    // Método para alterar o valor do i-ésimo coeficiente
    void setCoef(int i, double novoCoeficiente);

    // Operador de indexação
    double operator[](int i) const;

    // ---------------------------------------- TESTE 2 ----------------------------------- //

    // Função power modificada para const
    double power(double base, int exponent) const;

    // Método para redefinir o grau e os coeficientes do polinômio


    // Operadores de comparação
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;

    // Método para verificar se o polinômio é vazio
    bool empty() const;

    // Método para verificar se o polinômio é de grau zero e seu único coeficiente é zero
    bool isZero() const;

    // Método para obter o valor do polinômio para um dado valor real de x
    double getValor(double x) const;

    // Sobrecarga do operador de chamada de função para calcular o valor do polinômio para um dado valor real de x
    double operator()(double x);

    // Sobrecarga do operador de negação unário para retornar o negativo de um polinômio
    Poly operator-() const;

    // Sobrecarga do operador de adição binário para fazer a soma de dois polinômios
    Poly operator+(const Poly& other) const;

    // Sobrecarga do operador de subtração binário para fazer a subtração de dois polinômios
    Poly operator-(const Poly& other) const;

    Poly operator*(const Poly& other) const;

    std::pair<Poly, Poly> operator/(const Poly& divisor) const;

    // Declaração do operador de inserção
    friend std::ostream& operator<<(std::ostream& os, const Poly& p);
    friend std::istream& operator>>(std::istream& is, Poly& p);

    // Método para salvar o polinômio em um arquivo
    bool salvar(const std::string& nomeArquivo) const;

    // Adicionando a declaração do método ler
    bool ler(const string& nomeArquivo);

    void recriar(int novoGrau);

    void reduceDegree();

};

#endif // POLY_H
