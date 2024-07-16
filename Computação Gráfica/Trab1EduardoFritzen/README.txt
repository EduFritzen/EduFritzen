Trabalho 1 – Editor de imagens
Aluno: Eduardo Adriano Fritzen

Quesitos Obrigatórios Implementados:
- Carregar imagens colorida (RGB) em formato BMP.
- Mover cada imagem individualmente dentro da canvas2D com uso do mouse.
- Reexibir a imagem selecionada, em uma quarta imagem, das seguintes formas: Em canais separados RGB e Em tons de cinza (luminância)
- Rotacionar a imagem no eixo vertical e horizontal.
- Plotar o histograma de cada canal RGB e da luminância. 
- Botões que carregam a imagem “a.bmp”, “b.bmp” e “c.bmp”. 

Quesitos Bônus Implementados:
- Aplicar uma rotação qualquer a imagem. A rotação deve ser feita com o uso do mouse.
- Redimensionar a imagem com o uso do mouse.
- Clarear ou escurecer  
- Display de 7 segmentos para exibição de números (inteiros e reais), letras, hora, etc.(texto: "TRABALHO CG - 7 SEG DISPLAY - 05.04")
- Salvar e carregar o estado do programa.
- Adicionar criptografia ao arquivo que salva o estado do programa. (simples, mas funciona)
- Adicionar responsividade ao programa (coloque em tela cheia para testar). 
- Deletar a imagem selecionada.
- Espelhar a imagem no eixo vertical e horizontal.* (Não achei uma resposta se rotacionar e espelhar nos dois eixos são a mesma coisa, por tanto, fiz as 5 opções de manipulação de imagem que aparecem no Paint{girar 90°, -90° e 180°; inverter verticalmente e horizontalmente}, dessa forma, coloquei como quesito bônus, mas não tenho certeza).

Botões: Foi implemententado alguns botões na interface do programa, mas para acessar todas as funcionalidade é necessário usar o teclado.

Lista de instruções para interagir com o programa:

Ao clicar na imagem selecionada com o BOTÃO ESQUERDO DO MOUSE você pode executar os seguintes comandos

	Com o BOTÃO ESQUERDO DO MOUSE pressionado -> mexer a figura pela tela.
	Com o BOTÃO DIREITO DO MOUSE -> aplicar uma rotação de 90 graus.
	Com a WHEEL DO MOUSE PARA CIMA -> aplicar um redimensionamento (aumento) da imagem. 
	Com a WHEEL DO MOUSE PARA BAIXO -> aplicar um redimensionamento (redução) da imagem.
	Com a tecla SETA PARA A DIREITA(->) -> aplicar um redimensionamento (aumento) da imagem.
	Com a tecla SETA PARA A ESQUERDA(<-) -> aplicar um redimensionamento (redução) da imagem. 
	Com a tecla SETA PARA CIMA -> aumenta o brilho da imagem.
	Com a tecla SETA PARA BAIXO -> diminui o brilho da imagem. 
	Com a tecla A -> aplicar uma rotação de -90 graus.
	Com a tecla S -> aplicar uma rotação de 180 graus.
	Com a tecla D -> aplicar uma rotação de 90 graus.
	Com a tecla Q -> aplicar um espelhamento vertical.
	Com a tecla W -> aplicar um espelhamento horizontal.
	Com a tecla H -> plota o histograma da imagem. *Tive dificuldade para implementar, então fiz uma gambiarra, é necessário segurar a letra H para plotar o histograma
	Com a tecla J -> carrega a img1.
	Com a tecla K -> carrega a img2.
	Com a tecla L -> carrega a img3.
	Com a tecla R -> reexibir a imagem somente com o canal red.
	Com a tecla G -> reexibir a imagem somente com o canal green.
	Com a tecla B -> reexibir a imagem somente com o canal blue.
	Com a tecla Y -> reexibir a imagem em tom de cinza.
	Com a tecla DEL -> deletar a imagem selecionada.
	Com a tecla CTRL+S -> salvar o estado do programa.
	Com a tecla ESC -> sair do programa.



Documentação: deixei no cabeçalho a ideia de cada arquivo e em cada método um comentário de sua função.

Clean code: nomeei os métodos, classes e variáveis em inglês de acordo com suas incumbências. Os comentários deixei em português.

Estado do programa: Deixei salvo bastante imagens, delete algumas pra ter espaço.