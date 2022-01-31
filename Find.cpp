#include <bits/stdc++.h>
using namespace std;
void addEdge(vector<int> adj[], int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}
bool check(int a, int b)
{
    if (a == 1 && b == 1)
        return true;
    return false;
}
int convert(int i, int j, int m)
{
    return ((m * i) + j);
}
bool Dijkstra(vector<int> adj[], int src, int dest, int v, int pred[], int dist[])
{
    list<int> queue;
    bool visited[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++)
        {
            if (visited[adj[u][i]] == false)
            {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
    return false;
}
vector<int> getThePath(vector<int> adj[], int s, int dest, int v, int n, int m)
{
    int pred[v], dist[v];
    if (Dijkstra(adj, s, dest, v, pred, dist) == false)
    {
        cout << "Given source and destination are not connected";
        return {-1};
    }
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1)
    {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    sort(path.begin(), path.end());
    return path;
}
void makeAdjacencylist(vector<vector<int>> arr, int n, int m, vector<int> adj[])
{
    int temp1, temp2;
    temp1 = 0;
    temp2 = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == n - 1 || j == m - 1)
            {
                if (i == n - 1 && j != m - 1)
                {
                    if (check(arr[i][j], arr[i][j + 1]))
                    {
                        temp1 = convert(i, j, m);
                        temp2 = convert(i, j + 1, m);
                        addEdge(adj, temp1, temp2);
                    }
                }
                if (j == m - 1 && i != n - 1)
                {
                    if (check(arr[i][j], arr[i + 1][j]))
                    {
                        temp1 = convert(i, j, m);
                        temp2 = convert(i + 1, j, m);
                        addEdge(adj, temp1, temp2);
                    }
                }
            }
            else
            {
                if (check(arr[i][j], arr[i][j + 1]))
                {
                    temp1 = convert(i, j, m);
                    temp2 = convert(i, j + 1, m);
                    addEdge(adj, temp1, temp2);
                }
                if (check(arr[i][j], arr[i + 1][j]))
                {
                    temp1 = convert(i, j, m);
                    temp2 = convert(i + 1, j, m);
                    addEdge(adj, temp1, temp2);
                }
                if (check(arr[i][j], arr[i + 1][j + 1]))
                {
                    temp1 = convert(i, j, m);
                    temp2 = convert(i + 1, j + 1, m);
                    addEdge(adj, temp1, temp2);
                }
                if (j != 0 && i != n - 1)
                {
                    if (check(arr[i][j], arr[i + 1][j - 1]))
                    {
                        temp1 = convert(i, j, m);
                        temp2 = convert(i + 1, j - 1, m);
                        addEdge(adj, temp1, temp2);
                    }
                }
            }
        }
    }
}
void printMapWithLength(vector<int> route, int n, int m)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (convert(i, j, m) == route[counter])
            {
                cout << " 1 ";
                counter++;
            }
            else
            {
                cout << " O ";
            }
        }
        cout << endl;
    }
    cout << "The Total units of distace covered - " << route.size() - 1 << endl;
}
int main()
{
    int n, m;
    cout << "Enter the size of map : ";
    cin >> n >> m;
    int temp;
    vector<vector<int>> arr(n);
    cout << "Enter the map :-" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> temp;
            arr[i].push_back(temp);
        }
    }
    int source, dest;
    vector<int> adj[n * m];
    makeAdjacencylist(arr, n, m, adj);
    cout << "Do you want to car pool with another person (y/n): ";
    char pool;
    cin >> pool;
    vector<int> final;
    cout << "Indexing start from (1,1)\n\n"
         << endl;
    if (pool == 'N' || pool == 'n')
    {
        int x, y;
        cout << "Enter the coordinates of the starting point: ";
        cin >> x;
        cin >> y;
        source = convert(x - 1, y - 1, m);
        cout << "Enter the coordinates of the ending point: ";
        cin >> x;
        cin >> y;
        dest = convert(x - 1, y - 1, m);
        final = getThePath(adj, source, dest, n * m, n, m);
        if (final[0] != -1)
        {
            sort(final.begin(), final.end());
            printMapWithLength(final, n, m);
        }
    }
    else if (pool == 'Y' || pool == 'y')
    {
        int mid;
        int x, y;
        cout << "Enter the coordinates of the starting point : ";
        cin >> x;
        cin >> y;
        source = convert(x - 1, y - 1, m);
        cout << "Enter the coordinates of the car pooling point : ";
        cin >> x;
        cin >> y;
        mid = convert(x - 1, y - 1, m);
        cout << "Enter the coordinates of the ending point : ";
        cin >> x;
        cin >> y;
        dest = convert(x - 1, y - 1, m);
        vector<int> v1 = getThePath(adj, source, mid, n * m, n, m);
        vector<int> v2 = getThePath(adj, mid, dest, n * m, n, m);
        if (v1[0] != -1 && v2[0] != -1)
        {
            cout << "The route he should follow is :-\n"
                 << endl;

            final.insert(final.end(), v1.begin(), v1.end());

            final.insert(final.end(), v2.begin(), v2.end());

            sort(final.begin(), final.end());
            auto it = unique(final.begin(), final.end());
            final.resize(distance(final.begin(), it));
            printMapWithLength(final, n, m);
        }
    }
    else
        cout << "Not a valid choice" << endl;
    return 0;
}
