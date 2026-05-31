//
// Created by Victo on 21/05/2026.
//

#ifndef PROGRAMAS_E_FILA_RESERVA_H
#define PROGRAMAS_E_FILA_RESERVA_H

typedef struct Reserva {
    char nomeUsuario[100];
    int codigoLivro;
} Reserva;

typedef struct NoFila {
    Reserva reserva;
    struct NoFila* proximo;
} NoFila;

typedef struct Fila {
    NoFila* inicio;
    NoFila* fim;
} Fila;

// Cria a fila
Fila* criarFila();
// Insere uma reserva na fila
void enfileirarReserva(Fila* fila, Reserva reserva);
// Remove uma reserva da fila
Reserva desenfileirarReserva(Fila* fila);
// Verifica se a fila está vazia
int filaVazia(Fila* fila);
// Exibe todas as reservas
void exibirReservas(Fila* fila);


#endif //PROGRAMAS_E_FILA_RESERVA_H
