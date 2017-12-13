package janelas;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.SpringLayout;

import agendamento.Atendimento;
import agendamento.Data;
import componentes.AgendamentoListener;
import componentes.AppButton;
import componentes.AppPanel;
import entidades.Endereco;
import entidades.Servico;
import pagamentos.Pagamento;
import pessoa.Cliente;
import sistema.Agendador;
import sistema.AgendamentoException;
import sistema.Aplicacao;
import sistema.Buscador;

public class PainelAgendamento extends AppPanel {
	
	private static final long serialVersionUID = 1409553213723181010L;
	private String[] dataServicos = {"Consulta Médica", "Exame Médico"};
	SpringLayout layoutSpring = new SpringLayout();
	Agendador agendador = new Agendador();
	JTextField editPesquisa = new JTextField(32);
	JLabel txtNome = new JLabel("");
	
	JTextField textoNome = new JTextField();
	JTextField textoCpf = new JTextField();
	JTextField textoIdentidade= new JTextField();
	JTextField textoDataNascimento= new JTextField();
	JTextField textoTelefone = new JTextField();
	JTextField textoLogradouro = new JTextField(64);
	JTextField textoComplemento = new JTextField(32);
	JTextField textoBairro = new JTextField(32);
	JTextField textoCidade = new JTextField(32);
	JTextField textoEstado = new JTextField(32);
	JTextField textoCep = new JTextField(8);
	JTextField[] edits = {textoNome, textoCpf, textoIdentidade, textoDataNascimento, textoTelefone,
			textoLogradouro, textoComplemento, textoBairro, textoCidade, textoEstado, textoCep};
	
	JRadioButton consultaRadio = new JRadioButton(dataServicos[0]);
	JRadioButton exameRadio = new JRadioButton(dataServicos[1]);
	
	JButton btoConcluir = new JButton("Confirmar agendamento");
	
	JComboBox<Servico> comboServico = new JComboBox<Servico>();
	JComboBox<Atendimento> comboHorario = new JComboBox<Atendimento>();
	JComboBox<Pagamento> comboPagamento = new JComboBox<Pagamento>();
	JPanel painelInfo = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painelNovoCliente = new JPanel(layoutSpring);
	JPanel painelTipoServico = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painelServico = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painelCalendario = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painelHorarios = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painelPagamentos = new JPanel(new FlowLayout(FlowLayout.LEFT , 16, 0));
	JPanel painel = new JPanel();
	
	public PainelAgendamento() {
		super("Agendar cliente");
		add(painel, BorderLayout.CENTER);
		painel.setLayout(new BoxLayout(painel, BoxLayout.PAGE_AXIS));
		criarCliente();
		criarNovoCliente();
		criarInfoCliente();
		criarTipoServico();
		criarServico();
		criarCalendario();
		criarHorarios();
		criarPagamentos();
	}
	
	public void init() {
		int i;
		agendador.reiniciar();
		editPesquisa.setText("");
		txtNome.setText("");
		
		for (i = 0; i < edits.length; i++)
			edits[i].setText("");
		
		consultaRadio.setSelected(false);
		exameRadio.setSelected(false);
		
		comboServico.removeAllItems();
		comboHorario.removeAllItems();
		comboPagamento.setSelectedIndex(-1);
	
		ocultarPaineis(0, false);
	}

