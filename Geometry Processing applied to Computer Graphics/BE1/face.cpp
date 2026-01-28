#include <iostream>
#include <array>
using namespace std;

class Face {
    public:
        Face();
        Face(int s1, int s2, int s3);
        void setSommets(int s1, int s2, int s3);
        array<int, 3> getSommets();
        void addAdjacentFace(int f);
        array<int, 3> getAdjacentFaces();
        void print();
        
    private:
        int s1;
        int s2;
        int s3;
        int f1;
        int f2;
        int f3;
};

Face::Face() : s1(-1), s2(-1), s3(-1), f1(-1), f2(-1), f3(-1) {}

Face::Face(int s1, int s2, int s3) : s1(s1), s2(s2), s3(s3), f1(-1), f2(-1), f3(-1) {}

void Face::setSommets(int s1, int s2, int s3) {
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
}

array<int, 3> Face::getSommets() {
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

array<int, 3> Face::getAdjacentFaces() {
    return {f1, f2, f3};
}

void Face::print() {
    cout << "Sommets: " << s1 << " " << s2 << " " << s3 << endl;
    cout << "Faces: " << f1 << " " << f2 << " " << f3 << endl;
}