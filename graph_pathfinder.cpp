#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <sstream>
using namespace std;

class Graph{
private:
    int total;
    vector<vector<pair<int,int>>> link;

public:
    Graph(int n){
        total = n;
        link.resize(n);
    }

    void addedge(int from, int to, int w){
        if(from < 0 || to < 0 || from >= total || to >= total){
            cout << "Invalid node number!\n";
            return;
        }
        link[from].push_back({to, w});
    }

    void runbfs(int start, const vector<string> &names){
        if(start < 0 || start >= total){
            cout << "Invalid start node!\n";
            return;
        }

        vector<int> visited(total, 0);
        queue<int> q;

        visited[start] = 1;
        q.push(start);

        cout << "BFS: ";

        while(!q.empty()){
            int now = q.front();
            q.pop();

            cout << names[now] << " ";

            for(auto &nbr : link[now]){
                int ne = nbr.first;
                if(!visited[ne]){
                    visited[ne] = 1;
                    q.push(ne);
                }
            }
        }
        cout << "\n";
    }

    void rundfshelp(int now, vector<int> &visited, const vector<string> &names){
        visited[now] = 1;
        cout << names[now] << " ";

        for(auto &nbr : link[now]){
            int ne = nbr.first;
            if(!visited[ne]){
                rundfshelp(ne, visited, names);
            }
        }
    }

    void rundfs(int start, const vector<string> &names){
        if(start < 0 || start >= total){
            cout << "Invalid start node!\n";
            return;
        }

        vector<int> visited(total, 0);

        cout << "DFS: ";
        rundfshelp(start, visited, names);
        cout << "\n";
    }

    void rundijkstra(int start, const vector<string> &names){
        if(start < 0 || start >= total){
            cout << "Invalid start node!\n";
            return;
        }

        vector<int> dist(total, numeric_limits<int>::max());
        vector<int> parent(total, -1);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while(!pq.empty()){
            auto top = pq.top();
            pq.pop();

            int cost = top.first;
            int now = top.second;

            if(cost > dist[now]) continue;

            for(auto &nbr : link[now]){
                int ne = nbr.first;
                int w = nbr.second;

                if(dist[now] + w < dist[ne]){
                    dist[ne] = dist[now] + w;
                    parent[ne] = now;
                    pq.push({dist[ne], ne});
                }
            }
        }

        cout << "Shortest distances from " << names[start] << ":\n";

        for(int i = 0; i < total; i++){
            cout << "to " << names[i] << " = " << dist[i];

            if(dist[i] != numeric_limits<int>::max()){
                cout << " ; path: ";
                vector<int> path;

                for(int v = i; v != -1; v = parent[v]){
                    path.push_back(v);
                }

                for(int j = path.size() - 1; j >= 0; j--){
                    cout << names[path[j]];
                    if(j > 0) cout << " -> ";
                }
            }
            cout << "\n";
        }
    }

    void displayNodes(const vector<string> &names){
        cout << "Nodes: ";
        for(int i = 0; i < total; i++){
            cout << names[i] << " ";
        }
        cout << "\n";
    }

    void displayEdges(const vector<string> &names){
        cout << "Edges (from -> to : weight):\n";
        for(int i = 0; i < total; i++){
            for(auto &nbr : link[i]){
                cout << names[i] << " -> " << names[nbr.first] << " : " << nbr.second << "\n";
            }
        }
    }

    bool isConnected(){
        if(total == 0) return true;

        vector<int> visited(total, 0);
        queue<int> q;

        visited[0] = 1;
        q.push(0);

        int count = 1;

        while(!q.empty()){
            int now = q.front();
            q.pop();

            for(auto &nbr : link[now]){
                int ne = nbr.first;
                if(!visited[ne]){
                    visited[ne] = 1;
                    q.push(ne);
                    count++;
                }
            }
        }

        return count == total;
    }

    bool detectCycleDFS(int node, vector<int> &visited, vector<int> &recStack){
        visited[node] = 1;
        recStack[node] = 1;

        for(auto &nbr : link[node]){
            int ne = nbr.first;

            if(!visited[ne] && detectCycleDFS(ne, visited, recStack))
                return true;
            else if(recStack[ne])
                return true;
        }

        recStack[node] = 0;
        return false;
    }

    bool hasCycle(){
        vector<int> visited(total, 0);
        vector<int> recStack(total, 0);

        for(int i = 0; i < total; i++){
            if(!visited[i]){
                if(detectCycleDFS(i, visited, recStack))
                    return true;
            }
        }
        return false;
    }
};

