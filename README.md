/*
Trabalho desenvolvido por Lucas Paulo Martins Mariz - Técnico em informática formado pelo Coltec/UFMG e aluno de Ciência da Computação UFMG
*/

O projeto foi inteiramente desenvolvido em um ambiente linux, sendo assim, o melhor sistema para sua execução sem grandes problemas é o Linux (preferencialmente Ubuntu).
Para a execução é necessário instalar alguns pacotes relacionados a makefile, caso já não estejam instalados.
	
	$ sudo apt-get update
	$ sudo apt-get upgrade
	$ sudo apt-get install make

Após a instalação, basta digitar ir para o diretorio do trabalho utilizando o comando 'cd' e digitar o comando "make" no terminal, o qual irá compilar o main e a biblioteca:

	$ make

A biblioteca será automaticamente compilada e o programa irá gerar um arquivo executável "a.out", que deverá ser executado seguindo da seguinte forma:
	
	$ ./a.out

A execução do projeto é independente e não necessita da interferência do usuário pois todos os dados são resgatados do arquivo "dados.txt".

Para modificar as informações do programa basta alterar o arquivo "dados.txt". Ele está formatado da seguinte forma:
	- 1° Linha: 1° dígito-> número de elementos do grafo
				Dígitos seguintes-> nome de cada elemento
	- Linhas seguintes-> relacionamentos entre os elementos do grafo.



----> Arquivos presentes:
		- rb.c 		: main do trabalho;
		- Grafo.c 	: biblioteca com todas as funções para determinar as propriedades dos grafos;
		- Grafo.h	: linkagem das bibliotecas;
		- makefile	: arquivo make para compilar o rb.c e o Grafo.c;
		- dados.txt : arquivo com a entrada do trabalho (numero de elementos, elementos, relações);
		- rb.pdf	: documentação do trabalho. 

		[Iniciando a Remodelação do projeto]