/**
 * 
 */
package PesquisaEleitoral;

import java.util.ArrayList;
import java.util.Iterator;

/**
 *  Classe do repositório de questionários 
 */
public class Repositorio {
	ArrayList<Questionario> questionarios;
	
	/**
	 *  Construtor do Repositório 
	 */
	public Repositorio() {
		questionarios = new ArrayList<Questionario>();
	}
	
	/**
	 * Adiciona um questionário ao repositório
	 * @param  questionario Questionário a ser adicionado
	 */
	public void adicionarQuestionario(Questionario questionario) {
		questionarios.add(questionario);
	}
	
	/**
	 * Retorna o questinário no índice especificado do repositório
	 * @param  index Índice do respositório
	 * @return o questionário no índice especificado
	 */
	public Questionario getQuestionario(int index) {
		return questionarios.get(index);
	}
	
	/**
	 * Retorna o número de questionários do repositório
	 * @return  o número de questionários
	 */
	public int getSize() {
		return questionarios.size();
	}
	
	/**
	 * Remove um questionário do respositório
	 * @param  index Índice do questionário no repositório
	 */
	public void removerQuestionario(int index) {
		questionarios.remove(index);
	}

	/**
	 * Returna uma representação em uma cadeia de caracteres dos questionários do repositório e de seus campos.
	 * @return a representação em uma cadeia de caracteres
	 */
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
