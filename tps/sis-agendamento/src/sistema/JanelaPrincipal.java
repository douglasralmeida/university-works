package sistema;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Font;
import java.awt.SystemColor;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.border.Border;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import janelas.PainelAgendamento;
import janelas.PainelGestao;
import janelas.PainelHome;

public class JanelaPrincipal extends JFrame {

	private static final long serialVersionUID = 1033915334404746310L;
	JPanel[] paineis;
	JPanel painelCaderno;
	String[] dataPaineis = {"Home", "Agendar cliente", "Agenda do Dia", "Gestão", "Configurações"};
	private BorderLayout layout = new BorderLayout();
	private CardLayout cardLayout = new CardLayout();

	public JanelaPrincipal() {
		super("Sistema de Atendimento");
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(layout);
		setSize(800, 500);
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
				if (lsm.getMinSelectionIndex() > -1)
					cardLayout.show(painelCaderno, dataPaineis[lsm.getMinSelectionIndex()]);
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
		
		paineis = new JPanel[dataPaineis.length];
		paineis[0] = new PainelHome();
		paineis[1] = new PainelAgendamento();
		paineis[2] = new JPanel();
		paineis[2].add(new JLabel("Agenda do dia"));
		paineis[3] = new PainelGestao(this);
		paineis[4] = new JPanel();
		paineis[4].add(new JLabel("Configurações"));
		painelCaderno = new JPanel(cardLayout);
		for (i = 0; i < dataPaineis.length; i++)
			painelCaderno.add(paineis[i], dataPaineis[i]);
		cardLayout.show(painelCaderno, "Home");
		add(painelCaderno, BorderLayout.CENTER);
	}
}
