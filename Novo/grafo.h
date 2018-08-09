/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG E Aluno de Ciência da Computação UFMG
*/
//Declaração de funções:
typedef struct grafo Grafo;

// #1)
Grafo cria_grafo(int *excessao_zero);
// #2)
Grafo preenche_grafo(int *excessao_zero);
// #3)
void insere_aresta(Grafo gr, int orig, int dest);
// #4)
void imprime_matriz(Grafo gr);
// #5)
void inicializar();
// #6)
void propriedades(Grafo gr);
// #7)
void libera_matriz(int **m, int tam);
// #8)
int** aloca_matriz(int tam);