/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG E Aluno de Ciência da Computação UFMG
*/
//Declaração de funções:
typedef struct grafo Grafo;

// #1)
Grafo* cria_grafo(int *excessao_zero);
// #2)
Grafo* preenche_grafo(int *excessao_zero);
// #3)
void insere_aresta(Grafo *gr, int orig, int dest);
// #4)
void imprime_matriz(Grafo *gr);
// #5)
void inicializar();
// #6)
void propriedades(Grafo *gr);
// #7)
void libera_matriz(int **m, int tam);
// #8)
int** aloca_matriz(int tam);
// #9)
void reflexiva(Grafo *gr);
// #10)
void irreflexiva(Grafo *gr);
// #11)
void simetrica(Grafo *gr);
// #12)
void anti_simetrica(Grafo *gr);
// #13)
void assimetrica(Grafo *gr);
// #14)
void transitiva(Grafo *gr);
// #15)
void equivalencia(Grafo *gr);
// #16)
void ordem_parcial(Grafo *gr);
// #17)
void fecho_reflexivo(Grafo *gr);
// #18)
void fecho_simetrico(Grafo *gr);
// #19)
void fecho_transitivo(Grafo *gr);
// #20)
void fecho_padrao(Grafo *gr);