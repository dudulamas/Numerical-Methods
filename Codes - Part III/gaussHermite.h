#include <stdlib.h>
#include <stdio.h>


float gauss_hermite_2Pontos(int opc_formula){
	float w[2], x[2], I=0;

	w[0] = 0.8862269254;
	w[1] = 0.8862269254;

	x[0] = -1 * 0.7071067811;
	x[1] = 0.7071067811;

	for(int i = 0; i < 2; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}

float gauss_hermite_3Pontos(int opc_formula){
	float w[3], x[3], I=0;

	w[0] = 0.2954089751;
	w[1] = 1.181635900;
	w[2] = 0.2954089751;

	x[0] = -1 * 1.224744871;
	x[1] = 0;
	x[2] = 1.224744871;

	for(int i = 0; i < 3; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;

}

float gauss_hermite_4Pontos(int opc_formula){
	float w[4], x[4], I=0;

	w[0] = 0.08131283544;
	w[1] = 0.8049140900;
	w[2] = 0.8049140900;
	w[3] = 0.08131283544;

	x[0] = -1 * 1.650680123;
	x[1] = -1 * 0.5246476323;
	x[2] = 0.5246476323;
	x[3] = 1.650680123;

	for(int i = 0; i < 4; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}