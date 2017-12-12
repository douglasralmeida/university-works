package janelas;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Font;
import java.awt.SystemColor;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.border.Border;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import componentes.AgendamentoListener;
import componentes.AppPanel;
import sistema.Agendador;

public class JanelaPrincipal extends JFrame {

	private static final long serialVersionUID = 1033915334404746310L;
	AppPanel[] paineis;
	JPanel painelCaderno;
	String[] dataPaineis = {"Home", "Agendar cliente", "Gestão de Serviços", "Gestão de Funcionários"};
	private BorderLayout layout = new BorderLayout();
	private CardLayout cardLayout = new CardLayout();

	public JanelaPrincipal() {
		super("Sistema de Atendimento");
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(layout);
		setSize(800, 525);
		criarPainelEsquerdo();
		criarCards();
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	private void criarPainelEsquerdo() {
		JList<String> lista = new JList<String>(dataPaineis);
		JScrollPane listaScroll = new JScrollPane(lista);

		lista.setSelectedIndex(0);
		lista.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent e) {
				ListSelectionModel lsm = (ListSelectionModel)e.getSource();
				int index = lsm.getMinSelectionIndex();
				if (index > -1) {
					paineis[index].init();
					cardLayout.show(painelCaderno, dataPaineis[index]);
					paineis[index].addAgendamentoListener(new AgendamentoListener() {

						@Override
						public void AgendamentoConcluido(Agendador ag) {
							JOptionPane.showMessageDialog(null, "Agendamento efetuado com sucesso", "Agendamento concluído", JOptionPane.INFORMATION_MESSAGE);
							cardLayout.show(painelCaderno, dataPaineis[0]);
						}
					});
				}
			}
		});
		lista.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		Font fonteNova = new Font(lista.getFont().getFontName(), Font.PLAIN, 16);
		lista.setFont(fonteNova);
		Border bordaClara = BorderFactory.createMatteBorder(0, 0, 0, 1, SystemColor.controlShadow);
		Border bordaEscura = BorderFactory.createMatteBorder(0, 0, 0, 1, SystemColor.controlLtHighlight);
		Border bordaNova = BorderFactory.createCompoundBorder(bordaEscura, bordaClara);
		listaScroll.setBorder(bordaNova);

		add(listaScroll, BorderLayout.LINE_START);
	}
	
	private void criarCards() {
		int i;
		
		paineis = new AppPanel[dataPaineis.length];		
		paineis[0] = new PainelHome();
		paineis[1] = new PainelAgendamento();
		paineis[2] = new PainelServicos(this);
		paineis[3] = new PainelFuncionarios(this);
		painelCaderno = new JPanel(cardLayout);
		for (i = 0; i < dataPaineis.length; i++)
			painelCaderno.add(paineis[i], dataPaineis[i]);
		cardLayout.show(painelCaderno, "Home");
		add(painelCaderno, BorderLayout.CENTER);
	}
}