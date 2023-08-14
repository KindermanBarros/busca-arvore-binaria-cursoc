#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};

int altura(struct No* no) {
    if (no == NULL)
        return 0;
    return 1 + maximo(altura(no->esquerda), altura(no->direita));
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

struct No* rotacaoDireita(struct No* y) {
    struct No* x = y->esquerda;
    struct No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    return x;
}

struct No* rotacaoEsquerda(struct No* x) {
    struct No* y = x->direita;
    struct No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    return y;
}

int fatorBalanceamento(struct No* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

struct No* inserir(struct No* raiz, int valor) {
    if (raiz == NULL) {
        struct No* novoNo = (struct No*)malloc(sizeof(struct No));
        novoNo->valor = valor;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    else
        return raiz;

    int fatorBalanceamento = fatorBalanceamento(raiz);

    if (fatorBalanceamento > 1 && valor < raiz->esquerda->valor)
        return rotacaoDireita(raiz);

    if (fatorBalanceamento < -1 && valor > raiz->direita->valor)
        return rotacaoEsquerda(raiz);

    if (fatorBalanceamento > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fatorBalanceamento < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void imprimirInOrder(struct No* no) {
    if (no != NULL) {
        imprimirInOrder(no->esquerda);
        printf("%d ", no->valor);
        imprimirInOrder(no->direita);
    }
}

int main() {
    struct No* raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 20);

    printf("Árvore balanceada em ordem (in-order): ");
    imprimirInOrder(raiz);
    printf("\n");

    return 0;
}
