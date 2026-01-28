#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Sommet {
    public:
        Sommet();
        Sommet(double x, double y, double z);
        void setFace(int *f);
        void test();
        void print();

    // private:
        double x;
        double y;
        double z;
        int *Face;
};

Sommet::Sommet() : x(0), y(0), z(0), Face(nullptr) {}
Sommet::Sommet(double x, double y, double z) : x(x), y(y), z(z), Face(nullptr) {}

void Sommet::setFace(int *f) {
    Face = f;
}

void Sommet::test() {
    cout << "x: " << x << " y: " << y << " z: " << z << endl;
}

void Sommet::print() {
    cout << "x: " << x << " y: " << y << " z: " << z << " Face: " << Face << endl;
}

class Face {
    public:
        Face();
        Face(int *s1, int *s2, int *s3);
        void addAdjacentFace(Face *f);
        void print();
    // private:
        int *s1;
        int *s2;
        int *s3;
        Face *f1;
        Face *f2;
        Face *f3;
};

Face::Face() : s1(nullptr), s2(nullptr), s3(nullptr), f1(nullptr), f2(nullptr), f3(nullptr) {}

Face::Face(int *s1, int *s2, int *s3) : s1(s1), s2(s2), s3(s3), f1(nullptr), f2(nullptr), f3(nullptr) {}

void Face::addAdjacentFace(Face *f) {
    if (f1 == nullptr) {
        f1 = f;
    } else if (f2 == nullptr) {
        f2 = f;
    } else if (f3 == nullptr) {
        f3 = f;
    }
}

void Face::print() {
    cout << "Sommet 1: " << *s1 << " Sommet 2: " << *s2 << " Sommet 3: " << *s3 << endl;
    cout << "Face 1: " << f1 << " Face 2: " << f2 << " Face 3: " << f3 << endl;
}

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces);
        Mesh InitFromFile(std::string filename);
        void print();
        void SaveToFile(std::string filename);
    private:
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
    }

    std::vector<Face> Faces;
    for (int i=0; i<num_faces; i++) {
        int num_vertices_face, vertex_1_index, vertex_2_index, vertex_3_index;
        file >> num_vertices_face >> vertex_1_index >> vertex_2_index >> vertex_3_index;
        cout << "Face " << i << ": " << vertex_1_index << " " << vertex_2_index << " " << vertex_3_index << endl;
        Faces.push_back(Face(&vertex_1_index, &vertex_2_index, &vertex_3_index));
        
        if (sommets[vertex_1_index].Face == nullptr) {
            sommets[vertex_1_index].setFace(&i);
        }
        else if (sommets[vertex_2_index].Face == nullptr) {
            sommets[vertex_2_index].setFace(&i);
        }
        else if (sommets[vertex_3_index].Face == nullptr) {
            sommets[vertex_3_index].setFace(&i);
        }
    }

    // Definir le voisinage des faces
    // for (int i=0; i<num_faces; i++) {
    //     Face *f = &Faces[i];
    //     for (int j = 0; j < num_faces; j++) {
    //         if (i == j) continue;
    //         Face *adjFace = &Faces[j];
    //         if ((f->s1 == adjFace->s1 && f->s2 == adjFace->s2) || 
    //         (f->s1 == adjFace->s2 && f->s2 == adjFace->s1) ||
    //         (f->s1 == adjFace->s1 && f->s2 == adjFace->s3) ||
    //         (f->s1 == adjFace->s3 && f->s2 == adjFace->s1) ||
    //         (f->s1 == adjFace->s2 && f->s2 == adjFace->s3) ||
    //         (f->s1 == adjFace->s3 && f->s2 == adjFace->s2)) {
    //         f->addAdjacentFace(adjFace);
    //         }
    //         if ((f->s2 == adjFace->s1 && f->s3 == adjFace->s2) || 
    //         (f->s2 == adjFace->s2 && f->s3 == adjFace->s1) ||
    //         (f->s2 == adjFace->s1 && f->s3 == adjFace->s3) ||
    //         (f->s2 == adjFace->s3 && f->s3 == adjFace->s1) ||
    //         (f->s2 == adjFace->s2 && f->s3 == adjFace->s3) ||
    //         (f->s2 == adjFace->s3 && f->s3 == adjFace->s2)) {
    //         f->addAdjacentFace(adjFace);
    //         }
    //         if ((f->s3 == adjFace->s1 && f->s1 == adjFace->s2) || 
    //         (f->s3 == adjFace->s2 && f->s1 == adjFace->s1) ||
    //         (f->s3 == adjFace->s1 && f->s1 == adjFace->s3) ||
    //         (f->s3 == adjFace->s3 && f->s1 == adjFace->s1) ||
    //         (f->s3 == adjFace->s2 && f->s1 == adjFace->s3) ||
    //         (f->s3 == adjFace->s3 && f->s1 == adjFace->s2)) {
    //         f->addAdjacentFace(adjFace);
    //         }
    //     }
    // }
    

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
    Sommet s = Sommet(1, 2, 3);
    s.test();
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\test.off");
    cout << endl << "========" << endl;
    cout << "Mesh: " << endl;
    m.print();
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\test2.off");
    return 0;
}