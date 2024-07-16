/*******************************************************************************************
  bmpManager.h - Arquivo de cabeçalho para gerenciamento de imagens BMP

  Este arquivo contém as definições das classes Bmp e BmpManager, que são responsáveis
  pelo carregamento, manipulação e renderização de imagens no formato BMP.
                                                                                                                                                                               *
  -- Descrição das classes --
  - Bmp: Representa uma imagem BMP, permitindo o carregamento, manipulação e renderização
    da imagem.

  - BmpManager: Gerencia um conjunto de imagens BMP, permitindo adicionar, remover,
    mover, girar e redimensionar as imagens, bem como salvar e carregar dados das imagens.

********************************************************************************************/
#ifndef ___BMPMANAGER__H___
#define ___BMPMANAGER__H___

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cmath>
#include "gl_canvas2d.h"
#include "Ponto.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>

#define HEADER_SIZE      14 //sizeof(HEADER) vai dar 16 devido ao alinhamento de bytes
#define INFOHEADER_SIZE  40 //sizeof(INFOHEADER) da 40 e esta correto.
#define uchar unsigned char
#define M_PI 3.14159265358979323846

static int imagePressed = -1; // variavel responsavel para saber o indice de uma imagembmp selecionada
static int lastSelectedImageIndex = -1;

typedef struct {
   unsigned short int type;                 /* Magic identifier            */
   unsigned int size;                       /* File size in bytes          */
   unsigned short int reserved1, reserved2;
   unsigned int offset;                     /* Offset to image data em bytes*/
} HEADER;

typedef struct {
   unsigned int size;               /* Header size in bytes      */
   int width,height;                /* Width and height of image */
   unsigned short int planes;       /* Number of colour planes   */
   unsigned short int bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int ncolours;           /* Number of colours         */
   unsigned int impcolours;         /* Important colours         */
} INFOHEADER;

class Bmp
{
private:
   int width, height, imagesize, bytesPerLine, bits;
   unsigned char *data;

   HEADER     header;
   INFOHEADER info;

   void load(const char *fileName){
      FILE *fp = fopen(fileName, "rb");
      if( fp == NULL ){
         printf("\nErro ao abrir arquivo %s para leitura", fileName);
         return;
      }

      printf("\n\nCarregando arquivo %s", fileName);

      //le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
      //o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
      fread(&header.type,      sizeof(unsigned short int), 1, fp);
      fread(&header.size,      sizeof(unsigned int),       1, fp);
      fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
      fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
      fread(&header.offset,    sizeof(unsigned int),       1, fp); //indica inicio do bloco de pixels

      //le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
      fread(&info.size,        sizeof(unsigned int),       1, fp);
      fread(&info.width,       sizeof(int),                1, fp);
      fread(&info.height,      sizeof(int),                1, fp);
      fread(&info.planes,      sizeof(unsigned short int), 1, fp);
      fread(&info.bits,        sizeof(unsigned short int), 1, fp);
      fread(&info.compression, sizeof(unsigned int),       1, fp);
      fread(&info.imagesize,   sizeof(unsigned int),       1, fp);
      fread(&info.xresolution, sizeof(int),                1, fp);
      fread(&info.yresolution, sizeof(int),                1, fp);
      fread(&info.ncolours,    sizeof(unsigned int),       1, fp);
      fread(&info.impcolours,  sizeof(unsigned int),       1, fp);

      width  = info.width;
      height = info.height;
      bits   = info.bits;
      bytesPerLine =(3 * (width + 1) / 4) * 4;
      imagesize    = bytesPerLine*height;
      int delta    = bytesPerLine - (3 * width);

      printf("\nImagem: %dx%d - Bits: %d", width, height, bits);
      printf("\nbytesPerLine: %d", bytesPerLine);
      printf("\nbytesPerLine: %d", width * 3);
      printf("\ndelta: %d", delta);
      printf("\nimagesize: %d %d", imagesize, info.imagesize);

      //realiza diversas verificacoes de erro e compatibilidade
      if( header.type != 19778 ){
         printf("\nError: Arquivo BMP invalido");
         getchar();
         exit(0);
      }
      if( width*height*3 != imagesize ){
         printf("\nWarning: Arquivo BMP nao tem largura multipla de 4");
         getchar();
      }
      if( info.compression != 0 ){
         printf("\nError: Formato BMP comprimido nao suportado");
         getchar();
         return;
      }
      if( bits != 24 ){
         printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
         getchar();
         return;
      }
      if( info.planes != 1 ){
         printf("\nError: Numero de Planes nao suportado: %d", info.planes);
         getchar();
         return;
      }

      data = new unsigned char[imagesize];
      fseek(fp, header.offset, SEEK_SET);
      fread(data, sizeof(unsigned char), imagesize, fp);

      fclose(fp);
   }

public:
   Bmp(const char *fileName){
       width = height = 0;
       data = NULL;
       if( fileName != NULL && strlen(fileName) > 0 ){
          load(fileName);
       }
       else{
          printf("Error: Invalid BMP filename");
       }
   }

