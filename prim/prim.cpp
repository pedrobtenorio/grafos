#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <deque>
#include <queue> 
#include <functional>   

using namespace std;

typedef vector<pair<int, int>> edgeList;

typedef struct Graph {
    int numberOfNodes;
    vector<vector<pair<int, int>>> adjList;
} Graph;

Graph readGraphFromFile(const string &filename) {
    ifstream file(filename);
    Graph graph;
    int numberOfEdges;

    if (file.is_open()) {
        file >> graph.numberOfNodes >> numberOfEdges;
        graph.adjList.resize(graph.numberOfNodes);

        for (int i = 0; i < numberOfEdges; i++) {
            int u, v, weight;
            file >> u >> v >> weight;
            graph.adjList[u - 1].emplace_back(v - 1, weight);
            graph.adjList[v - 1].emplace_back(u - 1, weight);
        }
        file.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo de entrada." << endl;
        exit(1);
    }
    return graph;
}

typedef pair<int, int> pqElement;

pair<int, edgeList> prim(const Graph &graph, int start) {
    vector<int> minWeight(graph.numberOfNodes, numeric_limits<int>::max());
    vector<bool> inMST(graph.numberOfNodes, false);
    vector<int> parent(graph.numberOfNodes, -1);

    minWeight[start] = 0;
    int totalCost = 0;
    edgeList mstEdges;

    priority_queue<pqElement, vector<pqElement>, greater<pqElement>> minHeap;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        int weight = minHeap.top().first;
        minHeap.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        totalCost += weight;

        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u});
        }

        for (const auto &neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!inMST[v] && w < minWeight[v]) {
                minWeight[v] = w;
                parent[v] = u;
                minHeap.push({w, v});
            }
        }
    }

    return {totalCost, mstEdges};
}

void writeCostToFile(const string &filename, int cost) {
    ofstream file(filename);
    cout << cost << endl;
    if (file.is_open()) {
        file << cost << endl;
        file.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo de saida." << endl;
    }
}

void printMST(const edgeList &mstEdges) {
    for (size_t i = 0; i < mstEdges.size(); i++) {
        int u = mstEdges[i].first;
        int v = mstEdges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << ") ";
    }
    cout << endl;
}

void printHelp() {
    cout << "E necessario passar um arquivo de entrada para este programa." << endl;
    cout << "-h : mostra as informacoes sobre a execucao do programa." << endl;
    cout << "-o <arquivo> : redireciona a saida para o 'arquivo'." << endl;
    cout << "   Caso esta opcao nao seja fornecida, o programa salvara o custo em 'prim.txt' por padrao." << endl;
    cout << "-f <arquivo> : indica o 'arquivo' que contem o grafo de entrada." << endl;
    cout << "-s : mostra a solucao da Arvore Geradora Minima na tela." << endl;
    cout << "-i <vertice> : indica o vertice inicial. O padrao e o vertice 1." << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    string inputFile, outputFile = "prim.txt";
    bool showSolution = false, fileOutput = false;
    int startVertex = 1;

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
        } else if (arg == "-i" && i + 1 < argc) {
            startVertex = stoi(argv[++i]) - 1;

        }
    }

    if (inputFile.empty()) {
        printHelp();
    }


    Graph graph = readGraphFromFile(inputFile);
    auto result = prim(graph, startVertex);

    int totalCost = result.first;
    edgeList mstEdges = result.second;

    if (showSolution) {
        printMST(mstEdges);
    }

    else {
        writeCostToFile(outputFile, totalCost);
    }

    return 0;
}
