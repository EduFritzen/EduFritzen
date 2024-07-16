public class Jogador {
    
    public int num=0;
    private int vidas=0;
    final private int maxVidas=3;
    static boolean alerta=false;
    
    public Jogador(int num){//método construtor, não tem retorno, precisa ter o mesmo nome da classe
        this.num=num;//this é usado para referenciar um atributo externo (fora do método)
        this.vidas=1;
        System.out.printf("Jogador criado %d\n", num);
    }
    
    public int getVidas(){//um método para retornar um atributo privado
        return this.vidas;
    }
    
    public void setVidas(int vidas){//pq existe privado então? existe 
        if(vidas > maxVidas){      //um controle maior dessa forma sobre o atributo
            this.vidas=maxVidas;
        }
        else if(vidas < 0){
            this.vidas=0;
        }
        else{
            this.vidas=vidas;
        }
    }
}