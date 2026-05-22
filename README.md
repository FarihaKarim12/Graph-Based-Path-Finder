# 🔷 Graph - Based Path Finder

A **directed weighted graph visualizer** built as a DSA project — available in two versions:

- **C++ CLI version** — terminal-based, classic DSA implementation
- **Web GUI version** — interactive visual canvas with animated algorithms

---

## Features

### Graph Operations
- Add / remove nodes and edges (with weights)
- Directed edges with visual arrowheads
- Drag-and-drop node repositioning

### Algorithms (all animated in GUI)
| Algorithm | Description |
|---|---|
| BFS | Breadth-First Search — level-order traversal using a queue |
| DFS | Depth-First Search — recursive deep traversal |
| Dijkstra | Shortest path from a source node (non-negative weights) |
| Connectivity Check | BFS from node 0 to verify all nodes are reachable |
| Cycle Detection | DFS with recursion stack to detect back-edges |

### GUI Extras
- Step-by-step animation with adjustable speed
- Color-coded node states (visited, current, shortest path)
- Output log panel with per-algorithm results
- Built-in presets: Pakistan cities road network, random graph

---

## Project Structure

```
graph_pathfinder.cpp      # C++ CLI version (original DSA project)
graph_pathfinder.html     # Web GUI version (self-contained, no dependencies)
```

---

## Usage flow:
1. Enter number of nodes
2. Optionally name them (e.g. city names)
3. Enter edges as `from to weight`
4. Use the menu to run BFS, DFS, Dijkstra, etc.

---

## Data Structures Used

| Structure | Used For |
|---|---|
| `vector<vector<pair<int,int>>>` | Adjacency list (node → {neighbor, weight}) |
| `queue<int>` | BFS traversal |
| `priority_queue` (min-heap) | Dijkstra's algorithm |
| `vector<int>` (visited, recStack) | DFS and cycle detection |
| `unordered_map<string,int>` | Name-to-index mapping (CLI) |

---

## Algorithm Details

### BFS
Explores nodes layer by layer using a queue. Marks nodes visited before enqueuing to avoid duplicates. Time complexity: **O(V + E)**.

### DFS
Recursive depth-first traversal. Uses a visited array to avoid infinite loops in cyclic graphs. Time complexity: **O(V + E)**.

### Dijkstra
Greedy shortest-path algorithm using a min-heap priority queue. Skips stale queue entries with the `cost > dist[now]` check. Reconstructs paths via a `parent[]` array. Time complexity: **O((V + E) log V)**. Works only with **non-negative edge weights**.

### Cycle Detection
DFS with two arrays — `visited[]` and `recStack[]`. If a neighbor is found in the current recursion stack, a back-edge (cycle) exists. The recursion stack is cleaned up on backtrack.

### Connectivity Check
BFS from node 0. If the number of reachable nodes equals total nodes, the graph is fully connected (for directed graphs, this checks reachability, not strong connectivity).

---

## Sample Run (CLI)

```
How many nodes? 4
Do you want to name the cities? (y/n): y
Enter the city names, one per line:
Karachi
Hyderabad
Sukkur
Lahore

How many edges? 3
Enter each edge: from to weight
Karachi Hyderabad 136
Hyderabad Sukkur 322
Sukkur Lahore 383

--- GRAPH-BASED PATH FINDER MENU ---
6. Dijkstra shortest path from a node
Enter start node: Karachi

Shortest distances from Karachi:
to Karachi    = 0   ; path: Karachi
to Hyderabad  = 136 ; path: Karachi -> Hyderabad
to Sukkur     = 458 ; path: Karachi -> Hyderabad -> Sukkur
to Lahore     = 841 ; path: Karachi -> Hyderabad -> Sukkur -> Lahore
```

---

## Limitations

- Dijkstra does not support negative edge weights (use Bellman-Ford for that)
- Connectivity check in CLI is directional — checks reachability from node 0 only, not strong connectivity
- No support for parallel edges (multiple edges between same pair of nodes)

---

## Tech Stack

| Version | Language | Libraries |
|---|---|---|
| CLI | C++11 | STL only (`vector`, `queue`, `unordered_map`, `sstream`) |
| GUI | HTML / CSS / JavaScript | Vanilla JS, no frameworks or dependencies |

---

## Author

Built as a Data Structures & Algorithms project.  
Implements core graph theory concepts: adjacency lists, BFS, DFS, Dijkstra, cycle detection.

## Live Demo
https://farihakarim12.github.io/Product_Listing_Website/
