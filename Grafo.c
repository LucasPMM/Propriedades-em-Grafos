/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - T�cnico em inform�tica formado pelo Coltec/UFMG E Aluno de Ci�ncia da Computa��o UFMG
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h" 

struct grafo{
    int nro_vertices;       //N�mero total de vertices que o grafo ter�
    int n_ligacoes;         //N�mero total de liga��es que o grafo far�
    int** arestas;          //Matriz de adjac�ncias que armazena as liga��es do grafo
    int* grau;              //Vetor que representa a quantidade de liga��es que cada v�rtice faz
    int elementos[50];      //Nomes dos v�rtices fornecidos pelo usu�rio
//elementos[50] : o n�mero m�ximo de relacionamentos que o grafo pode ter � 50 (contando com ele mesmo)
/*
O programa funciona de forma transparente para o usu�rio. S�o inseridos os v�rtices 10, 13 e 15, por exemplo.
Internamente, se os v�rtices forem inseridos nessa ordem, eles ser�o armazenados no vetor elementos na posi��o 
[0], [1] e [2] e ser�o tratados como elementos 0, 1 e 2 nos momentos de compara��es. Contudo, na hora de printar 
para o usu�rio, seus nomes s�o traduzidos pelos verdadeiros armazenados no vetor elementos.
*/
    int lig_aux1;
    int lig_aux2;
//Propriedades:
    int reflexiva;
    int irreflexiva;
    int simetrica;
    int anti_simetrica;
    int assimetrica;
    int transitiva;
};

Grafo* cria_Grafo(){
//Fun��o que inicializa todo o grafo bem como suas propriedades dinamicamente alocadas.
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        int nro_vertices;
//--------------------Lendo dados do arquivo-----------//
        char url[]="dados.txt";
        char ch[1];
        FILE *arq;
        arq = fopen(url, "r");
        if(arq == NULL)
            printf("Erro, nao foi possivel abrir o arquivo\n");
        else
            ch[0]=fgetc(arq);   //Pega o primeiro caractere do arquivo que representa o n�mero de elementos
        fclose(arq);
        nro_vertices = atoi(ch);    //Transforma��o de char para inteiro
        gr->nro_vertices = nro_vertices;
//----------------------------------------------------//
        gr->grau = (int*) calloc(gr->nro_vertices,sizeof(int));
        gr->arestas = (int**) malloc(gr->nro_vertices * sizeof(int*));
        for(i=0; i<gr->nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(50 * sizeof(int));
        gr->n_ligacoes=0;
//--------------------Lendo dados do arquivo-----------//
        for(i=0;i<50;i++)
            gr->elementos[i] = -1;
        char info[50];
        arq = fopen(url, "r");
        if(arq == NULL)
            printf("Erro, nao foi possivel abrir o arquivo\n");
        else{
            int controle=0;
            while( (fgets(info, sizeof(info), arq))!=NULL ){
                if(controle){ //Se n�o estiver na primeira linha do arquivo temos as liga��es
                    //Lendo dados referentes aos relacionamentos feitos entre as arestas do grafo
                    int n1,n2;
                    char aux1[1], aux2[1];
                    aux1[0] = info[0];
                    aux2[0] = info[2];
                    //Convers�es de char para inteiro
                    n1 = aux1[0] - '0';
                    n2 = aux2[0] - '0';

                    int arest = insereAresta(gr, n1, n2);
                }
                else{ //Se estivermos na primeira linha do arquivo temos os nomes dados as arestas a partir da segunda posi��o da linha, pois na primeira tem a quantidade de arestas
                    int cont=0;
                    for(i=2;i<strlen(info);i+=2){
                        int nome;
                        char aux[1];
                        aux[0] = info[i];
                        nome = aux[0] - '0';
                        gr->elementos[cont] = nome;
                        cont++;
                    }
                }
                controle++;
            }
        }
        fclose(arq);
        //Inicializa��o das propriedades do grafo
        gr->reflexiva = -1;
        gr->irreflexiva = -1;
        gr->simetrica = -1;
        gr->anti_simetrica = -1;
        gr->assimetrica = -1;
        gr->transitiva = -1;
        gr->lig_aux1=-1;
        gr->lig_aux2=-1;
//----------------------------------------------------//
    }
    return gr;
}

