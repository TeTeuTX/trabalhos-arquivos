//integrantes:
//Ronald Teixeira de Assis
//Rodrigo Americo Nascimento D'icarahy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;
struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

typedef struct _IndiceCep IndiceCep;
struct _IndiceCep {
    char cep[8];
    long posicao;
};

int main(int argc, char **argv) {
    FILE *f_indice, *f_dados;
    IndiceCep item_indice;
    Endereco end_resultado;
    long inicio, fim, meio;
    long total_bytes, total_indices;
    int comparacoes = 0;
    int encontrado = 0;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s [CEP]\n", argv[0]);
        return 1;
    }

    f_indice = fopen("indice.dat", "rb");
    if (!f_indice) {
        fprintf(stderr, "Erro ao abrir indice.dat. Execute o gera_indice primeiro.\n");
        return 1;
    }

    f_dados = fopen("cep.dat", "rb");
    if (!f_dados) {
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        fclose(f_indice);
        return 1;
    }

    // Calcula total de registros de índice
    fseek(f_indice, 0, SEEK_END);
    total_bytes = ftell(f_indice);
    total_indices = total_bytes / sizeof(IndiceCep);

    inicio = 0;
    fim = total_indices - 1;

    // Busca binária sobre o arquivo de índices
    while (inicio <= fim) {
        comparacoes++;
        meio = inicio + (fim - inicio) / 2;

        fseek(f_indice, meio * sizeof(IndiceCep), SEEK_SET);
        fread(&item_indice, sizeof(IndiceCep), 1, f_indice);

        int cmp = strncmp(argv[1], item_indice.cep, 8);

        if (cmp == 0) {
            // Posiciona diretamente no registro correto do cep.dat original
            fseek(f_dados, item_indice.posicao * sizeof(Endereco), SEEK_SET);
            fread(&end_resultado, sizeof(Endereco), 1, f_dados);

            printf("\n--- Endereco Encontrado ---\n");
            printf("Logradouro: %.72s\n", end_resultado.logradouro);
            printf("Bairro:     %.72s\n", end_resultado.bairro);
            printf("Cidade:     %.72s\n", end_resultado.cidade);
            printf("UF:         %.72s\n", end_resultado.uf);
            printf("Sigla:      %.2s\n", end_resultado.sigla);
            printf("CEP:        %.8s\n", end_resultado.cep);
            printf("Posicao no arquivo original: %ld\n", item_indice.posicao);

            encontrado = 1;
            break;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (!encontrado) {
        printf("\nCEP %.8s nao encontrado.\n", argv[1]);
    }

    printf("Total de comparacoes no indice: %d\n", comparacoes);

    fclose(f_indice);
    fclose(f_dados);
    return 0;
}