#include <iostream>
#include "mesh.cpp"

using namespace std;

int main() {
    Mesh m = Mesh();
    m = m.InitFromFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE1\\queen.off");
    cout << endl << "========" << endl;
    cout << "Mesh: " << endl;
    //m.print();
    m.SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE1\\test.off");
    return 0;
}