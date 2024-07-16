//Exemplo de classe usando a herança de veiculo
public class Carro extends Veiculo{
    final private Double PMIN= 2500.00;
    private Double preco;


    public Carro(int codigo, String modelo){
        super(codigo, modelo);
        this.preco=PMIN;
    }

    public Carro(int codigo, String modelo, Double preco){
        super(codigo, modelo);
        this.preco=preco;
    }

    public double getPreco(){
        return this.preco;
    }

    public static void main(String[] args){
        
        Carro c1 = new Carro(202201, "Gol");
        Carro c2 = new Carro(202202, "Cobalt", 35000.00);

        System.out.println(c1.getPreco());
        System.out.println(c2.getPreco());
        System.out.println(c1.getModelo());
    }
}