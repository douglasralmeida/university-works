package agendamento;

import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Data {
	LocalDate data;
	ArrayList<Atendimento> atendimentos;
	
	public Data(LocalDate data) {
		this.data = data;
		this.data.format(DateTimeFormatter.ISO_LOCAL_DATE);
		atendimentos = new ArrayList<Atendimento>();
	}
	
	public ArrayList<Atendimento> getHorarios() {
		return this.atendimentos;
	}

	public void gerarHorarios() {
		LocalTime horaTemp = LocalTime.of(8, 0);
		
		while (horaTemp.getHour() < 17) {
			Atendimento atendimento = new Atendimento(horaTemp);
			atendimentos.add(atendimento);
			horaTemp = horaTemp.plusMinutes(30);
		}
	}
	
	public LocalDate getDia() {
		return data;
	}
	
	public String toString() {
		return data.toString();
	}

}
