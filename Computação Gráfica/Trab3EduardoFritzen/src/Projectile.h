#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector2.h"
#include "gl_canvas2d.h"
#include "Ponto.h"

// Classe que representa um proj�til disparado pelo canh�o.
// O proj�til possui posi��o, velocidade e estado (ativo ou n�o).

class Projectile {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;

    // Construtor que inicializa o proj�til com posi��o e velocidade especificadas.
    Projectile(const Vector2& pos, const Vector2& vel) : position(pos), velocity(vel), active(true) {}

    // Atualiza a posi��o do proj�til com base no tempo delta.
    void update(float deltaTime) {
        position = position + velocity * deltaTime;
    }

    // Renderiza o proj�til na tela.
    void render() const {
        if (active){
            CV::color(1, 1, 1);
            Ponto p = {position.x, position.y};
            CV::circleFill(p, 5, 12);
        }
    }

    // Reflete a velocidade do proj�til em rela��o ao eixo especificado.
    void reflect(const Vector2& axis) {
        if (axis.x == 1) {
            velocity.x = -velocity.x; // Inverte a velocidade no eixo X
        }
        if (axis.y == 1) {
            velocity.y = -velocity.y; // Inverte a velocidade no eixo Y
        }
    }

    // Retorna se o proj�til est� ativo.
    bool isActive() const {
        return active;
    }

    // Retorna a posi��o do proj�til.
    Vector2 getPosition() const {
        return position;
    }

private:
    // Verifica se o proj�til ultrapassou os limites da tela, desativando-o se necess�rio.
    void checkBoundary() {
        if (position.y < 0) {
            active = false;
        }
    }
};

#endif
