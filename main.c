#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_livros.h"
#include "fila_reserva.h"
#include "lista_historico.h"

char mostrarTela(No** raiz, Fila* fila, Lista* lista);
void inserirLivroNoSitema(No** raiz);
void realizarEmprestimo(No** raiz, Lista* lista);
void realizarDevolucao(No** raiz, Lista* lista);
void carregarLivrosDebug(No** raiz);
void exibirFilaReservasDoLivro(No* raiz);

int main(void) {
    setbuf(stdout, NULL);
    No* raiz = NULL;
    Fila* fila = criarFila();
    Lista* lista = criarLista();
    char sair = 'n';
    while (sair != 's') {
        sair = mostrarTela(&raiz, fila, lista);
    }
    liberarArvore(raiz);
}

void inserirLivroNoSitema(No** raiz) {
    printf("Codigo do livro:\n");
    int codigo;
    scanf("%d", &codigo);
    getchar();
    printf("Nome do livro:\n");
    char nomeLivro[100];
    fgets(nomeLivro, sizeof(nomeLivro), stdin);
    printf("Nome do autor:\n");
    char nomeAutor[100];
    fgets(nomeAutor, sizeof(nomeAutor), stdin);
    printf("Ano do livro:\n");
    int anoLivro;
    scanf("%d", &anoLivro);
    printf("Total de exemplares:\n");
    int totalLivros;
    scanf("%d", &totalLivros);
    getchar();
    Livro livro = {
        codigo,
        "",
        "",
        anoLivro,
        totalLivros,
        totalLivros,
        criarFila()
    };
    strcpy(livro.titulo, nomeLivro);
    strcpy(livro.autor, nomeAutor);
    *raiz = inserirBalanceado(*raiz, livro);
    //*raiz = inserir(*raiz, livro);

}

void buscarLivroPorCodigo(No* raiz) {
    printf("Codigo do livro\n");
    int codigo;
    scanf("%d", &codigo);
    No* resultado = buscar(raiz, codigo);
    if (resultado != NULL) {
        printf("Codigo: %d\n", resultado->livro.codigo);
        printf("Titulo: %s", resultado->livro.titulo);
        printf("Autor: %s", resultado->livro.autor);
        printf("Ano: %d\n", resultado->livro.ano);
        printf("Total: %d\n", resultado->livro.totalExemplares);
        printf("Disponiveis: %d\n\n", resultado->livro.disponiveis);
    } else {
        printf("Livro nao encontrado.\n");
    }

}

char mostrarTela(No** raiz, Fila* fila, Lista* lista) {
    int opcao;
    printf("\nSistema de Biblioteca Digital\nO que deseja fazer?\n");
    printf("1. cadastrar livro\n");
    printf("2. buscar livro\n");
    printf("3. listar livros Em ordem\n");
    printf("4. listar livros em Pós-ordem\n");
    printf("5. listar livros em Pré-ordem\n");
    printf("6. altura da arvore\n");
    printf("7. quantidade de livros no sistema\n");
    printf("8. cadastrar emprestimo de livro\n");
    printf("9. cadastrar devolucao de livro\n");
    printf("10. exibir reservas\n");
    printf("11. exibir historico de emprestimos de livros\n");
    printf("12. carregar livros no sistema (TESTES)\n");
    printf("0. encerrar sistema\n");
    scanf(" %d", &opcao);
    switch (opcao) {
        case 1:
            inserirLivroNoSitema(raiz);
            return 'n';
            break;
        case 2:
            buscarLivroPorCodigo(*raiz);
            return 'n';
            break;
        case 3:
            imprimirEmOrdem(*raiz);
            return 'n';
            break;
        case 4:
            imprimirPosOrdem(*raiz);
            return 'n';
            break;
        case 5:
            imprimirPreOrdem(*raiz);
            return 'n';
            break;
        case 6:
            int alturaArvore = calcularAlturaDaArvore(*raiz);
            printf("Altura da árvore: %d\n", alturaArvore);
            return 'n';
            break;
        case 7:
            int quantidadeLivros = contagemDeLivros(*raiz);
            printf("Quantidade de livros: %d\n", quantidadeLivros);
            return 'n';
            break;
        case 8:
            realizarEmprestimo(raiz, lista);
            return 'n';
            break;
        case 9:
            realizarDevolucao(raiz, lista);
            return 'n';
            break;
        case 10:
            exibirFilaReservasDoLivro(*raiz);
            return 'n';
            break;
        case 11:
            listarEmprestimos(lista);
            return 'n';
            break;
        case 12:
            carregarLivrosDebug(raiz);
            return 'n';
            break;
        case 0:
            return 's';
            break;
        default:
            printf("Opcao invalida\n");
            return 'n';
    }
}

