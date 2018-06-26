
public class AlarmeProtecao implements Alarme {
	ServicoExterno servicoExterno;
	public AlarmeProtecao() {
		servicoExterno = new Policia();
	}
	
	@Override
	public void chamarServicoExterno() {
		servicoExterno.chamar();		
	}}
