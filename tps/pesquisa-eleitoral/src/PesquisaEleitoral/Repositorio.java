/**
 * 
 */
package PesquisaEleitoral;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * @author Douglas
 *
 */
public class Repositorio {
	ArrayList<Questionario> questionarios;
	
	public Repositorio() {
		questionarios = new ArrayList<Questionario>();
	}
	
	public void adicionarQuestionario(Questionario questionario) {
		questionarios.add(questionario);
	}
	
	public Questionario getQuestionario(int index) {
		return questionarios.get(index);
	}
	
	public int getSize() {
		return questionarios.size();
	}
	
	public void removerQuestionario(int index) {
		questionarios.remove(index);
	}
	
	public String toString() {
		StringBuilder stringBuilder = new StringBuilder();
		
		//percorrer todo o questionario
		Iterator<Questionario> i = questionarios.iterator();
	    while (i.hasNext()) {
	    	Questionario q = i.next();
	    	stringBuilder.append(q.toString());
	    	stringBuilder.append("\n");
	    }
	    stringBuilder.delete(stringBuilder.length()-2, stringBuilder.length()-1);
	    //retorna o resultado
		return stringBuilder.toString();
	}
}
