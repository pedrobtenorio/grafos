# Teoria dos Grafos
 Implementação dos algoritmos: 
  * kosaraju
  * Prim
  * Kruskal
  * Dijkstra
  * Floyd-Warshall

## Estrutura de Diretórios
Cada algoritmo está em uma pasta separada, contendo seu próprio arquivo Makefile.

## Compilação e Execução

Para compilar e executar qualquer um dos algoritmos, siga as instruções abaixo:

### Passo 1: Navegue até a pasta do algoritmo

Use o comando abaixo para entrar na pasta do algoritmo que deseja compilar:

    cd nome_da_pasta_do_algoritmo

Exemplo para o algoritmo de Dijkstra:

    cd dijkstra

### Passo 2: Compile o código

Use o `make` para compilar o código.

### Passo 3: Execute o Algoritmo

Após a compilação, execute o algoritmo com a opção `-h` para ver as instruções detalhadas de uso.

    ./dijkstra.bin -h    # No Windows
    ./dijkstra -h        # No Unix/Linux

## Observações
  * Todas as implementações descritas consideram grafos com vértices identificados por números inteiros maiores que 0.
  * As saídas dos algoritmos não seguem um padrão específico.
  * Todas as implementações descritas consideram arquivos de entrada no seguinte formato:

      ```
      |V| |E|
      ```
      seguido de |E| linhas na forma:
      
      ```
      Vn Vm W(VnVm)
      ```
      Sendo: 
      * |V| o número de vértices do grafo;
      * |E| o número de arestas do grafo;
      * Vn e Vm vértices distintos de V;
      * VnVm uma aresta de E formada pelos vértices Vn e Vm;
      * W(VnVm) o peso da aresta VnVm (para grafos sem pesos, esse elemento pode ser omitido no arquivo de entrada).
