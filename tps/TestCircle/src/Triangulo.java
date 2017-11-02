public class Triangulo extends Point{
	private double comprimentoa;
	private double comprimentob;
	private double comprimentoc;
	public Triangulo(int comprimentoa, int comprimentob, int comprimentoc) throws Exception {
		super();
		
		if (comprimentoa <= 0 || comprimentob <= 0 || comprimentoc <= 0)
			throw new Exception("Informado lado com comprimento negativo ou igual a zero.");
		if (Math.abs(comprimentob - comprimentoc) < comprimentoa && comprimentob + comprimentoc > comprimentoa) {
			this.comprimentoa = comprimentoa;
			this.comprimentob = comprimentob;
			this.comprimentoc = comprimentoc;
		} else
			throw new Exception("Triangulo invalido.");
	}
	
	public int getPerimetro() {
		return (int) (this.comprimentoa + this.comprimentob + this.comprimentoc);
	}
	
	public double getArea() {
		double sp = getPerimetro()/2;
		
		return Math.sqrt(sp*(sp-comprimentoa)*(sp-comprimentob)*(sp-comprimentoc));
	}
	
	public String getTipo() {
		if (this.comprimentoa == this.comprimentob && this.comprimentob == this.comprimentoc)
			return "triangulo equilatero";
		else if (this.comprimentoa == this.comprimentob || this.comprimentob == this.comprimentoc || this.comprimentoa == this.comprimentoc)
			return "triangulo isosceles";
		else return "triangulo escaleno";
	}
	
	public String toString() {
		return "Triangulo: lados="+comprimentoa+";"+comprimentob+";"+comprimentoc+" area="+getArea()+" perimetro="+getPerimetro()+" tipo= "+getTipo() + " centro=(" + super.toString() + ")";
	}
}