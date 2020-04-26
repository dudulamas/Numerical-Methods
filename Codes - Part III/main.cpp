#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "gaussChebyshev.h"
#include "gaussHermite.h"
#include "gaussLaguerre.h"

using namespace std;

void menu()
{
	int opc_formulaInt, opc_funcao, pontos;

	do
	{

		cout << "\n1º: Escolha, primeiramente, uma fórmula:\n";
		cout << "1 - sin(x)\n";
		cout << "2 - cos(x)\n";
		cout << "3 - tg(x)\n";
		cout << "0 - Nenhuma delas. Sair\n\n";
		cout << "> ";

		cin >> opc_funcao;

		switch (opc_funcao)
		{
		case 1:
			opc_funcao = 1;
			break;
		case 2:
			opc_funcao = 2;
			break;
		case 3:
			opc_funcao = 3;
			break;
		case 0:
			break;
		default:
			cout << "\nOpção Inválida. Entre novamente.\n\n";
			opc_funcao = -1;
			break;
		}
	} while (opc_funcao == -1 && opc_funcao != 0);

	do
	{

		cout << "\n2º: Escolha agora a Fórmula de Integração:\n";
		cout << "1 - Gaus-Laguerre - 2 a 4 pontos\n";
		cout << "2 - Gauss-Hermite - 2 a 4 pontos\n";
		cout << "3 - Gauss-Chebyshev\n";
		cout << "0 - Nenhuma delas. Sair\n\n";
		cout << "> ";

		cin >> opc_formulaInt;

		switch (opc_formulaInt)
		{
		case 0:
			break;
		case 1:
			do {
				
				cout << "\nEntre com a quantidade de pontos:\n";
				cout << "1 - 2 Pontos\n";
				cout << "2 - 3 Pontos\n";
				cout << "3 - 4 Pontos\n";
				cout << "0 - Nenhuma delas. Sair\n\n> ";

				cin >> pontos;

				switch (pontos)
				{
				case 1:
					cout << "\n\nResolutado Final =  " << gauss_laguerre_2Pontos(opc_funcao) << "\n";
					break;

				case 2:
					cout << "\n\nResolutado Final =  " << gauss_laguerre_3Pontos(opc_funcao) << "\n";
					break;

				case 3:
					cout << "\n\nResolutado Final =  " << gauss_laguerre_4Pontos(opc_funcao) << "\n";
					break;

				case 0:
					break;
				default:
					cout << "\n\nOpção Inválida. Entre novamente.\n\n.";
					pontos = -1;
					break;
				}
			} while (pontos == -1 && pontos != 0);
			break;

		case 2:
			do {
				cout << "\nEntre com a quantidade de pontos:\n";
				cout << "1 - 2 Pontos\n";
				cout << "2 - 3 Pontos\n";
				cout << "3 - 4 Pontos\n";
				cout << "0 - Nenhuma delas. Sair\n\n> ";

				cin >> pontos;

				switch (pontos)	{
					case 0:
						break;
					case 1:
						cout << "\n>> Resolutado Final =  " << gauss_hermite_2Pontos(opc_funcao) << "\n";
						break;

					case 2:
						cout << "\n>> Resolutado Final =  " << gauss_hermite_3Pontos(opc_funcao) << "\n";
						break;

					case 3:
						cout << "\n>> Resolutado Final =  " << gauss_hermite_4Pontos(opc_funcao) << "\n";
						break;

					default:
						cout << "\n\nOpção Inválida. Entre novamente.\n\n.";
						pontos = -1;
						break;
				}
			} 
			while (pontos == -1 && pontos != 0);
			
			break;

		case 3:
			cout << "\nEntre com a quantidade de pontos:\n> ";
			cin >> pontos;
			cout << "\n>> Resolutado Final =  " << gauss_chebyshev(opc_funcao, pontos) << "\n";
			break;

		default:
			cout << "\nOpção Inválida. Entre novamente.\n";
			opc_formulaInt = -1;
			break;
		}
	} 
	while (opc_formulaInt == -1 && opc_formulaInt != 0);
}

int main()
{
	menu();
	return 0;
}