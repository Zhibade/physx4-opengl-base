#ifndef PHYSX4_GRID_H
#define PHYSX4_GRID_H

#include "drawable3D.h"

class Plane3D : public Drawable3D
{
public:
    Plane3D(unsigned int id);
    /* Gets the vertex data for the grid lines */
    void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) override;

private:
    const float PLANE_VERTEX_DATA[36] = {
            // Vertex             // Normals
            -2.5f, 0.0f, -2.5f, 0.0f, 1.0f, 0.0f,
            -2.5f, 0.0f, 2.5f, 0.0f, 1.0f, 0.0f,
            2.5f, 0.0f, 2.5f, 0.0f, 1.0f, 0.0f,

            2.5f, 0.0f, 2.5f, 0.0f, 1.0f, 0.0f,
            2.5f, 0.0f, -2.5f, 0.0f, 1.0f, 0.0f,
            -2.5f, 0.0f, -2.5f, 0.0f, 1.0f, 0.0f
    };
};


#endif //PHYSX4_GRID_H