void realizarEmprestimo(No** raiz, Lista* lista) {
    char nomeUsuario[100];
    int codigo;

    getchar();

    printf("Nome do usuario:\n");
    fgets(nomeUsuario, sizeof(nomeUsuario), stdin);

    printf("Codigo do livro:\n");
    scanf("%d", &codigo);

    No* resultado = buscar(*raiz, codigo);

    if (resultado == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }

    if (resultado->livro.disponiveis > 0) {
        resultado->livro.disponiveis--;

        Emprestimo emprestimo;

        strcpy(emprestimo.nomeUsuario, nomeUsuario);
        emprestimo.codigoLivro = resultado->livro.codigo;
        strcpy(emprestimo.tituloLivro, resultado->livro.titulo);

        inserirEmprestimo(lista, emprestimo);

        printf("Emprestimo realizado com sucesso!\n");
    } else {
        char resposta;

        printf("Livro indisponivel. Deseja entrar na fila de reserva? s/n\n");
        scanf(" %c", &resposta);

        if (resposta == 's') {
            Reserva reserva;

            strcpy(reserva.nomeUsuario, nomeUsuario);
            reserva.codigoLivro = codigo;

            enfileirarReserva(resultado->livro.filaReservas, reserva);
        }
    }
}

void realizarDevolucao(No** raiz, Lista* lista) {
    int codigo;

    printf("Codigo do livro:\n");
    scanf("%d", &codigo);

    No* resultado = buscar(*raiz, codigo);

    if (resultado == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }

    resultado->livro.disponiveis++;
    printf("Devolucao realizada com sucesso!\n");

    if (!filaVazia(resultado->livro.filaReservas)) {
        Reserva reserva = desenfileirarReserva(resultado->livro.filaReservas);
        resultado->livro.disponiveis--;
        Emprestimo emprestimo;

        strcpy(emprestimo.nomeUsuario, reserva.nomeUsuario);
        emprestimo.codigoLivro = resultado->livro.codigo;
        strcpy(emprestimo.tituloLivro, resultado->livro.titulo);

        inserirEmprestimo(lista, emprestimo);

        printf("\nExiste reserva para esse livro.\n");
        printf("Emprestimo realizado automaticamente para: %s\n", reserva.nomeUsuario);
    }
}

void carregarLivrosDebug(No** raiz) {

    Livro l1 = {
        5,
        "Dom Casmurro\n",
        "Machado de Assis\n",
        1899,
        5,
        5,
        criarFila()
    };

    Livro l2 = {
        3,
        "1984\n",
        "George Orwell\n",
        1949,
        3,
        3,
        criarFila()
    };

    Livro l3 = {
        7,
        "O Hobbit\n",
        "J.R.R Tolkien\n",
        1937,
        4,
        4,
        criarFila()
    };

    Livro l4 = {
        2,
        "Clean Code\n",
        "Robert Martin\n",
        2008,
        2,
        2,
        criarFila()
    };

    Livro l5 = {
        4,
        "Harry Potter\n",
        "J.K Rowling\n",
        1997,
        6,
        6,
        criarFila()
    };

    Livro l6 = {
        6,
        "C Linguagem\n",
        "Dennis Ritchie\n",
        1978,
        2,
        2,
        criarFila()
    };

    Livro l7 = {
        8,
        "Estruturas de Dados\n",
        "Nivio Ziviani\n",
        2010,
        1,
        1,
        criarFila()
    };

    *raiz = inserirBalanceado(*raiz, l1);
    *raiz = inserirBalanceado(*raiz, l2);
    *raiz = inserirBalanceado(*raiz, l3);
    *raiz = inserirBalanceado(*raiz, l4);
    *raiz = inserirBalanceado(*raiz, l5);
    *raiz = inserirBalanceado(*raiz, l6);
    *raiz = inserirBalanceado(*raiz, l7);

    // *raiz = inserir(*raiz, l1);
    // *raiz = inserir(*raiz, l2);
    // *raiz = inserir(*raiz, l3);
    // *raiz = inserir(*raiz, l4);
    // *raiz = inserir(*raiz, l5);
    // *raiz = inserir(*raiz, l6);
    // *raiz = inserir(*raiz, l7);

    printf("\nLivros de debug carregados com sucesso!\n");
}

void exibirFilaReservasDoLivro(No* raiz) {
    int codigo;

    printf("Codigo do livro:\n");
    scanf("%d", &codigo);

    No* resultado = buscar(raiz, codigo);

    if (resultado == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }

    exibirReservas(resultado->livro.filaReservas);
}
