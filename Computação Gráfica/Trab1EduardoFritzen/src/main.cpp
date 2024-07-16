#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "gl_canvas2d.h"
#include "buttonManager.h"
#include "panelmanager.h"
#include "bmpManager.h"
#include "SevenSegmentDisplayManager.h"

#define COLORS 14
#define ENCRYPTION 3

ButtonManager buttonManager;
PanelManager panelManager;
BmpManager bmpManager;
SevenSegmentDisplayManager sevenSegmentDisplayManager;

int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
static bool isLeftButtonDown = false;
static bool isRightButtonDown = false;
static bool isHKeyPressed = false;
typedef void (*MouseAction)(const Ponto&);

void render(){
   //Paineis Resposivos
   panelManager.UpdatePosition(0, 0, screenHeight, screenWidth, screenHeight - 120);
   panelManager.UpdatePosition(1,screenWidth / 20, screenHeight -  8, (screenWidth / 4) - 30, screenHeight - 110);
   panelManager.UpdatePosition(2,(screenWidth / 4)- 3, screenHeight -  8, (screenWidth / 3) - 30, screenHeight - 110);
   panelManager.UpdatePosition(3,(screenWidth / 3)- 3, screenHeight -  8, (screenWidth / 2) , screenHeight - 110);
   panelManager.UpdatePosition(4,(screenWidth) - 200, screenHeight -  8, (screenWidth / 2) + 100, screenHeight - 110);

   panelManager.Render();

   bmpManager.render();

   buttonManager.render();

   if (isHKeyPressed && imagePressed >= 0) {
        bmpManager.plotHistogram(imagePressed);
   }

   sevenSegmentDisplayManager.render("TRABALHO CG - 7 SEG DISPLAY - 05.04", screenWidth, 15);
}

void AddPanels() { //5 paineis adicionados
    Panel TopPainel(0, screenHeight, screenWidth, screenHeight - 120,0.93,0.93,0.93);
    panelManager.AddPanel(TopPainel);

    Panel FormasPainel(screenWidth / 20, screenHeight -  8, (screenWidth / 4) - 30, screenHeight - 110,0.85,0.85,0.85);
    panelManager.AddPanel(FormasPainel);

    Panel ColorPainel((screenWidth / 4)- 3, screenHeight -  8, (screenWidth / 3) - 30, screenHeight - 110,0.93,0.93,0.93);
    panelManager.AddPanel(ColorPainel);

    Panel Color1Painel((screenWidth / 3)- 3, screenHeight -  8, (screenWidth / 2) , screenHeight - 110,0.93,0.93,0.93);
    panelManager.AddPanel(Color1Painel);

    Panel FigsPainel((screenWidth) - 200, screenHeight -  8, (screenWidth / 2) + 100, screenHeight - 110,0.93,0.93,0.93);
    panelManager.AddPanel(FigsPainel);
}

void AddButtons() { // botoas adicionados
    Button* button1 = new Button(75, 625, 70, 50, 1, 0, 0, 1, "IMG1");
    Button* button2 = new Button(155, 625, 70, 50, 0, 1, 0, 2, "IMG2");
    Button* button3 = new Button(235, 625, 70, 50, 0, 0, 1, 3, "IMG3");
    Button* button4 = new Button(345, 625, 70, 50, 1, 1, 0, 4, "SAVE");
    Button* button5 = new Button(455, 625, 70, 50, 1, 0, 1, 5, "TAM+");
    Button* button6 = new Button(530, 625, 70, 50, 0, 1, 1, 6, "TAM-");
    Button* button7 = new Button(610, 625, 70, 50, 0.5f, 0.5f, 0.5f, 7, "ROTATE");
    Button* button8 = new Button(785, 625, 70, 50, 1.0, 0.5, 0.0, 8, "FLIP_V");
    Button* button9 = new Button(860, 625, 70, 50, 1.0, 0.5, 0.5, 9, "FLIP_H");
    Button* button10 = new Button(940, 625, 70, 50, 0.5, 0.0, 0.5, 10, "DEL");
    Button* button11 = new Button(1015, 625, 70, 50, 0.6, 0.3, 0.0, 11, "BRILHO+");
    Button* button12 = new Button(1090, 625, 70, 50, 0.0, 0.5, 0.5, 12, "BRILHO-");
    buttonManager.addButton(button1);
    buttonManager.addButton(button2);
    buttonManager.addButton(button3);
    buttonManager.addButton(button4);
    buttonManager.addButton(button5);
    buttonManager.addButton(button6);
    buttonManager.addButton(button7);
    buttonManager.addButton(button8);
    buttonManager.addButton(button9);
    buttonManager.addButton(button10);
    buttonManager.addButton(button11);
    buttonManager.addButton(button12);
}

