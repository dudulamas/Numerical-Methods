#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846


using namespace std;


float f(float valor, int opc_formula) { 
	switch(opc_formula) {
		case 1:
			return sin(valor);
		case 2:
			return cos(valor);
		case 3:
			return tan(valor);
		default:
			cout << "\nERRO, HOUVE ALGUM IMPREVISTO COM A FORMULA PASSADA.";
			return -100000;
			break;
	}

	return -100000;
}


float raiz_GaussChebyshev(int k, int n){
	return cos((2*k + 1)*M_PI)/(2*n - 1);
}

void print_separator() {
    cout << "\n\n###################################################################";
    cout << "\n###################################################################";
    cout << "\n###################################################################";
}

