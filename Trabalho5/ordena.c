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

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

int main(int argc, char** argv)
{
	FILE *f;
	Endereco *vetor;
	long tamanho;
	int n;

	if(argc < 2)
	{
		printf("Uso: %s bloco.dat\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if(f == NULL)
	{
		printf("Erro ao abrir %s\n", argv[1]);
		return 1;
	}

	fseek(f, 0, SEEK_END);
	tamanho = ftell(f);
	rewind(f);

	n = tamanho / sizeof(Endereco);
	vetor = (Endereco*) malloc(n * sizeof(Endereco));

	fread(vetor, sizeof(Endereco), n, f);
	fclose(f);

	qsort(vetor, n, sizeof(Endereco), compara);

	f = fopen(argv[1], "wb");
	fwrite(vetor, sizeof(Endereco), n, f);
	fclose(f);

	free(vetor);

	printf("%s ordenado (%d registros).\n", argv[1], n);

	return 0;
}