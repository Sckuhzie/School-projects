#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#ifndef MESH_H_
#define MESH_H_

#include "sommet.h"
#include "face.h"

class Mesh {
    public:
        Mesh();
        Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces);
        Sommet& getSommet(int i) { return sommets[i]; }
        Face& getFace(int i) { return faces[i]; }
        std::vector<Sommet> getSommets() const { return sommets; }
        std::vector<Face> getFaces() const { return faces; }
        Mesh InitFromFile(std::string filename);
        void SaveToFile(std::string filename);
        void print();

    private:
        std::vector<Sommet> sommets;
        std::vector<Face> faces;
        std::map<std::pair<int, int>, int> edges;
        double computeCotanAngle(Sommet sommetMain, Sommet sommet1, Sommet sommet2);
        double computeAreaFromSommet(Sommet sommet1, Sommet sommet2, Sommet sommet3);
};

#endif // MESH_H_