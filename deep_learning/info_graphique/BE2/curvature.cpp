#include <iostream>

#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"

int main() {


    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\queen.off");

    for (int i = 0; i<m.getSommets().size(); i++) {
        if (i%1000 == 0) {
            std::cout << i <<std::endl;
        }
        double curvatureValue = curvature(m, i);
        m.getSommet(i).setValue(curvatureValue);
    }

    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\curvature.off");

    return 0;
}