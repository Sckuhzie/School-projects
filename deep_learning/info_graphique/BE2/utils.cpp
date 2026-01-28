#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

#include "sommet.h"
#include "face.h"
#include "mesh.h"
#include "circulator.h"

std::vector<int> getAdjacentFace(int sommet, Mesh& mesh) {
    std::vector<int> adjacentFaces;
    Circulator_on_faces circ = Circulator_on_faces(mesh, sommet);
    int firstFace = *circ;
    adjacentFaces.push_back(firstFace);
    ++circ;
    while (*circ != firstFace) {
        adjacentFaces.push_back(*circ);
        ++circ;
    }
    return adjacentFaces;
}

double computeLaplacian(int sommet, Mesh mesh) {

    double sommetValue = mesh.getSommet(sommet).getValue();
    std::vector<int> adjacentFaces = getAdjacentFace(sommet, mesh);

    double laplacian = 0.0;
    double area = 0.0;

    double faceArea, cotanAngle1, cotanAngle2;

    for (int i=0; i<adjacentFaces.size(); i++) {

        std::array<int, 3> sommets = mesh.getFace(adjacentFaces[i]).getSommets();

        faceArea = mesh.getFace(adjacentFaces[i]).getArea();
        area += faceArea;

        for (int j=0; j<3; j++) {
            if (sommets[j] == sommet) {
                int sommet1 = sommets[(j+1)%3];
                int sommet2 = sommets[(j+2)%3];

                cotanAngle1 = mesh.getFace(adjacentFaces[i]).getCotanAngle((j+1)%3);
                cotanAngle2 = mesh.getFace(adjacentFaces[i]).getCotanAngle((j+2)%3);

                laplacian += cotanAngle1 * (mesh.getSommet(sommet1).getValue() - sommetValue);
                laplacian += cotanAngle2 * (mesh.getSommet(sommet2).getValue()- sommetValue);
            }
        }
    }
    return 3 * laplacian / (2 * area);
};

void iterationEquationChaleur(Mesh& mesh, double dt, double T, int source) {
    std::vector<Sommet> sommets = mesh.getSommets();
    std::vector<double> vector_newValues;

    for (int i=0; i<sommets.size(); i++) {
        if (i%1000 == 0) {
            std::cout << i << std::endl;
        }
        if (i == source) {
            vector_newValues.push_back(T);
        } else {
            double laplacian = computeLaplacian(i, mesh);
            double newValue = sommets[i].getValue() + dt * laplacian;

            vector_newValues.push_back(newValue);
        }
    }
    for (int i=0; i<sommets.size(); i++) {
        mesh.getSommet(i).setValue(vector_newValues[i]);
    }
}


void equationChaleur(Mesh& mesh, double dt, double T, int source, int nbIterations) {

    for (int i=0; i<mesh.getSommets().size(); i++) {
        std::vector<int> adjacentFaces = getAdjacentFace(i, mesh);
        mesh.getSommet(i).setAdjacentFaces(adjacentFaces);

        if (i%100 == 0) {
            std::cout << i << " : " << mesh.getSommet(i).getAdjacentFaces().size() <<std::endl;
        }
    }

    for (int i=0; i<nbIterations; i++) {
        iterationEquationChaleur(mesh, dt, T, source);
    }
}

std::array<double, 3> laplacianCurvature(Mesh& mesh, int sommet) {
    std::array<double, 3> sommetValues = mesh.getSommet(sommet).getCoords();
    std::vector<int> adjacentFaces = getAdjacentFace(sommet, mesh);

    std::array<double, 3> laplacian = {0.0, 0.0, 0.0};
    double area = 0.0;

    double faceArea, cotanAngle1, cotanAngle2;

    for (int i=0; i<adjacentFaces.size(); i++) {
        std::array<int, 3> sommets = mesh.getFace(adjacentFaces[i]).getSommets();
        
        faceArea = mesh.getFace(adjacentFaces[i]).getArea();
        area += faceArea;
        for (int j=0; j<3; j++) {
            if (sommets[j] == sommet) {
                int sommet1 = sommets[(j+1)%3];
                int sommet2 = sommets[(j+2)%3];
                std::array<double, 3> sommet1Values = mesh.getSommet(sommet1).getCoords();
                std::array<double, 3> sommet2Values = mesh.getSommet(sommet2).getCoords();

                cotanAngle1 = mesh.getFace(adjacentFaces[i]).getCotanAngle((j+1)%3);
                cotanAngle2 = mesh.getFace(adjacentFaces[i]).getCotanAngle((j+2)%3);

                for (int k=0; k<3; k++) {
                    laplacian[k] += cotanAngle1 * (sommet1Values[k] - sommetValues[k]);
                    laplacian[k] += cotanAngle2 * (sommet2Values[k] - sommetValues[k]);
                }
            }
        }
    }

    for (int i=0; i<3; i++) {
        laplacian[i] = 3 * laplacian[i] / (2 * area);
    }
    return laplacian;
};

double curvature(Mesh& mesh, int sommet) {

    std::array<double, 3> laplacian = laplacianCurvature(mesh, sommet);
    Sommet laplacianVector(laplacian[0], laplacian[1], laplacian[2]);

    double norm = laplacianVector.norm();
    double meanCurvature = norm / 2.0;

    return meanCurvature;
}