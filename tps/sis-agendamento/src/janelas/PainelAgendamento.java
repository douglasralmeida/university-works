package janelas;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.KeyEvent;
import javax.swing.ButtonGroup;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import componentes.AppPanel;

public class PainelAgendamento extends AppPanel {
	
	private static final long serialVersionUID = 1409553213723181010L;
	private String[] dataServicos = {"Consulta Médica", "Exame Médico"};
	
	public PainelAgendamento() {
		super("Agendar cliente");
		
		criarControles();
		
		add(new JPanel());
	}
		
	private void criarControles() {
		FlowLayout fl = new FlowLayout(FlowLayout.LEFT);		
		JPanel painelServico = new JPanel(fl);
		JRadioButton consultaRadio = new JRadioButton(dataServicos[0]);
		JRadioButton exameRadio = new JRadioButton(dataServicos[1]);
		ButtonGroup grupo = new ButtonGroup();
		
		fl.setHgap(16);
		consultaRadio.setMnemonic(KeyEvent.VK_C);
		exameRadio.setMnemonic(KeyEvent.VK_E);
		painelServico.setBackground(Color.WHITE);
		consultaRadio.setBackground(Color.WHITE);
		exameRadio.setBackground(Color.WHITE);
		painelServico.add(new JLabel("Serviço:"));		
		grupo.add(consultaRadio);
		grupo.add(exameRadio);
		painelServico.add(consultaRadio);
		painelServico.add(exameRadio);
		
		add(painelServico);
	}
}
