package br.ufsm.eduardo;
import java.util.HashMap;

public class ConversorRomano {
	
	private static HashMap<Character, Integer> tabela=new HashMap<Character, Integer>(){{
		put('I',1);
		put('V',5);
		put('X',10);
		put('L',50);
		put('C',100);
		put('D',500);
		put('M',1000);
	}
	};
	
	public int converte(String numeroRomano) {
		int acumulador = 0;
		int ultimoVizinhoDadireita = 0;
		for(int i=numeroRomano.length()-1;i>=0;i--) {
			int atual = tabela.get(numeroRomano.charAt(i));
			int multiplicador = 1;
			if(atual<ultimoVizinhoDadireita) multiplicador = -1;
				acumulador += tabela.get(numeroRomano.charAt(i)) * multiplicador;
				ultimoVizinhoDadireita = atual;
		}
		return acumulador;
	}
}
