#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>

#include "sommet.h"
#include "face.h"
#include "mesh.h"

using namespace std;


Mesh::Mesh() : sommets(), faces() {}

Mesh::Mesh(std::vector<Sommet> sommets, std::vector<Face> Faces) : sommets(sommets), faces(Faces) {}

void Mesh::print() {
    cout << "Nb de sommets : " << sommets.size() << endl;
    for (int i = 0; i < sommets.size(); i++) {
        cout << endl << "Sommet " << i << endl;
        sommets[i].print();
    }
    cout << "Nb de faces : " << faces.size() << endl;
    for (int i = 0; i < faces.size(); i++) {
        cout << endl << "Face " << i << endl;
        faces[i].print();
    }
}

Mesh Mesh::InitFromFile(std::string filename) {
    ifstream file(filename);
    string line;
    file >> line; // Read OFF header
    cout << line << endl;

    int num_vertices, num_faces, num_edges;
    file >> num_vertices >> num_faces >> num_edges;
    cout << "Number of vertices: " << num_vertices << endl;
    cout << "Number of faces: " << num_faces << endl;
    cout << "Number of edges: " << num_edges << endl;

    for (int i = 0; i<num_vertices; i++) {
        double x, y, z;
        file >> x >> y >> z;
        sommets.push_back(Sommet(x, y, z));
    }

    std::vector<Face> faces;
    std::map<pair<int, int>, int> edges;
    bool ret;
    int j;
    double area;
    double angle1, angle2, angle3;
    Sommet sommet1, sommet2, sommet3;
    for (int i=0; i<num_faces; i++) {
        int num_vertices_face, vertex_1_index, vertex_2_index, vertex_3_index;
        file >> num_vertices_face >> vertex_1_index >> vertex_2_index >> vertex_3_index;
        sommet1 = sommets[vertex_1_index];
        sommet2 = sommets[vertex_2_index];
        sommet3 = sommets[vertex_3_index];
        faces.push_back(Face(vertex_1_index, vertex_2_index, vertex_3_index, *this));

        if (sommets[vertex_1_index].getFace() == -1) {
            sommets[vertex_1_index].setFace(i);
        }
        if (sommets[vertex_2_index].getFace() == -1) {
            sommets[vertex_2_index].setFace(i);
        }
        if (sommets[vertex_3_index].getFace() == -1) {
            sommets[vertex_3_index].setFace(i);
        }

        if (sommets[vertex_2_index] < sommets[vertex_1_index]) std::swap(vertex_1_index, vertex_2_index);
        if (sommets[vertex_3_index] < sommets[vertex_1_index]) std::swap(vertex_1_index, vertex_3_index);
        if (sommets[vertex_3_index] < sommets[vertex_2_index]) std::swap(vertex_2_index, vertex_3_index);
        
        pair<int, int> edge1 = make_pair(vertex_1_index, vertex_2_index);
        pair<int, int> edge2 = make_pair(vertex_2_index, vertex_3_index);
        pair<int, int> edge3 = make_pair(vertex_1_index, vertex_3_index);

        ret = edges.insert(make_pair(edge1, i)).second;
        if (!ret) {
            j = edges[edge1];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }

        ret = edges.insert(make_pair(edge2, i)).second;
        if (!ret) {
            j = edges[edge2];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }
        
        ret = edges.insert(make_pair(edge3, i)).second;
        if (!ret) {
            j = edges[edge3];
            faces[i].addAdjacentFace(j);
            faces[j].addAdjacentFace(i);
        }
    }
    return Mesh(sommets, faces);
}

