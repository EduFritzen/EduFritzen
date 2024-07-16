#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "gl_canvas2d.h"
#include "Frames.h"
#include "Cannon.h"
#include "Projectile.h"
#include "Block.h"
#include "Menu.h"

#define MAXROWS 8

// Classes e variáveis globais para gerenciar o estado do jogo
Frames *frames;
int screenWidth = 500, screenHeight = 800;
Cannon* cannon;
std::vector<Projectile> projectiles;
std::vector<Block> blocks;
int mouseX, mouseY; // Variáveis globais do mouse para poder exibir dentro da render.
static bool isLeftButtonDown = false;
static bool isRightButtonDown = false;
typedef void (*MouseAction)(const Ponto&);
float deltaTime = 0.0f;
int score = 0;
bool gameStarted = false;
Menu* menu;
Vector2 lastProjectilePosition(screenWidth / 2, 50); // Inicializa na posição inicial do canhão
int projectileCount = 1; // Contador de projéteis a serem disparados no próximo disparo
int projectilesToShoot = 0; // Contador de projéteis restantes a serem disparados na sequência atual
float shootTimer = 0.0f; // Temporizador para controlar o intervalo de disparo
float shootInterval = 0.1f; // Intervalo de tempo entre disparos
bool canShoot = true; // Controle para verificar se pode disparar

// Função para atualizar a lista de blocos, removendo os blocos que foram destruídos
void updateBlocks() {
    blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
        [](const Block& block) { return block.getValue() <= 0; }),
        blocks.end());
}

// Função para adicionar uma nova fileira de blocos no topo da tela
void addNewRowOfBlocks() {
    int currentRows = blocks.size() / 7;
    if (currentRows < MAXROWS) { // Verifica se o número de fileiras é menor que 8
        int numBlocks = 7; // Número de blocos por fileira
        float totalWidth = screenWidth * 0.95; // Largura total ocupada pelos blocos (95% da largura da tela)
        float blockWidth = totalWidth / numBlocks; // Largura de cada bloco
        float blockHeight = blockWidth; // Altura proporcional à largura
        float xOffset = (screenWidth - totalWidth) / 2;

        // Move as fileiras existentes para baixo
        for (auto& block : blocks) {
            block.topLeft.y -= blockHeight;
            block.bottomRight.y -= blockHeight;
        }

        // Adiciona uma nova fileira de blocos no topo
        for (int i = 0; i < numBlocks; i++) {
            float x1 = xOffset + i * blockWidth;
            float x2 = xOffset + (i + 1) * blockWidth;
            blocks.emplace_back(x1, screenHeight - blockHeight, x2, screenHeight, 5);
        }
    } else {
        // Se o número máximo de fileiras for atingido, o jogo acaba e volta ao menu
        printf("Numero maximo de fileiras atingido. O jogo acabou!\n");
        gameStarted = false;
        blocks.clear(); // Limpa os blocos
    }
}

