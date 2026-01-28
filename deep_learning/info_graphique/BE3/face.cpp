#include <iostream>
#include <array>

#include "face.h"
#include "sommet.h"
using namespace std;


Face::Face() : s1(-1), s2(-1), s3(-1), f1(-1), f2(-1), f3(-1) {}

Face::Face(int s1, int s2, int s3) : s1(s1), s2(s2), s3(s3), f1(-1), f2(-1), f3(-1) {}

Face::Face(int s1, int s2, int s3, double area, double angle1, double angle2, double angle3) : s1(s1), s2(s2), s3(s3), f1(-1), f2(-1), f3(-1) {
    this->area = area;
    cotanAngle[0] = angle1;
    cotanAngle[1] = angle2;
    cotanAngle[2] = angle3;
}

Face::Face(int s1, int s2, int s3, Mesh& mesh) {
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    f1 = -1;
    f2 = -1;
    f3 = -1;
    
    Sommet sommet1 = mesh.getSommet(s1);
    Sommet sommet2 = mesh.getSommet(s2);
    Sommet sommet3 = mesh.getSommet(s3);

    // Compute area
    Sommet v1 = sommet2 - sommet1;
    Sommet v2 = sommet3 - sommet1;
    this->area = (v1 * v2).norm() / 2;

    // Compute cotan angles
    v1 = sommet2 - sommet1;
    v2 = sommet3 - sommet1;
    double angle = v1.computeAngle(v2);
    this->cotanAngle[0] = 1 / tan(angle);

    v1 = sommet1 - sommet2;
    v2 = sommet3 - sommet2;
    angle = v1.computeAngle(v2);
    this->cotanAngle[1] = 1 / tan(angle);

    v1 = sommet2 - sommet3;
    v2 = sommet1 - sommet3;
    angle = v1.computeAngle(v2);
    this->cotanAngle[2] = 1 / tan(angle);
    
};

void Face::setSommets(int s1, int s2, int s3) {
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
}

array<int, 3> Face::getSommets() const {
    return {s1, s2, s3};
}

void Face::addAdjacentFace(int f) {
    if (f1 == -1) {
        f1 = f;
    } else if (f2 == -1) {
        f2 = f;
    } else if (f3 == -1) {
        f3 = f;
    }
}

void Face::replaceAdjacentFace(int newF, int oldF) {
    if (f1 == oldF) {
        f1 = newF;
    } else if (f2 == oldF) {
        f2 = newF;
    } else if (f3 == oldF) {
        f3 = newF;
    }
}

array<int, 3> Face::getAdjacentFaces() const {
    return {f1, f2, f3};
}

void Face::print() {
    cout << "Sommets: " << s1 << " " << s2 << " " << s3 << endl;
    cout << "Faces: " << f1 << " " << f2 << " " << f3 << endl;
    cout << "Angle: " << cotanAngle[0] << " " << cotanAngle[1] << " " << cotanAngle[2] << endl;
    cout << "Area: " << area << endl;
}

double Face::getArea() const {
    return area;
};

double Face::getCotanAngle(int i) const {
    return cotanAngle[i];
};

bool Face::hasSommet(int s) const {
    return s1 == s || s2 == s || s3 == s;
}

int Face::getNextSommet(int s) const {
    if (s1 == s) {
        return s2;
    } else if (s2 == s) {
        return s3;
    } else {
        return s1;
    }
}

Sommet Face::getBarycenter(Mesh& mesh) {
    Sommet sommet0 = mesh.getSommet(s1);
    Sommet sommet1 = mesh.getSommet(s2);
    Sommet sommet2 = mesh.getSommet(s3);

    Sommet tempS1 = sommet2 * 1/2 * (1/cotanAngle[0] + 1/cotanAngle[1]);
    Sommet tempS2 = sommet0 * 1/2 * (1/cotanAngle[1] + 1/cotanAngle[2]);
    Sommet tempS3 = sommet1 * 1/2 * (1/cotanAngle[2] + 1/cotanAngle[0]);

    return tempS1 + tempS2 + tempS3;
}

void Face::computeAngleAndArea(Mesh& mesh) {

    Sommet sommet1 = mesh.getSommet(s1);
    Sommet sommet2 = mesh.getSommet(s2);
    Sommet sommet3 = mesh.getSommet(s3);

    // Compute area
    Sommet v1 = sommet2 - sommet1;
    Sommet v2 = sommet3 - sommet1;
    this->area = (v1 * v2).norm() / 2;

    // Compute cotan angles
    v1 = sommet2 - sommet1;
    v2 = sommet3 - sommet1;
    double angle = v1.computeAngle(v2);
    this->cotanAngle[0] = 1 / tan(angle);

    v1 = sommet1 - sommet2;
    v2 = sommet3 - sommet2;
    angle = v1.computeAngle(v2);
    this->cotanAngle[1] = 1 / tan(angle);

    v1 = sommet2 - sommet3;
    v2 = sommet1 - sommet3;
    angle = v1.computeAngle(v2);
    this->cotanAngle[2] = 1 / tan(angle);
}