void Mesh::SaveToFile(std::string filename, bool ColorVertex, bool ColorFace) {
    ofstream file(filename);
    file << "OFF" << endl;
    file << sommets.size() << " " << faces.size() << " 0" << endl;

    std::vector<double> values;
    for (int i = 0; i < sommets.size(); i++) {
        values.push_back(sommets[i].getValue());
    }
    double minValue = *min_element(values.begin(), values.end());
    double maxValue = *max_element(values.begin(), values.end());

    for (int i = 0; i < sommets.size(); i++) {
        double x = sommets[i].getCoords()[0];
        double y = sommets[i].getCoords()[1];
        double z = sommets[i].getCoords()[2];
        double value = values[i];
        int colorR = (value-minValue) / (maxValue-minValue) * 255;
        int colorG = 0;
        int colorB = 0;
        if (ColorVertex) {
            file << x << " " << y << " " << z << " " << colorR << " " << colorG << " " << colorB << endl;
        } else {
            file << x << " " << y << " " << z << endl;
        }
    }
    
    int colorR, colorG, colorB;

    for (int i = 0; i < faces.size(); i++) {
        int s1 = faces[i].getSommets()[0];
        int s2 = faces[i].getSommets()[1];
        int s3 = faces[i].getSommets()[2];
        if (ColorFace) {
            colorR = rand() % 256;
            colorG = rand() % 256;
            colorB = rand() % 256;
            file << "3 " << s1 << " " << s2 << " " << s3 << " " << colorR << " " << colorG << " " << colorB << endl;
        } else {
            file << "3 " << s1 << " " << s2 << " " << s3 << endl;
        }
    }
    file.close();
}

double Mesh::computeCotanAngle(Sommet sommetMain, Sommet sommet1, Sommet sommet2) {
    Sommet v1 = sommet1 - sommetMain;
    Sommet v2 = sommet2 - sommetMain;

    double angle = v1.computeAngle(v2);
    return 1 / tan(angle);
}

double Mesh::computeAreaFromSommet(Sommet sommet1, Sommet sommet2, Sommet sommet3) {
    Sommet v1 = sommet2 - sommet1;
    Sommet v2 = sommet3 - sommet1;
    return (v1 * v2).norm() / 2;
}

void Mesh::splitFace(double s1, double s2, double s3, int faceIndex) {

    Face face = faces[faceIndex];
    std::array<int, 3> faceSommets = face.getSommets();
    std::array<int, 3> adjacentFaces = face.getAdjacentFaces();

    Sommet sommet = Sommet(s1, s2, s3);
    sommet.setFace(faceIndex);
    this->sommets.push_back(sommet);

    // create the 3 new faces
    Face newFace1 = Face(faceSommets[0], faceSommets[1], sommets.size()-1);
    Face newFace2 = Face(faceSommets[1], faceSommets[2], sommets.size()-1);
    Face newFace3 = Face(faceSommets[2], faceSommets[0], sommets.size()-1);

    int adjacentFace1 = -1;
    int adjacentFace2 = -1;
    int adjacentFace3 = -1;

    for (int i = 0; i< 3; i++) {
        if (adjacentFaces[i] == -1) {
            continue;
        }

        array<int, 3> adjacentFaceSommets = faces[adjacentFaces[i]].getSommets();
        if ((adjacentFaceSommets[1] == faceSommets[0] && adjacentFaceSommets[0] == faceSommets[1]) ||
            (adjacentFaceSommets[2] == faceSommets[0] && adjacentFaceSommets[1] == faceSommets[1]) ||
            (adjacentFaceSommets[0] == faceSommets[0] && adjacentFaceSommets[2] == faceSommets[1])) {
            adjacentFace1 = adjacentFaces[i];
        } else if ((adjacentFaceSommets[1] == faceSommets[1] && adjacentFaceSommets[0] == faceSommets[2]) ||
                   (adjacentFaceSommets[2] == faceSommets[1] && adjacentFaceSommets[1] == faceSommets[2]) ||
                   (adjacentFaceSommets[0] == faceSommets[1] && adjacentFaceSommets[2] == faceSommets[2])) {
            adjacentFace2 = adjacentFaces[i];
        } else if ((adjacentFaceSommets[1] == faceSommets[2] && adjacentFaceSommets[0] == faceSommets[0]) ||
                   (adjacentFaceSommets[2] == faceSommets[2] && adjacentFaceSommets[1] == faceSommets[0]) ||
                   (adjacentFaceSommets[0] == faceSommets[2] && adjacentFaceSommets[2] == faceSommets[0])) {
            adjacentFace3 = adjacentFaces[i];
        }
    }


    // add the adjacent faces of the new faces
    newFace1.addAdjacentFace(adjacentFace1);
    newFace1.addAdjacentFace(faces.size());
    newFace1.addAdjacentFace(faces.size()+1);

    newFace2.addAdjacentFace(adjacentFace2);
    newFace2.addAdjacentFace(faceIndex);
    newFace2.addAdjacentFace(faces.size()+1);

    newFace3.addAdjacentFace(adjacentFace3);
    newFace3.addAdjacentFace(faceIndex);
    newFace3.addAdjacentFace(faces.size());

    // update the adjacent faces of the old faces
    for (int i = 0; i < 3; i++) {
        array<int, 3> sommetCurrentFace = faces[adjacentFaces[i]].getSommets();
        // check which edge is common with the current face
        if (sommetCurrentFace[0] == faceSommets[2] || sommetCurrentFace[1] == faceSommets[2] || sommetCurrentFace[2] == faceSommets[2]) {
            if (sommetCurrentFace[0] == faceSommets[1] || sommetCurrentFace[1] == faceSommets[1] || sommetCurrentFace[2] == faceSommets[1]) {
                faces[adjacentFaces[i]].replaceAdjacentFace(faces.size(), faceIndex);
            } else {
                faces[adjacentFaces[i]].replaceAdjacentFace(faces.size()+1, faceIndex);
            }
        }
    }

    // update the faces
    faces[faceIndex] = newFace1;
    faces.push_back(newFace2);
    faces.push_back(newFace3);

    // update the sommet
    if (sommets[faceSommets[2]].getFace() == faceIndex) {
        sommets[faceSommets[2]].setFace(sommets.size()-1);
    }
}