	private void criarCliente() {
		JPanel painelCliente = new JPanel();
		JButton btoCliente = new JButton("Pesquisar");
		btoCliente.setActionCommand("PESQUISAR");
		
		btoCliente.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				if (ev.getActionCommand() != "PESQUISAR")
					return;
				try {
					ocultarPaineis(0, false);
					Cliente clienteEscolhido = Buscador.PesquisarClientes(editPesquisa.getText());
					if (clienteEscolhido != null) {
						txtNome.setText(clienteEscolhido.getNome());
						agendador.escolherCliente(clienteEscolhido);
						painelInfo.setVisible(true);
						ocultarPaineis(2, true);
					} else {
						agendador.escolherCliente(null);
						ocultarPaineis(1, false);
					}
				} catch (Exception ex) {
					Aplicacao.exibirMsgErro(ex.getMessage());
					return;
				}
			}
		});
		painelCliente.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelCliente.setBackground(Color.WHITE);
		painelCliente.add(new JLabel("CPF do cliente:"));
		painelCliente.add(editPesquisa);
		painelCliente.add(btoCliente);
		painel.add(painelCliente);		
	}
	
	private void criarInfoCliente() {		
		painelInfo.setVisible(false);
		painelInfo.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelInfo.setBackground(Color.WHITE);
		painelInfo.add(new JLabel("Cliente: "));
		painelInfo.add(txtNome);
		
		painel.add(painelInfo);		
	}
	
	private void criarNovoCliente() {
		int i;
		
		painelNovoCliente.setVisible(false);
		painelNovoCliente.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelNovoCliente.setBackground(Color.WHITE);
		JLabel txtSubTitulo = new JLabel("CADASTRAR CLIENTE");
		painelNovoCliente.add(txtSubTitulo);

		JLabel labelNome = new JLabel("Nome:");
		JLabel labelCpf = new JLabel("CPF:");
		JLabel labelIdentidade= new JLabel("Identidade:");
		JLabel labelDataNascimento= new JLabel("Data de Nascimento:");
		JLabel labelTelefone = new JLabel("Telefone:");
		
		JLabel labelLogradouro = new JLabel("Logradouro:");
		JLabel labelComplemento = new JLabel("Complemento:");
		JLabel labelBairro = new JLabel("Bairro:");
		JLabel labelCidade = new JLabel("Cidade:");
		JLabel labelEstado = new JLabel("Estado:");
		JLabel labelCep = new JLabel("CEP:");
		
		JLabel[] labels = {labelNome, labelCpf, labelIdentidade, labelDataNascimento, labelTelefone,
				labelLogradouro, labelComplemento, labelBairro, labelCidade, labelEstado, labelCep};		
		
		layoutSpring.putConstraint(SpringLayout.NORTH, txtSubTitulo, 4, SpringLayout.NORTH, painelNovoCliente);
		layoutSpring.putConstraint(SpringLayout.WEST, txtSubTitulo, 4, SpringLayout.WEST, painelNovoCliente);
		for (i = 0; i < labels.length; i++) {
			painelNovoCliente.add(labels[i]);
			layoutSpring.putConstraint(SpringLayout.WEST, labels[i], 4, SpringLayout.WEST, txtSubTitulo);
		}
		painelNovoCliente.add(edits[0]);
		
		layoutSpring.putConstraint(SpringLayout.WEST, edits[0], 4, SpringLayout.EAST, labels[3]);
		layoutSpring.putConstraint(SpringLayout.NORTH, edits[0], 4, SpringLayout.SOUTH, txtSubTitulo);
		layoutSpring.putConstraint(SpringLayout.EAST, edits[0], -40, SpringLayout.EAST, painelNovoCliente);
		
		for (i = 1; i < edits.length; i++) {
			painelNovoCliente.add(edits[i]);
			layoutSpring.putConstraint(SpringLayout.WEST, edits[i], 0, SpringLayout.WEST, edits[0]);
			layoutSpring.putConstraint(SpringLayout.NORTH, edits[i], 4, SpringLayout.SOUTH, edits[i-1]);
			layoutSpring.putConstraint(SpringLayout.EAST, edits[i], -40, SpringLayout.EAST, painelNovoCliente);
		}
		for (i = 0; i < labels.length; i++) {
			layoutSpring.putConstraint(SpringLayout.NORTH, labels[i], 3, SpringLayout.NORTH, edits[i]);
		}
		
		JButton botaoSalvarCliente = new JButton("Salvar cliente");
		botaoSalvarCliente.setActionCommand("SALVAR");
		botaoSalvarCliente.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				if (ev.getActionCommand() != "SALVAR")
					return;
				Cliente novoCliente = new Cliente();
				Endereco endereco = new Endereco();
				try {
					novoCliente.setNome(textoNome.getText());
					novoCliente.setCpf(textoCpf.getText());
					novoCliente.setIdentidade(textoIdentidade.getText());
					LocalDate data = LocalDate.parse(textoDataNascimento.getText(), DateTimeFormatter.ofPattern("dd/MM/yyyy"));
					novoCliente.setDataNascimento(data);
					novoCliente.setTelefone(textoTelefone.getText());
					
					endereco.setLogradouro(textoLogradouro.getText());
					endereco.setComplemento(textoComplemento.getText());
					endereco.setBairro(textoBairro.getText());
					endereco.setCidade(textoCidade.getText());
					endereco.setEstado(textoEstado.getText());
					endereco.setCep(textoCep.getText());
					
					novoCliente.setEndereco(endereco);
					
					Aplicacao.getPessoas().adicionar(novoCliente);
					agendador.escolherCliente(novoCliente);
					txtNome.setText(novoCliente.getNome());
					painelInfo.setVisible(true);
					ocultarPaineis(2, true);
				}			
				catch (Exception ex) {
					Aplicacao.exibirMsgErro(ex.getMessage());
				}
			}
			
		});
		painelNovoCliente.add(botaoSalvarCliente);
		
		layoutSpring.putConstraint(SpringLayout.NORTH, botaoSalvarCliente, 8, SpringLayout.SOUTH, edits[edits.length-1]);
		layoutSpring.putConstraint(SpringLayout.EAST, botaoSalvarCliente, -40, SpringLayout.EAST, painelNovoCliente);
				
		painel.add(painelNovoCliente);
	}
	
	private void criarTipoServico() {
		ButtonGroup grupo = new ButtonGroup();
		
		painelTipoServico.setVisible(false);
		painelTipoServico.setAlignmentX(Component.LEFT_ALIGNMENT);
		consultaRadio.setMnemonic(KeyEvent.VK_C);
		consultaRadio.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				popularDatas("Especialidade");
			};
		});
		exameRadio.setMnemonic(KeyEvent.VK_E);
		exameRadio.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ev) {
				popularDatas("Exame");
			};
		});
		painelTipoServico.setBackground(Color.WHITE);
		consultaRadio.setBackground(Color.WHITE);
		exameRadio.setBackground(Color.WHITE);
		painelTipoServico.add(new JLabel("Tipo de Serviço:"));		
		grupo.add(consultaRadio);
		grupo.add(exameRadio);
		painelTipoServico.add(consultaRadio);
		painelTipoServico.add(exameRadio);
		
		painel.add(painelTipoServico);
	}
	
	private void criarServico() {
		painelServico.setVisible(false);
		painelServico.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelServico.setBackground(Color.WHITE);
		painelServico.add(new JLabel("Serviço:"));
		painelServico.add(comboServico);
		comboServico.addItemListener(new ItemListener() {

			@Override
			public void itemStateChanged(ItemEvent ev) {
				if (ev.getItem() == null)
					return;
		
				if (ev.getStateChange() == ItemEvent.SELECTED) {
					Servico servicoSelecionado = (Servico) ev.getItem();
					try {
						agendador.escolherServico(servicoSelecionado);
					} catch (AgendamentoException ex) {
						Aplicacao.exibirMsgErro(ex.getMessage());
						ex.printStackTrace();
					}
					ocultarPaineis(4, true);
				}
			}
		});	
		painel.add(painelServico);
	}
	
	private void criarCalendario() {
		JPanel calendario;
		
		painelCalendario.setVisible(false);
		painelCalendario.setAlignmentX(Component.LEFT_ALIGNMENT);
		calendario = gerarCalendario();
		painelCalendario.setBackground(Color.WHITE);
		painelCalendario.add(new JLabel("Data:"));
		painelCalendario.add(calendario);

		painel.add(painelCalendario);		
	}
	
	private JPanel gerarCalendario() {
		int i;
		String[] diasSemana = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};
		ButtonGroup bg = new ButtonGroup();
		LocalDate inicioMes = LocalDate.of(LocalDate.now().getYear(), LocalDate.now().getMonth(), 1);
		int numInicioSemana = inicioMes.getDayOfWeek().ordinal() + 1;
		int numMaxDiasMes = inicioMes.getMonth().length(false);
		
		JPanel calendario = new JPanel(new GridLayout(0, 7));
		
		for (i = 0; i < 7; i++) {
			JLabel lb = new JLabel(diasSemana[i]);
			lb.setHorizontalAlignment(JLabel.CENTER);
		    calendario.add(lb);
		}
		for (i = 0; i < numInicioSemana; i++) {
		    calendario.add(new JLabel(""));
		}
		for (i = 0; i < numMaxDiasMes; i++) {
			LocalDate data = LocalDate.of(LocalDate.now().getYear(), LocalDate.now().getMonthValue(), i+1);
			AppButton<LocalDate> bto = new AppButton<LocalDate>(String.valueOf(i+1));
			bto.setValue(data);
			bg.add(bto);
			bto.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent ev) {
					@SuppressWarnings("unchecked")
					AppButton<LocalDate> btoClicado = (AppButton<LocalDate>) ev.getSource();
					LocalDate dataEscolhida = btoClicado.getValue();
					try {
						agendador.escolherData(dataEscolhida);
						popularHorarios(agendador.getData());
						ocultarPaineis(5, true);
					} catch (Exception ex) {
						Aplicacao.exibirMsgErro(ex.getMessage());
					}
				}				
			});
		    calendario.add(bto);
		 }		
		calendario.setBackground(SystemColor.controlShadow);
		
		return calendario;
	}
	
	private void criarHorarios() {
		painelHorarios.setVisible(false);
		painelHorarios.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelHorarios.setBackground(Color.WHITE);
		painelHorarios.add(new JLabel("Horários disponíveis:"));
		painelHorarios.add(comboHorario);
		comboHorario.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent ev) {
				if (ev.getItem() == null)
					return;
		
				if (ev.getStateChange() == ItemEvent.SELECTED) {
					Atendimento atendimentoSelecionado = (Atendimento) ev.getItem();
					try {
						agendador.escolherHorario(atendimentoSelecionado);
					} catch (AgendamentoException ex) {
						Aplicacao.exibirMsgErro(ex.getMessage());
						ex.printStackTrace();
					}
					ocultarPaineis(6, true);
				}
			}
		});
		painel.add(painelHorarios);
	}
	
	private void criarPagamentos() {
		int i;
		int max = Aplicacao.getFormasPagamento().getSize();
		
		for (i = 0; i < max; i++)
			comboPagamento.addItem(Aplicacao.getFormasPagamento().getPagamento(i));
		comboPagamento.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent ev) {
				if (ev.getItem() == null)
					return;
		
				if (ev.getStateChange() == ItemEvent.SELECTED) {
					Pagamento pagamentoSelecionado = (Pagamento) ev.getItem();
					try {
						agendador.escolherPagamento(pagamentoSelecionado);
						for (AgendamentoListener al: ouvintes)
							al.AgendamentoConcluido(agendador);
			
					} catch (AgendamentoException ex) {
						Aplicacao.exibirMsgErro(ex.getMessage());
						ex.printStackTrace();
					}
					ocultarPaineis(6, true);
				}
			}
		});
		
		painelPagamentos.setVisible(false);
		painelPagamentos.setAlignmentX(Component.LEFT_ALIGNMENT);
		painelPagamentos.setBackground(Color.WHITE);
		painelPagamentos.add(new JLabel("Forma de pagamento:"));
		painelPagamentos.add(comboPagamento);
		btoConcluir.setActionCommand("CONFIRMAR");
		btoConcluir.setAlignmentX(Component.RIGHT_ALIGNMENT);
		btoConcluir.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent ev) {
				if (ev.getActionCommand() != "CONFIRMAR")
					return;
				Aplicacao.exibirMsgErro(ev.paramString());
				try {
					agendador.processar();
				} catch (AgendamentoException ex) {
					Aplicacao.exibirMsgErro(ex.getMessage());
				}
			}
		});
		painelPagamentos.add(btoConcluir);
		
		painel.add(painelPagamentos);
	}

	private void ocultarPaineis(int p, boolean achouPessoa) {
		int i;
		JPanel[] paineis = new JPanel[6];
		
		if (achouPessoa)
			paineis[0] = painelInfo;
		else
			paineis[0] = painelNovoCliente;
		paineis[1] = painelTipoServico;
		paineis[2] = painelServico;
		paineis[3] = painelCalendario;
		paineis[4] = painelHorarios;
		paineis[5] = painelPagamentos;
		
		painelInfo.setVisible(false);
		painelNovoCliente.setVisible(false);
		for (i = 0; i < p; i++)
			paineis[i].setVisible(true);
	}
	
	protected void popularDatas(String string) {
		int i;
		int max = Aplicacao.getServicos().getSize();
		Servico servico;
		
		comboServico.removeAllItems();
		for (i = 0; i < max; i++) {
			servico = Aplicacao.getServicos().getServico(i);
			if (servico.getClass().getSimpleName().equals(string))
				comboServico.addItem(servico);
		}
		ocultarPaineis(3, true);
	}
	
	public void popularHorarios(Data data) {
		int i;
		int max = data.getHorarios().size();
		Atendimento horario;
		
		comboHorario.removeAllItems();
		for (i = 0; i < max; i++) {
			horario = data.getHorarios().get(i);
			comboHorario.addItem(horario);
		}
		ocultarPaineis(4, true);
	}
}