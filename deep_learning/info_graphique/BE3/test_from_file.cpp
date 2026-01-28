#include <iostream>
#include <string>
#include <sstream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"

int main() {
    Mesh m = Mesh();
    m = m.initFromPoints("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\noise_poisson.txt");
    bool delaunay = m.isDelaunay();
    std::cout << "Is Delaunay : " << delaunay << std::endl;
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_from_file.off", false, true);

    return 0;
}