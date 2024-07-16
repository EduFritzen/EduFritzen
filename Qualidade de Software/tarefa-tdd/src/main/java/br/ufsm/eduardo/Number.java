package br.ufsm.eduardo;

public class Number {
	
	private int value;
	
	public Number(int value) {
		super();
		this.value = value;
	}
	
	public boolean isEven() {
		if (value % 2 == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public boolean isOdd() {
		if (!isEven()) {
			return true;
		}
		else {
			return false;
		}
	}
}
