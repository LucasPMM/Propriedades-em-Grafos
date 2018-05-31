/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG E Aluno de Ciência da Computação UFMG
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h" 

struct grafo{
    int nro_vertices;       //Número total de vertices que o grafo terá
    int n_ligacoes;         //Número total de ligações que o grafo fará
    int** arestas;          //Matriz de adjacências que armazena as ligações do grafo
    int* grau;              //Vetor que representa a quantidade de ligações que cada vértice faz
    int elementos[50];      //Nomes dos vértices fornecidos pelo usuário
//elementos[50] : o número máximo de relacionamentos que o grafo pode ter é 50 (contando com ele mesmo)
/*
O programa funciona de forma transparente para o usuário. São inseridos os vértices 10, 13 e 15, por exemplo.
Internamente, se os vértices forem inseridos nessa ordem, eles serão armazenados no vetor elementos na posição 
[0], [1] e [2] e serão tratados como elementos 0, 1 e 2 nos momentos de comparações. Contudo, na hora de printar 
para o usuário, seus nomes são traduzidos pelos verdadeiros armazenados no vetor elementos.
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
//Função que inicializa todo o grafo bem como suas propriedades dinamicamente alocadas.
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
            ch[0]=fgetc(arq);   //Pega o primeiro caractere do arquivo que representa o número de elementos
        fclose(arq);
        nro_vertices = atoi(ch);    //Transformação de char para inteiro
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
                if(controle){ //Se não estiver na primeira linha do arquivo temos as ligações
                    //Lendo dados referentes aos relacionamentos feitos entre as arestas do grafo
                    int n1,n2;
                    char aux1[1], aux2[1];
                    aux1[0] = info[0];
                    aux2[0] = info[2];
                    //Conversões de char para inteiro
                    n1 = aux1[0] - '0';
                    n2 = aux2[0] - '0';

                    int arest = insereAresta(gr, n1, n2);
                }
                else{ //Se estivermos na primeira linha do arquivo temos os nomes dados as arestas a partir da segunda posição da linha, pois na primeira tem a quantidade de arestas
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
        //Inicialização das propriedades do grafo
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

void libera_Grafo(Grafo* gr){   //Função para liberar o espaço alocado na memória
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest){    //Função para inserir um relacionamento 
    int i, nova_origem, novo_destino;
/*
Realização da tradução entre o nome colocado pelo usuário e a verdadeira posição que esse númemro ocupa no vetor,
de forma que os calculos ocorram de forma transparente para o usuário.
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
    gr->n_ligacoes++;           //O número total de relacionamentos do grafo aumenta.
    return 1;
}

void imprime_Grafo(Grafo *gr){  //Função que imprime os relacionamentos realizados no grafo
    if(gr == NULL)
        return;
    int i, j;
    //Tradução anteriormente mencionada na qual imprimi-se o verdadeiro nome do vértice usando sua verdadeira posição no vetor elementos
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ",gr->elementos[i]);
        for(j=0; j < gr->grau[i]; j++)
            printf("%d, ", gr->elementos[gr->arestas[i][j]]);    
        printf("\n");
    }
}

void eh_Reflexivo(Grafo *gr, int fecho){ //Verificar a propriedade reflexiva do grafo
//Fecho == 0 -> realizar a função normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho reflexivo
    int i, j, verificado=0;
    for(i=0; i < gr->nro_vertices; i++){
        for(j=0; j < gr->grau[i]; j++){
            if(i == gr->arestas[i][j]){ //Olhar se cada vértice se liga a ele mesmo
                verificado++;
            }
        }
    }
    if(verificado == gr->nro_vertices){
        printf("1. Reflexiva: V\n");
        gr->reflexiva = 1;
    }
    else if(fecho==1){
        //criar um segundo grafo, inserir as ligações, chamar a função eh_Irreflexivo, liberar o grafo
        Grafo* gr2 = cria_Grafo();
        int cont=0;
        for(i=0; i < gr2->nro_vertices; i++){
            for(j=0; j < gr2->grau[i]; j++){
                if(i == gr2->arestas[i][j]){}
                else
                    cont++;
            }
            if(cont == gr2->grau[i]){ //Inserir relacionamentos não reflexivos
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
            if(cont == gr->grau[i]){ //Caso nem todos os vértices sejam reflexivos, imprimir os que não são
                printf("(%d,%d); ",gr->elementos[i],gr->elementos[i]);                    
                entrou++;       
            }
            cont=0;
        }
        if(entrou)
            printf("\n");
    }
}

void eh_Irreflexivo(Grafo *gr, int fecho){ //Verificar se o grafo é irreflexivo (inverso da função anterior)
//Fecho == 0 -> realizar a função normalmente
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
    else if(fecho == 1){ //imprimir o fecho reflexivo da relação
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
    else{ //Caso seja reflexiva, imprimir esses casos que não a fazem ser irreflexiva
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
A melhor forma de implementar esse função seria de forma recursiva, pois após cada remoção os ponteiros mudam sua posição 
no processo de realocação. Contudo, ao tentar realizar essa função de forma recursiva, ocorreram diversos erros de segmentação
os quais não consegui resolver. Sendo assim, são realizadas várias chamadas a essa função até se ter a certeza que não faltam
ligações a serem removidas. 
*/
    int i, j, k, controle=0;
//Caminhar pela matriz de adjacências dos elementos que o elemento i se liga para verificar se existe a relação (i,n) e (n,i)
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
                    else{ //Caso seja um elemento reflexivo, não é necessario remover seu inverso
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
//Fecho == 0 -> realizar a função normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho simetrico
/*
Criação de um grafo auxiliar do qual cada aresta é removida se a mesma for simétrica.
Se o grafo não tiver nenhuma ligação no final significa que todos os relacionamentos 
obedecem a seguinte ordem: se existe (x,y) também existe (y,x) e ambos são removidos.
*/
    Grafo* gr2 = cria_Grafo();
    int i, j,k,entrou=0, controle=-1;
/*
Chamar a função até não ter ligacoes a serem disfeitas pois a cada remoção, as posições dos ponteiros são alteradas, 
fazendo com que seja necessário chamar a função algumas vezes para que tenha certeza que não sobraram ligações em posições não verificadas.
*/
    while(controle!=0){
        controle = remove_Simetrico(gr2);
    }
    controle=-1;
    if(gr2->n_ligacoes == 0 && fecho == 0){
        printf("3. Simetrica: V\n");
        gr->simetrica = 1;
    }
    else{ //Caso não seja simétrica, imprimir as ligações restantes no grafo
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

void eh_Anti_simetrico(Grafo *gr, int fecho){ //Verificar se o grafo é anti-simétrico
//Fecho == 0 -> realizar a função normalmente
//Fecho == 1 -> fazer os procedimentos necessarios para imprimir o fecho simetrico
    Grafo* gr2 = cria_Grafo();
    int i, j, k, temp=0, propriedade = 1;
    for(i=0;i<gr2->nro_vertices;i++){
        for(j=0;j<gr2->grau[i];j++){
            for(k=0;k<gr2->grau[gr2->arestas[i][j]];k++){
                if(i == gr2->arestas[gr2->arestas[i][j]][k]){
                    if(gr2->arestas[i][j] != gr2->arestas[gr2->arestas[i][j]][k]){ // Encontrou uma relação de simetria entre vertices diferentes
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
    if(temp != 0 && fecho == 0){ //Caso não seja anti_simetrica, é necessário apresentar as ligações que provam isso
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

void eh_Assimetrica(Grafo* gr){ //Verificar se o grafo é assimétrico
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

void eh_Transitivo(Grafo* gr, int fecho){ //Verificar se o grafo é transitivo 
//Ver se um vertice se liga com todos os ligantes de suas ligações
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
                        //printf("Necessãria a ligações: %d %d\n", gr->elementos[i],gr->elementos[gr->arestas[gr->arestas[temp][j]][k]]);
                        //Armazenar todas as ligações em um vetor dinamicamente alocado.
                        //Duas posições seguidas são um par de relacionamento que está faltando.
                        //Armazenar as posições em um vetor de caracteres.
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
        else{ //Caso não seja transitivo, imprimir ligações que satisfazem essa afirmação.
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

void relacao_Equivalencia(Grafo* gr){ //Verificar a relação de equivalencia
    //Reflexiva+Simétrica+Transitiva
    if(gr->reflexiva==1 && gr->simetrica==1 && gr->transitiva==-1)
        printf("Relacao de equivalencia: V\n");
    else
        printf("Relacao de equivalencia: F\n");
}

void relacao_Ordem_Parcial(Grafo* gr){ //Verificar a relação de ordem parcial
    //Reflexiva+Anti-Simétrica+Transitiva
    if(gr->reflexiva==1 && gr->anti_simetrica==1 && gr->transitiva==-1)
        printf("Relacao de ordem parcial: V\n\n");
    else
        printf("Relacao de ordem parcial: F\n\n");
}

void fecho_Reflexivo(Grafo* gr){
    if(gr->reflexiva == 1)
        eh_Irreflexivo(gr,1);
    else //Completar as ligações e imprimir
        eh_Reflexivo(gr,1);
}

void verificaFechoSimetrico(Grafo *gr3, Grafo *gr4){
    int i,j,k,entrou=0,controle=-1;
    //criar um grafo 2, realizar as ligações faltantes, imprimir todo o fecho simetrico, liberar o grafo
    /*A criação de dois grafos auxiliares de forma que um passe pela função remove_Simetrico e sua saída gere
    as ligações necessárias para imprimir o fecho de forma completa. As ligações faltentes são realizdas no 
    segundo grafo auxiliar*/
    while(controle!=0){
        controle = remove_Simetrico(gr3);
    }
    for(i=0; i < gr3->nro_vertices; i++){
        for(j=0; j < gr3->grau[i]; j++)
            insereAresta(gr4,gr3->elementos[gr3->arestas[i][j]],gr3->elementos[i]);
    }
    printf("Fecho simetrico da relacao = {");
    //imprimir todas ligações já existentes e depois imprimir as faltantes:
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
//Caso a relação não seja assimetrica não é necessário listar os pares pois já foram listados anteriormente.
}

void inicializar(){
    Grafo* gr = cria_Grafo();// inicialização do grafo
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