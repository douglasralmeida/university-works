package PesquisaEleitoral;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;

public class RenderizadorQuestionario extends JPanel implements ListCellRenderer<Questionario> {
		
	private static final long serialVersionUID = -1993026305358230021L;
	private JLabel txtNome = new JLabel();
	private JLabel txtSexo = new JLabel();
	private JLabel txtEscolaridade = new JLabel();
	private JLabel txtIdade = new JLabel();
	private JLabel txtRenda = new JLabel();
	private JPanel panelItem = new JPanel(new GridLayout(0, 1)); 
	
	public RenderizadorQuestionario() {
		setLayout(new BorderLayout(4, 4));
		
		panelItem.add(txtNome);
		panelItem.add(txtSexo);
		panelItem.add(txtEscolaridade);
		panelItem.add(txtIdade);
		panelItem.add(txtRenda);
		add(panelItem, BorderLayout.CENTER);
	}
	
	Color blend( Color c1, Color c2, float ratio ) {
	    if ( ratio > 1f ) ratio = 1f;
	    else if ( ratio < 0f ) ratio = 0f;
	    float iRatio = 1.0f - ratio;

	    int i1 = c1.getRGB();
	    int i2 = c2.getRGB();

	    int a1 = (i1 >> 24 & 0xff);
	    int r1 = ((i1 & 0xff0000) >> 16);
	    int g1 = ((i1 & 0xff00) >> 8);
	    int b1 = (i1 & 0xff);

	    int a2 = (i2 >> 24 & 0xff);
	    int r2 = ((i2 & 0xff0000) >> 16);
	    int g2 = ((i2 & 0xff00) >> 8);
	    int b2 = (i2 & 0xff);

	    int a = (int)((a1 * iRatio) + (a2 * ratio));
	    int r = (int)((r1 * iRatio) + (r2 * ratio));
	    int g = (int)((g1 * iRatio) + (g2 * ratio));
	    int b = (int)((b1 * iRatio) + (b2 * ratio));

	    return new Color( a << 24 | r << 16 | g << 8 | b );
	}
	
	@Override
	public Component getListCellRendererComponent(JList<? extends Questionario> lista, Questionario quest, int index,
			boolean estaSelecionado, boolean temFoco) {
		Color corMistura;
		
		txtNome.setText("<html>Candidato: <b>" + quest.getCandidato() + "</b></html>");
		txtSexo.setText("Sexo: " + quest.getSexo());
		txtIdade.setText("Idade: " + quest.getIdade());
		txtRenda.setText("Renda: " + quest.getRenda());
		txtEscolaridade.setText("Escolaridade: " + quest.getEscolaridade());
		txtNome.setOpaque(true);
		txtSexo.setOpaque(true);
		txtIdade.setOpaque(true);
		txtRenda.setOpaque(true);
		txtEscolaridade.setOpaque(true);
		
		if (estaSelecionado) {
			panelItem.setBorder(BorderFactory.createLineBorder(lista.getSelectionBackground()));
			corMistura = blend(lista.getBackground(), lista.getSelectionBackground(), 0.3f);
			txtNome.setBackground(corMistura);
			txtSexo.setBackground(corMistura);
			txtEscolaridade.setBackground(corMistura);
			txtRenda.setBackground(corMistura);
			txtIdade.setBackground(corMistura);
			setBackground(corMistura);
		} else {
			panelItem.setBorder(BorderFactory.createLineBorder(lista.getBackground()));
			txtNome.setBackground(lista.getBackground());
			txtRenda.setBackground(lista.getBackground());
			txtSexo.setBackground(lista.getBackground());
			txtEscolaridade.setBackground(lista.getBackground());
			txtIdade.setBackground(lista.getBackground());
			setBackground(lista.getBackground());
		}
		
		return this;
	}
}
