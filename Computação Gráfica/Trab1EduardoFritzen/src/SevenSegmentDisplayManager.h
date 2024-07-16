/*****************************************************************************************

sevenSegmentDisplayManager.h - Biblioteca para renderizar display de 7 segmentos na tela
usando a GL Canvas 2D.

Esta biblioteca fornece classes para criar e manipular displays de 7 segmentos na tela de
uma aplicação gráfica utilizando a GL Canvas 2D.

Classe segmentDisplay:

Representa um display de 7 segmentos na tela.
Permite renderizar caracteres e símbolos utilizando os segmentos do display.
Classe SevenSegmentDisplayManager:

Gerencia a renderização de múltiplos caracteres em displays de 7 segmentos na tela.
Permite renderizar strings de caracteres de forma centralizada na tela.
*******************************************************************************************/
#ifndef __SEVENSEGMENTDISPLAYMANAGER_H__
#define __SEVENSEGMENTDISPLAYMANAGER_H__

#include "gl_canvas2d.h"
#include <map>
#include <vector>
#include <string>

// Classe que representa um display de 7 segmentos na tela
class segmentDisplay {
private:
    std::map<char, std::vector<bool>> segments; // Mapa de caracteres para seus segmentos correspondentes

public:
    segmentDisplay() {
        // Inicialização dos segmentos para cada dígito de 0 a 9
        segments = {//segmentos:  inferior, inferior direito, superior direito, superior, superior esquerdo, inferior esquerdo, central
            {'0', {true, true, true, true, true, true, false}},
            {'1', {false, true, true, false, false, false, false}},
            {'2', {true, false, true, true, false, true, true}},
            {'3', {true, true, true, true, false, false, true}},
            {'4', {false, true, true, false, true, false, true}},
            {'5', {true, true, false, true, true, false, true}},
            {'6', {true, true, false, true, true, true, true}},
            {'7', {false, true, true, true, false, false, false}},
            {'8', {true, true, true, true, true, true, true}},
            {'9', {true, true, true, true, true, false, true}},
            {'A', {false, true, true, true, true, true, true}},
            {'B', {true, true, false, false, true, true, true}},
            {'C', {true, false, false, true, true, true, false}},
            {'D', {true, true, true, false, false, true, true}},
            {'E', {true, false, false, true, true, true, true}},
            {'F', {false, false, false, true, true, true, true}},
            {'G', {true, true, false, true, true, true, false}},
            {'H', {false, true, true, false, true, true, true}},
            {'I', {false, true, true, false, false, false, false}},
            {'J', {true, true, false, true, false, false, false}},
            {'L', {true, false, false, false, true, true, false}},
            {'N', {false, true, false, false, false, true, true}},
            {'O', {true, true, true, true, true, true, false}},
            {'P', {false, false, true, true, true, true, true}},
            {'Q', {true, true, true, false, false, true, true}},
            {'R', {false, false, false, false, false, true, true}},
            {'S', {true, true, false, true, true, false, true}},
            {'T', {true, false, false, false, true, true, true}},
            {'U', {true, true, true, false, true, true, false}},
            {'Y', {false, true, true, false, true, false, true}},
            {'.', {true, false, false, false, false, false, false}},
            {'-', {false, false, false, false, false, false, true}},
            {' ', {false, false, false, false, false, false, false}}// Ponto decimal
            };
    }

    // Método para renderizar o display de sete segmentos na posição (x, y) com tamanho size
    void render(char character, float x, float y, float size) {
        // Calcula o tamanho dos segmentos baseado no tamanho total do display
        float segmentSize = size / 3.0f;

        // Define as coordenadas dos segmentos do display de sete segmentos
        float segmentCoordinates[7][4] = {
            {x + segmentSize / 2, y, x + size - segmentSize / 2, y + segmentSize / 4},  // Segmento superior
            {x + size - segmentSize / 4, y + segmentSize / 4, x + size, y + size / 2 - segmentSize / 4},  // Segmento superior direito
            {x + size - segmentSize / 4, y + size / 2 + segmentSize / 4, x + size, y + size - segmentSize / 4}, // Segmento inferior direito
            {x + segmentSize / 2, y + size - segmentSize / 4, x + size - segmentSize / 2, y + size}, // Segmento inferior
            {x, y + size / 2 + segmentSize / 4, x + segmentSize / 4, y + size - segmentSize / 4},           // Segmento inferior esquerdo
            {x, y + segmentSize / 4, x + segmentSize / 4, y + size / 2 - segmentSize / 4},               // Segmento superior esquerdo
            {x + segmentSize / 2, y + size / 2 - segmentSize / 4, x + size - segmentSize / 2, y + size / 2 + segmentSize / 4} // Segmento central
        };

        // Verifica quais segmentos devem ser ativados para representar o número
        std::vector<bool> characterSegments = segments[character];
        for (int i = 0; i < 7; ++i) {
            if (characterSegments[i]) {
                CV::color(1.0f, 0.0f, 0.0f); // Cor vermelha
            } else {
                CV::color(0.5f, 0.5f, 0.5f); // Cor cinza
            }
            CV::rectFill(segmentCoordinates[i][0], segmentCoordinates[i][1], segmentCoordinates[i][2], segmentCoordinates[i][3]);
        }
    }
};

class SevenSegmentDisplayManager {
private:
    segmentDisplay display; // Instância da classe segmentDisplay

public:
    // Método para renderizar uma string de caracteres
    void render(const std::string& text, float screenWidth, float size) {
        float y = 10;
        float totalWidth = size * 1.5 * text.size(); // Calcula a largura total do texto renderizado
        float xOffset = (screenWidth - totalWidth) / 2.0f; // Calcula a posição x centralizada

        CV::color(0.0f, 0.0f, 0.0f); // Cor preta
        CV::rectFill(xOffset - 5, y - 5, xOffset + totalWidth + 5, y + size * 1.2 + 5); // Desenha o retângulo preto como fundo do texto

        for (char character : text) {
            display.render(character, xOffset, y, size);
            xOffset += size * 1.5; // Ajuste de espaço entre caracteres
        }
    }
};

#endif
