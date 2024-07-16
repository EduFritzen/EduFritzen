#ifndef CANNON_H
#define CANNON_H

#include "Vector2.h"

// Classe que representa o canhão do jogador.
// O canhão possui uma posição e uma direção, podendo rotacionar e ser renderizado.

class Cannon {
public:
    Vector2 position;
    Vector2 direction;

    // Construtor que inicializa o canhão na posição especificada e com a direção padrão (0, 1).
    Cannon(const Vector2& pos) : position(pos), direction(0, 1) {}

    // Rotaciona a direção do canhão em um ângulo especificado (em graus).
    void rotate(float angle) {
        float rad = angle * (3.14159265359 / 180.0);
        float cosA = cos(rad);
        float sinA = sin(rad);
        float newX = direction.x * cosA - direction.y * sinA;
        float newY = direction.x * sinA + direction.y * cosA;
        direction.set(newX, newY);
    }

    // Renderiza o canhão na tela.
    void render() const {
        CV::color(1, 0, 0);
        CV::line(position.x, position.y, position.x + direction.x * 20, position.y + direction.y * 20);
    }

    // Retorna a posição do canhão.
    Vector2 getPosition() const {
        return position;
    }

    // Retorna a direção do canhão.
    Vector2 getDirection() const {
        return direction;
    }

    // Define uma nova direção para o canhão.
    void setDirection(const Vector2& newDirection) {
        direction = newDirection;
    }
};

#endif
