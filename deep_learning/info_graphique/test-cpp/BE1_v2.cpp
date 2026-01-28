#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

class Sommet {
    public:
        Sommet();
        Sommet(double x, double y, double z);
        void setFace(int f);
        void print();
        bool operator<(const Sommet& other) const;

    // private:
        double x;
        double y;
        double z;
        int Face;
};

Sommet::Sommet() : x(0), y(0), z(0), Face(-1) {}
Sommet::Sommet(double x, double y, double z) : x(x), y(y), z(z), Face(-1) {}

void Sommet::setFace(int f) {
    Face = f;
}

void Sommet::print() {
    cout << x << " " << y << " " << z << " Face: " << Face << endl;
}

bool Sommet::operator<(const Sommet& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
}


class Face {
    public:
        Face();
        Face(int s1, int s2, int s3);
        void addAdjacentFace(int f);
        void print();
    // private:
        int s1;
        int s2;
        int s3;
        int f1;
        int f2;
        int f3;
};

Face::Face() : s1(-1), s2(-1), s3(-1), f1(-1), f2(-1), f3(-1) {}

Face::Face(int s1, int s2, int s3) : s1(s1), s2(s2), s3(s3), f1(-1), f2(-1), f3(-1) {}

void Face::addAdjacentFace(int f) {
    if (f1 == -1) {
        f1 = f;
    } else if (f2 == -1) {
        f2 = f;
    } else if (f3 == -1) {
        f3 = f;
    }
}

void Face::print() {
    cout << "Sommets: " << s1 << " " << s2 << " " << s3 << endl;
    cout << "Faces: " << f1 << " " << f2 << " " << f3 << endl;
}

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces);
        void addFace(Face f);
        void addVertex(Sommet s);
        Mesh InitFromFile(std::string filename);
        void SaveToFile(std::string filename);
        void print();
    private:
        std::vector<Sommet> sommets;
        std::vector<Face> faces;
};

Mesh::Mesh() : sommets(), faces() {}

Mesh::Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces) : sommets(sommets), faces(Faces) {}

void Mesh::addFace(Face f) {
    faces.push_back(f);
}

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
        
        if (sommets[vertex_1_index].Face == -1) {
            sommets[vertex_1_index].setFace(i);
        }
        if (sommets[vertex_2_index].Face == -1) {
            sommets[vertex_2_index].setFace(i);
        }
        if (sommets[vertex_3_index].Face == -1) {
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
        file << sommets[i].x << " " << sommets[i].y << " " << sommets[i].z << endl;
    }
    for (int i = 0; i < faces.size(); i++) {
        file << "3 " << faces[i].s1 << " " << faces[i].s2 << " " << faces[i].s3 << endl;
    }
    file.close();
}

int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\prism.off");
    cout << endl << "========" << endl;
    cout << "Mesh: " << endl;
    // m.print();
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\test2.off");
    return 0;
}