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
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon.off");
    m.splitFace(-0.5, -0.5, 0, 5);
    // m.print();
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_splitFace.off", false, true);

    Mesh m2 = Mesh();
    m2 = m2.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon.off");
    m2.flipEdge(0, 1);
    // m2.print();
    m2.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_flipEdge.off", false, true);

    Mesh m3 = Mesh();
    m3 = m3.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon.off");
    m3.splitEdge(4, 5, -0.3, -0.3, 0);
    // m3.print();
    m3.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_splitEdge.off", false, true);
}