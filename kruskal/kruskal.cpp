#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

typedef vector<pair<int, pair<int, int>>> edgeVector;

typedef struct Graph {
    int numberOfNodes;
    int numberOfEdges;
    edgeVector edges;
} Graph;

int find(vector<int> &fathers, int vertex) {
    if (fathers[vertex] == vertex) {
        return vertex;
    }
    return fathers[vertex] = find(fathers, fathers[vertex]);
}

void unite(vector<int> &fathers, int vertex1, int vertex2) {
    int root1 = find(fathers, vertex1);
    int root2 = find(fathers, vertex2);
    if (root1 != root2) {
        fathers[root1] = root2;
    }
}

Graph readGraphFromFile(const string &filename) {
    ifstream file(filename);
    Graph graph;

    if (file.is_open()) {
        file >> graph.numberOfNodes >> graph.numberOfEdges;

        for (int i = 0; i < graph.numberOfEdges; i++) {
            int u, v, weight;
            file >> u >> v >> weight;
            graph.edges.push_back({weight, {u - 1, v - 1}});
        }
        file.close();
    } else {
        cerr << "Não foi possível abrir o arquivo de entrada." << endl;
        exit(1);
    }
    return graph;
}

pair<int, edgeVector> kruskal(Graph &graph) {
    vector<int> fathers(graph.numberOfNodes);
    for (int i = 0; i < graph.numberOfNodes; i++) {
        fathers[i] = i;
    }

    sort(graph.edges.begin(), graph.edges.end());
    int totalCost = 0;
    edgeVector mstEdges;

    for (size_t i = 0; i < graph.edges.size(); i++) {
        int weight = graph.edges[i].first;
        int u = graph.edges[i].second.first;
        int v = graph.edges[i].second.second;

        if (find(fathers, u) != find(fathers, v)) {
            unite(fathers, u, v);
            totalCost += weight;
            mstEdges.push_back({weight, {u, v}});
        }
    }
    return {totalCost, mstEdges};
}

void writeCostToFile(const string &filename, int cost) {
    ofstream file(filename);
    if (file.is_open()) {
        file << cost << endl;
        file.close();
    } else {
        cerr << "Não foi possível abrir o arquivo de saída." << endl;
    }
}

void printMST(const edgeVector &mstEdges) {
    for (size_t i = 0; i < mstEdges.size(); i++) {
        int u = mstEdges[i].second.first;
        int v = mstEdges[i].second.second;
        cout << "(" << u + 1 << "," << v + 1 << ") ";
    }
    cout << endl;
}

void printHelp() {
    cout << "É necessário passar um arquivo de entrada para este programa." << endl;
    cout << "-h : mostra as informações sobre a execução do programa." << endl;
    cout << "-o <arquivo> : redireciona a saída para o 'arquivo'." << endl;
    cout << "   Caso esta opção não seja fornecida, o programa salvará o custo em 'kruskal.txt' por padrão." << endl;
    cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada." << endl;
    cout << "-s : mostra a solução da Árvore Geradora Mínima na tela." << endl;
    exit(0);
}


int main(int argc, char *argv[]) {
    string inputFile, outputFile = "kruskal.txt";
    bool showSolution = false, fileOutput = false;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h") {
            printHelp();
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
            fileOutput = true;
        } else if (arg == "-s") {
            showSolution = true;
        }
    }

    if (inputFile.empty()) {
        printHelp();
    }

    Graph graph = readGraphFromFile(inputFile);
    auto result = kruskal(graph);
    int totalCost = result.first;
    edgeVector mstEdges = result.second;

    if (showSolution) {
        printMST(mstEdges);
    } else {
        if (!fileOutput) {
            outputFile = "kruskal.txt";
        }
        writeCostToFile(outputFile, totalCost);
    }

    return 0;
}
