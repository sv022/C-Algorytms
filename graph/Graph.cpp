#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#define TYPE int

using namespace std;

class Graph {
private:
  vector < vector<int> > adjlist;
  vector < vector<TYPE> > adj;
  int V;

  void DFS(int v, vector<bool>& visited) { 
    visited[v] = true; 
 
    for (int u = 0; u < V; ++u) { 
        if (adj[v][u] == 1 && !visited[u]) 
            DFS(u, visited); 
    } 
  }

  int dfs(vector<vector<int> >& residualCapacity, vector<int>& parent, int current, int minCapacity) { 
    if (parent[current] == -1) { 
        return minCapacity; 
    } 
 
    int prev = parent[current]; 
    int pathFlow = dfs(residualCapacity, parent, prev, min(minCapacity, residualCapacity[prev][current])); 
 
    residualCapacity[prev][current] -= pathFlow; 
    residualCapacity[current][prev] += pathFlow; 
 
    return pathFlow; 
  }

  bool bfs(vector<vector<int> >& residualCapacity, vector<int>& parent, int source, int sink) { 
    int nodes = residualCapacity.size(); 
    vector<bool> visited(nodes, false); 
    queue<int> q; 
 
    q.push(source); 
    visited[source] = true; 
    parent[source] = -1; 
 
    while (!q.empty()) { 
        int current = q.front(); 
        q.pop(); 
 
        for (int neighbor = 0; neighbor < nodes; ++neighbor) { 
            if (!visited[neighbor] && residualCapacity[current][neighbor] > 0) { 
                q.push(neighbor); 
                parent[neighbor] = current; 
                visited[neighbor] = true; 
            } 
        } 
    } 
 
    return visited[sink]; 
  }

  int findMaxFlow(vector<vector<int> >& capacity, int source, int sink) { 
    int nodes = capacity.size(); 
 
    // Инициализация остаточной пропускной способности 
    vector<vector<int> > residualCapacity(nodes, vector<int>(nodes, 0)); 
    for (int i = 0; i < nodes; ++i) { 
        for (int j = 0; j < nodes; ++j) { 
            residualCapacity[i][j] = capacity[i][j]; 
        } 
    } 
 
    int maxFlow = 0; 
 
    // Поиск увеличивающих путей 
    vector<int> parent(nodes, -1); 
    while (bfs(residualCapacity, parent, source, sink)) { 
        int pathFlow = dfs(residualCapacity, parent, sink, INT_MAX); 
        maxFlow += pathFlow; 
    } 
 
    return maxFlow; 
  } 
    
public:
  Graph(int v){
    this->V = v;
    for (int i = 0; i < V; i++){
      vector <TYPE> temp;
      for (int j = 0; j < V; j ++)
        temp.push_back(0);
      adj.push_back(temp);
    } 
  } 

  Graph(){
    ifstream f("sample1.txt");
    f >> V;
    double x;
    for (int i = 0; i < V; i++){
      vector <TYPE> temp;
      for (int j = 0; j < V; j ++){
        f >> x;
        temp.push_back(x);
        }
      adj.push_back(temp);
    }


  }

  void addEdge(int v, int w, double weight){
    adj[v - 1][w - 1] = weight;
    adj[w - 1][v - 1] = weight;
  }

  void show(){
    for (int i = 0; i < V; i++){
      for (int j = 0; j < V; j++)
        cout << (adj[i][j] != 10000 ? adj[i][j] : 0) << ' ';
      cout << '\n';
    }
  }

