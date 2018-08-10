/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG e aluno de Ciência da Computação UFMG
*/
# Relações Binárias
### Considerações Iniciais: 
O projeto foi inteiramente desenvolvido em um ambiente linux, sendo assim, o melhor sistema para sua execução sem grandes problemas é o Linux (preferencialmente Ubuntu).
Para a execução é necessário instalar alguns pacotes relacionados ao makefile, caso já não estejam instalados.
	
	$ sudo apt-get update
	$ sudo apt-get upgrade
	$ sudo apt-get install make

Após a instalação, basta digitar ir para o diretorio do trabalho utilizando o comando "cd" e digitar o comando "make" no terminal, o qual irá compilar o main e a biblioteca:

	$ make

A biblioteca será automaticamente compilada e o programa irá gerar um arquivo executável "a.out", que deverá ser executado seguindo da seguinte forma:
	
	$ ./a.out

A execução do projeto é independente e não necessita da interferência do usuário pois todos os dados são resgatados do arquivo "dados.txt".

Para modificar as informações do programa basta alterar o arquivo "dados.txt". Ele está formatado da seguinte forma:
	- 1° Linha: 1° dígito-> número de elementos do grafo
				Dígitos seguintes-> nome de cada elemento
	- Linhas seguintes-> relacionamentos entre os elementos do grafo.



| Arquivo       | Função        								| 
| ------------- |:-----------------------------------------------------------------------------:|
| main.c        | main do trabalho                                                              |
| grafo.c       | biblioteca com todas as funções para determinar as propriedades dos grafos    |
| grafo.h       | linkagem das bibliotecas                                                      |
| makefile      | arquivo make para compilar o main.c e o grafo.c                               |
| dados.txt     | arquivo com a entrada do trabalho (numero de elementos, elementos, relações) 	|
| rb.pfd        | documentação do trabalho						        |

# Documentação: 
### Descrição Geral:
O desenvolvimento de uma estrutura na linguagem C na qual as relações seriam armazenadas em um grafo se torna uma tarefa um tanto quanto complexa dado o fato de ser necessário o uso de ponteiros de ponteiros, arquivos, vetores diâmicos, entre outros. Sendo assim, todo o processo foi minuciosamente esquematizado para evitar que erros de lógica pudessem vir a surgir.
### Arquivo grafo.c e suas funções:
Com o intuito de deixar o trabalho mais organizado, todas as funções designadas a determinar propriedades das relações foram feitas em um arquivo separado. Tal arquivo pode ser chamado como uma biblioteca, a qual é incluída através de seu respectivo arquivo ".h".
A estrutura principal do grafo consiste em alguns elementos e propriedades devidamente expliciadas. As propriedades podem assumir os valores 1 ou 0, dependendo da sua ocorrência ou não. Por padrão lógico, todas as propriedades são consideradas verdadeiras até que se prove ao contrário.
```c
struct grafo {
	int **matriz_adjacencia;	// Matriz de adjacencias que representa o grafo
	int n_vertices;			// Número total de vertices que o grafo terá
	int elementos[50];      	// Nomes dos vértices fornecidos pelo usuário
	int n_ligacoes;			// Número total de ligações que o grafo fará

    // Propriedades: 1 -> V | 0 -> F
    int propriedade_reflexiva;
    int propriedade_irreflexiva;
    int propriedade_simetrica;
    int propriedade_anti_simetrica;
    int propriedade_assimetrica;
    int propriedade_transitiva;

    int relacao_equivalencia;
    int relacao_ordem_parcial;
};
```
