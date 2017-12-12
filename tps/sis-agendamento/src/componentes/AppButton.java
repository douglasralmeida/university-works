package componentes;

import javax.swing.JButton;

public class AppButton<T> extends JButton {
	private static final long serialVersionUID = -3374853095147810309L;
	private T value;
	
	public AppButton(String s) {
		super(s);
	}
	
	public T getValue() {
	    return this.value;
	}

	public void setValue(T value) {
	    this.value = value;
	}
}
