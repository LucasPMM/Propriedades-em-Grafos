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
};


Grafo criaGrafo() {
	Grafo gr;
	gr = preencheGrafo();
	imprimeMatriz(gr);
	return gr;
}

Grafo preencheGrafo() {
//--------------------Lendo dados do arquivo-----------//
	Grafo gr;
	int i;
    char url[]="dados.txt", n_vertices[1];
    FILE *arq;
    arq = fopen(url, "r");

    for(i=0;i<50;i++) 
    	gr.elementos[i] = -1;

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else {
        n_vertices[0]=fgetc(arq);   //Pega o primeiro caractere do arquivo que representa o número de elementos
    	int n_vertices_inteiro = atoi(n_vertices);    //Transformação de char para inteiro
	    gr.n_vertices = n_vertices_inteiro;

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

                insereAresta(gr, n1, n2);
            } else { //Se estivermos na primeira linha do arquivo temos os nomes dados as arestas a partir da segunda posição da linha, pois na primeira tem a quantidade de arestas
                int cont=0;
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
    	fclose(arq);
	}
	return gr;
}

void insereAresta(Grafo gr, int orig, int dest) {    //Função para inserir um relacionamento 
    int i, nova_origem, novo_destino;
/*
Realização da tradução entre o nome colocado pelo usuário e a verdadeira posição que esse númemro ocupa no vetor,
de forma que os calculos ocorram de forma transparente para o usuário.
*/
    for(i=0;gr.elementos[i]!=-1;i++) {
        if(gr.elementos[i]==orig)
            nova_origem=i;
        if(gr.elementos[i]==dest)
            novo_destino=i;
    }

    gr.matriz_adjacencia[nova_origem][novo_destino] = 1;
    gr.n_ligacoes++;           //O número total de relacionamentos do grafo aumenta.
}

void imprimeMatriz(Grafo gr) {
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

void inicializar(){
	Grafo gr = criaGrafo(gr);
}