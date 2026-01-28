#include <array>

#ifndef FACE_H_
#define FACE_H_


#include "sommet.h"
#include "mesh.h"
class Mesh; // Forward declaration of Mesh class


class Face {
    public:
        Face();
        Face(int s1, int s2, int s3);
        Face(int s1, int s2, int s3, double area, double angle1, double angle2, double angle3);
        Face(int s1, int s2, int s3, Mesh& mesh);
        void setSommets(int s1, int s2, int s3);
        std::array<int, 3> getSommets() const;
        void addAdjacentFace(int f);
        void replaceAdjacentFace(int newF, int oldF);
        std::array<int, 3> getAdjacentFaces() const;
        void print();
        double getArea() const;
        double getCotanAngle(int i) const;
        bool containsPoint(double s1, double s2, double s3);

        bool hasSommet(int s) const;
        int getNextSommet(int s) const;
        Sommet getBarycenter(Mesh& mesh);
        
    private:
        int s1;
        int s2;
        int s3;
        int f1;
        int f2;
        int f3;
        std::array<double, 3> cotanAngle;
        double area;
        void computeAngleAndArea(Mesh& mesh);
};

#endif