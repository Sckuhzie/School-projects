#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Mesh; // Forward declaration of Mesh class

class Sommet {
    public:
        Sommet();
        Sommet(double x, double y, double z);
        void setFace(int f);
        void print();

        vector<Sommet> getAdjacentVertices(Mesh mesh); //
        double computeArea(); //       
        double computeLaplacian(); //

        bool operator==(const Sommet& other) const;
    // private:
        double x;
        double y;
        double z;
        int Face;
        double value;
};

Sommet::Sommet() : x(0), y(0), z(0), Face(-1) {}
Sommet::Sommet(double x, double y, double z) : x(x), y(y), z(z), Face(-1) {}

void Sommet::setFace(int f) {
    Face = f;
}

void Sommet::print() {
    cout << x << " " << y << " " << z << " Face: " << Face << endl;
}
bool Sommet::operator==(const Sommet& other) const {
    return x == other.x && y == other.y && z == other.z && Face == other.Face;
}

vector<Sommet> Sommet::getAdjacentVertices(Mesh mesh) {
    vector<Sommet> adjacentVertices;

    vector<int> exploredFaces;
    exploredFaces.push_back(Face);

    int verticeIndex;
    if (mesh.sommets[mesh.Faces[Face].s1] == this) {
        verticeIndex = mesh.Faces[Face].s1;
    }
    else if (mesh.sommets[mesh.Faces[Face].s2] == this) {
        verticeIndex = mesh.Faces[Face].s2;
    }
    else if (mesh.sommets[mesh.Faces[Face].s3] == this) {
        verticeIndex = mesh.Faces[Face].s3;
    }


    return adjacentVertices;
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
    cout << "Sommet 1: " << s1 << " Sommet 2: " << s2 << " Sommet 3: " << s3 << endl;
    cout << "Face 1: " << f1 << " Face 2: " << f2 << " Face 3: " << f3 << endl;
}

class Mesh {
    public:
        Mesh();
        Mesh(vector<Sommet> sommets, vector<Face> Faces);
        Mesh InitFromFile(string filename);
        void print();
        void SaveToFile(string filename);
    // private:
        std::vector<Sommet> sommets;
        std::vector<Face> Faces;
};

Mesh::Mesh() : sommets(), Faces() {}

Mesh::Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces) : sommets(sommets), Faces(Faces) {}

void Mesh::print() {
    for (int i = 0; i < sommets.size(); i++) {
        cout << "Sommet " << i << endl;
        sommets[i].print();
    }
    for (int i = 0; i < Faces.size(); i++) {
        cout << "Face " << i << endl;
        Faces[i].print();
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
        double x, y, z;
        file >> x >> y >> z;
        // cout << "Vertex " << i << ": " << x << " " << y << " " << z << endl;
        sommets.push_back(Sommet(x, y, z));
        if (i % 1000 == 0) {
            cout << i << endl;
        }
    }

    std::vector<Face> Faces;
    for (int i=0; i<num_faces; i++) {
        if (i % 1000 == 0) {
            cout << i << endl;
        }
        int num_vertices_face, vertex_1_index, vertex_2_index, vertex_3_index;
        file >> num_vertices_face >> vertex_1_index >> vertex_2_index >> vertex_3_index;
        // cout << "Face " << i << ": " << vertex_1_index << " " << vertex_2_index << " " << vertex_3_index << endl;
        Faces.push_back(Face(vertex_1_index, vertex_2_index, vertex_3_index));
        
        if (sommets[vertex_1_index].Face == -1) {
            sommets[vertex_1_index].setFace(i);
        }
        if (sommets[vertex_2_index].Face == -1) {
            sommets[vertex_2_index].setFace(i);
        }
        if (sommets[vertex_3_index].Face == -1) {
            sommets[vertex_3_index].setFace(i);
        }

        for (int j = 0; j < Faces.size()-1; j++) {
            int sharedVertices = 0;
            if (Faces[i].s1 == Faces[j].s1 || Faces[i].s1 == Faces[j].s2 || Faces[i].s1 == Faces[j].s3) sharedVertices++;
            if (Faces[i].s2 == Faces[j].s1 || Faces[i].s2 == Faces[j].s2 || Faces[i].s2 == Faces[j].s3) sharedVertices++;
            if (Faces[i].s3 == Faces[j].s1 || Faces[i].s3 == Faces[j].s2 || Faces[i].s3 == Faces[j].s3) sharedVertices++;
            
            if (sharedVertices == 2) {
                Faces[i].addAdjacentFace(j);
                Faces[j].addAdjacentFace(i);
            }
            
        }
    }
    

    return Mesh(sommets, Faces);
}

void Mesh::SaveToFile(std::string filename) {
    ofstream file(filename);
    file << "OFF" << endl;
    file << sommets.size() << " " << Faces.size() << " 0" << endl;
    for (int i = 0; i < sommets.size(); i++) {
        file << sommets[i].x << " " << sommets[i].y << " " << sommets[i].z << endl;
    }
    for (int i = 0; i < Faces.size(); i++) {
        file << "3 " << Faces[i].s1 << " " << Faces[i].s2 << " " << Faces[i].s3 << endl;
    }
    file.close();
}

int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\octaedron.off");
    cout << endl << "========" << endl;
    cout << "Mesh: " << endl;
    m.print();
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\test2.off");
    return 0;
}