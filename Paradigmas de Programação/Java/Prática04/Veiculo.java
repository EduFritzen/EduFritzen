public class Veiculo {
    private int codigo;
    private String modelo;
    static int qtdeVeiculo=0;

    public Veiculo(int codigo, String modelo){
        this.codigo=codigo;
        this.modelo=modelo;
        qtdeVeiculo++;
        System.out.printf("Veiculo criado!(%d)\n", qtdeVeiculo);
    }

    public String getModelo(){
        return this.modelo;
    }

    public int getCodigo(){
        return this.codigo;
    }

}
