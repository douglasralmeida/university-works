import java.util.ArrayList;
import java.util.List;

public class AreaEdificio {
	private List<Alarme> alarmes = new ArrayList<Alarme>();
	private EquipamentoCombate equipamento = null;
	private List<Porta> portas = new ArrayList<Porta>();
	private Boolean zonacritica;
	
	public AreaEdificio(Boolean eZonaCritica) {
		zonacritica = eZonaCritica;
	}
	
	public void adicionarAlarme(Alarme alarme) {
		if (alarmes.size() < 2)
			alarmes.add(alarme);
	}
}
