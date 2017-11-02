
public class Point {
	private double x;
	private double y;
	
	public void setCoordenadas(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public int getx() {
		return (int) x;
	}
	
	public int gety() {
		return (int) y;
	}
	
	public String toString() {
		return "Coordenada: x=" + this.x + " y=" + this.y;
	}
}
