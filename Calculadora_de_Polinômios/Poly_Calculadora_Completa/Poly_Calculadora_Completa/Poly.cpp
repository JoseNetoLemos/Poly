#include "Poly.h"
#include <algorithm>

// Construtor default
Poly::Poly() : grau(-1), a(nullptr) {}

// Construtor espec�fico
Poly::Poly(int n) : grau(-1), a(nullptr) {
    if (n >= 0) {
        grau = n;
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i)
            a[i] = 0.0;
    }
}

// Construtor de c�pia
Poly::Poly(const Poly& other) : grau(other.grau), a(new double[grau + 1]) {
    for (int i = 0; i <= grau; ++i)
        a[i] = other.a[i];
}

// Construtor de movimento
Poly::Poly(Poly&& other) noexcept : grau(other.grau), a(other.a) {
    other.grau = -1;
    other.a = nullptr;
}

// Construtor que aceita uma lista de inicializadores para inicializar os coeficientes do polin�mio
Poly::Poly(std::initializer_list<double> coeffs) : grau(coeffs.size() - 1), a(new double[grau + 1]) {
    std::copy(coeffs.begin(), coeffs.end(), a);
}


// Destrutor
Poly::~Poly() {
    delete[] a;
}

// Operador de atribui��o por c�pia
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

// Operador de atribui��o por movimento
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

// Operador de compara��o !=
bool Poly::operator!=(const Poly& other) const {
    return !(*this == other); // Usa o operador de compara��o ==
}

// Operador de compara��o ==
bool Poly::operator==(const Poly& other) const {
    if (this->grau != other.grau) return false; // Verifica se os graus s�o diferentes

    for (int i = 0; i <= grau; ++i) {
        if (this->getCoef(i) != other.getCoef(i)) return false; // Verifica se os coeficientes s�o diferentes
    }

    return true; // Se todos os coeficientes s�o iguais, retorna true
}

// M�todo de consulta para obter o grau do polin�mio
int Poly::getGrau() const {
    return grau;
}

// M�todo de consulta para obter o i-�simo coeficiente
double Poly::getCoef(int i) const {
    if (i < 0 || i > grau)
        return 0.0;
    return a[i];
}

// M�todo para alterar o valor do i-�simo coeficiente
void Poly::setCoef(int i, double novoCoeficiente) {
    if (i < 0 || i > grau || (i == grau && novoCoeficiente == 0.0))
        return;
    a[i] = novoCoeficiente;
}

// M�todo para reduzir o grau do polin�mio, removendo os termos de maior grau com coeficientes zero
void Poly::reduceDegree() {
    while (grau >= 0 && a[grau] == 0.0) {
        --grau;
    }
    // Realoca o array de coeficientes se necess�rio
    double* novoArray = new double[grau + 1];
    for (int i = 0; i <= grau; ++i) {
        novoArray[i] = a[i];
    }
    delete[] a;
    a = novoArray;
}



// Operador de inser��o
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

// Sobrecarga do operador de nega��o un�rio para retornar o negativo de um polin�mio
Poly Poly::operator-() const {
    if (grau == -1) return Poly(); // Se o polin�mio for vazio, retorna um polin�mio vazio
    Poly negativo(*this);
    for (int i = 0; i <= negativo.getGrau(); ++i) {
        negativo.setCoef(i, -negativo.getCoef(i));
    }
    return negativo;
}

// Sobrecarga do operador de adi��o de polin�mios
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

// Sobrecarga do operador de subtra��o de polin�mios
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