    // Construtor que aceita dados da imagem, largura e altura
    Bmp(unsigned char* imageData, int width, int height) : width(width), height(height) {
        // Aloca memória para armazenar os dados da imagem
        int imageSize = width * height * 3; // Supõe que a imagem tem 3 canais de cores (RGB)
        data = new unsigned char[imageSize];

        // Copia os dados da imagem para o membro 'data'
        std::memcpy(data, imageData, imageSize);
    }

   uchar* getImage(){
      return data;
   }

   int getWidth(void){
      return width;
   }

   int getHeight(void){
      return height;
   }

   void convertBGRtoRGB(){
      unsigned char tmp;
      if( data != NULL ){
         for(int y=0; y<height; y++){
             for(int x=0; x<width*3; x+=3){
                int pos = y*bytesPerLine + x;
                tmp = data[pos];
                data[pos] = data[pos+2];
                data[pos+2] = tmp;
             }
         }
      }
   }

   void render(int x, int y) { //Adicionada depois
        if (data == nullptr) {
            printf("Error: Imagem BMP não carregada\n");
            return;
        }

        int bytesPerPixel = 3; // RGB
        int pos = 0;
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                int r = data[pos++];
                int g = data[pos++];
                int b = data[pos++];
                CV::color(r / 255.0, g / 255.0, b / 255.0);
                CV::point(x + i, y + j);
            }
            pos += (bytesPerLine - width * bytesPerPixel); // Pular bytes extras
        }
    }

   bool Collided(Ponto mouse, int pos_x, int pos_y) {
        int left = pos_x;
        int right = pos_x + width;
        int top = pos_y;
        int bottom = pos_y + height;
        // Verifica se o mouse está dentro dos limites da imagem
        if (mouse.x >= left && mouse.x <= right && mouse.y >= top && mouse.y <= bottom) {
            return true;
        }
        return false;
   }

    void ApplyRotation(float angle) {
            // Converter o ângulo de graus para radianos
        float radianAngle = angle * M_PI / 180.0;

        // Calcular os componentes da matriz de rotação
        float cosTheta = cos(radianAngle);
        float sinTheta = sin(radianAngle);

        // Calcular as coordenadas do centro da imagem
        float centerX = width / 2.0f;
        float centerY = height / 2.0f;

        // Criar um novo array para armazenar a imagem rotacionada
        unsigned char* rotatedData = new unsigned char[imagesize];

        // Loop pelos pixels da imagem original
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Calcular as coordenadas originais do pixel em relação ao centro da imagem
                float xOffset = x - centerX;
                float yOffset = y - centerY;

                // Aplicar a rotação aos offsets
                float rotatedX = xOffset * cosTheta - yOffset * sinTheta + centerX;
                float rotatedY = xOffset * sinTheta + yOffset * cosTheta + centerY;

                // Arredondar para as coordenadas do pixel na imagem original
                int sourceX = round(rotatedX);
                int sourceY = round(rotatedY);

                // Verificar se as coordenadas estão dentro da imagem original
                if (sourceX >= 0 && sourceX < width && sourceY >= 0 && sourceY < height) {
                    // Copiar o pixel da imagem original para a imagem rotacionada
                    int sourceIndex = 3 * (sourceY * width + sourceX);
                    int destIndex = 3 * (y * width + x);
                    rotatedData[destIndex] = data[sourceIndex];
                    rotatedData[destIndex + 1] = data[sourceIndex + 1];
                    rotatedData[destIndex + 2] = data[sourceIndex + 2];
                } else {
                    // Preencher os pixels fora da imagem original com a cor de fundo
                    int destIndex = 3 * (y * width + x);
                    rotatedData[destIndex] = 255; // Vermelho
                    rotatedData[destIndex + 1] = 255; // Verde
                    rotatedData[destIndex + 2] = 255; // Azul
                }
            }
        }

        // Liberar a memória da imagem original
        delete[] data;

        // Atualizar os dados e as dimensões da imagem
        data = rotatedData;

        printf("Giro de %.0f graus\n", angle);
    }

    void FlipVertically() {
        // Implemente o código aqui
        int bytesPerPixel = 3; // RGB
        int halfHeight = height / 2;
        int lineSize = width * bytesPerPixel;
        // Loop para trocar as linhas de cima para baixo
        for (int y = 0; y < halfHeight; ++y) {
            // Calcular as posições de início e fim para a linha atual e a linha correspondente
            int startLine = y * lineSize;
            int endLine = (height - y - 1) * lineSize;
            // Trocar os pixels das linhas
            for (int x = 0; x < lineSize; ++x) {
                // Trocar os pixels da linha atual com os pixels correspondentes na linha oposta
                std::swap(data[startLine + x], data[endLine + x]);
            }
        }
        printf("Imagem espelhada verticalmente\n");
    }

    void FlipHorizontally() {
        int bytesPerPixel = 3; // RGB
        // Loop pelas linhas da imagem
        for (int y = 0; y < height; y++) {
            // Define os índices do início e do fim da linha atual
            int rowStart = y * bytesPerLine;
            int rowEnd = rowStart + width * bytesPerPixel - bytesPerPixel;
            // Loop pelos pixels na metade da largura da imagem
            for (int x = 0; x < width / 2; x++) {
                // Calcula os índices dos pixels no início e no fim da linha
                int pixelStart = rowStart + x * bytesPerPixel;
                int pixelEnd = rowEnd - x * bytesPerPixel;
                // Troca os valores dos pixels entre o início e o fim da linha
                for (int i = 0; i < bytesPerPixel; i++) {
                    std::swap(data[pixelStart + i], data[pixelEnd + i]);
                }
            }
        }
        printf("Imagem espelhada horizontalmente\n");
    }

    void ApplyZoom() {
        // Calcular as novas dimensões da imagem
        int newWidth = width * 2;
        int newHeight = height * 2;
        int newBytesPerLine = (3 * (newWidth + 1) / 4) * 4;
        int newImagesize = newBytesPerLine * newHeight;
        printf("Imagem redimensionada de %dx%d para %dx%d\n", width, height, newWidth, newHeight);
        // Criar um novo array para armazenar a imagem redimensionada
        unsigned char* resizedData = new unsigned char[newImagesize];

        // Loop pelos pixels da imagem original e redimensiona
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                // Calcular as coordenadas originais na imagem original
                int sourceX = x / 2;
                int sourceY = y / 2;

                // Calcular as posições nos arrays de dados original e redimensionado
                int sourceIndex = 3 * (sourceY * width + sourceX);
                int destIndex = 3 * (y * newWidth + x);

                // Copiar o pixel da imagem original para a imagem redimensionada
                resizedData[destIndex] = data[sourceIndex];
                resizedData[destIndex + 1] = data[sourceIndex + 1];
                resizedData[destIndex + 2] = data[sourceIndex + 2];
            }
        }

        // Liberar a memória da imagem original
        delete[] data;

        // Atualizar os dados e as dimensões da imagem
        data = resizedData;
        width = newWidth;
        height = newHeight;
        bytesPerLine = newBytesPerLine;
        imagesize = newImagesize;
    }

    void ApplyReduction() {
        // Calcular as novas dimensões da imagem
        int newWidth = width / 2;
        int newHeight = height / 2;
        int newBytesPerLine = (3 * (newWidth + 1) / 4) * 4;
        int newImagesize = newBytesPerLine * newHeight;

        // Criar um novo array para armazenar a imagem redimensionada
        unsigned char* resizedData = new unsigned char[newImagesize];

        // Loop pelos pixels da imagem original e redimensiona
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                // Calcular as coordenadas originais na imagem original
                int sourceX = x * 2;
                int sourceY = y * 2;

                // Calcular as posições nos arrays de dados original e redimensionado
                int sourceIndex = 3 * (sourceY * width + sourceX);
                int destIndex = 3 * (y * newWidth + x);

                // Média dos pixels nas dimensões reduzidas para evitar distorções
                unsigned char avgR = (data[sourceIndex] + data[sourceIndex + 3] + data[sourceIndex + bytesPerLine] + data[sourceIndex + bytesPerLine + 3]) / 4;
                unsigned char avgG = (data[sourceIndex + 1] + data[sourceIndex + 4] + data[sourceIndex + bytesPerLine + 1] + data[sourceIndex + bytesPerLine + 4]) / 4;
                unsigned char avgB = (data[sourceIndex + 2] + data[sourceIndex + 5] + data[sourceIndex + bytesPerLine + 2] + data[sourceIndex + bytesPerLine + 5]) / 4;

                // Atribuir a média ao pixel na imagem redimensionada
                resizedData[destIndex] = avgR;
                resizedData[destIndex + 1] = avgG;
                resizedData[destIndex + 2] = avgB;
            }
        }

        // Liberar a memória da imagem original
        delete[] data;

        // Atualizar os dados e as dimensões da imagem
        data = resizedData;
        width = newWidth;
        height = newHeight;
        bytesPerLine = newBytesPerLine;
        imagesize = newImagesize;

        printf("Imagem reduzida para %dx%d\n", width, height);
    }

    void rgbImage(char opc){
        if (data != nullptr) {
            for (int i = 0; i < width * height * 3; i += 3) {
                if(opc=='r'){
                    data[i + 1] = 0;    // Componente verde
                    data[i + 2] = 0;    // Componente azul
                }
                else if(opc=='g'){
                    data[i] = 0;        // Componente vermelho
                    data[i + 2] = 0;
                }
                else if(opc=='b'){
                    data[i] = 0;        // Componente vermelho
                    data[i + 1] = 0;    // Componente verde
                }
                else{
                    unsigned char grayValue = static_cast<unsigned char>(0.299 * data[i] + 0.587 * data[i + 1] + 0.114 * data[i + 2]);
                    // Define todos os componentes de cor para o valor de luminância
                    data[i] = grayValue;        // Componente vermelho
                    data[i + 1] = grayValue;    // Componente verde
                    data[i + 2] = grayValue;    // Componente azul
                }
            }
            printf("Apenas o canal %c da imagem foi mantido\n", opc);
        }
    }

    void brightnessImage(bool increase){
        if (data != nullptr) {
            float factor = increase ? 1.1f : 0.9f; // Fator de aumento ou diminuição do brilho
            for (int i = 0; i < width * height * 3; ++i) {
                // Aumenta ou diminui o valor de cada componente RGB do pixel
                int newValue = static_cast<int>(data[i] * factor);
                // Garante que os valores RGB permaneçam no intervalo [0, 255]
                data[i] = static_cast<unsigned char>(std::min(std::max(newValue, 0), 255));
            }
            printf("Brilho da imagem %s\n", increase ? "aumentado" : "diminuido");
        }
    }
};

