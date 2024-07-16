public class TestPoint {
    public static void main(String[] args) {
        Point p1 = new Point();
        Point p2 = new Point(4.0, 2.5);
        
        System.out.printf("Distancia: %f", p1.Dist(p2));
    }
}