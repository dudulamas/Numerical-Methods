#include <stdio.h>
#include <iostream>
#include <math.h>
#include <bits/stdc++.h>

#define N 4
using namespace std;

void imprime_matriz(int tamanho, float** matriz){
    for(int linha=0; linha<tamanho; linha++){
        for(int coluna=0; coluna < tamanho; coluna++)
            printf("%f ", matriz[linha][coluna]);
        printf("\n");
    }
}

void imprime_matriz_em_modulo(int tamanho, float** matriz){
    for(int linha=0; linha<tamanho; linha++){
        for(int coluna=0; coluna < tamanho; coluna++)
            printf("%f ", fabs(matriz[linha][coluna]));
        printf("\n");
    }
}

void imprime_vetor(int tamanho, float* vetor){
    for(int i=0; i<tamanho; i++)
        printf("%f ", vetor[i]);
    printf("\n");
}

void imprime_vetor_em_modulo(int tamanho, float* vetor){
    for(int i=0; i<tamanho; i++)
        printf("%f ", fabs(vetor[i]));
    printf("\n");
}

//troca a posicao de 2 elementos do vetor
float* modifica_vetor(int posicao_1, int posicao_2, float* vetor){

    float aux = vetor[posicao_1];
    vetor[posicao_1] = vetor[posicao_2];
    vetor[posicao_2] = aux;

    return vetor;
}

//Pivotacao parcial
//troca a posicao de 2 linhas do vetor
//linha 1 = linha do pivo
//linha 2 = linha do maior elemento a ser zerado na mesma coluna do pivo, em modulo
float** modifica_matriz(int n, int posicao_pivo, float** matriz, int *count){
    int quantidade_elementos_para_zerar = n - posicao_pivo - 1;
    float maior = 0;
    int linha_elemento_maior;
    for(int j=1; j<= quantidade_elementos_para_zerar; j++){
        if(maior < fabs(matriz[posicao_pivo+j][posicao_pivo])){
            maior = matriz[posicao_pivo+j][posicao_pivo];
            linha_elemento_maior = j;
        }
    }

    *count = *count + 5;

    float aux;
    for(int k=0; k<n; k++){
        aux = matriz[linha_elemento_maior][k];
        matriz[linha_elemento_maior][k] = matriz[posicao_pivo][k];
        matriz[posicao_pivo][k] = aux;
    }

    *count = *count + 3;

    return matriz;
}

float** calcula_L(int n, float* coeficientes, int *count){

    int aux = 0;
    *count = *count + 1;

    float **L = (float**)malloc(n * sizeof(float*));
    for (int i=0; i<n; i++)
        L[i] = (float*) malloc(n * sizeof(float));


    for(int j=0; j<n; j++){
        for(int i=0; i<n; i++){
            if(i == j)
                L[i][j] = 1;
            if(i<j)
                L[i][j] = 0;
            if(i>j){
                L[i][j] = coeficientes[aux];
                aux++;
            }
            *count = *count + 1;
        }
    }

    return L;
}

float*** calcula_LU(int n, float** U, int *count){

    float pivo, m;
    float* coeficientes = (float*)malloc((pow(n, 2)-n)/2 * sizeof(float));
    int aux = 0;

    for(int i=0; i<n-1; i++){
        pivo = U[i][i];
        int quantidade_elementos_para_zerar = n - i - 1; *count = *count + 1;
        if(pivo != 0){
            for(int j=1; j<=quantidade_elementos_para_zerar; j++){
                //m: coeficiente (sera usado na matriz L)
                m = U[i+j][i] / pivo;
                coeficientes[aux] = m;
                aux++;
                *count = *count + 3;
                for(int k=0; k<n; k++){
                    U[i+j][k] -= m * U[i][k];
                    *count = *count + 2;
                }
            }
        }
        else if(pivo == 0){
            U = modifica_matriz(n, i, U, count);
            for(int j=1; j<=quantidade_elementos_para_zerar; j++){
                //m: coeficiente (sera usado na matriz L)
                pivo = U[i][i];
                m = U[i+j][i] / pivo;
                coeficientes[aux] = m;
                aux++;

                *count = *count + 4;

                for(int k=0; k<n; k++){
                    U[i+j][k] -= m * U[i][k];
                    *count = *count + 1;
                }
            }
        }
    }

    float** L = calcula_L(n, coeficientes, count);
    float*** LU = (float***)malloc(2 * sizeof(float**));
    LU[0] = L;
    LU[1] = U;

    return LU;
}

float* calcula_y(int n, float** L, float* b, int *count){
    float* y = (float*)malloc(n * sizeof(float));

    for(int i=0; i<n; i++){
        y[i] = 0;
        for(int j=0; j<=i; j++){
            if(i!=j){
                y[i] -= y[j] * L[i][j];
            }
            else{
                y[i] += b[i];
                y[i] /= L[i][i];
            }
            *count = *count + 1;
        }
    }
    return y;
}

float* calcula_x(int n, float** U, float* y, int *count){
    float* x = (float*)malloc(n * sizeof(float));

    for(int i=n-1; i>-1; i--){
        x[i] = 0;
        for(int j=n-1; j>=i; j--){
            if(i!=j){
                x[i] -= x[j] * U[i][j];
            }
            else{
                x[i] += y[i];
                x[i] /= U[i][i];
            }
            *count = *count + 1;
        }
        *count = *count + 1;
    }
    return x;
}

//ENTRADA: matriz triangular e tamanho da matriz
//SAIDA: produto dos elementos da diagonal principal / determinante
float determinante(int tamanho, float** matriz){
    float determinante = 1;
    for(int i=0; i<tamanho; i++)
        for(int j=0; j<tamanho; j++)
            if(i==j)
                determinante *= matriz[i][j];

    return determinante;
}

//retorna true se o sistema for possivel e determinado
bool testa_sistema(float D){
    bool sistema_possivel_determinado = false;

    if(D!=0){
        sistema_possivel_determinado = true;
        //printf("Sistema possivel e determinado");
    } else
        //printf("Sistema possivel e indeterminado ou impossivel");

    return sistema_possivel_determinado;
}

double determinant(float **a,int n)
{
   int i,j,j1,j2;
   double det = 0;
   float **m = NULL;

   if (n < 1) { /* Error */

   } else if (n == 1) { /* Shouldn't get used */
      det = a[0][0];
   } else if (n == 2) {
      det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
   } else {
      det = 0;
      for (j1=0;j1<n;j1++) {
         m = (float**) malloc((n-1)*sizeof(float *));
         for (i=0;i<n-1;i++)
            m[i] = (float*) malloc((n-1)*sizeof(float));
         for (i=1;i<n;i++) {
            j2 = 0;
            for (j=0;j<n;j++) {
               if (j == j1)
                  continue;
               m[i-1][j2] = a[i][j];
               j2++;
            }
         }
         det += pow(-1.0,1.0+j1+1.0) * a[0][j1] * determinant(m,n-1);
         for (i=0;i<n-1;i++)
            free(m[i]);
         free(m);
      }
   }
   return det;
}
