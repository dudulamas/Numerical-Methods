//Class header file.
#include "matriz.h"

Matriz::Matriz(int rows, int columns, double fill)
: rowsize(rows), colsize(columns), values(rows, std::vector<double>(columns, fill)) {

}

Matriz::Matriz(int rows, int columns, std::vector<double> v)
: rowsize(rows), colsize(columns), values(rows, std::vector<double>(columns, 0.0)) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            this->values[i][j] = v[j + columns * i];
        }
    }
}

Matriz Matriz::MatrizIdentidade(int tamanho) {
    Matriz m = Matriz(tamanho, tamanho, 0.0);

    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            if(i == j) {
                m[i][j] = 1.0;
            } else {
                m[i][j] = 0.0;
            }
        }
    }

    return m;
}

Matriz  Matriz::operator+ (Matriz& m) const {
    Matriz n = *this;
    n += m;
    return n;
}

Matriz  Matriz::operator- (Matriz& m) const {
    Matriz n = *this;
    n -= m;
    return n;
}

Matriz& Matriz::operator+=(Matriz& m) {
    for(int i = 0; i < this->rowsize; i++) {
        for(int j = 0; j < this->colsize; j++) {
            this->values[i][j] += m[i][j];
        }
    }
}

Matriz& Matriz::operator-=(Matriz& m) {
    for(int i = 0; i < this->rowsize; i++) {
        for(int j = 0; j < this->colsize; j++) {
            this->values[i][j] -= m[i][j];
        }
    }
}

std::vector<double>& Matriz::operator[](int index) {
    return this->values[index];
}

int Matriz::getQuantLinhas() const {
    return this->rowsize;
}

int Matriz::getQuantColunas() const {
    return this->colsize;
}

void Matriz::print() const {
    std::cout << "Matriz:" << std::endl;

    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    for(int i = 0; i < this->rowsize; i++) {
        std::cout << "[";

        for(int j = 0; j < this->colsize - 1; j++) {
            std::cout << this->values[i][j] << ", ";
        }

        std::cout << this->values[i][this->colsize - 1] << "]" << std::endl;
    }

    std::cout << std::endl;
}
