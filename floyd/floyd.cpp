#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

typedef vector<vector<double>> matrix;

struct Graph {
    matrix adjMatrix;
    int numberOfNodes;
};

vector<double> getEdgeValues(const string& fileLine) {
    vector<double> edgeValues(3, 0);
    stringstream tempStream(fileLine);
    for(int j = 0; j < 3; j++) {
        tempStream >> edgeValues[j];
    }
    return edgeValues;
}

void initializeGraphAdjMatrix(Graph& graph) {
    matrix adjMatrix(graph.numberOfNodes + 1, vector<double>(graph.numberOfNodes + 1, numeric_limits<double>::infinity()));
    graph.adjMatrix = adjMatrix;
}

void createGraphFromFile(Graph& newGraph, const string& inputFilePath) {
    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada: " << inputFilePath << endl;
        exit(1);
    }

    string fileLine;
    int numberOfVertices, numberOfEdges;
    getline(inputFile, fileLine);
    stringstream(fileLine) >> numberOfVertices >> numberOfEdges;

    newGraph.numberOfNodes = numberOfVertices;
    initializeGraphAdjMatrix(newGraph);

    vector<double> edgeValues;
    for(int i = 0; i < numberOfEdges; i++) {
        getline(inputFile, fileLine);
        edgeValues = getEdgeValues(fileLine);
        newGraph.adjMatrix[edgeValues[0]][edgeValues[1]] = edgeValues[2];
    }

    inputFile.close();
}

void initializeDistMatrix(const Graph& graph, matrix& distMatrix) {
    distMatrix = graph.adjMatrix;
}

void initializePredecessorMatrix(const Graph& graph, vector<vector<int>>& predecessors) {
    predecessors = vector<vector<int>>(graph.numberOfNodes + 1, vector<int>(graph.numberOfNodes + 1, 0));
    for(int i = 1; i <= graph.numberOfNodes; i++) {
        predecessors[i][i] = 0;
    }
}

void printResult(int numberOfNodes, matrix &distMatrix, vector<vector<int>> &predecesors, bool print, ofstream * file) {

    for(int i = 1; i <= numberOfNodes; i++) {
        for(int j = 1; j <= numberOfNodes; j++) {
            if(distMatrix[i][j] != HUGE_VAL) {
                if(i != j) {
                    (*(file)) << "O menor custo de " << i << " para " << j << " e " << distMatrix[i][j] << "." << endl;
                    if(print) {
                        cout << "O menor custo de " << i << " para " << j << " e " << distMatrix[i][j] << "." << endl;
                    }
                }
            } else {
                if(i != j) {
                    (*(file)) << "Nao existe caminho de " << i << " para " << j << "." << endl;
                    if(print) {
                        cout << "Nao existe caminho de " << i << " para " << j << "." << endl;
                    }
                }
            }
        }
    }
}

void floyd(const Graph& graph, bool print, ofstream* file) {
    matrix distMatrix;
    vector<vector<int>> predecessors;

    initializeDistMatrix(graph, distMatrix);
    initializePredecessorMatrix(graph, predecessors);

    for(int i = 1; i <= graph.numberOfNodes; i++) {
        for(int j = 1; j <= graph.numberOfNodes; j++){
            if(distMatrix[i][j] < numeric_limits<double>::infinity()) {
                predecessors[i][j] = i;
            }
        }
    }

    for(int k = 1; k <= graph.numberOfNodes; k++) {
        for(int i = 1; i <= graph.numberOfNodes; i++) {
            for(int j = 1; j <= graph.numberOfNodes; j++) {
                if(distMatrix[i][k] + distMatrix[k][j] < distMatrix[i][j]) {
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                    predecessors[i][j] = k;
                }
            }
        }
    }

    printResult(graph.numberOfNodes, distMatrix, predecessors, print, file);
}

void printHelp() {
    cout << "E necessario passar um arquivo de entrada para este programa." << endl;
    cout << "Caso nao seja passado um arquivo de saida, sera criado 'floyd-saida.txt'." << endl << endl;
    cout << "Comandos:" << endl;
    cout << "-h : Exibe informacoes sobre a execucao e nao executa o programa." << endl;
    cout << "-o <arquivo> : Redireciona a saida para o 'arquivo'." << endl;
    cout << "-f <arquivo> : Indica o 'arquivo' com o grafo de entrada." << endl;
    cout << "-s : Mostra a solucao (em ordem crescente)." << endl;
    exit(0);
}

int main(int argc, char* argv[]) {
    vector<string> args(argv, argv + argc);
    string inputFilePath;
    string outputFilePath = "floyd-saida.txt";
    bool printOutput = false;
    Graph graph;
    ofstream outputFile;

    for(int i = 0; i < argc; i++) {
        if(args[i] == "-h") {
            printHelp();
        } else if(args[i] == "-o" && i < (argc - 1)) {
            outputFilePath = args[i + 1];
        } else if(args[i] == "-f" && i < (argc - 1)) {
            inputFilePath = args[i + 1];
        } else if(args[i] == "-s") {
            printOutput = true;
        }
    }

    if(inputFilePath.empty()) {
        cerr << "Erro! E necessario passar um arquivo de entrada." << endl << endl;
        printHelp();
    }

    createGraphFromFile(graph, inputFilePath);
    outputFile.open(outputFilePath);
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saida: " << outputFilePath << endl;
        exit(1);
    }

    floyd(graph, printOutput, &outputFile);
    outputFile.close();

    return 0;
}
