import java.util.ArrayList;
import java.util.List;

public class Central {
	private List<Alarme> alarmes = new ArrayList<Alarme>();
	private Edificio edificio = new Edificio();

	public void adicioanarAlarmeFogo(AreaEdificio area) {
		AlarmeFogo alarme = new AlarmeFogo();
		area.adicionarAlarme(alarme);
	}
	
	public void adicioanarAlarmeProtecao(AreaEdificio area) {
		AlarmeProtecao alarme = new AlarmeProtecao();
		area.adicionarAlarme(alarme);
	}
}