// Sobrecarga do operador de divis�o de polin�mios
std::pair<Poly, Poly> Poly::operator/(const Poly& divisor) const {
    if (divisor.isZero()) {
        std::cerr << "ERRO: Divis�o por um polin�mio nulo.\n";
        return std::make_pair(Poly(), Poly()); // Retorna um par de polin�mios vazios se o divisor for nulo
    }

    if (grau < divisor.getGrau()) {
        // Se o grau do dividendo for menor que o grau do divisor, o resultado � zero
        return std::make_pair(Poly(), *this);
    }

    Poly dividendo(*this); // Cria uma c�pia do dividendo
    Poly quociente(grau - divisor.getGrau()); // Inicializa o quociente com o grau adequado
    Poly resto; // Inicializa o resto como um polin�mio vazio

    // Algoritmo de divis�o de polin�mios
    while (dividendo.getGrau() >= divisor.getGrau()) {
        // Calcula o coeficiente do termo principal do quociente
        double coeficiente_quociente = dividendo.getCoef(dividendo.getGrau()) / divisor.getCoef(divisor.getGrau());

        // Atualiza o quociente
        quociente.setCoef(dividendo.getGrau() - divisor.getGrau(), coeficiente_quociente);

        // Atualiza o dividendo subtraindo o produto do divisor pelo termo principal do quociente
        Poly produto = divisor * quociente.getCoef(dividendo.getGrau() - divisor.getGrau()); // Produto entre o divisor e o termo principal do quociente
        dividendo = dividendo - produto; // Atualiza o dividendo subtraindo o produto calculado

        // Remove os termos com coeficiente zero do dividendo
        dividendo.reduceDegree();
    }

    resto = dividendo; // O resto � o dividendo ap�s a divis�o

    return std::make_pair(quociente, resto);
}




// M�todo para verificar se o polin�mio � vazio
bool Poly::empty() const {
    return (grau == -1);
}

// M�todo para verificar se o polin�mio � nulo (todos os coeficientes s�o zero)
bool Poly::isZero() const {
    for (int i = 0; i <= grau; ++i) {
        if (a[i] != 0.0) {
            return false; // Se encontrarmos um coeficiente n�o zero, o polin�mio n�o � nulo
        }
    }
    return true; // Se todos os coeficientes s�o zero, o polin�mio � nulo
}



Poly Poly::operator*(const Poly& other) const {
    if (empty() || other.empty()) {
        return Poly(); // Se um dos polin�mios for vazio, o resultado � vazio
    }

    int max_grau = grau + other.grau; // Grau m�ximo do polin�mio resultante
    Poly result(max_grau); // Polin�mio resultante inicializado com o grau m�ximo

    // Loop para multiplica��o dos termos
    for (int i = 0; i <= grau; ++i) {
        for (int j = 0; j <= other.grau; ++j) {
            int grau_resultante = i + j; // Grau do termo resultante
            double coeficiente_resultante = result.getCoef(grau_resultante) + (getCoef(i) * other.getCoef(j)); // Coeficiente do termo resultante

            // Atualiza��o do coeficiente no polin�mio resultante
            result.setCoef(grau_resultante, coeficiente_resultante);
        }
    }

    return result;
}


void Poly::ler(const std::string& arquivo) {
    std::ifstream arquivoEntrada(arquivo);
    if (arquivoEntrada.is_open()) {
        // L�gica para ler os coeficientes do arquivo e inicializar o polin�mio
        arquivoEntrada.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
    }
}


void Poly::recriar(int novoGrau) {
    // Libera a mem�ria do array atual
    delete[] a;

    // Define o novo grau
    grau = novoGrau;

    // Aloca mem�ria para o novo array de coeficientes
    a = new double[grau + 1];

    // Inicializa os coeficientes com zero
    for (int i = 0; i <= grau; ++i) {
        a[i] = 0.0;
    }
}


// Fun��o global para calcular a pot�ncia de um n�mero
double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}



// Implementa��o da fun��o power
double Poly::power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}
// Implementa��o dos outros membros da classe...


std::istream& operator>>(std::istream& is, Poly& p) {
    int grau;
    is >> grau;
    p.recriar(grau); // Redefine o polin�mio com o novo grau lido
    for (int i = grau; i >= 0; --i) {
        double coeficiente;
        std::cout << "Coeficiente para x^" << i << ": ";
        is >> coeficiente;
        p.setCoef(i, coeficiente); // Define o coeficiente do termo i do polin�mio
    }
    return is;
}


void Poly::salvar(const std::string& arquivo) const {
    std::ofstream arquivoSaida(arquivo);
    if (arquivoSaida.is_open()) {
        arquivoSaida << this->grau << std::endl;
        for (int i = 0; i <= this->grau; ++i) {
            arquivoSaida << this->getCoef(i) << " "; // Use getCoef(i) para obter o coeficiente do termo i
        }
        arquivoSaida.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar: " << arquivo << std::endl;
    }
}



double Poly::operator()(double x) const {
    double result = 0.0;
    double x_power = 1.0; // Inicializa x^0
    for (int i = 0; i <= grau; ++i) {
        result += getCoef(i) * x_power;
        x_power *= x; // Atualiza x_power para a pr�xima pot�ncia de x
    }
    return result;
}
