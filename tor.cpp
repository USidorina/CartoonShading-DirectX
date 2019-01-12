#include <stdlib.h>
#include "tor.h"

void normalize(XMFLOAT3 * v) {
    float length = sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
    *v = XMFLOAT3(v->x / length, v->y / length, v->z / length);
}

Tor::Tor(float r, float R) {

    this->r = r;
    this->R = R;

    initVertices();
    initIndices();
}

SimpleVertex * Tor::getVertices() {

    return verticesBuffer; 
}

WORD * Tor::getIndices() {

    return indicesBuffer; 
}

int Tor::getVerticesNumber() {
    
    return verticesNumber; 
}

int Tor::getIndicesNumber() {
    
    return indicesNumber; 
}

void Tor::initVertices() {

    int i = 0;

    float eps = 0.07f;

    float stepPhi = XM_2PI / circlesNumber;
    float stepPsi = XM_2PI / pointsInCircle;

    for (float phi = 0; phi < XM_2PI; phi += stepPhi) {
        for (float psi = 0; psi < XM_2PI; psi += stepPsi) {
            float x = (R + r * cosf(psi)) * cosf(phi);    //right
            float y = (R + r * cosf(psi)) * sinf(phi);    //up
            float z = r * sinf(psi);                      //straight

            XMFLOAT3 vertex = XMFLOAT3(x, y, z);
            XMFLOAT3 center = XMFLOAT3(cosf(phi) * R, sinf(phi) * R, 0.f);
            XMFLOAT3 normal = XMFLOAT3(vertex.x - center.x, vertex.y - center.y, vertex.z - center.z);

            normalize(&normal);

            XMFLOAT3 outlineVertex = XMFLOAT3(x + eps * normal.x, y + eps * normal.y, z + eps * normal.z);

            verticesBuffer[i]        = { vertex, normal };
            outlineVerticesBuffer[i] = { outlineVertex, normal };
            i++;
        }
    }
}

void Tor::initIndices() {

    for (WORD i = 0; i < circlesNumber; ++i) {
        for (WORD j = 0; j < pointsInCircle; ++j) {
            WORD currentBlock               = (WORD)(6 * (pointsInCircle * i + j));
            indicesBuffer[currentBlock]     = (WORD)(pointsInCircle * i + j);
            indicesBuffer[currentBlock + 1] = (WORD)(pointsInCircle * ((i + 1) % circlesNumber) + j);
            indicesBuffer[currentBlock + 2] = (WORD)(pointsInCircle * ((i + 1) % circlesNumber) + ((j + 1) % pointsInCircle));
            indicesBuffer[currentBlock + 3] = (WORD)(pointsInCircle * i + j);
            indicesBuffer[currentBlock + 4] = (WORD)(pointsInCircle * ((i + 1) % circlesNumber) + ((j + 1) % pointsInCircle));
            indicesBuffer[currentBlock + 5] = (WORD)(pointsInCircle * i + ((j + 1) % pointsInCircle));
        }
    }
}

SimpleVertex * Tor::getOutlineVertices() {

    return outlineVerticesBuffer;
}

WORD * Tor::getOutlineIndices() {

    return indicesBuffer;
}
