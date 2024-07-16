public class Ex4
{
	public static void main(String[] args) {
		System.out.println(soma(2,3));
		System.out.println(super_soma(2,3,6,7,2));
		mensagem("Oi bebe!");
	}
	
	public static int soma(int n1, int n2){
	    return (n1+n2);
	}
	
	public static int super_soma(int... num){
	    int res=0;
	    for(int i:num){
	        res=res+i;
	    }
	    return res;
	}

	public static void mensagem(String str){
	    System.out.print(str);
	}
}