void libera_Grafo(Grafo* gr){   //Fun��o para liberar o espa�o alocado na mem�ria
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest){    //Fun��o para inserir um relacionamento 
    int i, nova_origem, novo_destino;
/*
Realiza��o da tradu��o entre o nome colocado pelo usu�rio e a verdadeira posi��o que esse n�memro ocupa no vetor,
de forma que os calculos ocorram de forma transparente para o usu�rio.
*/
    for(i=0;gr->elementos[i]!=-1;i++){
        if(gr->elementos[i]==orig)
            nova_origem=i;
        if(gr->elementos[i]==dest)
            novo_destino=i;
    }
    if(gr == NULL)
        return 0;
    if(nova_origem < 0 || nova_origem >= gr->nro_vertices)
        return 0;
    if(novo_destino < 0 || novo_destino >= gr->nro_vertices)
        return 0;
    gr->arestas[nova_origem][gr->grau[nova_origem]] = novo_destino;
    gr->grau[nova_origem]++;    //O grau da aresta aumenta.
    gr->n_ligacoes++;           //O n�mero total de relacionamentos do grafo aumenta.
    return 1;
}

void imprime_Grafo(Grafo *gr){  //Fun��o que imprime os relacionamentos realizados no grafo
    if(gr == NULL)
        return;
    int i, j;
    //Tradu��o anteriormente mencionada na qual imprimi-se o verdadeiro nome do v�rtice usando sua verdadeira posi��o no vetor elementos
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ",gr->elementos[i]);
        for(j=0; j < gr->grau[i]; j++)
            printf("%d, ", gr->elementos[gr->arestas[i][j]]);    
        printf("\n");
    }
}

void eh_Reflexivo(Grafo *gr, int fecho){ //Verificar a propriedade reflexiva do grafo
//Fecho == 0 -> realizar a fun��o normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho reflexivo
    int i, j, verificado=0;
    for(i=0; i < gr->nro_vertices; i++){
        for(j=0; j < gr->grau[i]; j++){
            if(i == gr->arestas[i][j]){ //Olhar se cada v�rtice se liga a ele mesmo
                verificado++;
            }
        }
    }
    if(verificado == gr->nro_vertices){
        printf("1. Reflexiva: V\n");
        gr->reflexiva = 1;
    }
    else if(fecho==1){
        //criar um segundo grafo, inserir as liga��es, chamar a fun��o eh_Irreflexivo, liberar o grafo
        Grafo* gr2 = cria_Grafo();
        int cont=0;
        for(i=0; i < gr2->nro_vertices; i++){
            for(j=0; j < gr2->grau[i]; j++){
                if(i == gr2->arestas[i][j]){}
                else
                    cont++;
            }
            if(cont == gr2->grau[i]){ //Inserir relacionamentos n�o reflexivos
                //printf("Estou inserindo %d %d\n", gr->elementos[i],gr->elementos[i]);
                insereAresta(gr2,gr->elementos[i],gr->elementos[i]);
            }
            cont=0;
        }
        eh_Irreflexivo(gr2,1);
        libera_Grafo(gr2);
    }
    else{
        printf("1. Reflexiva: F\n");
        gr->reflexiva = 0;
        int entrou=0, cont=0;
        for(i=0; i < gr->nro_vertices; i++){
            for(j=0; j < gr->grau[i]; j++){
                if(i == gr->arestas[i][j]){}
                else
                    cont++;
            }
            if(cont == gr->grau[i]){ //Caso nem todos os v�rtices sejam reflexivos, imprimir os que n�o s�o
                printf("(%d,%d); ",gr->elementos[i],gr->elementos[i]);                    
                entrou++;       
            }
            cont=0;
        }
        if(entrou)
            printf("\n");
    }
}

