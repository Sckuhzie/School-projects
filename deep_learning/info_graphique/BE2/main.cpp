#include <iostream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"

using namespace std;

int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\octahedron.off");
    cout << endl << "========" << endl;
    cout << "Mesh: " << endl;
    // m.print();
    cout << "========" << endl;
    cout << "Adjacent Faces: " << endl;
    vector<int> adjFace = getAdjacentFace(2, m);
    for (int i = 0; i < adjFace.size(); i++) {
        cout << adjFace[i] << " ";
    }
    cout << endl;

    // for (int i=0; i < 6; i++) {
    //     cout << "Face " << i << " area: " << computeAreaFace(i, m) << endl;
    //     m.getSommet(i).setValue(1.897*i);
    // }
    m.getSommet(0).setValue(50);

    for (int i=0; i < 6; i++) {
        cout << endl << "Sommet " << i << " value: " << m.getSommet(i).getValue() << endl;
        double lap = computeLaplacian(i, m);
        cout  << "Laplacian Final : " << lap << endl;
    }

    cout << endl << "========" << endl;
    // m.print();

    // m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\test.off");
    return 0;
}