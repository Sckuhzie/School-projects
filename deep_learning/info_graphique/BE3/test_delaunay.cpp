#include <iostream>
#include <string>
#include <sstream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"


int main() {
    Mesh m2 = Mesh();
    m2 = m2.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon.off");
    m2.LawsonAlgorithm();
    bool delaunay = m2.isDelaunay();
    std::cout << "Is Delaunay : " << delaunay << std::endl;
    m2.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_hexagon.off", false, true);

    return 0;
}