void Mesh::flipEdge(int face1, int face2) {

    // case if one the faces is the infinite face
    if (face1 == -1 || face2 == -1) {
        return;
    }

    std::array<int, 4> points = getPointsFrom2Faces(face1, face2);
    int commonSommet1 = points[0];
    int commonSommet2 = points[1];
    int newSommet1 = points[2];
    int newSommet2 = points[3];

    std::array<int, 3> face1AdjacentFaces = faces[face1].getAdjacentFaces();
    std::array<int, 3> face2AdjacentFaces = faces[face2].getAdjacentFaces();

    // update the sommet of the new faces

    faces[face1].setSommets(commonSommet1, newSommet2, newSommet1);
    faces[face2].setSommets(commonSommet2, newSommet1, newSommet2);

    // update the old sommet
    if (sommets[commonSommet1].getFace() == face2) {
        sommets[commonSommet1].setFace(face1);
    }
    if (sommets[commonSommet2].getFace() == face1) {
        sommets[commonSommet2].setFace(face2);
    }

    // update the adjacent faces
    int face1update = -1;
    int face2update = -1;
    array<int, 3> adjacentFaceSommets;
    for (int i = 0; i < 3; i++) {
        adjacentFaceSommets = faces[face1AdjacentFaces[i]].getSommets();
        if ((adjacentFaceSommets[0] == newSommet1 && adjacentFaceSommets[1] == commonSommet2) ||
            (adjacentFaceSommets[1] == newSommet1 && adjacentFaceSommets[2] == commonSommet2) ||
            (adjacentFaceSommets[2] == newSommet1 && adjacentFaceSommets[0] == commonSommet2) 
            ) 
            {
            faces[face1AdjacentFaces[i]].replaceAdjacentFace(face2, face1);
            face1update = face1AdjacentFaces[i];
        }
        adjacentFaceSommets = faces[face2AdjacentFaces[i]].getSommets();
        if ((adjacentFaceSommets[0] == newSommet2 && adjacentFaceSommets[1] == commonSommet1) ||
            (adjacentFaceSommets[1] == newSommet2 && adjacentFaceSommets[2] == commonSommet1) ||
            (adjacentFaceSommets[2] == newSommet2 && adjacentFaceSommets[0] == commonSommet1) 
            ) 
            {
            faces[face2AdjacentFaces[i]].replaceAdjacentFace(face1, face2);
            face2update = face2AdjacentFaces[i];
        }
    }
    faces[face1].replaceAdjacentFace(face2update, face1update);
    faces[face2].replaceAdjacentFace(face1update, face2update);
}