void keyboard(int key){ //chamado toda vez que uma tecla é pressionada
   printf("Key: %d\n" , key);

   switch(key){
      case 27://Esc
	     exit(0);
         break;
	  case 19://Ctrl+s
         bmpManager.saveData("bmp.txt",ENCRYPTION);
         break;
	  case 100://Tecla D
         bmpManager.RotateBmp(imagePressed, 90.0f);
         break;
	  case 97://Tecla A
         bmpManager.RotateBmp(imagePressed, -90.0f);
         break;
      case 104://Tecla H
         if(imagePressed >= 0){
            isHKeyPressed = true;
         }
         break;
      case 106://Tecla J
         bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\normal_1.bmp");
         break;
      case 107://Tecla K
         bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\img1.bmp");
         break;
      case 108://Tecla L
         bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\img3.bmp");
         break;
      case 114://Tecla R
         if(imagePressed >= 0){
            bmpManager.rgbBmpImage(imagePressed,'r');
         }
         break;
      case 103://Tecla G
         if(imagePressed >= 0){
            bmpManager.rgbBmpImage(imagePressed,'g');
         }
         break;
      case 98://Tecla B
         if(imagePressed >= 0){
            bmpManager.rgbBmpImage(imagePressed,'b');
         }
         break;
      case 121://Tecla Y
         if(imagePressed >= 0){
            bmpManager.rgbBmpImage(imagePressed,'y');
         }
         break;
      case 201://up arrow
         if(imagePressed >= 0){
            bmpManager.brightnessBmpImage(imagePressed, true);
         }
         break;
      case 203://down arrow
         if(imagePressed >= 0){
            bmpManager.brightnessBmpImage(imagePressed, false);
         }
         break;
	  case 115://Tecla S
         bmpManager.RotateBmp(imagePressed, 180.0f);
         break;
	  case 113://Tecla Q
         bmpManager.FlipBmp(imagePressed, true);
         break;
	  case 119://Tecla W
         bmpManager.FlipBmp(imagePressed, false);
         break;
      case 200://left arrow para diminuir
         if(imagePressed >= 0){
            bmpManager.ResizeBmp(imagePressed, false);
         }
	     break;
	  case 202://right arrow para aumentar
         if(imagePressed >= 0){
            bmpManager.ResizeBmp(imagePressed, true);
         }
	     break;
	  case 127://del key
         bmpManager.RemoveBmp(imagePressed);
         imagePressed = -1; // Resetar a variável após a remoção
	     break;
   }
}

void keyboardUp(int key){ //funcao chamada toda vez que uma tecla for liberada
   printf("Liberou: %d\n" , key);
    if (key == 104) {
       isHKeyPressed = false; // Define a flag como falso quando a tecla H é liberada
   }
}

//funções para tratamento de mouse: cliques, movimentos e arrastos
void LeftButtonDown(const Ponto& mousePos){
    imagePressed = bmpManager.ClickedBmp(mousePos);
    isLeftButtonDown = true;
}
void LeftButtonUp(const Ponto& mousePos){
    isLeftButtonDown = false;
}
void RightButtonDown(const Ponto& mousePos){
    imagePressed = bmpManager.ClickedBmp(mousePos);
    isRightButtonDown = true;
}
void RightButtonUp(const Ponto& mousePos){
    isRightButtonDown = false;
}

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

    if (button >= 0 && button < 3) { // Caso ocorra alguma acao no mouse, a acao do mouse vai receber um ponto
        MouseAction mouseAction = mouseActions[button][state];
        if (mouseAction) {
            mouseAction(mousePos);
        }
    }

    if (isLeftButtonDown){
        int clickedButtonTag = buttonManager.checkCollision(x, y);
        if (clickedButtonTag != -1 && clickedButtonTag < 5) {
            // Aqui você pode realizar ações com base na tag do botão clicado
            switch (clickedButtonTag) {
                case 1:
                    bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\normal_1.bmp");
                    break;
                case 2:
                    bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\img1.bmp");
                    break;
                case 3:
                    bmpManager.LoadBmp(".\\Trab1EduardoFritzen\\images\\img3.bmp");
                    break;
                case 4:
                    bmpManager.saveData("bmp.txt",ENCRYPTION);
                    break;
            }
        }
        else if(clickedButtonTag != -1 && clickedButtonTag >= 5 && lastSelectedImageIndex>=0){
            switch (clickedButtonTag) {
                case 5:
                    bmpManager.ResizeBmp(lastSelectedImageIndex, true);
                    break;
                case 6:
                    bmpManager.ResizeBmp(lastSelectedImageIndex, false);
                    break;
                case 7:
                    bmpManager.RotateBmp(lastSelectedImageIndex, 90.0f);
                    break;
                case 8:
                    bmpManager.FlipBmp(lastSelectedImageIndex, true);
                    break;
                case 9:
                    bmpManager.FlipBmp(lastSelectedImageIndex, false);
                    break;
                case 10:
                    bmpManager.RemoveBmp(lastSelectedImageIndex);
                    imagePressed = -1; // Resetar a variável após a remoção
                    lastSelectedImageIndex= -1;
                    break;
                case 11:
                    bmpManager.brightnessBmpImage(lastSelectedImageIndex, true);
                    break;
                case 12:
                    bmpManager.brightnessBmpImage(lastSelectedImageIndex, false);
                    break;
            }
        }
    }

    if (isLeftButtonDown && imagePressed >= 0) { // Responsavel por mover e pintar a figura selecionada
        bmpManager.moveBmp(imagePressed, mousePos);
        lastSelectedImageIndex = imagePressed;
    }

    if (isRightButtonDown && imagePressed >= 0) { // Rotaciona a figura caso o botao direito é clicado
        bmpManager.RotateBmp(imagePressed, 90.0f);
    }

    if (wheel == 0 && direction != -2 && imagePressed >= 0) { // Verifica se a wheel do mouse foi movida
        if (direction > 0) { // Se a roda estiver indo para cima (sentido positivo)
            printf("Wheel para cima: ");
            bmpManager.ResizeBmp(imagePressed, true); // Aumenta o tamanho da imagem
        }
        else if (direction < 0) { // Se a roda estiver indo para baixo (sentido negativo)
            printf("Wheel para baixo: ");
            bmpManager.ResizeBmp(imagePressed, false); // Diminui o tamanho da imagem
        }
    }
}

int main(void)
{
   bmpManager.loadData("bmp.txt",ENCRYPTION);

   AddButtons();
   AddPanels();

   CV::init(&screenWidth, &screenHeight, "Trabalho1 CG Eduardo");
   CV::run();
}
