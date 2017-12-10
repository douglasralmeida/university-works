package componentes;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Image;
import java.net.URL;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class AppPanel extends JPanel {

	private static final long serialVersionUID = -8809042980038005933L;
	private String titulo;
	
	public AppPanel(String titulo) {
		this.titulo = titulo;
		setLayout(new BorderLayout());
		setBackground(Color.WHITE);		
		criarFundo();
	}
	
	private void criarFundo() {
		JPanel painel = new JPanel();
		URL imgUrl = getClass().getResource("/imagens/cabec.png");
		JLabel texto = new JLabel(titulo);
		ImageIcon icon = new ImageIcon(imgUrl);
		
		painel.setBackground(getBackground());
		painel.setLayout(new BoxLayout(painel, BoxLayout.PAGE_AXIS));
		icon.setImage(icon.getImage().getScaledInstance(700, 100, Image.SCALE_SMOOTH));
		JLabel textoImagem = new JLabel(icon);
		Font fonteNova = new Font(texto.getFont().getFontName(), Font.PLAIN, 18);
		texto.setFont(fonteNova);
		painel.add(textoImagem);
		painel.add(texto);
		add(painel, BorderLayout.NORTH);
	}
	
	public String getTitulo() {
		return titulo;
	}

}