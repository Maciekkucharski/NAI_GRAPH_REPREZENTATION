#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int inf = 999;

vector <vector<int>> read(istream &input_file) {

    vector <vector<int>> out;
    while (!input_file.eof()) {
        int start;
        int finish;
        int weight;
        input_file >> start;
        input_file >> finish;
        input_file >> weight;
        vector<int> edge = {start, finish, weight};
        out.push_back(edge);
    }
    out.pop_back();
    return out;
}

void generate_graph(vector <vector<int>> graph, ofstream &hook_out) {
    hook_out << "graph {\n";
    for (auto e: graph) {
        hook_out << e[0] << " -- " << e[1] << "[label=" << e[2] << "];\n";
    }
    hook_out << "}";
    system("dot -Tpng g.dot -o g.png");
}


void init_variables(int vertices_number, int start_vertex, vector<bool> &visited_vertices, vector<int> &target_weights,
                    vector<int> &parent) {
    visited_vertices = vector<bool>(vertices_number, false);
    for (int i = 0; i < vertices_number; i++) {
        target_weights.push_back(inf);
        parent.push_back(i);
    }
    target_weights[start_vertex] = 0;
}


int get_nearest_unvisited_vertex(int vertices_number, vector<bool> visited_vertices, vector<int> target_weights) {
    int min_weight = inf;
    int closest_vertex = 0;
    for (int i = 0; i < vertices_number; ++i) {
        if (!visited_vertices[i] && target_weights[i] < min_weight) {
            min_weight = target_weights[i];
            closest_vertex = i;
        }
    }
    return closest_vertex;
}


void display(int vertices_number, int start_vertex, vector<int> target_weights, vector<int> parent) {
    cout << "Vertex:\t\t\tWeight :\t\t\tPath\n";
    for (int i = 0; i < vertices_number; ++i) {
        cout << i << "\t\t\t" << target_weights[i] << "\t\t\t" << " ";
        cout << i << " ";
        int parent_node = parent[i];

        while (parent_node != start_vertex) {
            cout << " <- " << parent_node << " ";
            parent_node = parent[parent_node];
        }
        cout << endl;
    }
}


void dijkstra(int vertices_number, int start_vertex, vector<bool> &visited_vertices, vector<int> &target_weights,
              vector<int> &parent, vector <vector<int>> neighbour_weights) {
    init_variables(vertices_number, start_vertex, visited_vertices, target_weights, parent);
    for (int i = 0; i < vertices_number - 1; i++) {
        int nearest_vertex = get_nearest_vertex(vertices_number, visited_vertices, target_weights);
        visited_vertices[nearest_vertex] = true;

        for (int neighbour_vertex = 0; neighbour_vertex < vertices_number; ++neighbour_vertex) {
            if (neighbour_weights[nearest_vertex][neighbour_vertex] != inf && target_weights[neighbour_vertex] >
                                                                              target_weights[nearest_vertex] +
                                                                              neighbour_weights[nearest_vertex][neighbour_vertex]) {
                target_weights[neighbour_vertex] =
                        target_weights[nearest_vertex] + neighbour_weights[nearest_vertex][neighbour_vertex];
                parent[neighbour_vertex] = nearest_vertex;
            }
        }
    }
    display(vertices_number, start_vertex, target_weights, parent);
}


int main(int argc, char **argv) {

//    cout << "Reading Graph from file!" << std::endl;
//    string infile = argv[1];
//    ifstream hook_in(infile);
//    vector<vector<int>> graph = read(hook_in);
//    string outfile = argv[2];
//    ofstream hook_out(outfile);
//    generate_graph(graph, hook_out);

    int vertices_number, start_vertex;
    vector<bool> visited_vertices;
    vector<int> target_weights, parent;
    vector <vector<int>> neighbour_weights;

    cout << "number of vertices:"
            " ";
    cin >> vertices_number;
    cout << "\nPaste matrix: \n";
    for (int i = 0; i < vertices_number; i++) {
        vector<int> row_weight_vector;
        for (int j = 0; j < vertices_number; j++) {
            int tmp_weight;
            cin >> tmp_weight;
            row_weight_vector.push_back(tmp_weight);
        }
        neighbour_weights.push_back(row_weight_vector);
    }

    cout << "start vertex: ";
    cin >> start_vertex;
    dijkstra(vertices_number, start_vertex, visited_vertices, target_weights, parent, neighbour_weights);

}



