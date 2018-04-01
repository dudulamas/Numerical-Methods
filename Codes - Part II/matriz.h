#ifndef MATRIZ_H
#define MATRIZ_H

//Imported classes from the project.

//Imported libraries.
#include <iostream>
#include <iomanip>
#include <vector>

class Matriz {
private:
    int rowsize, colsize;
    std::vector<std::vector<double> > values;
public:
    Matriz(int linhas, int colunas, double fill);
    Matriz(int linhas, int colunas, std::vector<double> v);
    //Matriz(int linhas, int colunas, float[] inputs);
    static Matriz MatrizIdentidade(int tamanho);

    Matriz  operator+ (Matriz& m) const;
    Matriz  operator- (Matriz& m) const;
    Matriz& operator+=(Matriz& m);
    Matriz& operator-=(Matriz& m);

    std::vector<double>& operator[](int index);

    int getQuantLinhas() const;
    int getQuantColunas() const;
    void print() const;
};

#endif /* MATRIZ_H */