void eh_Irreflexivo(Grafo *gr, int fecho){ //Verificar se o grafo � irreflexivo (inverso da fun��o anterior)
//Fecho == 0 -> realizar a fun��o normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho reflexivo
    int i, j, verificado=0;
    for(i=0; i < gr->nro_vertices; i++){
        for(j=0; j < gr->grau[i]; j++){
            if(i == gr->arestas[i][j]){
                verificado++;
            }
        }
    }
    if(verificado == 0){
        printf("2. Irreflexiva: V\n");
        gr->irreflexiva = 1;
    }
    else if(fecho == 1){ //imprimir o fecho reflexivo da rela��o
        //Imprimir todos os vertices ja existentes e depois os faltantes
        printf("Fecho reflexivo da relacao = {");
        int entrou=0;
        for(i=0; i < gr->nro_vertices; i++){
            for(j=0; j < gr->grau[i]; j++){
                if(entrou)
                    printf(",");
                entrou=0;
                if(i != gr->arestas[i][j]){
                    printf("(%d,%d)",gr->elementos[i], gr->elementos[gr->arestas[i][j]]);    
                    entrou=1;
                }
            }
        }
        entrou=0;
        for(i=0; i < gr->nro_vertices; i++){
            for(j=0; j < gr->grau[i]; j++){
                if(entrou)
                    printf(",");
                entrou=0;
                if(i == gr->arestas[i][j]){
                    printf("(%d,%d)", gr->elementos[gr->arestas[i][j]],gr->elementos[gr->arestas[i][j]]);   
                    entrou=1;               
                }
            }
        }
        printf("}\n");
    }
    else{ //Caso seja reflexiva, imprimir esses casos que n�o a fazem ser irreflexiva
        printf("2. Irreflexiva: F\n");
        gr->irreflexiva = 0;
        for(i=0; i < gr->nro_vertices; i++){
            for(j=0; j < gr->grau[i]; j++){
                if(i == gr->arestas[i][j])
                    printf("(%d,%d); ", gr->elementos[gr->arestas[i][j]],gr->elementos[gr->arestas[i][j]]);                    
            }
        }
        printf("\n");
    }
}

int removeAresta(Grafo* gr, int orig, int dest){ //Retirar um relacionamento
    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig]){//elemento nao encontrado
        return 0;
    }
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    gr->n_ligacoes--;
    return 1;
}

int remove_Simetrico(Grafo* gr2){
/*
A melhor forma de implementar esse fun��o seria de forma recursiva, pois ap�s cada remo��o os ponteiros mudam sua posi��o 
no processo de realoca��o. Contudo, ao tentar realizar essa fun��o de forma recursiva, ocorreram diversos erros de segmenta��o
os quais n�o consegui resolver. Sendo assim, s�o realizadas v�rias chamadas a essa fun��o at� se ter a certeza que n�o faltam
liga��es a serem removidas. 
*/
    int i, j, k, controle=0;
//Caminhar pela matriz de adjac�ncias dos elementos que o elemento i se liga para verificar se existe a rela��o (i,n) e (n,i)
    for(i=0;i<gr2->nro_vertices;i++){
        for(j=0;j<gr2->grau[i];j++){
            for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                    if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){
                        int aux1=gr2->arestas[i][j];
                        int aux2=gr2->arestas[gr2->arestas[i][j]][k];
                        int y = removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);
                        int x = removeAresta(gr2,aux2,aux1);
                        controle++;
                    }
                    else{ //Caso seja um elemento reflexivo, n�o � necessario remover seu inverso
                        int x = removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);                        
                        controle++;
                    }
                }
            }
        }
    }
    return controle;
}

void eh_Simetrico(Grafo *gr, int fecho){ //Verificar a simetria do grafo
//Fecho == 0 -> realizar a fun��o normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho simetrico
/*
Cria��o de um grafo auxiliar do qual cada aresta � removida se a mesma for sim�trica.
Se o grafo n�o tiver nenhuma liga��o no final significa que todos os relacionamentos 
obedecem a seguinte ordem: se existe (x,y) tamb�m existe (y,x) e ambos s�o removidos.
*/
    Grafo* gr2 = cria_Grafo();
    int i, j,k,entrou=0, controle=-1;
/*
Chamar a fun��o at� n�o ter ligacoes a serem disfeitas pois a cada remo��o, as posi��es dos ponteiros s�o alteradas, 
fazendo com que seja necess�rio chamar a fun��o algumas vezes para que tenha certeza que n�o sobraram liga��es em posi��es n�o verificadas.
*/
    while(controle!=0){
        controle = remove_Simetrico(gr2);
    }
    controle=-1;
    if(gr2->n_ligacoes == 0 && fecho == 0){
        printf("3. Simetrica: V\n");
        gr->simetrica = 1;
    }
    else{ //Caso n�o seja sim�trica, imprimir as liga��es restantes no grafo
        printf("3. Simetrica: F\n");
        gr->simetrica = 0;
        int entrou=0;
        //imprime_Grafo(gr2);
        for(i=0; i < gr2->nro_vertices; i++){
            for(j=0; j < gr2->grau[i]; j++){
                printf("(%d,%d); ",gr2->elementos[gr2->arestas[i][j]],gr2->elementos[i]);                    
                entrou++;                    
            }
        }
        if(entrou)
            printf("\n");
    }
    libera_Grafo(gr2);
}

