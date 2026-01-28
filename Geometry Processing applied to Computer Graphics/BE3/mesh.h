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
        void SaveToFile(std::string filename, bool colorVertex, bool colorFace);
        void print();
        void splitFace(double s1, double s2, double s3, int faceIndex);
        void splitEdge(int face1, int face2, double s1, double s2, double s3);
        void flipEdge(int face1, int face2);
        void insertion2D(double s1, double s2, double s3);
        bool isEdgeLocalDelaunay(int face1, int face2);
        bool isDelaunay();
        void LawsonAlgorithm();
        void updateDelaunay();
        std::array<int, 4> getPointsFrom2Faces(int face1, int face2);
        bool orientationTest(int point1, int point2, int point3);
        Mesh initFromPoints(std::string filename);

    private:
        std::vector<Sommet> sommets;
        std::vector<Face> faces;
        std::map<std::pair<int, int>, int> edges;
        double computeCotanAngle(Sommet sommetMain, Sommet sommet1, Sommet sommet2);
        double computeAreaFromSommet(Sommet sommet1, Sommet sommet2, Sommet sommet3);
        void addPointOutsideMesh(double s1, double s2, double s3);
        void makeConvexShape(int newSommet, int sommet1, int closestFace, int newFace, bool right);
        void initMeshBoundingBox(std::string filename);

};

#endif // MESH_H_