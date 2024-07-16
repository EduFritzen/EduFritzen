#ifndef CANNON_H
#define CANNON_H

#include "Vector2.h"

// Classe que representa o canh�o do jogador.
// O canh�o possui uma posi��o e uma dire��o, podendo rotacionar e ser renderizado.

class Cannon {
public:
    Vector2 position;
    Vector2 direction;

    // Construtor que inicializa o canh�o na posi��o especificada e com a dire��o padr�o (0, 1).
    Cannon(const Vector2& pos) : position(pos), direction(0, 1) {}

    // Rotaciona a dire��o do canh�o em um �ngulo especificado (em graus).
    void rotate(float angle) {
        float rad = angle * (3.14159265359 / 180.0);
        float cosA = cos(rad);
        float sinA = sin(rad);
        float newX = direction.x * cosA - direction.y * sinA;
        float newY = direction.x * sinA + direction.y * cosA;
        direction.set(newX, newY);
    }

    // Renderiza o canh�o na tela.
    void render() const {
        CV::color(1, 0, 0);
        CV::line(position.x, position.y, position.x + direction.x * 20, position.y + direction.y * 20);
    }

    // Retorna a posi��o do canh�o.
    Vector2 getPosition() const {
        return position;
    }

    // Retorna a dire��o do canh�o.
    Vector2 getDirection() const {
        return direction;
    }

    // Define uma nova dire��o para o canh�o.
    void setDirection(const Vector2& newDirection) {
        direction = newDirection;
    }
};

#endif