void eh_Anti_simetrico(Grafo *gr, int fecho){ //Verificar se o grafo � anti-sim�trico
//Fecho == 0 -> realizar a fun��o normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho simetrico
    Grafo* gr2 = cria_Grafo();
    int i, j, k, temp=0, propriedade = 1;
    for(i=0;i<gr2->nro_vertices;i++){
        for(j=0;j<gr2->grau[i];j++){
            for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                    if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){ // Encontrou uma rela��o de simetria entre vertices diferentes
                        //printf("---- %d - %d-----\n", gr->elementos[gr2->arestas[i][j]], gr->elementos[gr2->arestas[gr2->arestas[i][j]][k]]);
                        temp++;
                        int aux1=gr2->arestas[i][j];
                        int aux2=gr2->arestas[gr2->arestas[i][j]][k];
                        removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);
                        int x = removeAresta(gr2,aux2,aux1);
                    }
                    else{
                        removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);                        
                    }
                }
            }
        }
    }
    libera_Grafo(gr2);
    if(temp != 0 && fecho == 0){ //Caso n�o seja anti_simetrica, � necess�rio apresentar as liga��es que provam isso
        printf("4. Anti_simetrica: F\n");
        gr->anti_simetrica = 0;
        gr2 = cria_Grafo();
        for(i=0;i<gr2->nro_vertices;i++){
            for(j=0;j<gr2->grau[i];j++){
                for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                    if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                        if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){
                            int aux1=gr2->arestas[i][j];
                            int aux2=gr2->arestas[gr2->arestas[i][j]][k];
                            removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);
                            int x = removeAresta(gr2,aux2,aux1);
                            printf("(%d,%d) e (%d,%d); ", gr2->elementos[aux2],gr2->elementos[aux1], gr2->elementos[aux1], gr2->elementos[aux2]);
                        }
                        else{ //Caso de arestas reflexivas
                            removeAresta(gr2,gr2->arestas[i][j],gr2->arestas[gr2->arestas[i][j]][k]);                        
                        }
                    }
                }
            }
        }
        printf("\n");
    }
    else if(fecho == 1){
        int entrou=0;
        gr2 = cria_Grafo();
        printf("Fecho simetrico da relacao = {");
        for(i=0;i<gr2->nro_vertices;i++){
            for(j=0;j<gr2->grau[i];j++){
                for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                    if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                        if(entrou)
                            printf(",");
                        if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){
                            int aux1=gr2->arestas[i][j];
                            int aux2=gr2->arestas[gr2->arestas[i][j]][k];
                            printf("(%d,%d)", gr2->elementos[aux2],gr2->elementos[aux1]);
                        }
                        else{
                            printf("(%d,%d)",gr2->elementos[gr2->arestas[i][j]],gr2->elementos[gr2->arestas[gr2->arestas[i][j]][k]]);
                        }
                        entrou=1;
                    }
                }
            }
        }
        printf("}\n");
    }
    else{
        printf("4. Anti_simetrica: V\n");
        gr->anti_simetrica = 1;
    }
    //libera_Grafo(gr2);
}

int verificaAssimetria(Grafo* gr){
    Grafo* aux = cria_Grafo();
    int controle = remove_Simetrico(aux);
    if(controle==0)
        return 1;
    else
        return 0;

}

