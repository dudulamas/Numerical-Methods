#ifndef METHODS_H
#define METHODS_H

#include <math.h>
#include <stdlib.h>
#include "result.h"
#include <cmath>
#include <iostream>

using namespace std;


float functionRocket(double d, double a) {
    return a*d - (d*(log(d)));
}

float functionRocketDerivate(float d, float a) {
    return a-1-log(d);
}

float funcao(float ajuste, float d){
    float value = (ajuste*d) - (d*log(d));
    return value;
}

float derivada(float ajuste, float d){
    float value = ajuste-1-log(d);
    return value;
}



resultBissecaoFakePoint *bisection(float isolamento_a, float isolamento_b, float a, float e, int maxIter){
    //Alocando um espaço de memória para armazenarmos as iteração
    resultBissecaoFakePoint *results = (resultBissecaoFakePoint *) malloc(sizeof(resultBissecaoFakePoint) * maxIter);

    float fa = a * isolamento_a - (isolamento_a * log(isolamento_a));
    float fb = a * isolamento_b - (isolamento_b * log(isolamento_b));

    if( fa * fb > 0 or isnan(fa) or isnan(fb) ){
        cout << "Sem raízes no intervalo: f(a)=" << fa << " |f(b)=" << fb << endl;
        return NULL;
    }

    cout << "f(a)=" << fa << " |f(b)=" << fb << endl;

    float d, fd;
    int contador = 0;

    do {
        struct resultBissecaoFakePoint result;

        d = (isolamento_a + isolamento_b) / 2;
        fd = a * d - (d * log(d));
        fa = funcao(a,isolamento_a);
        fb = funcao(a, isolamento_b);

        cout << "f(a)=" << fa << " |f(b)=" << fb << endl;

        // Armazenando a Iteração Corrente:
        result.round = contador;
        result.i1 = isolamento_a;
        result.i2 = isolamento_b;
        result.f1 = fa;
        result.f2 = fb;
        result.midpoint = d;
        result.fmidpoint = fd;
        result.absolutValueOfInterval = fabs(isolamento_b - isolamento_a);
        result.hasNext = true;

        results[contador] = result;

        //ALTERANDO OS VALORES PARA A PROXIMA ITERACAO
        if(fa * fd > 0)
            isolamento_a = d;
        else
            isolamento_b = d;

        contador++;
    } while ( (fabs(isolamento_b-isolamento_a) > e) and (fabs(fd) > e) and contador < maxIter );

    if(contador < maxIter)
        results[contador].hasNext = false;

    cout << "Imprimindo Resultados " << contador << endl;
    int i = 0;
    while (results[i].hasNext == true) {
        cout << "Round: " << results[i].round << " " << results[i].i1 << " " << results[i].f1 <<
                   " " << results[i].i2 << " " << results[i].f2 << " " << results[i].midpoint <<
                   " " << results[i].fmidpoint << " " << results[i].absolutValueOfInterval << " " << results[i].hasNext << endl;
        i++;
    }

    cout << "FIM \n\n" << endl;

    return results;
}

resultBissecaoFakePoint *fakePoint(float ajuste, double isolamento_a, double isolamento_b, double e1, double e2, int maxIter) {
    float x0 = isolamento_a, x1 = isolamento_b, fx0 = funcao(ajuste,x0), fx1 = funcao(ajuste,x1);

    if (fx0*fx1 > 0 or isnan(fx0) or isnan(fx1)) {
        cout << "Sem raízes no intervalo: f(x0)=" << fx0 << " |f(x1)=" << fx1 << endl;
        return NULL;
    }

    int count = 0;
    float x, fx;
    resultBissecaoFakePoint *results = (resultBissecaoFakePoint *) malloc(sizeof(resultBissecaoFakePoint) * maxIter);

    do {
        struct resultBissecaoFakePoint result;
        x = (x0*fx1 - x1*fx0)/(fx1-fx0);
        fx = funcao(ajuste,x);

        // CAPTURANDO AS ITERACOES:
        result.round = count;
        result.i1 = x0;
        result.i2 = x1;
        result.f1 = funcao(ajuste, x0);
        result.f2 = funcao(ajuste, x1);
        result.midpoint = x;
        result.fmidpoint = fx;
        result.absolutValueOfInterval = fabs(x1-x0);
        result.hasNext = true;
        results[count] = result;

        // TROCANDO OS VALORES PARA A PROXIMA ITERACAO
        if(fx0*fx > 0) {
            x0 = x;
        }
        else {
            x1 = x;
        }

        count++;
    }while((fabs(fx) > e1) and (fabs(x1-x0) > e2) and count < maxIter);

    if(count < maxIter)
        results[count].hasNext = false;


    cout << "Imprimindo Resultados " << endl;
    int i = 0;
    while (results[i].hasNext == true) {
         cout << "Round: " << results[i].round << " " << results[i].i1 << " " << results[i].f1 <<
                    " " << results[i].i2 << " " << results[i].f2 << " " << results[i].midpoint <<
                    " " << results[i].fmidpoint << " " << results[i].absolutValueOfInterval << endl;
         i++;
    }
    cout << "FIM \n\n" << endl;


    return results;

}

resultNewtonRaphson *newtonRaphson(float ajuste, float x, float precisaoResult, float precisaoX, int maxIter) {
    cout << maxIter << endl;
    int inter = 0;
    float xprox, fx, ffx;
    resultNewtonRaphson *results;

    if (isnan(funcao(ajuste,x)))
        return NULL;

    results =(resultNewtonRaphson *) malloc(sizeof(resultNewtonRaphson) * maxIter);

    cout << "Começando o loop" << endl;
    do {
        fx = funcao(ajuste,x);
        ffx = derivada(ajuste,x);
        xprox = x - fx/ffx; // Formula
        if( isnan(fx) or isnan(ffx) or isnan(xprox)) {
            //STOP!
            cout << "Someone is NaN in inter: " << inter << " ,fx=" << fx << " | ffx=" << ffx << " | xprox=" << xprox << endl;
            return NULL;
        }

        struct resultNewtonRaphson result;
        result.round = inter;
        result.x = x;
        result.fx = fabs(fx);
        result.xprox = xprox;
        result.fxprox = fabs(funcao(ajuste, xprox));
        result.xmenusxprox = fabs(xprox - x);
        result.hasNext = true;
        results[inter] = result;

        if ( fabs( funcao(ajuste,x)) < precisaoResult or fabs( xprox-x ) < precisaoX ) {
            cout << "Convergiu no round: " << inter << " " << fabs(funcao(ajuste,xprox)) << " " << fabs(xprox-x) << endl;
            break;
        }
        x = xprox;

        cout << "Armazenado, Round=" << inter << endl;

        inter++;
    }while (inter < maxIter);

    //cout << "Iter Stop: " << inter << " " << fabs(funcao(ajuste,xprox)) << " " << (fabs(funcao(ajuste,xprox)) < precisaoResult) << " "
    //         << fabs(xprox-x) << " " << (fabs(xprox-x) < precisaoX) << endl;


    cout << "Imprimindo Resultados " << endl;
    int i = 0;
    while (i <= inter) {
         cout << "Round: " << results[i].round << " " << results[i].x << " " << results[i].fx
              << " " << results[i].xprox << " " << results[i].fxprox << " " << results[i].hasNext << endl;
         i++;
    }
    cout << "FIM \n\n" << endl;



    return results;
}

#endif // METHODS_H
