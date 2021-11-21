package fr.umlv.BabaIsYou.src;

/**
 * Record that represent the coordinates of a Block.
 * @author Yassine
 *
 */
public record Coordinates(int line, int column) {

	/**
	 * @return line
	 */
	public int getLine() {
		return line;
	}
	
	/**
	 * @return column
	 */
	public int getCol() {
		return column;
	} 
	
	@Override
	public String toString() {		
		return "(" + line + " " + column + ")";
	}

}
