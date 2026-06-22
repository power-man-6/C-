#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

class Graph {
private:
    int n;
    vector<vector<int>> graph;
    vector<char> cities;
    vector<int> dist;
    vector<bool> visited;
    vector<int> path;

    int findCity(char c) {
        for (int i = 0; i < n; i++) {
            if (cities[i] == c)
                return i;
        }
        return -1;
    }

public:
    Graph(int cityCount) : n(cityCount) {
        graph.resize(n, vector<int>(n, INF));
        cities.resize(n);
        dist.resize(n);
        visited.resize(n);
        path.resize(n);
    }

    void inputCities() {
        for (int i = 0; i < n; i++) {
            cin >> cities[i];
        }
    }

    void addEdge(char from, char to, int weight) {
        int u = findCity(from);
        int v = findCity(to);
        if (u != -1 && v != -1) {
            graph[u][v] = weight;
        }
    }

    void dijkstra(char startCity, char endCity) {
        int start = findCity(startCity);
        int end = findCity(endCity);

        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            visited[i] = false;
            path[i] = -1;
        }
        dist[start] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            int minDist = INF;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && graph[u][v] != INF && dist[u] != INF) {
                    if (dist[u] + graph[u][v] < dist[v]) {
                        dist[v] = dist[u] + graph[u][v];
                        path[v] = u;
                    }
                }
            }
        }

        if (dist[end] == INF) {
            cout << "No path" << endl;
        }
        else {
            cout << dist[end] << endl;
            printPath(start, end);
        }
    }

    void printPath(int start, int end) {
        vector<int> route;
        int cur = end;

        while (cur != -1) {
            route.push_back(cur);
            cur = path[cur];
        }

        reverse(route.begin(), route.end());

        for (size_t i = 0; i < route.size(); i++) {
            cout << cities[route[i]];
            if (i < route.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int n, m;

    cout << "请输入测试用例（每输入一组完整数据后立即输出结果）" << endl;
    cout << "输入格式：n m，然后输入城市名、道路信息、起点终点" << endl;
    cout << "输入 0 0 结束程序" << endl << endl;

    while (true) {
        // 读取 n 和 m
        cin >> n >> m;

        // 结束条件
        if (n == 0 && m == 0) {
            cout << "程序结束" << endl;
            break;
        }

        // 创建图对象
        Graph graph(n);

        // 输入城市名字
        graph.inputCities();

        // 输入道路信息
        for (int i = 0; i < m; i++) {
            char a, b;
            int d;
            cin >> a >> b >> d;
            graph.addEdge(a, b, d);
        }

        // 输入起点和终点
        char startCity, endCity;
        cin >> startCity >> endCity;

        // 输出当前测试用例的结果
        cout << "========== 输出 ==========" << endl;
        graph.dijkstra(startCity, endCity);
        cout << "==========================" << endl << endl;
    }

    return 0;
}