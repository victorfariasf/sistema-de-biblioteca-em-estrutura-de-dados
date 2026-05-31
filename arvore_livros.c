#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_livros.h"

No* criarNo(Livro livro) {
    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    novo->livro = livro;
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

No* inserir(No* raiz, Livro livro) {
    if (raiz == NULL) {
        return criarNo(livro);
    }

    if (livro.codigo < raiz->livro.codigo) {
        raiz->esquerda = inserir(raiz->esquerda, livro);
    } else if (livro.codigo > raiz->livro.codigo) {
        raiz->direita = inserir(raiz->direita, livro);
    } else if (livro.codigo == raiz->livro.codigo) {
        printf("Codigo ja cadastrado.\n");
    }

    return raiz;
}

No* buscar(No* raiz, int codigo) {
    if (raiz == NULL || raiz->livro.codigo == codigo) {
        return raiz;
    }

    if (codigo < raiz->livro.codigo) {
        return buscar(raiz->esquerda, codigo);
    } else {
        return buscar(raiz->direita, codigo);
    }
}

void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);

        printf("Codigo: %d\n", raiz->livro.codigo);
        printf("Titulo: %s", raiz->livro.titulo);
        printf("Autor: %s", raiz->livro.autor);
        printf("Ano: %d\n", raiz->livro.ano);
        printf("Total: %d\n", raiz->livro.totalExemplares);
        printf("Disponiveis: %d\n\n", raiz->livro.disponiveis);

        imprimirEmOrdem(raiz->direita);
    }
}
void imprimirPreOrdem(No* raiz) {
    if (raiz != NULL) {

        printf("Codigo: %d\n", raiz->livro.codigo);
        printf("Titulo: %s", raiz->livro.titulo);
        printf("Autor: %s", raiz->livro.autor);
        printf("Ano: %d\n", raiz->livro.ano);
        printf("Total: %d\n", raiz->livro.totalExemplares);
        printf("Disponiveis: %d\n\n", raiz->livro.disponiveis);

        imprimirPreOrdem(raiz->esquerda);

        imprimirPreOrdem(raiz->direita);
    }
}
void imprimirPosOrdem(No* raiz) {
    if (raiz != NULL) {

        imprimirPosOrdem(raiz->esquerda);

        imprimirPosOrdem(raiz->direita);

        printf("Codigo: %d\n", raiz->livro.codigo);
        printf("Titulo: %s", raiz->livro.titulo);
        printf("Autor: %s", raiz->livro.autor);
        printf("Ano: %d\n", raiz->livro.ano);
        printf("Total: %d\n", raiz->livro.totalExemplares);
        printf("Disponiveis: %d\n\n", raiz->livro.disponiveis);
    }
}

int contagemDeLivros(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contagemDeLivros(raiz->esquerda) + contagemDeLivros(raiz->direita);
}

int calcularAlturaDaArvore(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int alturaEsquerda = calcularAlturaDaArvore(raiz->esquerda);
    int alturaDireira = calcularAlturaDaArvore(raiz->direita);
    if (alturaEsquerda > alturaDireira) {
        return alturaEsquerda + 1;
    }else {
        return alturaDireira + 1;
    }
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}