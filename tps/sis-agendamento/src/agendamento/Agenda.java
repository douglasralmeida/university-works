package agendamento;

import java.time.LocalDate;
import java.util.ArrayList;
import entidades.Servico;
import pessoa.Atendente;

public class Agenda {
	ArrayList<Data> datas;
	Servico servico;
	Atendente atendente;
	
	public Agenda(Servico servico, Atendente atendente) {
		this.atendente = atendente;
		this.servico = servico;
		datas = new ArrayList<Data>();
	}
	
	public void gerarAtendimentos() {
		LocalDate datatemp = LocalDate.of(LocalDate.now().getYear(), LocalDate.now().getMonth(), 1);
		int mes = datatemp.getMonthValue();
		
		while (datatemp.getMonthValue() == mes) {
			if (datatemp.getDayOfWeek().getValue() > 1 && datatemp.getDayOfWeek().getValue() < 7) {
				Data data = new Data(datatemp);
				data.gerarHorarios();
				datas.add(data);
			}
			datatemp = datatemp.plusDays(1);
		}
	}
	
	public ArrayList<Data> getDatas() {
		return this.datas;
	}
	
	public Servico getServico() {
		return this.servico;
	}
}
