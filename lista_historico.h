//
// Created by Victo on 21/05/2026.
//

#ifndef PROGRAMAS_E_LISTA_HISTORICO_H
#define PROGRAMAS_E_LISTA_HISTORICO_H

typedef struct Emprestimo {
    char nomeUsuario[100];
    int codigoLivro;
    char tituloLivro[100];
} Emprestimo;

typedef struct NoLista {
    Emprestimo emprestimo;
    struct NoLista* proximo;
} NoLista;

typedef struct Lista {
    NoLista* inicio;
} Lista;

// Cria a lista
Lista* criarLista();

// Insere empréstimo
void inserirEmprestimo(Lista* lista, Emprestimo emprestimo);

// Lista empréstimos
void listarEmprestimos(Lista* lista);

// Verifica se lista está vazia
int listaVazia(Lista* lista);

#endif //PROGRAMAS_E_LISTA_HISTORICO_H
