public class Ex5
{
	public static void main(String[] args) {
		
		System.out.printf("Alerta: %s\n", Jogador.alerta ? "sim" : "não");
		//foi acessado o alerta sem instanciar qualquer jogador
		
		Jogador j1 = new Jogador(1);//processo de instanciação da classe Jogador
		Jogador j2 = new Jogador(2);//o new é o responsável pela instanciação
		                            //é ele que vai alocar na heap a memória 
		                            //necessária para o objeto.
	    //j1.num=10;
	    //j2.num=5;
	    System.out.printf("num:%d %d",j1.num, j2.num);//os objetos são independentes
	                                              //um do outro
        
        //j1.vidas=3; error:letra has private access
        System.out.printf("\n%d ",j1.getVidas());
        j1.setVidas(100);//como não é permitido 100, ele seta em 3
        System.out.printf("%d\n",j1.getVidas());
        
        Jogador.alerta=true;//se modificado um atribudo static, a modificação vale para todos os objetos instanciados
        System.out.printf("Alerta: %s\n", Jogador.alerta ? "sim" : "não");
	}
}
/*todos os elementos static, atributos ou propriedades, tem o mesmo local
de memória e vais ser comum para todos os objetos da classe e não é 
necessário instanciar uma classe para chamar um método ou atributo static*/