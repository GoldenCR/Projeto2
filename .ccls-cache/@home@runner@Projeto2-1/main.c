#include <stdio.h>
#include "tarefas.h"

int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos = 0; 
    ERROS erro = fs[4](tarefas, &pos); 

    if (erro != OK) {
        printf("Erro ao tentar carregar as tarefas: %d\n", erro);
        return 1; 
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;

        if (opcao < 0 || opcao > 2) {
            printf("Opcao invalida\n");
        } else if (opcao == 0) {
            fs[opcao](tarefas, &pos); 
        } else if (opcao == 1) {
            fs[opcao](tarefas, &pos);
        } else if (opcao == 2) {
            fs[opcao](tarefas, &pos); 
        }

    } while (opcao >= 0);

    erro = fs[3](tarefas, &pos);
    if (erro != OK) {
        printf("Erro ao tentar salvar as tarefas: %d\n", erro);
        return 1;
    }

    return 0;
}