void Mesh::splitEdge(int face1, int face2, double s1, double s2, double s3) {
    // chech if the faces are adjacent
    std::array<int, 4> points = getPointsFrom2Faces(face1, face2);
    int commonSommet1 = points[0];
    int commonSommet2 = points[1];
    int otherSommet1 = points[2];
    int otherSommet2 = points[3];

    std::array<int, 3> face1AdjacentFaces = faces[face1].getAdjacentFaces();
    std::array<int, 3> face2AdjacentFaces = faces[face2].getAdjacentFaces();

    // Creation of the new sommet
    Sommet newSommetobject = Sommet(s1, s2, s3);
    newSommetobject.setFace(face1);
    this->sommets.push_back(newSommetobject);
    int newSommet = sommets.size() - 1;

    // update the sommet of the old faces and create new faces
    faces[face1].setSommets(newSommet, commonSommet2, otherSommet1);
    faces[face2].setSommets(newSommet, otherSommet2, commonSommet2);
    Face newFace1Object = Face(newSommet, otherSommet1, commonSommet1);
    Face newFace2Object = Face(newSommet, commonSommet1, otherSommet2);
    // this->faces.push_back(newFace1Object);
    int newFace1 = faces.size();
    // this->faces.push_back(newFace2Object);
    int newFace2 = faces.size() + 1;

    // update the old sommet
    if (sommets[commonSommet1].getFace() == face1 || sommets[commonSommet1].getFace() == face2) {
        sommets[commonSommet1].setFace(newFace1);
    }

    // update the adjacent faces
    newFace1Object.addAdjacentFace(face1);
    newFace1Object.addAdjacentFace(newFace2);
    newFace2Object.addAdjacentFace(face2);
    newFace2Object.addAdjacentFace(newFace1);


    array<int, 3> adjacentFaceSommets;
    for (int i = 0; i < 3; i++) {
        adjacentFaceSommets = faces[face1AdjacentFaces[i]].getSommets();
        if ((adjacentFaceSommets[0] == commonSommet1 && adjacentFaceSommets[1] == otherSommet2) ||
            (adjacentFaceSommets[1] == commonSommet1 && adjacentFaceSommets[2] == otherSommet2) ||
            (adjacentFaceSommets[2] == commonSommet1 && adjacentFaceSommets[0] == otherSommet2) 
            ) 
            {
            faces[face1AdjacentFaces[i]].replaceAdjacentFace(newFace1, face1);
            faces[face1].replaceAdjacentFace(newFace1, face1AdjacentFaces[i]);
            newFace1Object.addAdjacentFace(face1AdjacentFaces[i]);
        }
        adjacentFaceSommets = faces[face2AdjacentFaces[i]].getSommets();
        if ((adjacentFaceSommets[0] == otherSommet2 && adjacentFaceSommets[1] == commonSommet1) ||
            (adjacentFaceSommets[1] == otherSommet2 && adjacentFaceSommets[2] == commonSommet1) ||
            (adjacentFaceSommets[2] == otherSommet2 && adjacentFaceSommets[0] == commonSommet1) 
            ) 
            {
            faces[face2AdjacentFaces[i]].replaceAdjacentFace(newFace2, face2);
            faces[face2].replaceAdjacentFace(newFace2, face2AdjacentFaces[i]);
            newFace2Object.addAdjacentFace(face2AdjacentFaces[i]);
        }
    }

    faces.push_back(newFace1Object);
    faces.push_back(newFace2Object);
}

bool orientationTest(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0;
}

