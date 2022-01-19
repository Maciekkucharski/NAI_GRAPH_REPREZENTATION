#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int inf = 999;

vector<vector<int>> read(istream &input_file) {

    vector<vector<int>> out;
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

void generate_graph(const vector<vector<int>> graph, ofstream &hook_out, const vector<vector<int>> path) {
    hook_out << "graph {\n";
    for (auto e: graph) {
        bool used_path = false;
        for (auto z: path) {
            if ((e[0] == z[0] && e[1] == z[1]) ||(e[0] == z[1] && e[1] == z[0])){
                hook_out << e[0] << " -- " << e[1] << "[label=" << e[2] << ", color=red];\n";
                used_path = !used_path;
            }
        }
        if (!used_path) {
            hook_out << e[0] << " -- " << e[1] << "[label=" << e[2] << "];\n";
        }
    }
    hook_out << "}";
}


void init_variables(int vertices_number, int start_vertex, vector<bool> &visited_vertices, vector<int> &target_weights,
                    vector<int> &parent_matrix) {
    visited_vertices = vector<bool>(vertices_number, false);
    for (int i = 0; i < vertices_number; i++) {
        target_weights.push_back(inf);
        parent_matrix.push_back(i);
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


void dijkstra(int vertices_number, int start_vertex, vector<bool> &visited_vertices, vector<int> &target_weights,
              vector<int> &parent_matrix, vector<vector<int>> neighbour_weights) {
    init_variables(vertices_number, start_vertex, visited_vertices, target_weights, parent_matrix);
    for (int i = 0; i < vertices_number - 1; i++) {
        int nearest_vertex = get_nearest_unvisited_vertex(vertices_number, visited_vertices, target_weights);
        visited_vertices[nearest_vertex] = true;

        for (int potential_neighbour_vertex = 0;
             potential_neighbour_vertex < vertices_number; ++potential_neighbour_vertex) {
            if (neighbour_weights[nearest_vertex][potential_neighbour_vertex] != inf &&
                target_weights[potential_neighbour_vertex] >
                target_weights[nearest_vertex] + neighbour_weights[nearest_vertex][potential_neighbour_vertex]) {
                target_weights[potential_neighbour_vertex] =
                        target_weights[nearest_vertex] + neighbour_weights[nearest_vertex][potential_neighbour_vertex];
                parent_matrix[potential_neighbour_vertex] = nearest_vertex;
            }
        }
    }
}


vector<vector<int>> convert(vector<vector<int>> neighbour_weights) {
    vector<vector<int>> graph;
    for (int i = 0; i < neighbour_weights.size(); i++) {
        for (int j = i + 1; j < neighbour_weights.size(); ++j) {
            if ((neighbour_weights[i][j] != 999) && (neighbour_weights[i][j] != 0)) {
                vector<int> edge;
                edge.push_back(i);
                edge.push_back(j);
                edge.push_back(neighbour_weights[i][j]);
                graph.push_back(edge);
            }
        }
    }
    return graph;
}

int main(int argc, char **argv) {
    int vertices_number, start_vertex;
    vector<bool> visited_vertices;
    vector<int> target_weights, parent_matrix;
    vector<vector<int>> neighbour_weights;

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
    dijkstra(vertices_number, start_vertex, visited_vertices, target_weights, parent_matrix, neighbour_weights);
    vector<vector<int>> graph = convert(neighbour_weights);

    cout << "What vertex do you want to go to?: ";
    int chosen_vertex;
    cin >> chosen_vertex;
    int parent_node = parent_matrix[chosen_vertex];

    vector<int> path;
    path.push_back(chosen_vertex);
    while (parent_node != start_vertex) {
        path.push_back(parent_node);
        parent_node = parent_matrix[parent_node];
    }
    path.push_back(start_vertex);



    vector<vector<int>> converted_path;
    for (int i = 0; i < path.size() - 1; ++i) {
        vector<int> edge;
        edge.push_back(path[i]);
        edge.push_back(path[i + 1]);
        converted_path.push_back(edge);
    }


    string outfile = "new_graph.dot";
    ofstream hook_out(outfile);
    generate_graph(graph, hook_out, converted_path);


}



