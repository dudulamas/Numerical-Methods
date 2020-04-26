#include <iostream>
#include <stdio.h>

using namespace std;


float gauss_laguerre_2Pontos(int opc_formula){
	float w[2], x[2], I=0;

	w[0] = 0.8535533905;
	w[1] = 0.1464466094;

	x[0] = 0.5857864376;
	x[1] = 3.414213562;

	for(int i = 0; i < 2; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}


float gauss_laguerre_3Pontos(int opc_formula){
	float w[3], x[3], I=0;

	w[0] = 0.7110930099;
	w[1] = 0.2785177335;
	w[2] = 0.01038925650;

	x[0] = 0.4157745567;
	x[1] = 2.294280360;
	x[2] = 6.289945082;

	for(int i = 0; i < 3; i++){
		I += w[i] * f(x[i], opc_formula);
		cout << "\n" << I;
	}

	return I;
}


float gauss_laguerre_4Pontos(int opc_formula){
	float w[4], x[4], I=0;

	w[0] = 0.6031541043;
	w[1] = 0.3574186924;
	w[2] = 0.03888790851;
	w[3] = 0.0005392947055 ;

	x[0] = 0.3225476896;
	x[1] = 1.745761101;
	x[2] = 4.536620296;
	x[3] = 9.395070912;

	for(int i = 0; i < 4; i++){
		I += w[i] * f(x[i], opc_formula);
	}

	return I;
}