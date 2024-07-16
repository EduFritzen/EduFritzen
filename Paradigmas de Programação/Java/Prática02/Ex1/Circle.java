public class Circle {
    private double x;
    private double y;
    private double r;
    
    public Circle() {
       x = y = r = 0.0;
       System.out.println("New Circle");
    }
    public Circle(double x, double y, double r) {
       this.x=x;
       this.y=y;
       this.r=r;
    }
    public double area() {
       return Math.PI * r * r;
    }
    public void setRadius(double radius){
       this.r=radius;
    }
    // O método main é chamado pela JVM para iniciar a execução de um programa.
    // Geralmente, este método fica em uma classe separada, com acesso às demais classes.
    public static void main(String[] args) {
       Circle c = new Circle();
       Circle c2 = new Circle();
       Circle c3 = new Circle(2.1,3.2, 2.7);
       c.setRadius(2.5);
       System.out.println("Area do circulo: " + c.area());
       c2.setRadius(5.0);
       System.out.println("Area do circulo 3: " + c3.area());
       c.r=0.5;

    }
    
 }