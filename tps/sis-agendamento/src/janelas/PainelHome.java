package janelas;

import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Font;
import java.net.URL;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class PainelHome extends JPanel {

	private static final long serialVersionUID = 6032140882012173147L;

	public PainelHome() {
		setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		URL imgURL = getClass().getResource("/imagens/logo.jpg");
		JLabel textoImagem = new JLabel(new ImageIcon(imgURL));
		JLabel texto = new JLabel("Home");
		
		this.setBackground(Color.WHITE);
		textoImagem.setAlignmentX(Component.CENTER_ALIGNMENT);
		Font fonteNova = new Font(texto.getFont().getFontName(), Font.PLAIN, 18);
		texto.setFont(fonteNova);
		
		add(textoImagem);
		add(texto);
		JPanel painelPesquisar = new JPanel(new FlowLayout(FlowLayout.LEFT));
		painelPesquisar.add(new JLabel("Pesquisar: "));
		add(painelPesquisar);
	}
}