  void getrandomGraph(){
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++){
        int val = rand() % 3;
        //if (val % 3 == 0) val = 0;
        adj[i][j] = val;
        adj[j][i] = adj[i][j];
      }
    for (int i = 0; i < V; i++) adj[i][i] = 10000;
  }

  double primasearch(){
    vector <bool> visited;
    int visitcount = 1;
    for (int i = 0; i < V; i++) visited.push_back(false);
    int v = 0;
    int w;
    double sum;
    while (visitcount != V){
      double mn = 10000;
      for (int i = 0; i < V; i++)
        if (adj[v][i] < mn && !visited[i]){
          w = i;
          mn = adj[v][i];
        }
      visited[w] = true;
      sum += mn;
      v = w;
      visitcount++;
    }

    return sum;
  }

  int connectivity() { 
    int connectivityCount = 0;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i) { 
        if (!visited[i]) { 
            DFS(i, visited); 
            connectivityCount++; 
        } 
    } 
    return connectivityCount; 
  }

  void nearestNeighbor(int startVertex) { 
    vector<bool> visited(V, false); // Массив для отслеживания посещенных вершин 
 
    visited[startVertex] = true; // Помечаем начальную вершину как посещенную 
    int currentVertex = startVertex; // Текущая вершина 
    int totalWeight = 0; // Общий вес пути 
    cout << "Constructed path: " << currentVertex; 
 
    for (int count = 0; count < V - 1; ++count) { 
        int nearestVertex = -1; // Ближайшая непосещенная вершина 
        int minWeight = 100001; // Минимальный вес ребра 
 
        // Перебираем смежные вершины 
        for (int v = 0; v < V; ++v) { 
            if (adj[currentVertex][v] > 0 && !visited[v]) { 
                if (adj[currentVertex][v] < minWeight) { 
                    minWeight = adj[currentVertex][v]; 
                    nearestVertex = v; 
                } 
            } 
        } 
 
        // Добавляем ближайшую вершину к пути 
        cout << " -> " << nearestVertex; 
        visited[nearestVertex] = true; 
        totalWeight += minWeight; 
        currentVertex = nearestVertex; 
    } 
 
    // Заканчиваем путь, возвращаясь в начальную вершину 
    cout << " -> " << startVertex << endl; 
    totalWeight += adj[currentVertex][startVertex]; 
    cout << "Total: " << totalWeight << endl; 
  }

  void deikstra(int startVertex) { 
  vector<int> dist(V, INT_MAX); // Массив для хранения расстояний до вершин 
  vector<bool> visited(V, false); // Массив для отслеживания посещенных вершин 
 
  dist[startVertex] = 0; // Расстояние до начальной вершины равно 0 
 
  for (int count = 0; count < V - 1; ++count) { 
    int minDist = 10001; // Минимальное расстояние 
    int minIndex = -1; // Индекс вершины с минимальным расстоянием 
 
    // Находим вершину с минимальным расстоянием из непосещенных вершин 
    for (int v = 0; v < V; ++v) { 
      if (!visited[v] && dist[v] < minDist) { 
        minDist = dist[v]; 
        minIndex = v; 
      } 
    } 
 
    if (minIndex == -1) 
      break; 
 
    visited[minIndex] = true; // Помечаем вершину как посещенную 
 
    // Обновляем расстояния до смежных вершин 
    for (int v = 0; v < V; ++v) { 
      if (!visited[v] && adj[minIndex][v] != 0 && 
          dist[minIndex] != INT_MAX && 
          dist[minIndex] + adj[minIndex][v] < dist[v]) { 
          dist[v] = dist[minIndex] + adj[minIndex][v]; 
        } 
      } 
    } 
 
  // Выводим кратчайшие пути 
    cout << "Shortest paths from " << startVertex << ":" << endl; 
    for (int v = 0; v < V; ++v) { 
      cout << "Vert " << v << ": " << dist[v] << endl; 
    } 
  }

  int maxFlow(int source, int sink){
    return findMaxFlow(adj, source, sink);
  }

};

void graphmanual(){
  Graph G(5);
  G.addEdge(1, 3, 9);
  G.addEdge(1, 4, 2);
  G.addEdge(2, 5, 3);
  G.addEdge(3, 4, 1);
  G.show();
}



int main(){
  Graph G(7);
  G.getrandomGraph();
  G.show();
  cout << G.maxFlow(0, 6);
}

