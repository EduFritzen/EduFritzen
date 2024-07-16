import java.util.Arrays;

public class Ex2
{
	public static void main(String[] args) {
        int[] num={9,3,4,5,2,6,7,1,8};
        int[] vet= new int [10];
        Arrays.sort(num);
        Arrays.fill(vet, 10);
        
        for(int n:num){ //forma mais simples de ler os elementos de um array
            System.out.printf("%d ", n);
        }
        System.out.print("\n");
        for(int n:vet){ //forma mais simples de ler os elementos de um array
            System.out.printf("%d ", n);
        }
        System.out.print("\n");
        
        System.arraycopy(num, 1, vet, 3, 5);//origem, a partir de, destino, a partir de, até qual ser trocado

        for(int n:vet){ //forma mais simples de ler os elementos de um array
            System.out.printf("%d ", n);
        }
        
        if(Arrays.equals(num, vet))
            System.out.print("\nOs vetores são iguais");
        else
            System.out.print("\nOs vetores não são iguais");
            
        //como usar o Arrays.binarySearch
    	Arrays.sort(vet); //precisa estar ordenado para funcionar
    	int a=Arrays.binarySearch(vet,3);
    	System.out.printf("%d ", a);
    	if(a>0)//se a for um número maior que 0 o elemento está no array
    	    System.out.print("\nO elemento 3 está no vetor");
    	else
    	    System.out.print("\nO elemento 3 não está no vetor");
	}
}