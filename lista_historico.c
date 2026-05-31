#include <stdio.h>
#include <stdlib.h>
#include "lista_historico.h"

// Cria lista
Lista* criarLista() {

    Lista* lista = (Lista*) malloc(sizeof(Lista));

    lista->inicio = NULL;

    return lista;
}

// Verifica se lista está vazia
int listaVazia(Lista* lista) {

    return lista->inicio == NULL;
}

// Insere empréstimo na lista
void inserirEmprestimo(Lista* lista, Emprestimo emprestimo) {

    NoLista* novo = (NoLista*) malloc(sizeof(NoLista));

    novo->emprestimo = emprestimo;
    novo->proximo = NULL;

    // Se lista estiver vazia
    if (listaVazia(lista)) {

        lista->inicio = novo;

    } else {

        NoLista* atual = lista->inicio;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

    printf("\nEmprestimo registrado com sucesso!\n");
}

// Lista empréstimos
void listarEmprestimos(Lista* lista) {

    if (listaVazia(lista)) {

        printf("\nNenhum emprestimo registrado.\n");
        return;
    }

    NoLista* atual = lista->inicio;

    printf("\n===== HISTORICO DE EMPRESTIMOS =====\n");

    while (atual != NULL) {

        printf("Usuario: %s\n", atual->emprestimo.nomeUsuario);
        printf("Codigo do livro: %d\n", atual->emprestimo.codigoLivro);
        printf("Titulo: %s\n\n", atual->emprestimo.tituloLivro);

        atual = atual->proximo;
    }
}