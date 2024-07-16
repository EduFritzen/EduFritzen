#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector2.h"
#include "gl_canvas2d.h"
#include "Ponto.h"

// Classe que representa um projétil disparado pelo canhão.
// O projétil possui posição, velocidade e estado (ativo ou não).

class Projectile {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;

    // Construtor que inicializa o projétil com posição e velocidade especificadas.
    Projectile(const Vector2& pos, const Vector2& vel) : position(pos), velocity(vel), active(true) {}

    // Atualiza a posição do projétil com base no tempo delta.
    void update(float deltaTime) {
        position = position + velocity * deltaTime;
    }

    // Renderiza o projétil na tela.
    void render() const {
        if (active){
            CV::color(1, 1, 1);
            Ponto p = {position.x, position.y};
            CV::circleFill(p, 5, 12);
        }
    }

    // Reflete a velocidade do projétil em relação ao eixo especificado.
    void reflect(const Vector2& axis) {
        if (axis.x == 1) {
            velocity.x = -velocity.x; // Inverte a velocidade no eixo X
        }
        if (axis.y == 1) {
            velocity.y = -velocity.y; // Inverte a velocidade no eixo Y
        }
    }

    // Retorna se o projétil está ativo.
    bool isActive() const {
        return active;
    }

    // Retorna a posição do projétil.
    Vector2 getPosition() const {
        return position;
    }

private:
    // Verifica se o projétil ultrapassou os limites da tela, desativando-o se necessário.
    void checkBoundary() {
        if (position.y < 0) {
            active = false;
        }
    }
};

#endif
