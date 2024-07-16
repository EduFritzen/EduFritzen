import java.util.Scanner;

public class Ex1
{
	public static void main(String[] args) {
   
        Scanner scan = new Scanner(System.in);
        
        int n1,n2,res;
        final int NUM=5;
        String nome;
        
        System.out.print("Digite seu nome: ");
        nome=scan.nextLine();
        System.out.print("Digite um numeral: ");
        n1=scan.nextInt();
        System.out.print("Digite outro numeral: ");
        n2=scan.nextInt();
        res=n1+n2;
        System.out.printf("%s a soma de %d com %d eh igual a %d\n",nome,n1,n2,res);
        
        if(n1<NUM){
            System.out.print("n1 eh menor que a constante");
        }
        else{
            System.out.print("n1 eh maior que a constante");
        }
        
        int[] vet= new int[5];
        int[] vet2={1,2,3,4};
        final int tam=vet2.length;
        vet[0]=2;
        System.out.printf("  %d", vet[0]);
        System.out.printf("  %d", tam);
	}
}