void eh_Assimetrica(Grafo* gr){ //Verificar se o grafo � assim�trico
    int retorno = verificaAssimetria(gr);
    if(retorno == 1){
        gr->assimetrica = 1;
        printf("5. Assimetrica: V\n");
        return;
    }
    else{
        gr->assimetrica = 0;
        printf("5. Assimetrica: F\n");
        return;
/*      Parte que imprime os pares faltantes para ser assimetrica
        int i,j,k,entrou=0,e=0;

        for(i=0;i<gr->nro_vertices;i++){
            for(j=0;j<gr->grau[i];j++){
                for(k=0;k<gr->grau[gr->arestas[i][j]];k++){
                    if(i == gr->arestas[gr->arestas[i][j]][k]){
                        if(entrou%2==0 && entrou!=0)
                            printf(",");
                        else if(entrou%3==0 && entrou!=0)
                            printf(";");
                        if(entrou%2!=0){
                            e=1;
                            printf(" e ");
                        }
                        if(e){
                            e=0;
                            printf("(%d,%d);",gr->elementos[i], gr->elementos[gr->arestas[i][j]]);    
                        }
                        else
                            printf("(%d,%d)",gr->elementos[i], gr->elementos[gr->arestas[i][j]]);    
                        entrou++;
                    }
                }
            }
        }
        printf("\n");
*/ 
    }
    if(gr->irreflexiva == 1 && gr->anti_simetrica == 1){
        gr->assimetrica = 1;
        printf("5. Assimetrica: V\n");
        return;
    }
}

void copia_Transitivo(Grafo* gr,int fecho){
    if(fecho==1){
        int i=0,j=0,k=0,l=0;
        char *ligacoes_faltantes=NULL, tamanho=2;
        for(i=0;i<gr->nro_vertices;i++){
            int temp = i;
            for(j=0;j<gr->grau[i];j++){
                int soma_arestas=0;
                for(k=0;k<gr->grau[gr->arestas[temp][j]];k++){
                    //if(i!=gr->arestas[gr->arestas[temp][j]][k]){
                        int entrou = 1;
                        for(l=0;l<gr->grau[i];l++){
                            soma_arestas++;
                            if(gr->arestas[gr->arestas[temp][j]][k] == gr->arestas[i][l]){
                                entrou = 1;
                                break;
                            }
                            else
                                entrou = 0;
                        }
                        if(entrou == 0){
                            //printf("Completar com a ligacao: %d %d\n", gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                            gr->lig_aux1=gr->elementos[i];
                            gr->lig_aux2=gr->elementos[gr->arestas[gr->arestas[temp][j]][k]];
                            return;
                        }
                    //}
                }
            }
        }
    }
    gr->lig_aux1=-1;
    gr->lig_aux2=-1;
}

void verifica_ligacoes_faltantes(Grafo* gr){
    int i=0,j=0,k=0,l=0;
    char *ligacoes_faltantes=NULL, tamanho=2;
    for(i=0;i<gr->nro_vertices;i++){
        int temp = i;
        for(j=0;j<gr->grau[i];j++){
            int soma_arestas=0;
            for(k=0;k<gr->grau[gr->arestas[temp][j]];k++){
                //if(i!=gr->arestas[gr->arestas[temp][j]][k]){
                    int entrou = 1;
                    for(l=0;l<gr->grau[i];l++){
                        soma_arestas++;
                        if(gr->arestas[gr->arestas[temp][j]][k] == gr->arestas[i][l]){
                            entrou = 1;
                            break;
                        }
                        else
                            entrou = 0;
                    }
                    if(entrou == 0){
                        //printf("Completar com a ligacao: %d %d\n", gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                        gr->lig_aux1=gr->elementos[i];
                        gr->lig_aux2=gr->elementos[gr->arestas[gr->arestas[temp][j]][k]];
                        return;
                    }
                //}
            }
        }
    }
    gr->lig_aux1=-1;
    gr->lig_aux2=-1;
}

