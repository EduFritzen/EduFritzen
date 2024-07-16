/*****************************************************************************************

   panelManager.h - Biblioteca para gerenciamento de pain�is na tela usando a GL Canvas 2D.

   Esta biblioteca fornece classes para criar e manipular pain�is na tela de uma aplica��o
   gr�fica utilizando a GL Canvas 2D.

   Classe Panel:
   - Representa um painel na tela com coordenadas, dimens�es e cor configur�veis.
   - Permite definir a visibilidade do painel e renderiz�-lo na tela.

   Classe PanelManager:
   - Gerencia m�ltiplos pain�is na tela.
   - Permite adicionar, configurar a visibilidade, renderizar e atualizar a posi��o dos pain�is.

*******************************************************************************************/

#ifndef __PANELMANAGER_H__
#define __PANELMANAGER_H__

#include "gl_canvas2d.h"
#include <vector>

// Classe que representa um painel na tela
class Panel {
private:
  float x, y, width, height; // Coordenadas e dimens�es do painel
  float r, g, b; // Componentes de cor do painel
  bool visible; // Flag para indicar se o painel est� vis�vel
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

  // M�todos para manipula��o dos atributos do painel
  void SetVisible(bool v) {
    visible = v;
  }

  bool IsVisible() const {
    return visible;
  }

  // M�todo para renderizar o painel na tela
  void Render() const {
    if (!visible) return;

    CV::color(r, g, b);
    CV::rectFill(x, y, width , height);
    CV::color(0,0,0);
    CV::rect(x, y, width , height);
    CV::color(0);
  }

  // M�todo para atualizar a posi��o e dimens�es do painel
  void SetPosition(float _x, float _y, float _width, float _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
  }
};

// Classe respons�vel por gerenciar v�rios pain�is na tela
class PanelManager {
private:
  std::vector<Panel> panels; // Vetor de pain�is
  std::vector<bool> active; // Vetor de flags para indicar se os pain�is est�o ativos
  unsigned int selected_panel; // �ndice do painel selecionado
  bool selected_panel_active = false; // Flag para indicar se o painel selecionado est� ativo
  float currentColor[3]; // Cor atual selecionada para os pain�is
public:
  // Construtor para inicializar os atributos do gerenciador de pain�is
  PanelManager() {
    currentColor[0] = 1.0f;
    currentColor[1] = 1.0f;
    currentColor[2] = 1.0f;
  }

  // M�todo para adicionar um novo painel ao gerenciador
  void AddPanel(Panel panel) {
    panels.push_back(panel);
    active.push_back(true);
  }

  // M�todo para definir a visibilidade de um painel
  void SetVisible(unsigned int index, bool v) {
    if (index >= 0 && index < panels.size()) {
      panels[index].SetVisible(v);
    }
  }

  // M�todo para verificar se um painel est� vis�vel
  bool IsVisible(unsigned int index)  {
    if (index >= 0 && index < panels.size()) {
      return panels[index].IsVisible();
    }
    return false;
  }

  // M�todo para renderizar todos os pain�is do gerenciador
  void Render()  {
    for (unsigned int i = 0; i < panels.size(); i++) {
      if (active[i]) {
        panels[i].Render();
      }
    }
  }

  // M�todo para atualizar a posi��o e dimens�es de um painel
  void UpdatePosition(int index, float x, float y, float width, float height) {
      panels[index].SetPosition(x, y, width, height);
  }
};

#endif
