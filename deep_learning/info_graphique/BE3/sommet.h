#include <array>
#include <vector>

#ifndef SOMMET_H_
#define SOMMET_H_

class Sommet {
    public:
        Sommet();
        Sommet(double x, double y, double z);

        double x;
        double y;
        double z;

        std::array<double, 3> getCoords() const;
        int getFace();
        void setFace(int f);
        double getValue();
        void setValue(double v);
        void print();
        bool operator<(const Sommet& other) const;

        Sommet operator+(const Sommet& other) const;
        Sommet operator-(const Sommet& other) const;
        Sommet operator*(const Sommet& other) const;
        Sommet operator*(double scalar) const;
        Sommet operator/(double scalar) const;
        double norm() const;
        double norm2d() const;
        double dot(const Sommet& other) const;
        double computeAngle(const Sommet& other);
        void setAdjacentFaces(std::vector<int> faces);
        // std::vector<int> getAdjacentFaces();
        

    private:
        int Face;
        double value;
        // std::vector<int> adjacentFaces;
};

#endif // SOMMET_H_