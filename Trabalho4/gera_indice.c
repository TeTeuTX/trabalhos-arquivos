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

int compara_indice(const void *a, const void *b) {
    return strncmp(((IndiceCep*)a)->cep, ((IndiceCep*)b)->cep, 8);
}

int main() {
    FILE *f_dados, *f_indice;
    Endereco e;
    IndiceCep *indices;
    long total_bytes, qtd_registros;
    long i = 0;

    f_dados = fopen("cep.dat", "rb");
    if (!f_dados) {
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        return 1;
    }

    fseek(f_dados, 0, SEEK_END);
    total_bytes = ftell(f_dados);
    qtd_registros = total_bytes / sizeof(Endereco);
    rewind(f_dados);

    printf("Total de registros em cep.dat: %ld\n", qtd_registros);

    // Aloca memória apenas para o array de índices
    indices = (IndiceCep*) malloc(qtd_registros * sizeof(IndiceCep));
    if (!indices) {
        fprintf(stderr, "Erro de alocacao de memoria para o indice\n");
        fclose(f_dados);
        return 1;
    }

    printf("Lendo registros sequencialmente e gerando indices...\n");
    while (fread(&e, sizeof(Endereco), 1, f_dados) == 1) {
        strncpy(indices[i].cep, e.cep, 8);
        indices[i].posicao = i;
        i++;
    }
    fclose(f_dados);

    printf("Ordenando o array de indices com qsort...\n");
    qsort(indices, qtd_registros, sizeof(IndiceCep), compara_indice);

    printf("Gravando arquivo de indice ordenado (indice.dat)...\n");
    f_indice = fopen("indice.dat", "wb");
    if (!f_indice) {
        fprintf(stderr, "Erro ao criar indice.dat\n");
        free(indices);
        return 1;
    }

    fwrite(indices, sizeof(IndiceCep), qtd_registros, f_indice);
    fclose(f_indice);
    free(indices);

    printf("Indice gerado e salvo com sucesso em indice.dat!\n");
    return 0;
}