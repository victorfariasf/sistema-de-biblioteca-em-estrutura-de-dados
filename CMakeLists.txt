cmake_minimum_required(VERSION 4.2)
project(programas_E C)

set(CMAKE_C_STANDARD 11)

add_executable(programas_E main.c
        fila_reserva.h
        fila_reserva.c
        arvore_livros.h
        arvore_livros.c
        lista_historico.h
        lista_historico.c
)
