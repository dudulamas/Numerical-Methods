
#define M_PI 3.14159265358979323846


float gauss_chebyshev(int opc_formula, int n){
	float w, I=0;

	w = M_PI / (n+1);

	for(int i = 0; i < 2; i++){
		I += f(raiz_GaussChebyshev(i, n), opc_formula);
	}

	return w*I;
}
