# Projeto de Análise Empírica dos Algoritmos de Busca

## 1. Introdução

O projeto foi solicitado pelo professor **Selan Rodrigues dos Santos** como atividade avaliativa da turma de **Estrutura de Dados Básica I** do curso **Bacharelado de Tecnologia da Informação** da **Universidade Federal do Rio Grande do Norte**.

O software desenvolvido visa analisar, de maneira empírica, 5 algoritmos de busca: 

 - Busca Linear
 - Busca Binária
 - Busca Ternária
 - *Jump Search*
 - *Fibonacci Search*

As buscas binária e ternária são implementadas de forma recursiva e iterativa no projeto, portanto, somamos 7 implementações para comparar o desempenho de cada de acordo com o aumento do número de amostras.

## 2. Como usar

Para compilar o projeto, faz-se necessário a instalação da ferramenta [CMake](https://cmake.org/) no computador.

Com o CMake instalado, basta acessar a pasta do projeto pelo Terminal, cmd, ou pelo software de shellscript e digitar os comandos:

    ccmake .
    make

Feito isso, basta executar o software.

## 3. Execução
Para realizar a execução do software, enviamos alguns parâmetros para configurar os testes junto do comando de execução, na seguinte forma:

    ./Search [PALAVRA_BINÁRIA] [MIN_SIZE] [MAX_SIZE] [SAMPLES_AMOUNT] [TESTS_AMOUNT]
A estrutura acima é recebida no `main()` e interpretada deste modo:

 - `[PALAVRA_BINÁRIA]` é uma palavra de 7 bits e cada bit liga ou desliga (1 ou 0, respectivamente) o teste de cada função, onde `[I] [II] [III] [IV] [V] [VI] [VII]` representam:
 -- `[I]`: Busca Linear Iterativa
 -- `[II]`: Busca Binária Iterativa
 -- `[III]`: Busca Ternária Iterativa
 -- `[IV]`: Jump Search
 -- `[V]`: Fibonacci Search
 -- `[VI]`: Busca Binária Recursiva
 -- `[VII]`: Busca Ternária Recursiva

 - `[MIN_SIZE]` é o tamanho mínimo que os vetores criados irão assumir nos testes.
 - `[MAX_SIZE]` é o tamanho máximo que os vetores criados irão assumir nos testes.
 - `[SAMPLES_AMOUNT]` é a quantidade de vetores que serão criados com o tamanho variando de `[MIN_SIZE]` até `[MAX_SIZE]`.
 - `[TESTS_AMOUNT]` é a quantidade de vezes que cada teste vai se repetir, o tempo de cada repetição é somado e dividido pela quantidade de testes, criando-se, uma média de testes.

Um exemplo de como podemos executar o código:
`./Search 1111111 0 350000000 3500 100`
No caso acima, o programa vai executar todos os algoritmos de busca com 3500 vetores de tamanho a variar entre 0 e 350 milhões, igualmente, repetindo cada teste 100 vezes escrevendo o resultado num arquivo de texto.

>Caso o usuário desejar, o programa pode executar somente alguns algoritmos e criar o arquivo com esses dados, no entanto, o arquivo final gerado terá colunas vazias para os algoritmos que não foram ligados.

## 4. Resultado
O software escreve os resultados obtidos em um arquivo `tempos.txt` na pasta `data`  com a seguinte estrutura:
`N       ILS            IBS            ITS            IJS            IFS            RBS            RTS`           
|N|ILS|IBS|ITS|IJS|IFS|RBS|RTS|
|-|---|---|---|---|---|---|---|
|Número de Amostras|Tempo de execução|Tempo de execução|Tempo de execução|Tempo de execução|Tempo de execução|Tempo de execução|Tempo de execução|

> O tempo de execução é medido em milisegundos.
 
## 5. Limitações
Utilizamos o limite de 350 milhões no parâmetro `[MAX_SIZE]` nos nossos testes, esse valor foi escolhido por limitações de hardware (memória, processador...). Em relação ao limite de cada parâmetro, eles são salvos como variáveis do tipo `int`, portanto, limitam-se em 2,147,483,647.

Vale ressaltar, que quanto maior o número de testes, consequentemente, mais demorado é o processo.

## 6. Autores
Os autores desse projeto foram:

Carlos Eduardo Alves Sarmento ![Twitter Follow](https://img.shields.io/twitter/follow/edusrmt.svg?style=social)

Victor Raphaell Vieira Rodrigues ![Twitter Follow](https://img.shields.io/twitter/follow/__victorvieira.svg?style=social)