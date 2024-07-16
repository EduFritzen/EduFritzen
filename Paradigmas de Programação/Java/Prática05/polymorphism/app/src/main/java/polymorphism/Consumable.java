package polymorphism;

public class Consumable extends GameItem {
  
  private String useTo;
  private boolean consumed;

  public Consumable(String name, double weight, String useTo) {
    super(name, weight);
    this.useTo = useTo;
    this.consumed = false;
  }
  
  public void consume() {
    consumed = true;
    setWeight(0);
  }
  
  public boolean isConsumed() {
    return consumed;
  }

  public String toString() {
    return super.toString() + ", " + "Consumed: " + consumed;
  }
}