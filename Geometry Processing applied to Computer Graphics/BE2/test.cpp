#include <iostream>
#include <string>
#include <sstream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"
#include "iterator.h"
#include "circulator.h"


int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2v2\\octahedron.off");
    m.print();

    Circulator_on_faces circ = Circulator_on_faces(m, 0);
    int firstFace = *circ;
    cout << *circ << endl;
    ++circ;
    while (*circ != firstFace) {
        cout << *circ << endl;
        ++circ;
    }


    

    return 0;
}