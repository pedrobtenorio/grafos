#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int nodeId;
    double priority;

    bool operator<(const Node& other) const {
        return priority > other.priority;
    }
};

struct Solution {
    int initialVertex;
    map<int, double> totalCost;
    map<int, int> prevNode;
};

void printHelp() {
    cout << "E necessario passar um arquivo de entrada para este programa." << endl;
    cout << "Caso nao seja passado um arquivo de saida, sera criado 'dijkstra-saida.txt'." << endl << endl;
    cout << "Comandos:" << endl;
    cout << "-h : Exibe informacoes sobre a execucao e nao executa o programa." << endl;
    cout << "-o <arquivo> : Redireciona a saida para o 'arquivo'." << endl;
    cout << "-f <arquivo> : Indica o 'arquivo' com o grafo de entrada." << endl;
    cout << "-s : Mostra a solucao." << endl;
    cout << "-i <vertice> : Indica o vertice inicial." << endl;

    exit(0);
}

void getNodesPath(const Solution& solution, int finalVertex, bool print, ofstream& file) {
    int current = finalVertex;
    vector<int> path;

    while (current != solution.initialVertex) {
        path.push_back(current);
        current = solution.prevNode.at(current);
    }
    path.push_back(solution.initialVertex);

    if (print) {
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it << (it == path.rend() - 1 ? "" : " ");
        }
        cout << endl;
    }
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        file << *it << (it == path.rend() - 1 ? "" : " ");
    }
    file << endl;
}

void generateTextSolution(const Solution& solution, int numberOfNodes, ofstream& file) {
    for (int i = 1; i <= numberOfNodes; ++i) {
        if (i != solution.initialVertex) {
            if (solution.totalCost.at(i) != HUGE_VAL) {
                cout << i << ":" << static_cast<int>(solution.totalCost.at(i)) << " ";  
                file << i << ":" << static_cast<int>(solution.totalCost.at(i)) << " ";
            } else {
                cout << i << ": -1 ";  
                file << i << ": -1 ";  
            }
        } else {
            cout << i << ":0 "; 
            file << i << ":0 ";
        }
    }
    cout << endl;

    file << endl;
}

vector<double> getEdgeValues(const string& fileLine) {
    vector<double> edgeValues(3, 0.0);
    stringstream tempStream(fileLine);

    for (int j = 0; j < 3; ++j) {
        tempStream >> edgeValues[j];
    }

    return edgeValues;
}

void createGraphFromFile(vector<vector<double>>& graph, const string& inputFilePath) {
    string fileLine;
    stringstream tempStream;
    ifstream inputFile(inputFilePath);
    int numberOfVertices;
    int numberOfEdges;
    vector<double> edgeValues;

    getline(inputFile, fileLine);
    tempStream << fileLine;
    tempStream >> numberOfVertices;
    tempStream >> numberOfEdges;

    graph.assign(numberOfVertices + 1, vector<double>(numberOfVertices + 1, 0.0));

    for (int i = 0; i < numberOfEdges; ++i) {
        getline(inputFile, fileLine);
        edgeValues = getEdgeValues(fileLine);
        graph[edgeValues[0]][edgeValues[1]] = edgeValues[2];
        graph[edgeValues[1]][edgeValues[0]] = edgeValues[2];
    }
}

Node createNode(int nodeId, double priority) {
    return {nodeId, priority};
}

vector<Node> getNeighbors(const vector<vector<double>>& graph, int nodeId) {
    vector<Node> neighbors;
    int numberOfNodes = graph.size() - 1;

    for (int i = 1; i <= numberOfNodes; ++i) {
        if (graph[nodeId][i] > 0) {
            neighbors.push_back(createNode(i, graph[nodeId][i]));
        }
    }

    return neighbors;
}

void dijkstra(Solution& dijkstraSolution, const vector<vector<double>>& graph, int initialVertex) {
    if (initialVertex != -1) {
        int numberOfNodes = graph.size() - 1;
        map<int, double> totalCost;
        map<int, int> prevNode;
        set<int> visited;

        priority_queue<Node> heap;

        prevNode[initialVertex] = initialVertex;
        heap.push(createNode(initialVertex, 0));

        for (int i = 1; i <= numberOfNodes; ++i) {
            totalCost[i] = (i != initialVertex) ? HUGE_VAL : 0.0;
        }

        while (!heap.empty()) {
            Node currentNode = heap.top();
            heap.pop();
            visited.insert(currentNode.nodeId);
            vector<Node> neighbors = getNeighbors(graph, currentNode.nodeId);

            for (const auto& neighbor : neighbors) {
                if (!visited.count(neighbor.nodeId)) {
                    double newPriority = currentNode.priority + neighbor.priority;
                    if (newPriority < totalCost[neighbor.nodeId]) {
                        totalCost[neighbor.nodeId] = newPriority;
                        prevNode[neighbor.nodeId] = currentNode.nodeId;
                        heap.push(createNode(neighbor.nodeId, newPriority));
                    }
                }
            }
        }

        dijkstraSolution = {initialVertex, totalCost, prevNode};

    } else {
        cout << "Erro! E necessario indicar o vertice inicial." << endl << endl;
        printHelp();
    }
}

int main(int argc, char* argv[]) {
    vector<string> args(argv, argv + argc);
    string inputFilePath;
    string outputFilePath = "dijkstra-saida.txt";
    bool printOutput = false;
    int numberOfNodes;
    int initialVertex = 1;
    vector<vector<double>> graph;
    Solution dijkstraSolution;

    for (int i = 0; i < argc; ++i) {
        if (args[i] == "-h") {
            printHelp();
        } else if (args[i] == "-o") {
            if (i < argc - 1) {
                outputFilePath = args[i + 1];
            }
        } else if (args[i] == "-f") {
            if (i < argc - 1) {
                inputFilePath = args[i + 1];
            }
        } else if (args[i] == "-s") {
            printOutput = true;
        } else if (args[i] == "-i") {
            if (i < argc - 1) {
                initialVertex = stoi(args[i + 1]);
            }
        }
    }

    if (!inputFilePath.empty()) {
        createGraphFromFile(graph, inputFilePath);
        dijkstra(dijkstraSolution, graph, initialVertex);
        numberOfNodes = graph.size() - 1;
        ofstream outputFile(outputFilePath);

        generateTextSolution(dijkstraSolution, numberOfNodes, outputFile);

        outputFile.close();
    } else {
        cout << "Erro! Nenhum arquivo de entrada foi passado." << endl << endl;
        printHelp();
    }

    return 0;
}
