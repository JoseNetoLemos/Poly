#ifndef POLY_H
#define POLY_H
#include <iostream> // Inclua a biblioteca iostream aqui


class Poly {
private:
    int grau;       // Grau do polinomio
    double *a;      // Coeficientes

public:

    // Declaração da função imprimir
    friend void imprimir(const std::string& Nome, const Poly& P);
    // Construtores
    Poly();
    explicit Poly(int n);
    Poly(const Poly& other);
    Poly(Poly&& other) noexcept;

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
    double operator[](int i) const {
        if (i < 0 || i > grau)
            return 0.0;
        return a[i];
    }

    // ---------------------------------------- TESTE 2 ----------------------------------- //

 // Função power modificada para const
    double power(double base, int exponent) const {
        double result = 1.0;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }


    // Método para redefinir o grau e os coeficientes do polinômio
    void recriar(int novoGrau) {
        delete[] a;
        if (novoGrau < 0) {
            grau = -1;
            a = nullptr;
        } else {
            grau = novoGrau;
            a = new double[grau + 1];
            a[grau] = 1.0;
            for (int i = 0; i < grau; ++i)
                a[i] = 0.0;
        }
    }

    // Operador de comparação de igualdade
    bool operator==(const Poly& other) const {
        if (grau != other.grau)
            return false;
        for (int i = 0; i <= grau; ++i) {
            if (a[i] != other.a[i])
                return false;
        }
        return true;
    }

    // Operador de comparação de desigualdade
    bool operator!=(const Poly& other) const {
        return !(*this == other);
    }

    // Método para verificar se o polinômio é vazio
    bool empty() const {
        return grau < 0;
    }

    // Método para verificar se o polinômio é de grau zero e seu único coeficiente é zero
    bool isZero() const {
        return grau == 0 && a[0] == 0.0;
    }

    // Método para obter o valor do polinômio para um dado valor real de x
    double getValor(double x) const {
        if (empty())
            return 0.0;
        double valor = 0.0;
        for (int i = 0; i <= grau; ++i)
            valor += a[i] * power(x, i);
        return valor;
    }

    // Sobrecarga do operador de chamada de função para calcular o valor do polinômio para um dado valor real de x
    double operator()(double x) const {
        return getValor(x);
    }

};

// Declaração do operador de inserção
std::ostream& operator<<(std::ostream& os, const Poly& p);



#endif // POLY_H
