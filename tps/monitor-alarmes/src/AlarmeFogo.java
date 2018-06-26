
public class AlarmeFogo implements Alarme {
	ServicoExterno servicoExterno;
	public AlarmeFogo() {
		servicoExterno = new Bombeiros();
	}
	
	@Override
	public void chamarServicoExterno() {
		servicoExterno.chamar();		
	}
}
