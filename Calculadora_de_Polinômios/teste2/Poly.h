#ifndef POLY_H
#define POLY_H
#include <iostream> // Inclua a biblioteca iostream aqui


class Poly {
private:
    int grau;       // Grau do polinomio
    double *a;      // Coeficientes

public:

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
    double operator[](int i) const {
        if (i < 0 || i > grau)
            return 0.0;
        return a[i];
    }

    // ---------------------------------------- TESTE 2 ----------------------------------- //

 // Fun��o power modificada para const
    double power(double base, int exponent) const {
        double result = 1.0;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }


    // M�todo para redefinir o grau e os coeficientes do polin�mio
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

    // Operador de compara��o de igualdade
    bool operator==(const Poly& other) const {
        if (grau != other.grau)
            return false;
        for (int i = 0; i <= grau; ++i) {
            if (a[i] != other.a[i])
                return false;
        }
        return true;
    }

    // Operador de compara��o de desigualdade
    bool operator!=(const Poly& other) const {
        return !(*this == other);
    }

    // M�todo para verificar se o polin�mio � vazio
    bool empty() const {
        return grau < 0;
    }

    // M�todo para verificar se o polin�mio � de grau zero e seu �nico coeficiente � zero
    bool isZero() const {
        return grau == 0 && a[0] == 0.0;
    }

    // M�todo para obter o valor do polin�mio para um dado valor real de x
    double getValor(double x) const {
        if (empty())
            return 0.0;
        double valor = 0.0;
        for (int i = 0; i <= grau; ++i)
            valor += a[i] * power(x, i);
        return valor;
    }

    // Sobrecarga do operador de chamada de fun��o para calcular o valor do polin�mio para um dado valor real de x
    double operator()(double x) const {
        return getValor(x);
    }

};

// Declara��o do operador de inser��o
std::ostream& operator<<(std::ostream& os, const Poly& p);



#endif // POLY_H
