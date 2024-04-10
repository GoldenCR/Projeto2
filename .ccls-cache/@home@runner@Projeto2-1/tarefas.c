#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    printf("Entre com a prioridade de 1 a 10: ");
    scanf("%d", &prioridade);
    clearBuffer();
    if (prioridade < 1 || prioridade > 10) {
        printf("Prioridade fora do intervalo permitido.\n");
        return OK;
    }
    tarefas[*pos].prioridade = prioridade;
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, sizeof(tarefas[*pos].categoria), stdin);
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, sizeof(tarefas[*pos].descricao), stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0'; 
    (*pos)++;
    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
    if (*pos == 0) {
        return SEM_TAREFAS;
    }

    char categoria[100];
    clearBuffer();
    printf("Entre com a categoria (ou deixe vazio para listar todas as tarefas): ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0'; 
    if (categoria[0] == '\0') { 
        for (int i = 0; i < *pos; i++) {
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
        return OK;
    }

    int encontradas = 0;
    for (int i = 0; i < *pos; i++) {
        if (strstr(tarefas[i].categoria, categoria) != NULL) {
            encontradas++;
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }
    if (encontradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s'.\n", categoria);
        return NAO_ENCONTRADO;
    }
    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "rb");
    if (f == NULL) {
        f = fopen("tarefas.bin", "wb");
        if (f == NULL)
            return ABRIR;
        *pos = 0;
        fclose(f); 
        return OK;
    }

    int qtd = fread(tarefas, sizeof(Tarefa), TOTAL, f);
    if (qtd != TOTAL) {
        fclose(f);
        return LER;
    }

    qtd = fread(pos, sizeof(int), 1, f);
    if (qtd != 1) {
        fclose(f);
        return LER;
    }

    fclose(f);
    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}