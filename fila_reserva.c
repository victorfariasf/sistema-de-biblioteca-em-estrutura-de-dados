#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_reserva.h"

// Cria a fila
Fila* criarFila() {

    Fila* fila = (Fila*) malloc(sizeof(Fila));

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

// Verifica se a fila está vazia
int filaVazia(Fila* fila) {

    return fila->inicio == NULL;
}

// Enfileira uma reserva
void enfileirarReserva(Fila* fila, Reserva reserva) {

    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));

    novo->reserva = reserva;
    novo->proximo = NULL;

    // Se a fila estiver vazia
    if (filaVazia(fila)) {

        fila->inicio = novo;
        fila->fim = novo;

    } else {

        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    printf("\nReserva adicionada com sucesso!\n");
}

// Remove uma reserva da fila
Reserva desenfileirarReserva(Fila* fila) {

    Reserva reserva;

    // Caso a fila esteja vazia
    if (filaVazia(fila)) {

        printf("\nFila vazia!\n");

        strcpy(reserva.nomeUsuario, "");
        reserva.codigoLivro = -1;

        return reserva;
    }

    NoFila* temp = fila->inicio;

    reserva = temp->reserva;

    fila->inicio = fila->inicio->proximo;

    // Se a fila ficou vazia
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);

    return reserva;
}

// Exibe reservas
void exibirReservas(Fila* fila) {

    if (filaVazia(fila)) {

        printf("\nNenhuma reserva na fila.\n");
        return;
    }

    NoFila* atual = fila->inicio;

    printf("\n===== FILA DE RESERVAS =====\n");

    while (atual != NULL) {

        printf("Usuario: %s\n", atual->reserva.nomeUsuario);
        printf("Codigo do livro: %d\n\n", atual->reserva.codigoLivro);

        atual = atual->proximo;
    }
}

