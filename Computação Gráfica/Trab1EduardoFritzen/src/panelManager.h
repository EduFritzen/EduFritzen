/*****************************************************************************************

   panelManager.h - Biblioteca para gerenciamento de painéis na tela usando a GL Canvas 2D.

   Esta biblioteca fornece classes para criar e manipular painéis na tela de uma aplicação
   gráfica utilizando a GL Canvas 2D.

   Classe Panel:
   - Representa um painel na tela com coordenadas, dimensões e cor configuráveis.
   - Permite definir a visibilidade do painel e renderizá-lo na tela.

   Classe PanelManager:
   - Gerencia múltiplos painéis na tela.
   - Permite adicionar, configurar a visibilidade, renderizar e atualizar a posição dos painéis.

*******************************************************************************************/

#ifndef __PANELMANAGER_H__
#define __PANELMANAGER_H__

#include "gl_canvas2d.h"
#include <vector>

// Classe que representa um painel na tela
class Panel {
private:
  float x, y, width, height; // Coordenadas e dimensões do painel
  float r, g, b; // Componentes de cor do painel
  bool visible; // Flag para indicar se o painel está visível
  float currentColor[3]; // Cor atual do painel
public:
  // Construtor para inicializar os atributos do painel
  Panel(float _x, float _y, float _width, float _height, float _r, float _g, float _b, bool _visible = true) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    r = _r;
    g = _g;
    b = _b;
    visible = _visible;
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
  }

  // Métodos para manipulação dos atributos do painel
  void SetVisible(bool v) {
    visible = v;
  }

  bool IsVisible() const {
    return visible;
  }

  // Método para renderizar o painel na tela
  void Render() const {
    if (!visible) return;

    CV::color(r, g, b);
    CV::rectFill(x, y, width , height);
    CV::color(0,0,0);
    CV::rect(x, y, width , height);
    CV::color(0);
  }

  // Método para atualizar a posição e dimensões do painel
  void SetPosition(float _x, float _y, float _width, float _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
  }
};

// Classe responsável por gerenciar vários painéis na tela
class PanelManager {
private:
  std::vector<Panel> panels; // Vetor de painéis
  std::vector<bool> active; // Vetor de flags para indicar se os painéis estão ativos
  unsigned int selected_panel; // Índice do painel selecionado
  bool selected_panel_active = false; // Flag para indicar se o painel selecionado está ativo
  float currentColor[3]; // Cor atual selecionada para os painéis
public:
  // Construtor para inicializar os atributos do gerenciador de painéis
  PanelManager() {
    currentColor[0] = 1.0f;
    currentColor[1] = 1.0f;
    currentColor[2] = 1.0f;
  }

  // Método para adicionar um novo painel ao gerenciador
  void AddPanel(Panel panel) {
    panels.push_back(panel);
    active.push_back(true);
  }

  // Método para definir a visibilidade de um painel
  void SetVisible(unsigned int index, bool v) {
    if (index >= 0 && index < panels.size()) {
      panels[index].SetVisible(v);
    }
  }

  // Método para verificar se um painel está visível
  bool IsVisible(unsigned int index)  {
    if (index >= 0 && index < panels.size()) {
      return panels[index].IsVisible();
    }
    return false;
  }

  // Método para renderizar todos os painéis do gerenciador
  void Render()  {
    for (unsigned int i = 0; i < panels.size(); i++) {
      if (active[i]) {
        panels[i].Render();
      }
    }
  }

  // Método para atualizar a posição e dimensões de um painel
  void UpdatePosition(int index, float x, float y, float width, float height) {
      panels[index].SetPosition(x, y, width, height);
  }
};

#endif
