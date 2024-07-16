#ifndef __BUTTONMANAGER_H__
#define __BUTTONMANAGER_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "gl_canvas2d.h"
#include "bmpManager.h"
#include "Color.h"
#include <functional>

int screenWidth = 1366, screenHeight = 700;
int InicioXPainel = (screenWidth / 17) + 5;
int InicioYPainel = screenHeight - 30;

class Button {
private:
    float x, y, width, height;
    float r, g, b;
    int tag;
    bool buttonPressed;
    std::string buttonText;

public:
    Button(float _x, float _y, float _width, float _height, float _r, float _g, float _b, int _tag, const std::string& text) {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        r = _r;
        g = _g;
        b = _b;
        tag = _tag;
        buttonText = text;
        buttonPressed = false;
    }

    bool isCollided(float mouseX, float mouseY) {
        return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    }

    void render() {
        CV::color(r, g, b);
        CV::rectFill(x, y, x + width, y + height);
        CV::color(0, 0, 0);
        CV::text(x + 4, y + height / 2, buttonText.c_str());
    }

    void setPressed(bool pressed) {
        buttonPressed = pressed;
    }

    bool isPressed() {
        return buttonPressed;
    }

    int getTag() {
        return tag;
    }

    std::string getButtonText() const {
        return buttonText;
    }
};

class ButtonManager {
private:
    std::vector<Button*> buttons;

public:
    void addButton(Button* button) {
        buttons.push_back(button);
    }

    int checkCollision(float mouseX, float mouseY) {
        for (unsigned int i = 0; i < buttons.size(); i++) {
            if (buttons[i]->isCollided(mouseX, mouseY)) {
                return buttons[i]->getTag();
            }
        }
        return -1; // Nenhum botão foi clicado
    }

    void render() {
        for (unsigned int i = 0; i < buttons.size(); i++) {
            buttons[i]->render();
        }
    }
};

#endif
