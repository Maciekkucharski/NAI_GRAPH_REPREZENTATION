//#include <iostream>
//#include <vector>
//#include <fstream>
//
//using namespace std;
//
//const int inf = INT_MAX;
//int V, start_vertex, weight[100][100];
//int dist[100];
//bool visited_vertices[100] = {0};
//int parent[100];
//
//
//void init_variables() {
//    for (int i = 0; i < V; i++) {
//        dist[i] = inf;
//        parent[i] = i;
//    }
//    dist[start_vertex] = 0;
//}
//
//int get_nearest_vertex() {
//    int minvalue = inf;
//    int minnode = 0;
//    for (int i = 0; i < V; ++i) {
//        if (!visited_vertices[i] && dist[i] < minnode) { //check if not visited_vertices and distnce less the curent min val
//            minvalue = dist[i];
//            minnode = i;
//        }
//    }
//    return minnode;
//}
//
//void dijkstra() {
//    for (int i = 0; i < V - 1; i++) {
//        int nearest = get_nearest_vertex();
//        visited_vertices[nearest] = true;//mark as visited_vertices
//
//        for (int adj = 0; adj < V; ++adj) {
//            if (weight[nearest][adj] != inf
//                && dist[adj] > dist[nearest] + weight[nearest][adj]) {
//                dist[adj] = dist[nearest] + weight[nearest][adj];
//                parent[adj] = nearest;
//            }
//        }
//    }
//}
//
//void display() {
//    cout << "Node:\t\t\tCost :\t\t\tPath";
//    for (int i = 0; i < V; ++i) {
//        cout << i << "\t\t\t" << dist[i] << "\t\t\t" << " ";
//        cout << i << " ";
//        int parnode = parent[i];
//
//        while (parnode != start_vertex) {
//            cout << " <- " << parnode << " ";
//            parnode = parent[parnode];
//        }
//        cout << endl;
//    }
//}
//
//
//int main(void) {
//    int start_vertex;
//    cin >> V;
//    for (int i = 0; i < V; i++)
//        for (int j = 0; j < V; j++)
//            cin >> weight[i][j];
//    cin >> start_vertex;
//    init_variables();
//    dijkstra();
//    display();
//}