class BmpManager {
private:
    std::vector<std::pair<Bmp, std::pair<int, int>>> bmps;

public:
    BmpManager() {}

    int ClickedBmp(Ponto mouse) {
        for(unsigned int i = 0; i < bmps.size(); i++){
            Bmp& bmp = bmps[i].first; // Obtém a instância de Bmp do primeiro elemento do par
            int posX = bmps[i].second.first; // Obtém a posição x da imagem
            int posY = bmps[i].second.second; // Obtém a posição y da imagem
            if(bmp.Collided(mouse, posX, posY)){
                return i;
            }
        }
        return -1;
    }

    void moveBmp(int index, const Ponto& newPos) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            auto& bmpInfo = bmps[index];
            int width = bmpInfo.first.getWidth(); // Obtém a largura da imagem
            int height = bmpInfo.first.getHeight(); // Obtém a altura da imagem
            int newPosX = newPos.x - width / 2; // Calcula a nova posição x para centrar a imagem
            int newPosY = newPos.y - height / 2; // Calcula a nova posição y para centrar a imagem
            bmpInfo.second.first = newPosX; // Atualiza a posição x da imagem
            bmpInfo.second.second = newPosY; // Atualiza a posição y da imagem
        }
    }

    void RotateBmp(int index, float angle) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            bmps[index].first.ApplyRotation(angle);
        }
    }

    void FlipBmp(int index, bool isVertically) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size() && isVertically) {
            bmps[index].first.FlipVertically();
        }
        else if (index >= 0 && static_cast<unsigned int>(index) < bmps.size() && !isVertically){
            bmps[index].first.FlipHorizontally();
        }
    }

    void ResizeBmp(int index, bool aumenta) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size() && aumenta) {
            bmps[index].first.ApplyZoom();
        }
        else if(index >= 0 && static_cast<unsigned int>(index) < bmps.size() && !aumenta){
            bmps[index].first.ApplyReduction();
        }
    }

    void RemoveBmp(int index) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            bmps.erase(bmps.begin() + index); // Remove o elemento da lista na posição 'index'
        }
    }

    void render() {
        for (auto& bmpInfo : bmps) {
            Bmp& bmp = bmpInfo.first;
            int x = bmpInfo.second.first; // Obtém a posição x da imagem
            int y = bmpInfo.second.second; // Obtém a posição y da imagem
            bmp.render(x, y); // Renderiza a imagem na posição (x, y)
        }
    }

    void saveData(const std::string& nomeArquivo, int criptografia) {
        std::ofstream arquivo(nomeArquivo);
        if (!arquivo) {
            std::cerr << "Erro ao abrir arquivo" << std::endl;
            return;
        }
        for (auto& bmpInfo : bmps) {
            Bmp& bmp = bmpInfo.first;
            std::pair<int, int>& pos = bmpInfo.second;

            arquivo << pos.first + criptografia << " " << pos.second + criptografia << " "; // Salva a posição da imagem com criptografia

            int width = bmp.getWidth();
            int height = bmp.getHeight();
            int imageSize = width * height * 3;
            uchar* imageData = bmp.getImage();

            arquivo << width + criptografia << " " << height + criptografia << " " << imageSize + criptografia << " "; // Salva as dimensões da imagem com criptografia

            for (int i = 0; i < imageSize; ++i) {
                arquivo << static_cast<int>(imageData[i]) + criptografia << " "; // Salva os dados da imagem BMP com criptografia
            }
            arquivo << std::endl;
        }
        arquivo.close();
        printf("Estado do programa salvo.\n");
    }

    void loadData(const std::string& nomeArquivo, int criptografia) {
        std::ifstream arquivo(nomeArquivo);
        if (!arquivo) {
            std::cerr << "Erro ao abrir arquivo" << std::endl;
            return;
        }

        int posX, posY, width, height, imageSize;
        while (arquivo >> posX >> posY >> width >> height >> imageSize) {
            posX -= criptografia; // Descriptografa a posição da imagem
            posY -= criptografia;
            width -= criptografia; // Descriptografa as dimensões da imagem
            height -= criptografia;
            imageSize -= criptografia; // Descriptografa o tamanho da imagem

            uchar* imageData = new uchar[imageSize];
            for (int i = 0; i < imageSize; ++i) {
                int byteValue;
                arquivo >> byteValue;
                imageData[i] = static_cast<uchar>(byteValue - criptografia); // Descriptografa os dados da imagem
            }

            Bmp bmp(imageData, width, height);
            delete[] imageData;
            bmp.ApplyZoom();
            bmp.ApplyReduction();
            bmps.emplace_back(std::make_pair(bmp, std::make_pair(posX, posY)));
        }

        arquivo.close();
    }

    void LoadBmp(const std::string& filePath) {
        Bmp newBmp(filePath.c_str());
        newBmp.convertBGRtoRGB();
        bmps.emplace_back(std::make_pair(newBmp, std::make_pair(50, 50)));
        printf("\nImagem carregada\n");
    }

    void rgbBmpImage(int index, char opc) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            bmps[index].first.rgbImage(opc);
        }
    }

    void brightnessBmpImage(int index, bool opc) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            bmps[index].first.brightnessImage(opc);
        }
    }

    void plotHistogram(int index) {
        if (index >= 0 && static_cast<unsigned int>(index) < bmps.size()) {
            Bmp& bmp = bmps[index].first;
            int width = bmp.getWidth();
            int height = bmp.getHeight();

            // Inicializa os histogramas com zeros
            std::vector<int> redHistogram(64, 0);
            std::vector<int> greenHistogram(64, 0);
            std::vector<int> blueHistogram(64, 0);
            std::vector<int> luminanceHistogram(64, 0);

            // Calcula os histogramas para os canais vermelho, verde e azul
            uchar* imageData = bmp.getImage();
            for (int i = 0; i < width * height * 3; i += 3) {
                int redValue = static_cast<int>(imageData[i]);
                int greenValue = static_cast<int>(imageData[i + 1]);
                int blueValue = static_cast<int>(imageData[i + 2]);
                float Y = 0.299 * redValue + 0.587 * greenValue + 0.114 * blueValue;
                int luminanceBin = static_cast<int>(Y / 4);
                // Normaliza os valores dos canais para o intervalo de 0 a 63
                int redBin = redValue / 4;
                int greenBin = greenValue / 4;
                int blueBin = blueValue / 4;
                redHistogram[redBin]++;
                greenHistogram[greenBin]++;
                blueHistogram[blueBin]++;
                luminanceHistogram[luminanceBin]++;
            }

            // Encontra o maior valor nos histogramas para normalização
            int maxFrequency = std::max({*std::max_element(redHistogram.begin(), redHistogram.end()),
                                         *std::max_element(greenHistogram.begin(), greenHistogram.end()),
                                         *std::max_element(blueHistogram.begin(), blueHistogram.end()),
                                         *std::max_element(luminanceHistogram.begin(), luminanceHistogram.end())});

            // Desenha um retângulo preto que cobre o gráfico
            CV::color(0, 0, 0); // Cor preta
            CV::rect(0, 0, 256, 100); // Retângulo que cobre o gráfico do canal vermelho
            CV::rect(0, 106, 256, 206); // Retângulo que cobre o gráfico do canal verde
            CV::rect(0, 212, 256, 312); // Retângulo que cobre o gráfico do canal azul
            CV::rect(0, 318, 256, 418); // Retângulo que cobre o gráfico da luminância

            // Desenha os histogramas de cada canal RGB
            int histogramHeight = 100; // Altura do histograma
            //int histogramWidth = 64; // Largura do histograma
            int binWidth = 4; // Largura de cada barra no histograma (256 / 64)
            for (int i = 0; i < 64; i++) {
                // Normaliza a altura de cada barra nos histogramas
                int redBarHeight = static_cast<int>(static_cast<double>(redHistogram[i]) / maxFrequency * histogramHeight);
                int greenBarHeight = static_cast<int>(static_cast<double>(greenHistogram[i]) / maxFrequency * histogramHeight);
                int blueBarHeight = static_cast<int>(static_cast<double>(blueHistogram[i]) / maxFrequency * histogramHeight);
                int luminanceBarHeight = static_cast<int>(static_cast<double>(luminanceHistogram[i]) / maxFrequency * histogramHeight);

                // Calcula as coordenadas dos cantos opostos dos retângulos para cada canal
                float x = i * binWidth;

                // Renderiza os retângulos para cada canal
                // Vermelho
                CV::color(1, 0, 0); // Vermelho
                CV::rect(x, 0, x + binWidth, redBarHeight);
                // Verde
                CV::color(0, 1, 0); // Verde
                CV::rect(x, 106, x + binWidth, 106 + greenBarHeight);
                // Azul
                CV::color(0, 0, 1); // Azul
                CV::rect(x, 212, x + binWidth, 212 + blueBarHeight);
                // Luminância
                CV::color(0.5f, 0.5f, 0.5f); // Branco (luminância)
                CV::rect(x, 318, x + binWidth, 318 + luminanceBarHeight);
            }
        }
    }






};
#endif
