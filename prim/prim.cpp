#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <deque>

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
        cerr << "Não foi possível abrir o arquivo de entrada." << endl;
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

    vector<pqElement> pq;
    pq.push_back({0, start});
    make_heap(pq.begin(), pq.end(), greater<pqElement>());

    while (!pq.empty()) {
        pop_heap(pq.begin(), pq.end(), greater<pqElement>());
        int u = pq.back().second;
        int weight = pq.back().first;
        pq.pop_back();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;
        totalCost += weight;

        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u});
        }

        // Explore adjacent vertices
        for (const auto &neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!inMST[v] && w < minWeight[v]) {
                minWeight[v] = w;
                parent[v] = u;

                pq.push_back({w, v});
                push_heap(pq.begin(), pq.end(), greater<pqElement>());
            }
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

void printMST(const edgeList &mstEdges) {
    for (size_t i = 0; i < mstEdges.size(); i++) {
        int u = mstEdges[i].first;
        int v = mstEdges[i].second;
        cout << "(" << u + 1 << "," << v + 1 << ") ";
    }
    cout << endl;
}

void printHelp() {
    cout << "É necessário passar um arquivo de entrada para este programa." << endl;
    cout << "-h : mostra as informações sobre a execução do programa." << endl;
    cout << "-o <arquivo> : redireciona a saída para o 'arquivo'." << endl;
    cout << "   Caso esta opção não seja fornecida, o programa salvará o custo em 'prim.txt' por padrão." << endl;
    cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada." << endl;
    cout << "-s : mostra a solução da Árvore Geradora Mínima na tela." << endl;
    cout << "-i <vértice> : indica o vértice inicial. O padrão é o vértice 1." << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    string inputFile, outputFile = "prim.txt";
    bool showSolution = false, fileOutput = false;
    bool startVertexProvided = false;
    int startVertex;

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
            startVertexProvided = true;
        }
    }

    if (inputFile.empty()) {
        printHelp();
    }

    if (!startVertexProvided) {
        cerr << "Erro: Vértice inicial não especificado. Utilize o parâmetro '-i <vértice>' para definir o vértice inicial." << endl;
        return 1;
    }

    Graph graph = readGraphFromFile(inputFile);
    auto result = prim(graph, startVertex);

    int totalCost = result.first;
    edgeList mstEdges = result.second;

    if (showSolution) {
        printMST(mstEdges);
    }

    if (fileOutput || !showSolution) {
        writeCostToFile(outputFile, totalCost);
    }

    return 0;
}
