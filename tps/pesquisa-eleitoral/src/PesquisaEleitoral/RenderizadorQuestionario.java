package PesquisaEleitoral;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;

public class RenderizadorQuestionario extends JPanel implements ListCellRenderer<Questionario> {
		
	private static final long serialVersionUID = -1993026305358230021L;
	private JLabel txtNome = new JLabel();
	
	public RenderizadorQuestionario() {
		setLayout(new BorderLayout(5, 5));
		
		JPanel panelTexto = new JPanel(new GridLayout(0, 1));
		panelTexto.add(txtNome);
		add(panelTexto, BorderLayout.CENTER);
	}
	
	@Override
	public Component getListCellRendererComponent(JList<? extends Questionario> lista, Questionario quest, int index,
			boolean estaSelecionado, boolean temFoco) {
		txtNome.setText(quest.getCandidato());
		txtNome.setOpaque(true);
		
		if (estaSelecionado) {
			txtNome.setBackground(lista.getSelectionBackground());
			setBackground(lista.getSelectionBackground());
		} else {
			txtNome.setBackground(lista.getBackground());
			setBackground(lista.getBackground());
		}
		
		return this;
	}
}
