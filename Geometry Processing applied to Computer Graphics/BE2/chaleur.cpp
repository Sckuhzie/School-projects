#include <iostream>
#include <string>
#include <sstream>
#include "mesh.h"
#include "utils.cpp"

#include "mesh.cpp"
#include "sommet.cpp"
#include "face.cpp"

using namespace std;


int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\queen.off");

    double temperature = 50;
    m.getSommet(2).setValue(temperature);

    cout << endl << "========" << endl;
    for (int i = 0; i<100000; i++) {
        cout << "ITERATION : "<< i << endl;
        iterationEquationChaleur(m, 0.000001, temperature, 2);
        
        // std::ostringstream oss;
        // oss << "C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\test_chaleur_" << i << ".off";
        // m.SaveToFile(oss.str());
    }

    // m.print();
    // m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE2\\test_chaleur.off");
    return 0;
}