// Função principal de atualização do jogo, chamada a cada frame
void update() {
    float deltaTime = 1.0 / frames->getFrames();

    // Controle de disparo dos projéteis
    if (projectilesToShoot > 0) {
        shootTimer -= deltaTime;
        if (shootTimer <= 0.0f) {
            Vector2 projPos = cannon->getPosition();
            Vector2 projVel = cannon->getDirection() * 300.0f;
            projectiles.emplace_back(projPos, projVel);
            shootTimer = shootInterval;
            projectilesToShoot--;
        }
    }

    auto proj = projectiles.begin(); // Inicializa o iterador do vetor de projéteis
    while (proj != projectiles.end()) {
        proj->update(deltaTime);

        // Verifica as colisões com as bordas da tela
        if (proj->position.x < 0 || proj->position.x > screenWidth) {
            proj->velocity.x *= -1; // Inverta a velocidade na direção X
        }
        if (proj->position.y > screenHeight) {
            proj->velocity.y *= -1; // Inverta a velocidade na direção Y
        }

        // Verifica as colisões com os blocos
        for (auto& block : blocks) {
            char collisionSide = 'N'; // Inicializa com 'N'
            if (block.checkCollision(proj->position, collisionSide)) {
                block.reduceValue();
                score = score + 10;
                switch (collisionSide) {
                    case 'L':
                    case 'R':
                        proj->reflect(Vector2(1, 0)); // Refletir no eixo X
                        break;
                    case 'T':
                    case 'B':
                        proj->reflect(Vector2(0, 1)); // Refletir no eixo Y
                        break;
                }
            }
        }

        if (proj->position.y < 0) {
            lastProjectilePosition = proj->position; // Atualize a posição do último projétil
            proj = projectiles.erase(proj);
        } else {
            ++proj;
        }
    }
    updateBlocks(); // Chama a função para atualizar os blocos
    cannon->position.x = lastProjectilePosition.x; // Atualiza a posição do canhão com base na posição do último projétil

    // Verifica se todos os projéteis saíram da tela para permitir novo disparo
    if (projectiles.empty() && !canShoot) {
        canShoot = true; // Permite que novos projéteis sejam disparados
        addNewRowOfBlocks(); // Adiciona uma nova fileira de blocos após cada jogada
    }
}

// Função para desenhar a linha pontilhada
void drawDottedLine(Vector2 start, Vector2 direction, float length, float segmentLength, float gapLength) {
    Vector2 currentPos = start;
    Vector2 segment = direction * segmentLength;
    Vector2 gap = direction * gapLength;

    for (float traveled = 0; traveled < length; traveled += segmentLength + gapLength) {
        Vector2 nextPos = currentPos + segment;
        if (nextPos.x < 0 || nextPos.x > screenWidth || nextPos.y < 0 || nextPos.y > screenHeight) {
            break; // Pare de desenhar se a linha sair da tela
        }
        CV::color(1, 1, 0);
        CV::line(currentPos.x, currentPos.y, nextPos.x, nextPos.y);
        currentPos = nextPos + gap;
    }
}

// Função para renderizar a barra de pontuação na parte superior da tela
void renderScoreBar() {
    float barHeight = 50.0f;
    float barWidth = screenWidth;

    // Define a cor da barra (cinza claro)
    CV::color(0.8f, 0.8f, 0.8f);
    CV::rectFill(0, 0, barWidth, barHeight);

    // Define a cor do texto (preto)
    CV::color(0, 0, 0);
    char scoreStr[20];
    snprintf(scoreStr, sizeof(scoreStr), "Score: %d", score);
    CV::text(10, barHeight / 2 + 5, scoreStr); // Desenha o texto na barra
}

// Função para renderizar o FPS no canto inferior direito da tela
void renderFPS() {
    float fps = frames->getFrames();
    char fpsStr[20];
    snprintf(fpsStr, sizeof(fpsStr), "FPS: %.2f", fps);

    // Define a cor do texto (branco)
    CV::color(1, 1, 1);
    CV::text(screenWidth - 80, 20, fpsStr); // Desenha o texto no canto inferior direito
}

// Função principal de renderização, chamada a cada frame
void render(){
    CV::clear(0, 0, 0); // Limpa a tela com a cor preta
    if (!gameStarted) {
        menu->render(); // Renderiza o menu se o jogo não começou
    }
    else {
        renderScoreBar(); // Renderiza a barra de pontuação
        cannon->render(); // Renderiza o canhão
        for (auto& proj : projectiles) {
            proj.render(); // Renderiza cada projétil
        }
        for (auto& block : blocks) {
            block.render(); // Renderiza cada bloco
        }

        // Desenha a linha pontilhada de direção do canhão
        Vector2 start = cannon->getPosition();
        Vector2 direction = cannon->getDirection();
        float length = 800.0f; // Ajuste conforme necessário
        float segmentLength = 10.0f;
        float gapLength = 5.0f;
        drawDottedLine(start, direction, length, segmentLength, gapLength);

        renderFPS(); // Renderiza o FPS no canto inferior direito
    }

    update(); // Chama a função de atualização do jogo
}

