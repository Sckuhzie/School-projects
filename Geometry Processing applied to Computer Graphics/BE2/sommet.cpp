#include <iostream>
#include <array>
#include "sommet.h"
#include <vector>
#include <cmath>

using namespace std;


Sommet::Sommet() : x(0), y(0), z(0), Face(-1), value(0) {}

Sommet::Sommet(double x, double y, double z) : x(x), y(y), z(z), Face(-1), value(0) {}

std::array<double, 3> Sommet::getCoords() const {
    return {x, y, z};
}

int Sommet::getFace() {
    return Face;
}

void Sommet::setFace(int f) {
    Face = f;
}

double Sommet::getValue() {
    return value;
}

void Sommet::setValue(double v) {
    value = v;
}

void Sommet::print() {
    cout << x << " " << y << " " << z << " Face: " << Face << "; Value : " << value <<endl;
}

bool Sommet::operator<(const Sommet& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
}

Sommet Sommet::operator+(const Sommet& other) const {
    return Sommet(x + other.x, y + other.y, z + other.z);
}

Sommet Sommet::operator-(const Sommet& other) const {
    return Sommet(x - other.x, y - other.y, z - other.z);
}

Sommet Sommet::operator*(const Sommet& other) const {
    return Sommet(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}

double Sommet::norm() const {
    return sqrt(x*x + y*y + z*z);
}

double Sommet::dot(const Sommet& other) const {
    return x*other.x + y*other.y + z*other.z;
}

double Sommet::computeAngle(const Sommet& other) {
    // Ne prend pas en compte l'orientation de l'angle (resultat toujours positif)
    double cosAngle = dot(other) / (norm() * other.norm());
    return acos(cosAngle);
}

void Sommet::setAdjacentFaces(std::vector<int> faces) {
    adjacentFaces = faces;
}

vector<int> Sommet::getAdjacentFaces() {
    return adjacentFaces;
}