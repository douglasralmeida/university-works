public class Circle extends Point{
	private double radius;
	private String color;
	private double length;
	
	public Circle() {
		super();
		super.setCoordenadas(0, 0);
		this.radius = 1.0;
		this.color = "red";
		this.length = this.radius * 2 * Math.PI; 
	}
	
	public Circle(double radius) {
		this();
		this.radius = radius;
	}
	
	public Circle (double radius, String color) {
		this(radius);
		this.color = color;
	}
	
	public String getColor() {
		return this.color;
	}
	
	public double getLength() {
		return this.length;
	}
	
	public double getRadius() {
		return this.radius;
	}
	
	public double getArea() {
		return this.radius*this.radius*Math.PI;
	}
	
	public void setRadius(double radius) {
		this.radius = radius;
		this.length = radius * 2 * Math.PI;
	}

	public void setColor(String color) {
		this.color = color;
	}
	
	public void showCentro() {
		System.out.println("x=" + getx() + " y=" + gety());
	}
	
	public String toString() {
		return "Circulo: raio=" + this.radius + " cor=" + this.color + " comprimento=" + this.length + " centro=(" + super.toString() + ")";	
	}
}