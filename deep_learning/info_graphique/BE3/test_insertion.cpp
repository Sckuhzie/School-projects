#include <iostream>
#include <string>
#include <sstream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"

// Le but de ce fichier est d'illustrer un problème dans l'algorithme d'insertion de points dans un maillage 2D.
// La première insertion functionne correctement, mais la deuxième fait planter le programme.

int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon_delaunay.off");
    m.insertion2D(2,0.4,0);
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_insertion.off", false, true);

    Mesh m2 = Mesh();
    m2 = m2.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_files\\hexagon.off");
    m2.insertion2D(2,0.4,0);
    m2.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3\\off_output\\test_insertion2.off", false, true);
    return 0;
}