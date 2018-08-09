/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG E Aluno de Ciência da Computação UFMG
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h" 

struct grafo {
	int **matriz_adjacencia;	// Matriz de adjacencias que representa o grafo
	int n_vertices;				// Número total de vertices que o grafo terá
	int elementos[50];      	// Nomes dos vértices fornecidos pelo usuário
	int n_ligacoes;				// //Número total de ligações que o grafo fará

    // Propriedades: 1 -> V | 0 -> F
    int propriedade_reflexiva;
    int propriedade_irreflexiva;
    int propriedade_simetrica;
    int propriedade_anti_simetrica;
    int propriedade_assimetrica;
    int propriedade_transitiva;

    int relacao_equivalencia;
    int relacao_ordem_parcial;

    // Fechos das relações:
};


Grafo cria_grafo(int *excessao_zero) {
	Grafo gr;
    int aux; 

	gr = preenche_grafo(&aux);
    *excessao_zero = aux;
	if(!aux)
        imprime_matriz(gr);
	return gr;
}

void libera_matriz(int **m, int tam) {   //Função para liberar o espaço alocado na memória
    int i;
    for(i=0;i<tam;i++)
        free(m[i]);
    free(m);
}

Grafo preenche_grafo(int *excessao_zero) {
//--------------------Lendo dados do arquivo-----------//
	Grafo gr;
	int i;
    char url[] = "dados.txt", n_vertices[1];
    FILE *arq;
    arq = fopen(url, "r");

    for(i=0;i<50;i++) 
    	gr.elementos[i] = -1;

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else {
        n_vertices[0] = fgetc(arq);   //Pega o primeiro caractere do arquivo que representa o número de elementos
    	int n_vertices_inteiro = atoi(n_vertices);    //Transformação de char para inteiro
	    gr.n_vertices = n_vertices_inteiro;

        // Inicialização das propriedades
        gr.propriedade_reflexiva = 1;
        gr.propriedade_irreflexiva = 1;
        gr.propriedade_simetrica = 1;
        gr.propriedade_anti_simetrica = 1;
        gr.propriedade_assimetrica = 1;
        gr.propriedade_transitiva = 1;
        gr.relacao_equivalencia = 1;
        gr.relacao_ordem_parcial = 1;

        if(gr.n_vertices == 0)    // Todas propriedades são verdadeiras
            *excessao_zero = 1;
        else {
            *excessao_zero = 0;
    	    // Alocação da Matriz de adjacencias quadrada:

    	    gr.matriz_adjacencia = (int**) calloc(gr.n_vertices, sizeof(int*));
    	    for(i=0;i<gr.n_vertices;i++)
    	    	gr.matriz_adjacencia[i] = (int*) calloc(gr.n_vertices, sizeof(int)); 

       		char info[50];
            int linha=0;
            while(fgets(info, sizeof(info), arq)!=NULL) {
                if(linha) { //Se não estiver na primeira linha do arquivo temos as ligações
                    //Lendo dados referentes aos relacionamentos feitos entre as arestas do grafo
                    int n1,n2;
                    char aux1[1], aux2[1];
                    aux1[0] = info[0];
                    aux2[0] = info[2];
                    //Conversões de char para inteiro
                    n1 = aux1[0] - '0';
                    n2 = aux2[0] - '0';

                    insere_aresta(gr, n1, n2);
                } 
                else { //Se estivermos na primeira linha do arquivo temos os nomes dados as arestas a partir da segunda posição da linha, pois na primeira tem a quantidade de arestas
                    int cont = 0;
                    for(i=1;i<strlen(info);i+=2) {
                        int nome;
                        char aux[1];
                        aux[0] = info[i];
                        nome = aux[0] - '0';
                        gr.elementos[cont] = nome;
                        cont++;
                    }
                }
                linha++;
            }
        }
    	fclose(arq);
	}
	return gr;
}