bool Mesh::orientationTest(int point1, int point2, int point3) {
    double x1 = sommets[point1].getCoords()[0];
    double y1 = sommets[point1].getCoords()[1];
    double x2 = sommets[point2].getCoords()[0];
    double y2 = sommets[point2].getCoords()[1];
    double x3 = sommets[point3].getCoords()[0];
    double y3 = sommets[point3].getCoords()[1];
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0;
}

bool testInsideTriangle2D(Mesh mesh, int face, double x, double y) {
    array<int, 3> sommets = mesh.getFace(face).getSommets();
    array<double, 3> coords1 = mesh.getSommet(sommets[0]).getCoords();
    array<double, 3> coords2 = mesh.getSommet(sommets[1]).getCoords();
    array<double, 3> coords3 = mesh.getSommet(sommets[2]).getCoords();
    return orientationTest(coords1[0], coords1[1], coords2[0], coords2[1], x, y) && orientationTest(coords2[0], coords2[1], coords3[0], coords3[1], x, y) && orientationTest(coords3[0], coords3[1], coords1[0], coords1[1], x, y);
}

void Mesh::insertion2D(double s1, double s2, double s3) {
    // Case point inside the mesh
    for (int i = 0; i < faces.size(); i++) {
        if (testInsideTriangle2D(*this, i, s1, s2)) {
            splitFace(s1, s2, s3, i);
            return;
        }
    }
    // Case point outside the mesh
    cout << "Point is not inside the mesh" << endl;
    addPointOutsideMesh(s1, s2, s3);   
}

void Mesh::addPointOutsideMesh(double s1, double s2, double s3) {
    // Find the closest edge to the point
    double minDistance = std::numeric_limits<double>::max();
    int closestFace = -1;
    int closestEdgeStart = -1;
    int closestEdgeEnd = -1;

    for (int i = 0; i < faces.size(); i++) {
        array<int, 3> sommetsFace = faces[i].getSommets();
        for (int j = 0; j < 3; j++) {
            int start = sommetsFace[j];
            int end = sommetsFace[(j + 1) % 3];
            double x1 = sommets[start].getCoords()[0];
            double y1 = sommets[start].getCoords()[1];
            double x2 = sommets[end].getCoords()[0];
            double y2 = sommets[end].getCoords()[1];

            // Compute distance from point to edge
            double middle_edge_x = (x1 + x2) / 2;
            double middle_edge_y = (y1 + y2) / 2;
            double distance_s = pow(middle_edge_x - s1, 2) + pow(middle_edge_y - s2, 2);
       
            if (distance_s < minDistance) {
                minDistance = distance_s;
                closestFace = i;
                closestEdgeStart = start;
                closestEdgeEnd = end;
            }
        }
    }

    std::cout << "Closest edge: " << closestEdgeStart << " " << closestEdgeEnd << std::endl;

    // Add the new point and create new faces
    Sommet newSommet(s1, s2, s3);
    sommets.push_back(newSommet);
    int newSommetIndex = sommets.size() - 1;

    if (!orientationTest(newSommetIndex, closestEdgeStart, closestEdgeEnd)) {
        std::swap(closestEdgeStart, closestEdgeEnd);
    }

    Face newFace(newSommetIndex, closestEdgeStart, closestEdgeEnd);

    newFace.addAdjacentFace(closestFace);
    faces[closestFace].addAdjacentFace(faces.size());
    faces.push_back(newFace);
    makeConvexShape(newSommetIndex, closestEdgeStart, closestFace, faces.size()-1, true);
    makeConvexShape(newSommetIndex, closestEdgeEnd, closestFace, faces.size()-1, false);
}

