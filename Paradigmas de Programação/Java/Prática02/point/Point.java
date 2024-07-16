public class Point {
    private double x;
    private double y;

    public Point(){
        x = 0.0;
        y = 0.0;
    }

    public Point(Double dx, double dy){
        x = dx;
        y = dy;
    }

    public void Desloc(Double dx, Double dy){
        x = x + dx;
        y = y + dy;
    }

    public double Dist(Point p){
        return(Math.sqrt((p.x-x)*(p.x-x) + (p.y-y)*(p.y-y)));
    }
}