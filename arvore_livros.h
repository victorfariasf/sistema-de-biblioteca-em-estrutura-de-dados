//
// Created by Victo on 21/05/2026.
//

#ifndef PROGRAMAS_E_ARVORE_LIVROS_H
#define PROGRAMAS_E_ARVORE_LIVROS_H
#include "fila_reserva.h"

typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int totalExemplares;
    int disponiveis;
    Fila* filaReservas;
}Livro;

typedef struct No{
    Livro livro;
    struct No *esquerda;
    struct No *direita;
} No;

No* criarNo(Livro livro);
No* inserir(No* raiz, Livro livro);
No* buscar(No* raiz, int codigo);
void imprimirEmOrdem(No* raiz);
void imprimirPreOrdem(No* raiz);
void imprimirPosOrdem(No* raiz);
void liberarArvore(No* raiz);
int contagemDeLivros(No* raiz);
int calcularAlturaDaArvore(No* raiz);

#endif //PROGRAMAS_E_ARVORE_LIVROS_H