void Mesh::makeConvexShape(int newSommet, int sommet1, int closestFace, int newFace, bool right) {
    // Get the face adjacent to the closestFace
    array<int, 3> adjacentFaces = faces[closestFace].getAdjacentFaces();
    for (int i = 0; i < 3; i++) {
        if (std::find(faces[adjacentFaces[i]].getSommets().begin(), faces[adjacentFaces[i]].getSommets().end(), sommet1) != faces[adjacentFaces[i]].getSommets().end()) {
            int otherFace = adjacentFaces[i];
            std::array<int, 4> points = getPointsFrom2Faces(closestFace, otherFace);
            int point3 = points[3];

            if(right) {
                if (orientationTest(newSommet, point3, sommet1)) {
                    std::cout << "Convex shape : " << newSommet << " " << sommet1 << " " << point3 << std::endl; 
                    // If the newSommet is on the left of the edge, flip the edge
                    Face newFace1 = Face(newSommet, sommet1, point3);
                    newFace1.addAdjacentFace(newFace);
                    newFace1.addAdjacentFace(otherFace);
                    faces.push_back(newFace1);
                    
                    faces[otherFace].addAdjacentFace(faces.size()-1);
                    faces[newFace].addAdjacentFace(faces.size()-1);

                    makeConvexShape(newSommet, point3, otherFace, faces.size()-1, right);
                } 
            } else {
                if (orientationTest(newSommet, sommet1, point3)) {
                    std::cout << "Convex shape : " << newSommet << " " << sommet1 << " " << point3 << std::endl; 
                    // If the newSommet is on the left of the edge, flip the edge
                    Face newFace1 = Face(newSommet, sommet1, point3);
                    newFace1.addAdjacentFace(newFace);
                    newFace1.addAdjacentFace(otherFace);
                    faces.push_back(newFace1);
                    
                    faces[otherFace].addAdjacentFace(faces.size()-1);
                    faces[newFace].addAdjacentFace(faces.size()-1);

                    makeConvexShape(newSommet, point3, otherFace, faces.size()-1, right);
                }
            }
        }
    }

}

Sommet projector(Sommet s) {
    double x = s.x;
    double y = s.y;
    double z = x*x + y*y;
    return Sommet(x, y, z);
}

bool Mesh::isEdgeLocalDelaunay(int face1, int face2) {

    // Get the two other sommets of the faces
    array<int, 4> points = getPointsFrom2Faces(face1, face2);
    if (points[0] == -1) {
        return true;
    }
    Sommet commonSommet1 = sommets[points[0]];
    Sommet commonSommet2 = sommets[points[1]];
    Sommet otherSommet1 = sommets[points[2]];
    Sommet otherSommet2 = sommets[points[3]];


    // Project the points
    Sommet p = projector(commonSommet1);
    Sommet q = projector(commonSommet2);
    Sommet r = projector(otherSommet1);
    Sommet s = projector(otherSommet2);

    double test = -((q-p)*(r-p)).dot(s-p);
    double test2 = -((p-q)*(s-q)).dot(r-q);
    return test < 0 && test2 < 0;
};

bool Mesh::isDelaunay() {
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < faces[i].getAdjacentFaces().size(); j++) {
            if (!isEdgeLocalDelaunay(i, faces[i].getAdjacentFaces()[j])) {
                return false;
            }
        }
    }
    return true;
}

