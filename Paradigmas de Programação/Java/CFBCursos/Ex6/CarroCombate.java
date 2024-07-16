public class CarroCombate extends Carro{
    private final int MAX_ARMAMENTO=100;
    private final int MIN_ARMAMENTO=0;
    private int qtdeArmamento;
    
    public CarroCombate(String nome, int blindagem){
        super(nome);//o super chama o construtor da classe pai
        setArmamento(true);
        setBlindagem(blindagem);
        this.qtdeArmamento=100;
    }
    
    public void setQtdeArmamento(int qtdeArmamento){
        this.qtdeArmamento+=qtdeArmamento;
        if(this.qtdeArmamento > MAX_ARMAMENTO){
            this.qtdeArmamento=MAX_ARMAMENTO;
        }
        if(this.qtdeArmamento > MIN_ARMAMENTO){
            this.qtdeArmamento=MIN_ARMAMENTO;
        }
    }
    
    public int getQtdeArmamento(){
        return this.qtdeArmamento;
    }
    
    public void atirar(){
        if(this.qtdeArmamento > MIN_ARMAMENTO){
            setQtdeArmamento(-1);
        }
        else{
            System.out.println("Sem armamento");
        }
    }
    
    public void info(){
        super.info();
        System.out.printf("Qtde.Arm...:%d\n", this.qtdeArmamento);
    }
}