class CorCar {

    private String cor="Preto";

    public CorCar(String cor){
        this.cor=cor;
    }
}

class PrecoCar {
    final private int PMIN=5000;
    private int preco=PMIN;

    public PrecoCar(int p){
        if(p<PMIN){
            this.preco=PMIN;
        }
        else{
            this.preco=p;
        } 
    }

    public int GetPreco(){
        return this.preco;
    }
}

class Comissao {

    public Comissao(int c){
        double x = c * 0.05;
        System.out.printf("Comissao: %f", x);
    }
}

class Carro {
    public static void main(String[] args) {
        CorCar c1 = new CorCar("Azul");
        PrecoCar p1 = new PrecoCar(1000);
        Comissao cm1 = new Comissao(p1.GetPreco());

    }    
}