std::array<int, 4> Mesh::getPointsFrom2Faces(int face1, int face2) {
    // Get the common edge between to faces
    // If one face is the infinite face, return {-1, -1, -1, -1}
    // If the faces are the same or the face are not adjacent, trigger an error
    // Return 4 points : commonSommet1, commonSommet2, otherSommet1, otherSommet2
    // commonSommet1, commonSommet2 and otherSommet1 are the points of the first face, in counterclockwise order
    // commonSommet2, commonSommet1 and otherSommet2 are the points of the second face, in counterclockwise order

    if (face1 == face2) {
        cout << "Faces are the same" << endl;
        throw std::invalid_argument("Faces are the same");
    }
    if (face1 == -1 || face2 == -1) {
        return {-1, -1, -1, -1};
    }

    array<int, 3> face1AdjacentFaces = faces[face1].getAdjacentFaces();
    array<int, 3> face2AdjacentFaces = faces[face2].getAdjacentFaces();

    bool isAdjacent1 = false;
    bool isAdjacent2 = false;

    for (int i = 0; i < 3; i++) {
        if (face1AdjacentFaces[i] == face2) {
            isAdjacent1 = true;
        }
        if (face2AdjacentFaces[i] == face1) {
            isAdjacent2 = true;
        }
    }
    if (!isAdjacent1 || !isAdjacent2) {
        cout << "Faces are not adjacent" << endl;
        print();
        throw std::invalid_argument("Faces are not adjacent");
    }

    // Get the common edge
    array<int, 3> face1Sommets = faces[face1].getSommets();
    array<int, 3> face2Sommets = faces[face2].getSommets();

    int commonSommet1 = -1;
    int commonSommet2 = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (face1Sommets[i] == face2Sommets[j]) {
                if (commonSommet1 == -1) {
                    commonSommet1 = face1Sommets[i];
                } else {
                    commonSommet2 = face1Sommets[i];
                }
            }
        }
    }

    int otherSommet1 = -1;
    int otherSommet2 = -1;
    for (int i = 0; i < 3; i++) {
        if (face1Sommets[i] != commonSommet1 && face1Sommets[i] != commonSommet2) {
            otherSommet1 = face1Sommets[i];
        }
        if (face2Sommets[i] != commonSommet1 && face2Sommets[i] != commonSommet2) {
            otherSommet2 = face2Sommets[i];
        }
    }

    if (orientationTest(commonSommet1, commonSommet2, otherSommet1)) {
        return {commonSommet1, commonSommet2, otherSommet1, otherSommet2};
    } else {
        return {commonSommet2, commonSommet1, otherSommet1, otherSommet2};
    }
}

void Mesh::LawsonAlgorithm() {
    while (!isDelaunay()) {
        updateDelaunay();
    }
}

void Mesh::updateDelaunay() {
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < faces[i].getAdjacentFaces().size(); j++) {
            if (!isEdgeLocalDelaunay(i, faces[i].getAdjacentFaces()[j])) {
                flipEdge(i, faces[i].getAdjacentFaces()[j]);
            }
        }
    }
}

void Mesh::initMeshBoundingBox(std::string filename) {
    ifstream file(filename);
    string line;
    int num_points;
    file >> num_points;
    cout << "Number of points : " << num_points << endl;
    double x_min, y_min, x_max, y_max, z;
    file >> x_min >> y_min >> z;
    x_max = x_min;
    y_max = y_min;
    double x, y;
    for (int i = 1; i < num_points; i++) {
        file >> x >> y >> z;
        if (x < x_min) {
            x_min = x;
        }
        if (y < y_min) {
            y_min = y;
        }
        if (x > x_max) {
            x_max = x;
        }
        if (y > y_max) {
            y_max = y;
        }
    }
    file.close();

    // Pour eviter des triangles isocèles qui font bugger delaunay avec les cercles circonscrits
    x_min -= 1;
    y_min -= 1.1;
    x_max += 1.2; 
    y_max += 1.3;

    Sommet sommet1 = Sommet(x_min, y_min, 0);
    Sommet sommet2 = Sommet(x_max, y_min, 0);
    Sommet sommet3 = Sommet(x_min, y_max, 0);
    Sommet sommet4 = Sommet(x_max, y_max, 0);

    sommets.push_back(sommet1);
    sommets.push_back(sommet2);
    sommets.push_back(sommet3);
    sommets.push_back(sommet4);

    Face face1 = Face(0, 1, 2, *this);
    Face face2 = Face(1, 3, 2, *this);
    face1.addAdjacentFace(1);
    face2.addAdjacentFace(0);

    faces.push_back(face1);
    faces.push_back(face2);

    SaveToFile("C:\\Users\\paull\\Documents\\GitHub\\info_graphique\\BE3v2\\off_output\\test_from_file.off", false, true);
}

Mesh Mesh::initFromPoints(std::string filename) {

    initMeshBoundingBox(filename);

    ifstream file(filename);
    string line;

    int num_points;
    file >> num_points;

    double x, y, z;

    for (int i = 0; i < num_points; i++) {
        file >> x >> y >> z;
        std::cout << "Point " << i << " : " << x << " " << y << " " << z << endl;
        insertion2D(x, y, z);
        updateDelaunay();
    }
    return Mesh(sommets, faces);
}