//Declaração de funções:

typedef struct grafo Grafo;

//#1)
Grafo* cria_Grafo();
//#2)
void libera_Grafo(Grafo* gr);
//#3)
int insereAresta(Grafo* gr, int orig, int dest);
//#4)
void imprime_Grafo(Grafo *gr);
//#5)
void eh_Reflexivo(Grafo *gr, int fecho);
//#6)
void eh_Irreflexivo(Grafo *gr, int fecho);
//#7)
int removeAresta(Grafo* gr, int orig, int dest);
//#8)
int remove_Simetrico(Grafo* gr2);
//#9)
void eh_Simetrico(Grafo *gr, int fecho);
//#10)
void eh_Anti_simetrico(Grafo *gr, int fecho);
//#11)
void eh_Assimetrica(Grafo* gr);
//#12)
void eh_Transitivo(Grafo* gr, int fecho);
//#13)
void relacao_Equivalencia(Grafo* gr);
//#14)
void relacao_Ordem_Parcial(Grafo* gr);
//#15)
void fecho_Reflexivo(Grafo* gr);
//#16)
void fecho_Simetrico(Grafo* gr);
//#17)
void fecho_Transitivo(Grafo* gr);
//#18)
void inicializar();