void eh_Transitivo(Grafo* gr, int fecho){ //Verificar se o grafo � transitivo 
//Ver se um vertice se liga com todos os ligantes de suas liga��es
    int i=0,j=0,k=0,l=0;
    char *ligacoes_faltantes=NULL, tamanho=2;
    Grafo* gr2 = cria_Grafo();
    for(i=0;i<gr->nro_vertices;i++){
        int temp = i;
        for(j=0;j<gr->grau[i];j++){
            int verificado=0;
            for(k=0;k<gr->grau[gr->arestas[temp][j]];k++){
                //if(i!=gr->arestas[gr->arestas[temp][j]][k]){
                    int entrou = 1;
                    for(l=0;l<gr->grau[i];l++){
                        if(gr->arestas[gr->arestas[temp][j]][k] == gr->arestas[i][l]){
                            verificado++;
                            entrou = 1;
                            break;
                        }
                        else
                            entrou = 0;
                    }
                    if(entrou == 0 && fecho == 0){
                        gr->transitiva = 0;
                        //printf("Necess�ria a liga��es: %d %d\n", gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                        //Armazenar todas as liga��es em um vetor dinamicamente alocado.
                        //Duas posi��es seguidas s�o um par de relacionamento que est� faltando.
                        //Armazenar as posi��es em um vetor de caracteres.
                        if(ligacoes_faltantes==NULL){
                            ligacoes_faltantes = (char*) malloc (tamanho * sizeof (char));
                            ligacoes_faltantes[0] = gr->elementos[i]+'0';
                            ligacoes_faltantes[1] = gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]+'0';
                        }
                        else{
                            tamanho+=2;
                            ligacoes_faltantes = (char*) realloc (ligacoes_faltantes,tamanho*sizeof(char));
                            ligacoes_faltantes[tamanho-2] = gr->elementos[i]+'0';
                            ligacoes_faltantes[tamanho-1] = gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]+'0'; 
                        }
                    }
                    else if(entrou == 0 && fecho == 1){
                        //printf("Completar com a ligacao: %d %d\n", gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                        insereAresta(gr2,gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                    }
                //}
            }
        }
    }
    if(fecho == 0){
        int existe_ligacao=0;
        verifica_ligacoes_faltantes(gr2);
        while(gr2->lig_aux1!=-1){
            for(i=0;i<strlen(ligacoes_faltantes)-1;i=i+2){
                if(ligacoes_faltantes[i]==gr2->lig_aux1+'0' && ligacoes_faltantes[i+1]==gr2->lig_aux2+'0'){
                    existe_ligacao=1;
                }
            }
            if(existe_ligacao==0){
                tamanho+=2;
                ligacoes_faltantes = (char*) realloc (ligacoes_faltantes,tamanho*sizeof(char));
                ligacoes_faltantes[tamanho-2] = gr2->lig_aux1+'0';
                ligacoes_faltantes[tamanho-1] = gr2->lig_aux2+'0'; 
            }
            existe_ligacao=0;
            insereAresta(gr2,gr2->lig_aux1,gr2->lig_aux2);
            verifica_ligacoes_faltantes(gr2);
        }
        if(gr->transitiva == -1)
            printf("6. Transitiva: V\n");
        else{ //Caso n�o seja transitivo, imprimir liga��es que satisfazem essa afirma��o.
            printf("6. Transitiva: F\n");
            for(i=0;i<tamanho;i+=2){
                printf("(%c,%c); ",ligacoes_faltantes[i],ligacoes_faltantes[i+1]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else{
        int controle_pior_caso=0;
        copia_Transitivo(gr2,fecho);
        while(gr2->lig_aux1!=-1){
            insereAresta(gr2,gr2->lig_aux1,gr2->lig_aux2);
            copia_Transitivo(gr2,fecho);
            controle_pior_caso=1;
        }

        int entrou=0;
        printf("Fecho transitivo da relacao = {");
        if(gr->transitiva==-1){
            for(i=0; i < gr->nro_vertices; i++){
                for(j=0; j < gr->grau[i]; j++){
                    if(entrou)
                        printf(",");
                    printf("(%d,%d)",gr->elementos[i], gr->elementos[gr->arestas[i][j]]);    
                    entrou=1;
                }
            }
        }
        else if(controle_pior_caso=1){
            for(i=0; i < gr2->nro_vertices; i++){
                for(j=0; j < gr2->grau[i]; j++){
                    if(entrou)
                        printf(",");
                    printf("(%d,%d)",gr2->elementos[i], gr2->elementos[gr2->arestas[i][j]]);    
                    entrou=1;
                }
            }   
        }
        else{
            for(i=0;i<gr2->nro_vertices;i++){
                for(j=0;j<gr2->grau[i];j++){
                    for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                        if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                            if(entrou)
                                printf(",");
                            if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){
                                int aux1=gr2->arestas[i][j];
                                int aux2=gr2->arestas[gr2->arestas[i][j]][k];
                                printf("(%d,%d)", gr2->elementos[aux2],gr2->elementos[aux1]);
                            }
                            else{
                                printf("(%d,%d)",gr2->elementos[gr2->arestas[i][j]],gr2->elementos[gr2->arestas[gr2->arestas[i][j]][k]]);
                            }
                            entrou=1;
                        }
                    }
                }
            }
        }
        printf("}\n\n");
        libera_Grafo(gr2);
    }
}

