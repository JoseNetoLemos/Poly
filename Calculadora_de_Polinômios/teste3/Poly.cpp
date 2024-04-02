#include "Poly.h" // Inclua o arquivo de cabeçalho Poly.h

#include <iostream> // Adicione esta linha
#include <fstream>

// Construtor default
Poly::Poly() : grau(-1), a(nullptr) {}

// Construtor específico
Poly::Poly(int n) : grau(-1), a(nullptr) {
    if (n >= 0) {
        grau = n;
        a = new double[grau + 1];
        a[grau] = 1.0;  // Coeficiente do termo de maior grau
        for (int i = 0; i < grau; ++i)
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

// Definição do operador de inserção
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



std::istream& operator>>(std::istream& in, Poly& polinomio) {
    for (int i = polinomio.getGrau(); i >= 0; --i) {
        std::cout << "x^" << i << ": ";
        double coeficiente;
        in >> coeficiente;
        polinomio.setCoef(i, coeficiente);
    }
    return in;
}

bool Poly::salvar(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false; // Falha ao abrir o arquivo
    }

    arquivo << "POLY " << getGrau() << std::endl;
    for (int i = getGrau(); i >= 0; --i) {
        arquivo << getCoef(i) << " ";
    }
    arquivo << std::endl;

    arquivo.close();
    return true;
}
