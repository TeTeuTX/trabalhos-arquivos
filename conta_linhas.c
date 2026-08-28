//integrantes:
//Ronald Teixeira de Assis
//Rodrigo Americo Nascimento D'icarahy

#include <stdio.h>

int main(int argc, char** argv)
{
	FILE *entrada;
	int c;
	long long total_linhas = 0;

	// O programa espera apenas 1 argumento adicional: o nome do arquivo de entrada
	if(argc != 2)
	{
		fprintf(stderr, "Erro na chamada do comando.\n");
		fprintf(stderr, "Uso: %s [ARQUIVO]\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1], "r");
	if(!entrada)
	{
		fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	// Leitura caractere por caractere
	c = fgetc(entrada);
	while(c != EOF)
	{
		if(c == '\n')
		{
			total_linhas++;
		}
		c = fgetc(entrada);
	}

	fclose(entrada);

	printf("Total de linhas: %lld\n", total_linhas);

	return 0;
}