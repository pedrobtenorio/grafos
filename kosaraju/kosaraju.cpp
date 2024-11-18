#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

struct Graph {
    int numberOfNodes;
    vector<vector<int>> adjList;
    vector<vector<int>> adjListRev;
};

Graph readGraphFromFile(const string &filename) {
    ifstream file(filename);
    Graph graph;
    int numberOfEdges;
    
    if (file.is_open()) {
        file >> graph.numberOfNodes >> numberOfEdges;
        graph.adjList.resize(graph.numberOfNodes);
        graph.adjListRev.resize(graph.numberOfNodes);

        for (int i = 0; i < numberOfEdges; i++) {
            int u, v;
            file >> u >> v;
            graph.adjList[u - 1].push_back(v - 1);
            graph.adjListRev[v - 1].push_back(u - 1);
        }
        file.close();
    } else {
        cerr << "Nao foi possivel abrir o arquivo de entrada." << endl;
        exit(1);
    }
    return graph;
}

void dfs1(int node, vector<bool> &visited, stack<int> &finishStack, const Graph &graph) {
    visited[node] = true;
    for (int neighbor : graph.adjList[node]) {
        if (!visited[neighbor]) {
            dfs1(neighbor, visited, finishStack, graph);
        }
    }
    finishStack.push(node);
}

void dfs2(int node, vector<bool> &visited, vector<int> &scc, const Graph &graph) {
    visited[node] = true;
    scc.push_back(node + 1);
    for (int neighbor : graph.adjListRev[node]) {
        if (!visited[neighbor]) {
            dfs2(neighbor, visited, scc, graph);
        }
    }
}

vector<vector<int>> kosaraju(const Graph &graph) {
    stack<int> finishStack;
    vector<bool> visited(graph.numberOfNodes, false);

    for (int i = 0; i < graph.numberOfNodes; i++) {
        if (!visited[i]) {
            dfs1(i, visited, finishStack, graph);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> stronglyConnectedComponents;

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();

        if (!visited[node]) {
            vector<int> scc;
            dfs2(node, visited, scc, graph);
            stronglyConnectedComponents.push_back(scc);
        }
    }
    return stronglyConnectedComponents;
}

void outputSCCs(const vector<vector<int>> &sccs, const string &outputFile, bool fileOutput) {
    if (fileOutput) {
        ofstream file(outputFile);
        if (file.is_open()) {
            for (const auto &scc : sccs) {
                for (int node : scc) file << node << " ";
                file << endl;
            }
            file.close();
        } else {
            cerr << "Nao foi possivel abrir o arquivo de saida." << endl;
        }
    } else {
        for (const auto &scc : sccs) {
            for (int node : scc) cout << node << " ";
            cout << endl;
        }
    }
}

void printHelp() {
    cout << "E necessario passar um arquivo de entrada para este programa." << endl;
    cout << "-h : mostra as informacoes sobre a execucao do programa." << endl;
    cout << "-f <arquivo> : indica o 'arquivo' que contem o grafo de entrada." << endl;
    cout << "-o <arquivo> : redireciona a saida para o 'arquivo'." << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    string inputFile, outputFile;
    bool fileOutput = false;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h") {
            printHelp();
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
            fileOutput = true;
        }
    }

    if (inputFile.empty()) {
        printHelp();
    }

    Graph graph = readGraphFromFile(inputFile);
    auto sccs = kosaraju(graph);
    outputSCCs(sccs, outputFile, fileOutput);

    return 0;
}
