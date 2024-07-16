#ifndef BLOCK_H
#define BLOCK_H

#include "Ponto.h"
#include "Color.h"

// Classe que representa um bloco no jogo.
// Um bloco possui uma posição (definida por dois pontos: topLeft e bottomRight) e um valor.
// O valor determina a quantidade de colisões necessárias para destruir o bloco e a sua cor.

class Block {
public:
    Ponto topLeft;
    Ponto bottomRight;
    int value;

    // Construtor que inicializa um bloco com posição e valor específicos.
    Block(float x1, float y1, float x2, float y2, int val) : topLeft(x1, y1), bottomRight(x2, y2), value(val) {}

    // Renderiza o bloco na tela.
    void render() const {
        Color color = getColorForValue(value);
        CV::color(color.r, color.g, color.b);
        CV::rectFill(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        CV::color(0, 0, 0);
        CV::rect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        char valStr[4];
        snprintf(valStr, sizeof(valStr), "%d", value);
        CV::text((topLeft.x + bottomRight.x) / 2 - 5, (topLeft.y + bottomRight.y) / 2, valStr);
    }

    // Atualiza o estado do bloco, retornando true se o bloco deve ser removido.
    bool update() {
        return value <= 0;
    }

    // Verifica se houve colisão com um projétil, retornando o lado da colisão.
    bool checkCollision(const Vector2& projPos, char& collisionSide) const {
        collisionSide = 'N'; // Inicializa com 'N' para "Nenhuma colisão"
        if (projPos.x >= topLeft.x && projPos.x <= bottomRight.x &&
            projPos.y >= topLeft.y && projPos.y <= bottomRight.y) {

            float dxLeft = projPos.x - topLeft.x;
            float dxRight = bottomRight.x - projPos.x;
            float dyTop = projPos.y - topLeft.y;
            float dyBottom = bottomRight.y - projPos.y;

            float minDist = std::min({dxLeft, dxRight, dyTop, dyBottom});

            if (minDist == dxLeft) {
                collisionSide = 'L'; // Left
            } else if (minDist == dxRight) {
                collisionSide = 'R'; // Right
            } else if (minDist == dyTop) {
                collisionSide = 'T'; // Top
            } else if (minDist == dyBottom) {
                collisionSide = 'B'; // Bottom
            }

            return true;
        }
        return false;
    }

    // Retorna true se o bloco deve ser removido.
    bool shouldBeRemoved() const {
        return value <= 0;
    }

    // Reduz o valor do bloco em 1.
    void reduceValue() {
        if (value > 0) value--;
    }

    // Retorna o valor atual do bloco.
    int getValue() const {
        return value;
    }

private:
    // Retorna a cor correspondente ao valor do bloco.
    Color getColorForValue(int value) const {
        if (value == 1) return Color(0, 0, 1);
        if (value == 2) return Color(0, 1, 0);
        if (value == 3) return Color(1, 0.5, 0);
        if (value == 4) return Color(1, 0, 0);
        if (value == 5) return Color(0.5, 0, 0.5);
        return Color(255, 255, 255); // Default white color
    }
};

#endif
