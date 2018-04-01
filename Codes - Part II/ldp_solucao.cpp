//Class header file.
#include "ldp_solucao.h"

LDP_Solucao::LDP_Solucao(const Matriz& o, const Matriz& l, const Matriz& d, const Matriz& p, const Matriz& r, const Matriz& sp1, const Matriz& sp2, const Matriz& s, const Matriz& i)
: orig(o), L(l), D(d), P(p), resultado(r), solucaoparcial1(sp1), solucaoparcial2(sp2), solucao(s), index(i) {}

LDP_Solucao LDP_Solucao::resolverPorLDP(const Matriz& s, const Matriz& r, int pivot) {
    Matriz O = s;
    Matriz R = r;
    Matriz L = Matriz(s.getQuantLinhas(), s.getQuantColunas(), 0);
    Matriz D = Matriz(s.getQuantLinhas(), s.getQuantColunas(), 0);
    Matriz P = s;
    Matriz I = Matriz(r.getQuantLinhas(), 1, 0);

    for(int i = 0; i < I.getQuantLinhas(); i++) {
        I[i][0] = i;
    }

    for(int j = 0; j < P.getQuantColunas(); j++) {
        if(pivot == 1) {
            PivotacaoParcialInferior pivot = PivotacaoParcialInferior(j, j, P);

            P = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(P);
            R = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(R);
            L = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(L);
        } else if(pivot == 2) {
            PivotacaoTotalInferiorDireita pivot = PivotacaoTotalInferiorDireita(j, j, P);

            P = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(P);
            P = TrocarColunas(pivot.getColuna1(), pivot.getColuna2()).executarSobre(P);
            R = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(R);
            L = TrocarLinhas(pivot.getLinha1(), pivot.getLinha2()).executarSobre(L);
            I = TrocarLinhas(pivot.getColuna1(), pivot.getColuna2()).executarSobre(I);
        }

        for(int i = j + 1; i < L.getQuantLinhas(); i++) {
            L[i][j] = P[i][j] / P[j][j];
            P = AdicionarLinhaALinha(j, i, - P[i][j] / P[j][j]).executarSobre(P);
        }
    }

    for(int i = 0; i < P.getQuantLinhas(); i++) {
        L[i][i] = 1;

        D[i][i] = P[i][i];
        P = UniformizarLinha(i, i).executarSobre(P);
    }

    Matriz P1 = Matriz(R.getQuantLinhas(), R.getQuantColunas(), 0);
    for(int i = 0; i < P1.getQuantLinhas(); i++) {
        P1[i][0] = R[i][0];
        for(int j = i - 1; j >= 0; j--) {
            P1[i][0] -= L[i][j] * P1[j][0];
        }
        P1[i][0] /= L[i][i];
    }

    Matriz P2 = Matriz(P1.getQuantLinhas(), P1.getQuantColunas(), 0);
    for(int i = 0; i < P2.getQuantLinhas(); i++) {
        P2[i][0] = P1[i][0] / D[i][i];
    }

    Matriz S = Matriz(P2.getQuantLinhas(), P2.getQuantColunas(), 0);
    for(int i = S.getQuantLinhas() - 1; i >= 0; i--) {
        S[i][0] = P2[i][0];
        for(int j = i + 1; j < P.getQuantColunas(); j++) {
            S[i][0] -= P[i][j] * S[j][0];
        }
        S[i][0] /= P[i][i];
    }

    return LDP_Solucao(O, L, D, P, R, P1, P2, S, I);
}

Matriz LDP_Solucao::getOriginal() const {
    return this->orig;
}

Matriz LDP_Solucao::getL() const {
    return this->L;
}

Matriz LDP_Solucao::getD() const {
    return this->D;
}

Matriz LDP_Solucao::getP() const {
    return this->P;
}

Matriz LDP_Solucao::getResultado() const {
    return this->resultado;
}

Matriz LDP_Solucao::getSolucaoParcial1() const {
    return this->solucaoparcial1;
}

Matriz LDP_Solucao::getSolucaoParcial2() const {
    return this->solucaoparcial2;
}

Matriz LDP_Solucao::getSolucao() const {
    return this->solucao;
}

Matriz LDP_Solucao::getIndex() const {
    return this->index;
}

Matriz LDP_Solucao::getResultadoEmOrdem() {
    Matriz m = Matriz(this->index.getQuantLinhas(), 1, 0);

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        m[this->index[i][0]][0] = this->resultado[i][0];
    }

    return m;
}

Matriz LDP_Solucao::getSolucaoEmOrdem() {
    Matriz m = Matriz(this->index.getQuantLinhas(), 1, 0);

    for(int i = 0; i < m.getQuantLinhas(); i++) {
        m[this->index[i][0]][0] = this->solucao[i][0];
    }

    return m;
}
