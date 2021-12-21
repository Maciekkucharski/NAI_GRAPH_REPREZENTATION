#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
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

void generate_graph(vector<vector<int>> graph, ofstream &hook_out){
    hook_out << "graph {\n";
    for(auto e:graph){
        hook_out << e[0] << " -- " << e[1] << "[label=" << e[2] << "];\n";
    }
    hook_out << "}";
    system("dot -Tpng g.dot -o g.png");
}

int main(int argc, char **argv) {
    cout << "Reading Graph from file!" << std::endl;
    string infile = argv[1];
    ifstream hook_in(infile);
    vector<vector<int>> graph = read(hook_in);
    string outfile = argv[2];
    ofstream hook_out(outfile);
    generate_graph(graph, hook_out);

    return 0;
}