void insere_aresta(Grafo gr, int orig, int dest) {    //Função para inserir um relacionamento 
    int i, nova_origem, novo_destino;
/*
Realização da tradução entre o nome colocado pelo usuário e a verdadeira posição que esse númemro ocupa no vetor,
de forma que os calculos ocorram de forma transparente para o usuário.
*/
    for(i=0;gr.elementos[i]!=-1;i++) {
        if(gr.elementos[i] == orig)
            nova_origem=i;
        if(gr.elementos[i] == dest)
            novo_destino=i;
    }

    gr.matriz_adjacencia[nova_origem][novo_destino] = 1;
    gr.n_ligacoes++;           //O número total de relacionamentos do grafo aumenta.
}

void imprime_matriz(Grafo gr) {
	int i, j;

	printf("\n\t");
	for(i=0;i<gr.n_vertices;i++)
		printf("%d ", gr.elementos[i]);

	printf("\n\n\n");
	for(i=0;i<gr.n_vertices;i++) {
		printf("%d\t", gr.elementos[i]);
		for(j=0;j<gr.n_vertices;j++) {
			printf("%d ", gr.matriz_adjacencia[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int** aloca_matriz(int tam) {  
    int i,j; 
    int **m = (int**) calloc(tam, sizeof(int*));
 
    for(i=0;i<tam;i++)
        m[i] = (int*) calloc(tam, sizeof(int)); 
    return m;
}

void reflexiva(Grafo gr) {
    int i, **matriz_adjacencia_auxiliar = aloca_matriz(gr.n_vertices);

    for(i=0;i<gr.n_vertices;i++)
        if(gr.matriz_adjacencia[i][i] == 0){
            matriz_adjacencia_auxiliar[i][i] = 1;
            gr.propriedade_reflexiva = 0;
        }

    if(gr.propriedade_reflexiva == 1)
        printf("1. Reflexiva: V\n");
    else {
        printf("1. Reflexiva: F\n");
        for(i=0;i<gr.n_vertices;i++) {
            if(matriz_adjacencia_auxiliar[i][i] == 1)
                printf("(%d,%d); ", gr.elementos[i], gr.elementos[i]);
        }
        printf("\n");
    }
}

void irreflexiva(Grafo gr) {
    int i, **matriz_adjacencia_auxiliar = aloca_matriz(gr.n_vertices);

    for(i=0;i<gr.n_vertices;i++)
        if(gr.matriz_adjacencia[i][i] == 1){
            matriz_adjacencia_auxiliar[i][i] = 1;
            gr.propriedade_irreflexiva = 0;
        }

    if(gr.propriedade_irreflexiva == 1)
        printf("2. Irreflexiva: V\n");
    else {
        printf("2. Irreflexiva: F\n");
        for(i=0;i<gr.n_vertices;i++) {
            if(matriz_adjacencia_auxiliar[i][i] == 1)
                printf("(%d,%d); ", gr.elementos[i], gr.elementos[i]);
        }
        printf("\n");
    }
}

void simetrica(Grafo gr) {
    int i, j, **matriz_adjacencia_auxiliar = aloca_matriz(gr.n_vertices);
    
    for(i=0;i<gr.n_vertices;i++) 
        for(j=0;j<gr.n_vertices;j++)
            if(gr.matriz_adjacencia[i][j] == 1)
                if(gr.matriz_adjacencia[j][i] == 0){
                    gr.propriedade_simetrica = 0;
                    matriz_adjacencia_auxiliar[i][j] = 1;
                }

    if(gr.propriedade_simetrica == 1)
        printf("3. Simetrica: V\n");
    else {
        printf("3. Simetrica: F\n");
        for(i=0;i<gr.n_vertices;i++) {
            for(j=0;j<gr.n_vertices;j++) {
                if(matriz_adjacencia_auxiliar[i][j] == 1)
                    printf("(%d,%d) e (%d,%d); ", gr.elementos[i], gr.elementos[j], gr.elementos[j], gr.elementos[i]);
            }
        }
        printf("\n");
    }
}

void propriedades(Grafo gr) {
    printf("\n\nPropriedades:\n\n");
    reflexiva(gr); 
    irreflexiva(gr);
    simetrica(gr);
}

void inicializar() {
    int excessao_zero;
	Grafo gr = cria_grafo(&excessao_zero);
    propriedades(gr);
    libera_matriz(gr.matriz_adjacencia, gr.n_vertices);
}