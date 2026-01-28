#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>

#include "sommet.h"
#include "face.h"
#include "mesh.h"

using namespace std;


Mesh::Mesh() : sommets(), faces() {}

Mesh::Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces) : sommets(sommets), faces(Faces) {}

void Mesh::print() {
    cout << "Nb de sommets : " << sommets.size() << endl;
    for (int i = 0; i < sommets.size(); i++) {
        cout << endl << "Sommet " << i << endl;
        sommets[i].print();
    }
    cout << "Nb de faces : " << faces.size() << endl;
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
    double area;
    double angle1, angle2, angle3;
    Sommet sommet1, sommet2, sommet3;
    for (int i=0; i<num_faces; i++) {
        // if (i % 1000 == 0) {
        //     cout << i << endl;
        // }
        int num_vertices_face, vertex_1_index, vertex_2_index, vertex_3_index;
        file >> num_vertices_face >> vertex_1_index >> vertex_2_index >> vertex_3_index;
        // cout << endl << "Face " << i << ": " << vertex_1_index << " " << vertex_2_index << " " << vertex_3_index << endl;
        sommet1 = sommets[vertex_1_index];
        sommet2 = sommets[vertex_2_index];
        sommet3 = sommets[vertex_3_index];

        // area = computeAreaFromSommet(sommet1, sommet2, sommet3);
        // angle1 = computeCotanAngle(sommet1, sommet2, sommet3);
        // angle2 = computeCotanAngle(sommet2, sommet1, sommet3);
        // angle3 = computeCotanAngle(sommet3, sommet1, sommet2);
        // faces.push_back(Face(vertex_1_index, vertex_2_index, vertex_3_index, area, angle1, angle2, angle3));
        faces.push_back(Face(vertex_1_index, vertex_2_index, vertex_3_index, *this));

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

    std::vector<double> values;
    for (int i = 0; i < sommets.size(); i++) {
        values.push_back(sommets[i].getValue());
    }
    double minValue = *min_element(values.begin(), values.end());
    double maxValue = *max_element(values.begin(), values.end());

    for (int i = 0; i < sommets.size(); i++) {
        double x = sommets[i].getCoords()[0];
        double y = sommets[i].getCoords()[1];
        double z = sommets[i].getCoords()[2];
        double value = values[i];
        int colorR = (value-minValue) / (maxValue-minValue) * 255;
        int colorG = 0;
        int colorB = 0;
        file << x << " " << y << " " << z << " " << colorR << " " << colorG << " " << colorB << endl;
    }
    for (int i = 0; i < faces.size(); i++) {
        int s1 = faces[i].getSommets()[0];
        int s2 = faces[i].getSommets()[1];
        int s3 = faces[i].getSommets()[2];
        file << "3 " << s1 << " " << s2 << " " << s3 << endl;
    }
    file.close();
}

double Mesh::computeCotanAngle(Sommet sommetMain, Sommet sommet1, Sommet sommet2) {
    Sommet v1 = sommet1 - sommetMain;
    Sommet v2 = sommet2 - sommetMain;

    double angle = v1.computeAngle(v2);
    return 1 / tan(angle);
}

double Mesh::computeAreaFromSommet(Sommet sommet1, Sommet sommet2, Sommet sommet3) {
    Sommet v1 = sommet2 - sommet1;
    Sommet v2 = sommet3 - sommet1;
    return (v1 * v2).norm() / 2;
}