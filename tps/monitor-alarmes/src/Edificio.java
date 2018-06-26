import java.util.ArrayList;
import java.util.List;

public class Edificio {
	private List<AreaEdificio> areas= new ArrayList<AreaEdificio>();

	public void adicionarAlarme(AreaEdificio area, Alarme alarme) {
		area.adicionarAlarme(alarme);
	}
	
	public void adicionarArea(Boolean zonaCritica) {
		AreaEdificio novaArea = new AreaEdificio(zonaCritica);
		areas.add(novaArea);		
	}

	public List<AreaEdificio> getAreas() {
		return areas;
	}
}
