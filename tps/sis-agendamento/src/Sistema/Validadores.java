package sistema;
public class Validadores {
	private static final int[] pesoCpf = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

	private static int calcularDigito(String str, int[] peso) {
	    int digito;  
		int i;
	    int soma = 0;
	    
	    for (i = str.length() - 1; i >= 0; i--) {
	         digito = Integer.parseInt(str.substring(i, i + 1));
	         soma += digito * peso[peso.length - str.length() + i];
	    }
	    soma = 11 - soma % 11;
	    
	    if (soma > 9)
	    	return 0;
	    return soma;
	   }
	
	public static boolean ehValidoCPF(String cpf) {
	    if ((cpf==null) || (cpf.length()!=11))
	    	return false;

	    Integer digito1 = calcularDigito(cpf.substring(0,9), pesoCpf);
	    Integer digito2 = calcularDigito(cpf.substring(0,9) + digito1, pesoCpf);
	    
	    return cpf.equals(cpf.substring(0,9) + digito1.toString() + digito2.toString());
	   }
}