void relacao_Equivalencia(Grafo* gr){ //Verificar a rela��o de equivalencia
    //Reflexiva+Sim�trica+Transitiva
    if(gr->reflexiva==1 && gr->simetrica==1 && gr->transitiva==-1)
        printf("Relacao de equivalencia: V\n");
    else
        printf("Relacao de equivalencia: F\n");
}

void relacao_Ordem_Parcial(Grafo* gr){ //Verificar a rela��o de ordem parcial
    //Reflexiva+Anti-Sim�trica+Transitiva
    if(gr->reflexiva==1 && gr->anti_simetrica==1 && gr->transitiva==-1)
        printf("Relacao de ordem parcial: V\n\n");
    else
        printf("Relacao de ordem parcial: F\n\n");
}

void fecho_Reflexivo(Grafo* gr){
    if(gr->reflexiva == 1)
        eh_Irreflexivo(gr,1);
    else //Completar as liga��es e imprimir
        eh_Reflexivo(gr,1);
}

void verificaFechoSimetrico(Grafo *gr3, Grafo *gr4){
    int i,j,k,entrou=0,controle=-1;
    //criar um grafo 2, realizar as liga��es faltantes, imprimir todo o fecho simetrico, liberar o grafo
    /*A cria��o de dois grafos auxiliares de forma que um passe pela fun��o remove_Simetrico e sua sa�da gere
    as liga��es necess�rias para imprimir o fecho de forma completa. As liga��es faltentes s�o realizdas no 
    segundo grafo auxiliar*/
    while(controle!=0){
        controle = remove_Simetrico(gr3);
    }
    for(i=0; i < gr3->nro_vertices; i++){
        for(j=0; j < gr3->grau[i]; j++)
            insereAresta(gr4,gr3->elementos[gr3->arestas[i][j]],gr3->elementos[i]);
    }
    printf("Fecho simetrico da relacao = {");
    //imprimir todas liga��es j� existentes e depois imprimir as faltantes:
    for(i=0;i<gr4->nro_vertices;i++){
        for(j=0;j<gr4->grau[i];j++){
            for(k=0;k<gr4->grau[gr4->arestas[i][j]];k++){
                if(i == gr4->arestas[gr4->arestas[i][j]][k]){
                    if(entrou)
                        printf(",");
                    if(gr4->arestas[i][j] != gr4->arestas[gr4->arestas[i][j]][k]){
                        int aux1=gr4->arestas[i][j];
                        int aux2=gr4->arestas[gr4->arestas[i][j]][k];
                        printf("(%d,%d)", gr4->elementos[aux2],gr4->elementos[aux1]);
                    }
                    else{
                        printf("(%d,%d)",gr4->elementos[gr4->arestas[i][j]],gr4->elementos[gr4->arestas[gr4->arestas[i][j]][k]]);
                    }
                    entrou=1;
                }
            }
        }
    }
    printf("}\n");
    libera_Grafo(gr3);
    libera_Grafo(gr4);
}

void fecho_Simetrico(Grafo* gr, Grafo* gr3, Grafo* gr4){
    if(gr->simetrica == 1)
        eh_Anti_simetrico(gr,1);
    else
        verificaFechoSimetrico(gr3,gr4);
}

void fecho_Transitivo(Grafo* gr){
//    if(gr->irreflexiva == 1 && gr->anti_simetrica == 1)
        eh_Transitivo(gr,1);
//Caso a rela��o n�o seja assimetrica n�o � necess�rio listar os pares pois j� foram listados anteriormente.
}

void inicializar(){
    Grafo* gr = cria_Grafo();// inicializa��o do grafo
    Grafo* gr3 = cria_Grafo();
    Grafo* gr4 = cria_Grafo();
    system("clear");
//    printf("\n\nPropriedades:\n\n");
//    imprime_Grafo(gr);
    printf("\n\n");
    eh_Reflexivo(gr,0);
    eh_Irreflexivo(gr,0);
    eh_Simetrico(gr,0);
    eh_Anti_simetrico(gr,0);
    eh_Assimetrica(gr);
    eh_Transitivo(gr,0);
    relacao_Equivalencia(gr);
    relacao_Ordem_Parcial(gr);
    fecho_Reflexivo(gr);
    fecho_Simetrico(gr,gr3,gr4);
    fecho_Transitivo(gr);
    libera_Grafo(gr);
}