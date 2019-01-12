#pragma once
#ifndef TOR_H
#define TOR_H

#include <windows.h>
#include <directxmath.h>

using namespace DirectX;

struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT3 Normal;
};

class Tor {

public:

    Tor(float r, float R);

    SimpleVertex * getVertices();
    WORD *         getIndices();

    SimpleVertex * getOutlineVertices();
    WORD *         getOutlineIndices();

    int            getVerticesNumber();
    int            getIndicesNumber();

    ~Tor() = default;

private:

    void initVertices();
    void initIndices();

    static const int pointsInCircle = 40;
    static const int circlesNumber  = 40;
    static const int verticesNumber = pointsInCircle * circlesNumber;
    static const int indicesNumber  = verticesNumber * 6;

    float R;
    float r;

    SimpleVertex outlineVerticesBuffer[verticesNumber];
    SimpleVertex verticesBuffer[verticesNumber];
    WORD         indicesBuffer[indicesNumber];
};

#endif
