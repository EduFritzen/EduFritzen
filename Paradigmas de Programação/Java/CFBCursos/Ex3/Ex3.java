import java.security.SecureRandom;

public class Ex3
{
	public static void main(String[] args) {
		int[][] matriz=new int[3][3];
		
		for(int i=0;i<3;i++){
		    for(int j=0;j<3;j++){
		        matriz[i][j]=new SecureRandom().nextInt(10);
		        System.out.printf("%2d ", matriz[i][j]);
		    }
		    System.out.print("\n");
		}
	}
}