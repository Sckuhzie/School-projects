#include <iostream>
#include <array>

#include "mesh.h"

class Circulator_on_faces {
    public:
        Circulator_on_faces(Mesh& mesh, int vertexIndex)
            : mesh(mesh), vertexIndex(vertexIndex), currentFaceIndex(-1) {
            currentFaceIndex = mesh.getSommet(vertexIndex).getFace();
            otherVertexIndex = mesh.getFace(currentFaceIndex).getNextSommet(vertexIndex);
        }
    
        Circulator_on_faces& operator++() {
            if (currentFaceIndex == -1) return *this;
    
            // Find the next incident face
            Face currentFace = mesh.getFace(currentFaceIndex);
            int nextVertexIndex = currentFace.getNextSommet(otherVertexIndex);
            std::array<int, 3> adjacentFaces = currentFace.getAdjacentFaces();
            for (int i = 0; i < 3; ++i) {
                if (adjacentFaces[i] != -1
                    && mesh.getFace(adjacentFaces[i]).hasSommet(nextVertexIndex)
                    && mesh.getFace(adjacentFaces[i]).hasSommet(vertexIndex)) 
                    {
                    currentFaceIndex = adjacentFaces[i];
                    otherVertexIndex = nextVertexIndex;
                    break;
                }
            }
            return *this;
        }
    
        int operator*() {
            return currentFaceIndex;
        }
    
    private:
        Mesh& mesh;
        int vertexIndex;
        int currentFaceIndex;
        int otherVertexIndex;
    };