#include <iostream>
#include <array>

using namespace std;

class Sommet {
    public:
        Sommet();
        Sommet(double x, double y, double z);
        std::array<double, 3> getCoords() const;
        int getFace();
        void setFace(int f);
        void print();
        bool operator<(const Sommet& other) const;

    private:
        double x;
        double y;
        double z;
        int Face;
};

Sommet::Sommet() : x(0), y(0), z(0), Face(-1) {}

Sommet::Sommet(double x, double y, double z) : x(x), y(y), z(z), Face(-1) {}

std::array<double, 3> Sommet::getCoords() const {
    return {x, y, z};
}

int Sommet::getFace() {
    return Face;
}

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