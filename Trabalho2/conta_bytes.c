//integrantes:
//Ronald Teixeira de Assis
//Rodrigo Americo Nascimento D'icarahy
#include <stdio.h>

int main(int argc, char** argv)
{
    FILE *entrada;
    int c;
    long long contagem[256] = {0}; // Array para contar de 0 a 255 bytes

    if(argc != 2)
    {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO]\n", argv[0]);
        return 1;
    }

    // Abertura em modo binário para garantir leitura exata de todos os bytes (0 a 255)
    entrada = fopen(argv[1], "rb");
    if(!entrada)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    // Leitura byte a byte até o fim do arquivo
    c = fgetc(entrada);
    while(c != EOF)
    {
        // c como unsigned char garante índice correto no intervalo 0 a 255
        contagem[(unsigned char)c]++;
        c = fgetc(entrada);
    }

    fclose(entrada);

    // Impressão apenas das letras maiúsculas e minúsculas
    printf("--- Frequência de Letras ---\n");

    // Letras maiúsculas: 'A' até 'Z' (65 a 90)
    for(int i = 'A'; i <= 'Z'; i++)
    {
        if(contagem[i] > 0)
        {
            printf("Letra '%c' (0x%02X / %3d): %lld\n", i, i, i, contagem[i]);
        }
    }

    // Letras minúsculas: 'a' até 'z' (97 a 122)
    for(int i = 'a'; i <= 'z'; i++)
    {
        if(contagem[i] > 0)
        {
            printf("Letra '%c' (0x%02X / %3d): %lld\n", i, i, i, contagem[i]);
        }
    }

    return 0;
}