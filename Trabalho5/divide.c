#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char** argv)
{
	FILE *original, *blocos[8];
	Endereco reg;
	char nome[20];
	int i;
	long total = 0;

	if(argc < 2)
	{
		printf("Uso: %s arquivo_original.dat\n", argv[0]);
		return 1;
	}

	original = fopen(argv[1], "rb");
	if(original == NULL)
	{
		printf("Erro ao abrir %s\n", argv[1]);
		return 1;
	}

	for(i = 0; i < 8; i++)
	{
		sprintf(nome, "bloco%d.dat", i + 1);
		blocos[i] = fopen(nome, "wb");
	}

	i = 0;
	fread(&reg, sizeof(Endereco), 1, original);
	while(!feof(original))
	{
		fwrite(&reg, sizeof(Endereco), 1, blocos[i % 8]);
		i++;
		total++;
		fread(&reg, sizeof(Endereco), 1, original);
	}

	fclose(original);
	for(i = 0; i < 8; i++)
		fclose(blocos[i]);

	printf("Arquivo dividido em 8 blocos (%ld registros no total).\n", total);

	return 0;
}