int main(){
    int n;
    cout << "How many nodes? ";
    while(!(cin >> n) || n <= 0){
        cout << "Invalid input! Enter a positive integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    vector<string> index2name(n);
    unordered_map<string,int> name2index;

    cout << "Do you want to name the cities? (y/n): ";
    char choice;
    cin >> choice;
    bool useNames = (choice == 'y' || choice == 'Y');
    cin.ignore();

    if(useNames){
        cout << "Enter the city names, one per line:\n";
        for(int i = 0; i < n; i++){
            string name;
            getline(cin, name);

            if(name.empty()){
                cout << "Empty name not allowed!\n";
                i--;
                continue;
            }

            if(name2index.count(name)){
                cout << "Duplicate name! Enter a unique name.\n";
                i--;
                continue;
            }

            index2name[i] = name;
            name2index[name] = i;
        }
    } else {
        for(int i = 0; i < n; i++){
            index2name[i] = to_string(i);
            name2index[index2name[i]] = i;
        }
    }

    Graph g(n);

    int e;
    cout << "How many edges? ";
    while(!(cin >> e) || e < 0){
        cout << "Invalid input! Enter a non-negative integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter each edge: from to weight\n";

    for(int i = 0; i < e; i++){
        string line, a, b;
        int w;

        getline(cin, line);
        stringstream ss(line);
        ss >> a >> b >> w;

        int ia = -1, ib = -1;

        try{
            if(useNames){
                if(!name2index.count(a) || !name2index.count(b)){
                    cout << "Invalid city name, try again.\n";
                    i--;
                    continue;
                }
                ia = name2index[a];
                ib = name2index[b];
            } else {
                ia = stoi(a);
                ib = stoi(b);

                if(ia < 0 || ib < 0 || ia >= n || ib >= n){
                    cout << "Invalid node number, try again.\n";
                    i--;
                    continue;
                }
            }

            if(w <= 0){
                cout << "Weight must be positive!\n";
                i--;
                continue;
            }
        } catch(...){
            cout << "Invalid input! Try again.\n";
            i--;
            continue;
        }

        g.addedge(ia, ib, w);
    }

    int choiceMenu;

    do{
        cout << "\nGRAPH-BASED PATH FINDER MENU\n";
        cout << "1. Display all nodes\n";
        cout << "2. Display all edges\n";
        cout << "3. Add an edge\n";
        cout << "4. Perform BFS\n";
        cout << "5. Perform DFS\n";
        cout << "6. Dijkstra shortest path from a node\n";
        cout << "7. Check if graph is fully connected\n";
        cout << "8. Check if graph has a cycle\n";
        cout << "9. Exit\n";

        cout << "Enter your choice: ";

        while(!(cin >> choiceMenu)){
            cout << "Invalid input! Enter a number between 1 and 9.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
        }

        cin.ignore();

        switch(choiceMenu){
            case 1:
                g.displayNodes(index2name);
                break;

            case 2:
                g.displayEdges(index2name);
                break;

            case 3:{
                cout << "Enter edge (from to weight): ";
                string line, a, b;
                int w;

                getline(cin, line);
                stringstream ss(line);
                ss >> a >> b >> w;

                int ia = -1, ib = -1;

                try{
                    if(useNames){
                        if(!name2index.count(a) || !name2index.count(b)){
                            cout << "Invalid city name!\n";
                            break;
                        }
                        ia = name2index[a];
                        ib = name2index[b];
                    } else {
                        ia = stoi(a);
                        ib = stoi(b);

                        if(ia < 0 || ib < 0 || ia >= n || ib >= n){
                            cout << "Invalid node number!\n";
                            break;
                        }
                    }

                    if(w <= 0){
                        cout << "Weight must be positive!\n";
                        break;
                    }
                } catch(...){
                    cout << "Invalid input!\n";
                    break;
                }

                g.addedge(ia, ib, w);
                break;
            }

            case 4:{
                cout << "Enter start node: ";
                string startName;
                getline(cin, startName);

                int start = -1;

                try{
                    if(useNames){
                        if(!name2index.count(startName)){
                            cout << "Invalid city name!\n";
                            break;
                        }
                        start = name2index[startName];
                    } else start = stoi(startName);

                    if(start < 0 || start >= n){
                        cout << "Invalid node number!\n";
                        break;
                    }
                } catch(...){
                    cout << "Invalid input!\n";
                    break;
                }

                g.runbfs(start, index2name);
                break;
            }

            case 5:{
                cout << "Enter start node: ";
                string startName;
                getline(cin, startName);

                int start = -1;

                try{
                    if(useNames){
                        if(!name2index.count(startName)){
                            cout << "Invalid city name!\n";
                            break;
                        }
                        start = name2index[startName];
                    } else start = stoi(startName);

                    if(start < 0 || start >= n){
                        cout << "Invalid node number!\n";
                        break;
                    }
                } catch(...){
                    cout << "Invalid input!\n";
                    break;
                }

                g.rundfs(start, index2name);
                break;
            }

            case 6:{
                cout << "Enter start node: ";
                string startName;
                getline(cin, startName);

                int start = -1;

                try{
                    if(useNames){
                        if(!name2index.count(startName)){
                            cout << "Invalid city name!\n";
                            break;
                        }
                        start = name2index[startName];
                    } else start = stoi(startName);

                    if(start < 0 || start >= n){
                        cout << "Invalid node number!\n";
                        break;
                    }
                } catch(...){
                    cout << "Invalid input!\n";
                    break;
                }

                g.rundijkstra(start, index2name);
                break;
            }

            case 7:
                if(g.isConnected())
                    cout << "The graph is fully connected!\n";
                else
                    cout << "The graph is NOT fully connected!\n";
                break;

            case 8:
                if(g.hasCycle())
                    cout << "The graph contains a cycle!\n";
                else
                    cout << "The graph does NOT contain a cycle.\n";
                break;

            case 9:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while(choiceMenu != 9);

    return 0;
}