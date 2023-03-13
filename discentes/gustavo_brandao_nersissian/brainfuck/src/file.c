#include <stdio.h>

#define MEMORY_SIZE 30000

int brainfuck() {
	
    char memory[MEMORY_SIZE] = {0}; // Array para representar a memória
    char *ptr = memory; // Ponteiro para a posição atual na memória
    FILE *fp = fopen("arquivo.txt", "r"); // Abre o arquivo para leitura

    if (fp == NULL) { // Verifica se houve erro ao abrir o arquivo
        printf("Erro ao abrir o arquivo.\n"); // Exibe uma mensagem de erro
        return 1; // Retorna um código de erro
    }

    char c; // Caractere atual lido do arquivo
    while ((c = fgetc(fp)) != EOF) { // Lê o próximo caractere até o final do arquivo
        switch (c) {
            case '>': // Incrementa o ponteiro para a próxima posição na memória
                ++ptr;
                break;
            case '<': // Decrementa o ponteiro para a posição anterior na memória
                --ptr;
                break;
            case '+': // Incrementa o valor na posição atual da memória
                ++(*ptr);
                break;
            case '-': // Decrementa o valor na posição atual da memória
                --(*ptr);
                break;
            case '.': // Imprime o caractere ASCII correspondente ao valor na posição atual da memória
                putchar(*ptr);
                break;
            case ',': // Lê um caractere do usuário e armazena o valor na posição atual da memória
                *ptr = getchar();
                break;
            case '[': // Início de um loop while
                if (*ptr == 0) { // Se o valor na posição atual da memória for zero, pula para o "]" correspondente
                    int brackets = 1; // Contador de colchetes para encontrar o "]" correspondente
                    while (brackets > 0) {
                        c = fgetc(fp); // Lê o próximo caractere
                        if (c == '[') {
                            ++brackets; // Incrementa o contador de colchetes
                        } else if (c == ']') {
                            --brackets; // Decrementa o contador de colchetes
                        }
                    }
                }
                break;
            case ']': // Fim de um loop while
                if (*ptr != 0) { // Se o valor na posição atual da memória for diferente de zero, volta para o "[" correspondente
                    int brackets = 1; // Contador de colchetes para encontrar o "[" correspondente
                    while (brackets > 0) {
                        fseek(fp, -2, SEEK_CUR); // Volta dois caracteres no arquivo (um para o "]" e outro para o comando anterior ao "[")
                        c = fgetc(fp); // Lê o próximo caractere
                        if (c == '[') {
                            --brackets; // Decrementa o contador de colchetes
                        } else if (c == ']') {
                            ++brackets; // Incrementa o contador de colchetes
                        }
                    }
                }
                break;
        }
    }

    fclose(fp); // Fecha o arquivo

    return 0; // Retorna 0 para indicar que a execução foi concluída com sucesso
}
