#ifndef __PONTO_H__
#define __PONTO_H__

#include "gl_canvas2d.h"
#include <vector>

class Ponto{
public:
    float x, y;

    Ponto() : x(0), y(0) {}
    Ponto(float _x, float _y) : x(_x), y(_y) {}

    void set(float _x, float _y) {
        x = _x;
        y = _y;
    }

    Ponto distancia(Ponto p) {
        float dist = sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
        return Ponto(dist, dist);
    }

    Ponto operator - (const Ponto& v) const {
        return Ponto(x - v.x, y - v.y);
    }

    Ponto operator + (const Ponto& v) const {
        return Ponto(x + v.x, y + v.y);
    }

};

#endif
