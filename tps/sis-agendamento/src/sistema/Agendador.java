package sistema;

import java.time.LocalDate;
import java.util.ArrayList;

import agendamento.Agenda;
import agendamento.Atendimento;
import agendamento.Data;
import entidades.Servico;
import pagamentos.Pagamento;
import pessoa.Atendente;
import pessoa.Cliente;

public class Agendador {
	
	Cliente cliente = null;
	Servico servico = null;
	ArrayList<Data> datasDisponiveis = null;
	Agenda agenda = null;
	Data data = null;
	Atendimento horario = null;
	Atendente atendente = null;
	Pagamento pagamento = null;

	public Agendador() {
		
	}
	
	public void reiniciar() {
		cliente = null;
		servico = null;
		datasDisponiveis = null;
		agenda = null;
		data = null;
		horario = null;
		atendente = null;
		pagamento = null;
	}
	
	public void escolherCliente(Cliente cliente) throws AgendamentoException {
		this.cliente = cliente;
		servico = null;
		datasDisponiveis = null;
		agenda = null;
		data = null;
		horario = null;
		atendente = null;
		pagamento = null;
	}
	
	public void escolherServico(Servico servico) throws AgendamentoException {
		if (cliente == null)
			new AgendamentoException("Antes de escolher um serviço, você deve escolher um cliente primeiro.");
		
		this.servico = servico;
		datasDisponiveis = getDatas();
		if (datasDisponiveis.isEmpty())
			new AgendamentoException("Não existem horários disponíveis para esse serviço em nenhuma data.");
		
		data = null;
		horario = null;
		pagamento = null;
	}
	
	private ArrayList<Data> getDatas() throws AgendamentoException {
		int i;
		int max = Aplicacao.getAgendas().getSize();
		Agenda agendaAtual;
		
		if (servico == null)
			new AgendamentoException("Antes de listar os dias para agendamento, você deve escolher um serviço primeiro.");
		
		datasDisponiveis = new ArrayList<Data>();
		for (i = 0; i < max; i++) {
			agendaAtual = Aplicacao.getAgendas().getAgenda(i);
			if (agendaAtual.getServico() == servico)
				datasDisponiveis.addAll(agendaAtual.getDatas());
		}
		
		return datasDisponiveis;
	}
	
	public void escolherData(LocalDate data) throws AgendamentoException {
		int i;
		int max = datasDisponiveis.size();
		
		if (servico == null)
			new AgendamentoException("Antes de escolher um dia para agendamento, você deve escolher um serviço primeiro.");
		
		if (data.isBefore(LocalDate.now()))
			new AgendamentoException("Não é possível agendar um atendimento para um dia anterior ao dia de hoje.");
		
		for (i = 0; i < max; i++) {
			if (datasDisponiveis.get(i).getDia().isEqual(data))
				this.data = datasDisponiveis.get(i);
		}
		
		if (this.data == null)
			new AgendamentoException("Não existe atendimento na data escolhida.");
		
		horario = null;
		pagamento = null;
	}
	
	public void escolherHorario(Atendimento horario) throws AgendamentoException {
		if (data == null)
			new AgendamentoException("Antes de escolher um horário para agendamento, você deve escolher um dia para atendimento primeiro.");
		
		this.horario = horario;
		pagamento = null;
	}
	
	public void escolherPagamento(Pagamento pagamento)  throws AgendamentoException {
		if (horario == null)
			new AgendamentoException("Antes de escolher uma forma de pagamento, você deve escolher um horário de atendimento primeiro.");

		this.pagamento = pagamento;
	}
	
	public void processar() throws AgendamentoException {
		if (pagamento == null)
			new AgendamentoException("Antes de confirmar o agendamento, você deve escolher uma forma de pagamento.");
		
		if (!pagamento.autorizar())
			new AgendamentoException("O pagamento não foi autorizado. Esse agendamento será cancelado.");
		
		horario.marcar(cliente);
	}

	public Data getData() {
		return this.data;
	}
}
