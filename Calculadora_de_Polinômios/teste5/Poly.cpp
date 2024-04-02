#include "Poly.h"
#include <algorithm>

// Construtor default
Poly::Poly() : grau(-1), a(nullptr) {}

// Construtor específico
Poly::Poly(int n) : grau(-1), a(nullptr) {
    if (n >= 0) {
        grau = n;
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
            a[i] = 0.0;
    }
}

// Construtor de cópia
Poly::Poly(const Poly& other) : grau(other.grau), a(new double[grau + 1]) {
    for (int i = 0; i <= grau; ++i)
        a[i] = other.a[i];
}

// Construtor de movimento
Poly::Poly(Poly&& other) noexcept : grau(other.grau), a(other.a) {
    other.grau = -1;
    other.a = nullptr;
}

// Construtor que aceita uma lista de inicializadores para inicializar os coeficientes do polinômio
Poly::Poly(std::initializer_list<double> coeffs) : grau(coeffs.size() - 1), a(new double[grau + 1]) {
    std::copy(coeffs.begin(), coeffs.end(), a);
}


// Destrutor
Poly::~Poly() {
    delete[] a;
}

// Operador de atribuição por cópia
Poly& Poly::operator=(const Poly& other) {
    if (this != &other) {
        delete[] a;
        grau = other.grau;
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
            a[i] = other.a[i];
    }
    return *this;
}

// Operador de atribuição por movimento
Poly& Poly::operator=(Poly&& other) noexcept {
    if (this != &other) {
        delete[] a;
        grau = other.grau;
        a = other.a;
        other.grau = -1;
        other.a = nullptr;
    }
    return *this;
}

// Operador de comparação !=
bool Poly::operator!=(const Poly& other) const {
    return !(*this == other); // Usa o operador de comparação ==
}

// Operador de comparação ==
bool Poly::operator==(const Poly& other) const {
    if (this->grau != other.grau) return false; // Verifica se os graus são diferentes

    for (int i = 0; i <= grau; ++i) {
        if (this->getCoef(i) != other.getCoef(i)) return false; // Verifica se os coeficientes são diferentes
    }

    return true; // Se todos os coeficientes são iguais, retorna true
}

// Método de consulta para obter o grau do polinômio
int Poly::getGrau() const {
    return grau;
}

// Método de consulta para obter o i-ésimo coeficiente
double Poly::getCoef(int i) const {
    if (i < 0 || i > grau)
        return 0.0;
    return a[i];
}

// Método para alterar o valor do i-ésimo coeficiente
void Poly::setCoef(int i, double novoCoeficiente) {
    if (i < 0 || i > grau || (i == grau && novoCoeficiente == 0.0))
        return;
    a[i] = novoCoeficiente;
}

// Método para reduzir o grau do polinômio, removendo os termos de maior grau com coeficientes zero
void Poly::reduceDegree() {
    while (grau >= 0 && a[grau] == 0.0) {
        --grau;
    }
    // Realoca o array de coeficientes se necessário
    double* novoArray = new double[grau + 1];
    for (int i = 0; i <= grau; ++i) {
        novoArray[i] = a[i];
    }
    delete[] a;
    a = novoArray;
}



// Operador de inserção
std::ostream& operator<<(std::ostream& os, const Poly& p) {
    os << p.getCoef(p.getGrau()) << "*x^" << p.getGrau();
    for (int i = p.getGrau() - 1; i >= 0; --i) {
        if (p.getCoef(i) != 0.0) {
            os << " + " << p.getCoef(i);
            if (i > 0) {
                os << "*x^" << i;
            }
        }
    }
    return os;
}

// Sobrecarga do operador de negação unário para retornar o negativo de um polinômio
Poly Poly::operator-() const {
    if (grau == -1) return Poly(); // Se o polinômio for vazio, retorna um polinômio vazio
    Poly negativo(*this);
    for (int i = 0; i <= negativo.getGrau(); ++i) {
        negativo.setCoef(i, -negativo.getCoef(i));
    }
    return negativo;
}

// Sobrecarga do operador de adição de polinômios
Poly Poly::operator+(const Poly& other) const {
    int max_grau = std::max(grau, other.grau);
    Poly result(max_grau);

    for (int i = 0; i <= max_grau; ++i) {
        double coef_this = (i <= grau) ? getCoef(i) : 0.0;
        double coef_other = (i <= other.grau) ? other.getCoef(i) : 0.0;
        result.setCoef(i, coef_this + coef_other);
    }

    // Remover termos com coeficiente zero
    result.reduceDegree();

    return result;
}

// Sobrecarga do operador de subtração de polinômios
Poly Poly::operator-(const Poly& other) const {
    int max_grau = std::max(grau, other.grau);
    Poly result(max_grau);

    for (int i = 0; i <= max_grau; ++i) {
        double coef_this = (i <= grau) ? getCoef(i) : 0.0;
        double coef_other = (i <= other.grau) ? other.getCoef(i) : 0.0;
        result.setCoef(i, coef_this - coef_other);
    }

    // Remover termos com coeficiente zero
    result.reduceDegree();

    return result;
}


// Método para verificar se o polinômio é vazio
bool Poly::empty() const {
    return (grau == -1);
}

// Método para verificar se o polinômio é nulo (todos os coeficientes são zero)
bool Poly::isZero() const {
    for (int i = 0; i <= grau; ++i) {
        if (a[i] != 0.0) {
            return false; // Se encontrarmos um coeficiente não zero, o polinômio não é nulo
        }
    }
    return true; // Se todos os coeficientes são zero, o polinômio é nulo
}
