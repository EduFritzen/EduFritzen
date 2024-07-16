#ifndef MENU_H
#define MENU_H

#include "gl_canvas2d.h"
#include "Vector2.h"
#include <vector>
#include <string>

// Classe que representa o menu do jogo.
// O menu possui uma lista de opções e controla qual opção está selecionada.

class Menu {
private:
    std::vector<std::string> options;
    int selectedOption;

public:
    // Construtor que inicializa o menu com opções padrão.
    Menu() {
        options.push_back("Exit");
        options.push_back("Start Game");
        selectedOption = 0;
    }


void render() {
    int screenWidth = 500, screenHeight = 800;
    CV::clear(0, 0, 0); // Limpa a tela com a cor preta

    const char* title = "Balls Bounce";
    int titleWidth = strlen(title) * 10; // Estimativa da largura do título (10 pixels por caractere)
    int titleX = (screenWidth / 2) - (titleWidth / 2); // Centraliza o título horizontalmente
    int titleY = screenHeight - 100; // Ajusta a posição vertical do título (100 pixels abaixo do topo)

    CV::color(1, 1, 1); // Define a cor do texto (branco)
    CV::text(titleX, titleY, title);

    for (size_t i = 0; i < options.size(); i++) {
        if (i == static_cast<size_t>(selectedOption)) {
            CV::color(1, 0, 0); // Cor vermelha para a opção selecionada
        } else {
            CV::color(1, 1, 1); // Cor branca para as outras opções
        }
        CV::text(screenWidth / 2 - 50, screenHeight / 2 + i * 30, options[i].c_str());
    }

    }
    // Define a próxima opção selecionada.
    void nextOption() {
        selectedOption = (selectedOption + 1) % options.size();
    }

    // Define a opção selecionada anterior.
    void previousOption() {
        selectedOption = (selectedOption - 1 + options.size()) % options.size();
    }

    // Retorna a opção atualmente selecionada.
    int getSelectedOption() const {
        return selectedOption;
    }
};

#endif
