//Class header file.
#include "lu_solucao.h"

LU_Solucao::LU_Solucao(const Matriz& o, const Matriz& l, const Matriz& u, const Matriz& r, const Matriz& sp, const Matriz& s, const Matriz& i)
: orig(o), L(l), U(u), resultado(r), solucaoparcial(sp), solucao(s), index(i) {}

LU_Solucao LU_Solucao::resolverPorLU(const Matriz& s, const Matriz& r, int pivot) {
    Matriz O = s;
    Matriz R = r;
    Matriz L = Matriz(s.getQuantLinhas(), s.getQuantColunas(), 0);
    Matriz U = s;
    Matriz I = Matriz(r.getQuantLinhas(), 1, 0);

    for(int i = 0; i < I.getQuantLinhas(); i++) {
        I[i][0] = i;
    }

    for(int j = 0; j < U.getQuantColunas(); j++) {
        if(pivot == 1) {
            PivotacaoParcialInferior pivot = PivotacaoParcialInferior(j, j, U);

            U = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(U);
            R = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(R);
            L = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(L);
        } else if(pivot == 2) {
            PivotacaoTotalInferiorDireita pivot = PivotacaoTotalInferiorDireita(j, j, U);

            U = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(U);
            U = TrocarColunas(pivot.getColuna1(), pivot.getColuna2()).executarSobre(U);
            R = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(R);
            L = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(L);
            I = TrocarLinhas(pivot.getColuna1(), pivot.getColuna2()).executarSobre(I);
        }

        for(int i = j + 1; i < L.getQuantLinhas(); i++) {
            L[i][j] = U[i][j] / U[j][j];
            U = AdicionarLinhaALinha(j, i, - U[i][j] / U[j][j]).executarSobre(U);
        }
    }

    for(int i = 0; i < U.getQuantLinhas(); i++) {
        L[i][i] = 1;
    }

    Matriz P = Matriz(R.getQuantLinhas(), R.getQuantColunas(), 0);
    for(int i = 0; i < P.getQuantLinhas(); i++) {
        P[i][0] = R[i][0];
        for(int j = i - 1; j >= 0; j--) {
            P[i][0] -= L[i][j] * P[j][0];
        }
        P[i][0] /= L[i][i];
    }

    Matriz S = Matriz(P.getQuantLinhas(), P.getQuantColunas(), 0);
    for(int i = S.getQuantLinhas() - 1; i >= 0; i--) {
        S[i][0] = P[i][0];
        for(int j = i + 1; j < U.getQuantColunas(); j++) {
            S[i][0] -= U[i][j] * S[j][0];
        }
        S[i][0] /= U[i][i];
    }

    return LU_Solucao(O, L, U, R, P, S, I);
}

Matriz LU_Solucao::getOriginal() const {
    return this->orig;
}

Matriz LU_Solucao::getL() const {
    return this->L;
}

Matriz LU_Solucao::getU() const {
    return this->U;
}

Matriz LU_Solucao::getResultado() const {
    return this->resultado;
}

Matriz LU_Solucao::getSolucaoParcial() const {
    return this->solucaoparcial;
}

Matriz LU_Solucao::getSolucao() const {
    return this->solucao;
}

Matriz LU_Solucao::getIndex() const {
    return this->index;
}

Matriz LU_Solucao::getResultadoEmOrdem() {
    Matriz m = Matriz(this->index.getQuantLinhas(), 1, 0);

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        m[this->index[i][0]][0] = this->resultado[i][0];
    }

    return m;
}

Matriz LU_Solucao::getSolucaoEmOrdem() {
    Matriz m = Matriz(this->index.getQuantLinhas(), 1, 0);

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        m[this->index[i][0]][0] = this->solucao[i][0];
    }

    return m;
}
