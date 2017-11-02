public class TestCircle {
	
	public static void main(String[] args) {
		Triangulo t1, t2, t3, t4;
		
		try {
			t1 = new Triangulo(3, 4, 5);
			System.out.println(t1);
			
			t2 = new Triangulo(3, 4, 3);
			System.out.println(t2);
			
			t3 = new Triangulo(3, 3, 3);
			System.out.println(t3);
			
			t4 = new Triangulo(0, 3, 4);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	} 		
}