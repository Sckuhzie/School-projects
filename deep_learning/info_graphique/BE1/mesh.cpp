#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "sommet.cpp"
#include "face.cpp"

using namespace std;

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces);
        Mesh InitFromFile(std::string filename);
        void SaveToFile(std::string filename);
        void print();
    private:
        std::vector<Sommet> sommets;
        std::vector<Face> faces;
        std::map<pair<int, int>, int> edges;
};

Mesh::Mesh() : sommets(), faces() {}

Mesh::Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces) : sommets(sommets), faces(Faces) {}

void Mesh::print() {
    for (int i = 0; i < sommets.size(); i++) {
        cout << endl << "Sommet " << i << endl;
        sommets[i].print();
    }
    for (int i = 0; i < faces.size(); i++) {
        cout << endl << "Face " << i << endl;
        faces[i].print();
    }
}

Mesh Mesh::InitFromFile(std::string filename) {
    ifstream file(filename);
    string line;
    file >> line; // Read OFF header
    cout << line << endl;

    int num_vertices, num_faces, num_edges;
    file >> num_vertices >> num_faces >> num_edges;
    cout << "Number of vertices: " << num_vertices << endl;
    cout << "Number of faces: " << num_faces << endl;
    cout << "Number of edges: " << num_edges << endl;

    std::vector<Sommet> sommets;

    for (int i = 0; i<num_vertices; i++) {
        // if (i % 1000 == 0) {
        //     cout << i << endl;
        // }
        double x, y, z;
        file >> x >> y >> z;
        // cout << "Vertex " << i << ": " << x << " " << y << " " << z << endl;
        sommets.push_back(Sommet(x, y, z));
    }

    std::vector<Face> faces;
    std::map<pair<int, int>, int> edges;
    bool ret;
    int j;
    for (int i=0; i<num_faces; i++) {
        // if (i % 1000 == 0) {
        //     cout << i << endl;
        // }
        int num_vertices_face, vertex_1_index, vertex_2_index, vertex_3_index;
        file >> num_vertices_face >> vertex_1_index >> vertex_2_index >> vertex_3_index;
        // cout << endl << "Face " << i << ": " << vertex_1_index << " " << vertex_2_index << " " << vertex_3_index << endl;
        faces.push_back(Face(vertex_1_index, vertex_2_index, vertex_3_index));
        
        if (sommets[vertex_1_index].getFace() == -1) {
            sommets[vertex_1_index].setFace(i);
        }
        if (sommets[vertex_2_index].getFace() == -1) {
            sommets[vertex_2_index].setFace(i);
        }
        if (sommets[vertex_3_index].getFace() == -1) {
            sommets[vertex_3_index].setFace(i);
        }

        if (sommets[vertex_2_index] < sommets[vertex_1_index]) std::swap(vertex_1_index, vertex_2_index);
        if (sommets[vertex_3_index] < sommets[vertex_1_index]) std::swap(vertex_1_index, vertex_3_index);
        if (sommets[vertex_3_index] < sommets[vertex_2_index]) std::swap(vertex_2_index, vertex_3_index);
        
        pair<int, int> edge1 = make_pair(vertex_1_index, vertex_2_index);
        pair<int, int> edge2 = make_pair(vertex_2_index, vertex_3_index);
        pair<int, int> edge3 = make_pair(vertex_1_index, vertex_3_index);

        // cout << "Edges : " << endl;
        // cout << "Edge 1 : " << vertex_1_index << " " << vertex_2_index << endl;
        // cout << "Edge 2 : " << vertex_2_index << " " << vertex_3_index << endl;
        // cout << "Edge 3 : " << vertex_1_index << " " << vertex_3_index << endl;

        ret = edges.insert(make_pair(edge1, i)).second;
        if (!ret) {
            j = edges[edge1];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }

        ret = edges.insert(make_pair(edge2, i)).second;
        if (!ret) {
            j = edges[edge2];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }
        
        ret = edges.insert(make_pair(edge3, i)).second;
        if (!ret) {
            j = edges[edge3];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }
    }
    return Mesh(sommets, faces);
}

void Mesh::SaveToFile(std::string filename) {
    ofstream file(filename);
    file << "OFF" << endl;
    file << sommets.size() << " " << faces.size() << " 0" << endl;
    for (int i = 0; i < sommets.size(); i++) {
        double x = sommets[i].getCoords()[0];
        double y = sommets[i].getCoords()[1];
        double z = sommets[i].getCoords()[2];
        file << x << " " << y << " " << z << endl;
    }
    for (int i = 0; i < faces.size(); i++) {
        int s1 = faces[i].getSommets()[0];
        int s2 = faces[i].getSommets()[1];
        int s3 = faces[i].getSommets()[2];
        file << "3 " << s1 << " " << s2 << " " << s3 << endl;
    }
    file.close();
}