// Função para criar os blocos iniciais
void createNewBlocks(int numRows) {
    float totalWidth = screenWidth * 0.95; // Largura total ocupada pelos blocos (95% da largura da tela)
    float blockWidth = totalWidth / 7; // Largura de cada bloco
    float blockHeight = blockWidth; // Altura proporcional à largura
    float xOffset = (screenWidth - totalWidth) / 2;

    for (int row = 0; row < numRows; row++) {
        for (int i = 0; i < 7; i++) {
            float x1 = xOffset + i * blockWidth;
            float x2 = xOffset + (i + 1) * blockWidth;
            float y1 = screenHeight - (row + 1) * blockHeight;
            float y2 = screenHeight - row * blockHeight;
            blocks.emplace_back(x1, y1, x2, y2, 5);
        }
    }
}

// Função de callback para teclas pressionadas
void keyboard(int key){ //chamado toda vez que uma tecla é pressionada
   printf("Key: %d\n", key);

   if (!gameStarted) {
        switch (key) {
            case 201: //up arrow
                menu->previousOption();
                break;
            case 203: //down arrow
                menu->nextOption();
                break;
            case 13: // Enter key
                if (menu->getSelectedOption() == 0) {
                    gameStarted = true;
                }
                else if (menu->getSelectedOption() == 1) {
                    exit(0);
                }
                break;
        }
   }
   switch(key){
      case 27://Esc
	     exit(0);
         break;
   }
}

void keyboardUp(int key){ //funcao chamada toda vez que uma tecla for liberada
   printf("Liberou: %d\n", key);
}

// Funções para tratamento de mouse: cliques, movimentos e arrastos
void LeftButtonDown(const Ponto& mousePos){
    isLeftButtonDown = true;
}
void LeftButtonUp(const Ponto& mousePos){
    isLeftButtonDown = false;
    if (canShoot) {
        projectilesToShoot = projectileCount; // Iniciar a sequência de disparos
        shootTimer = 0.0f; // Reiniciar o temporizador
        canShoot = false;
        projectileCount++;
    }
}
void RightButtonDown(const Ponto& mousePos){
    isRightButtonDown = true;
}
void RightButtonUp(const Ponto& mousePos){
    isRightButtonDown = false;
}

// Matriz responsável por guardar as ações do mouse
MouseAction mouseActions[3][2] = { // Matriz responsavel por guardar as acoes do mouse, se ocorrer alguma acao no mouse essa matriz guarda ela
    {LeftButtonDown, LeftButtonUp},  // Botão esquerdo
    {nullptr, nullptr},             // Botão do meio
    {RightButtonDown, RightButtonUp} // Botão direito
};

void mouse(int button, int state, int wheel, int direction, int x, int y){
    mouseX = x;
    mouseY = y;

    Ponto mousePos;
    mousePos.x = mouseX;
    mousePos.y = mouseY;

    // Atualiza a direção do canhão para apontar da posição do canhão para a posição atual do mouse
    Vector2 cannonToMouse(mouseX - cannon->position.x, mouseY - cannon->getPosition().y);
    cannonToMouse.normalize(); // Normaliza o vetor para ter comprimento 1
    cannon->setDirection(cannonToMouse);

    if (button >= 0 && button < 3) { // Caso ocorra alguma acao no mouse, a acao do mouse vai receber um ponto
        MouseAction mouseAction = mouseActions[button][state];
        if (mouseAction) {
            mouseAction(mousePos);
        }
    }
}

int main(void)
{
   cannon = new Cannon(lastProjectilePosition);
   frames = new Frames();
   menu = new Menu();
   createNewBlocks(1); // Inicializa com apenas uma fileira de blocos

   CV::init(&screenWidth, &screenHeight, "Trabalho3 CG Eduardo");
   CV::run();
}
