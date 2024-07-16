class AnimalRunner extends Thread {
	protected String name;
    protected String animal;

	public AnimalRunner(String name) {
		this.name = name;
	}

	private void runLikeAnimal() {
		System.out.println(name + " is running fast");
	}

	public void run() {
		System.out.println(name + " " + animal + " is at the start of the race!");
		for (int pos = 10; pos > 0; pos--) {
			runLikeAnimal();
			System.out.println(name + " is at position " + pos);
		}
		System.out.println(name + " " + animal + " finished the race!");
	}
}

class Rabbit extends AnimalRunner {

	public Rabbit(String name) {
		super(name);
		animal="Rabbit";
		run();
	}

}

class Turtle extends AnimalRunner {

	public Turtle(String name) {
		super(name);
		animal="Turtle";
		run();
	}
    
}

class Horse extends AnimalRunner {

	public Horse(String name) {
		super(name);
		animal="Horse";
		run();
	}
    
}

class BetterThreadRace {
	public static void main(String[] args) {
		Rabbit r = new Rabbit("Snowball");
		Turtle t = new Turtle("Donatello");
        Horse s = new Horse("Jucelino");
		r.start();
		t.start();
        s.start();
	}
}