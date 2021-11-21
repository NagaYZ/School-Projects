package fr.umlv.BabaIsYou.src;

import fr.umlv.zen5.KeyboardKey;

/**
 * Enum class that represents the 4 possible direction (UP, RIGHT, LEFT, DOWN).
 * @author Yassine
 *
 */
public enum Direction {
	UP,DOWN,LEFT,RIGHT;
	
	/**
	 * @param key
	 * @return the direction corresponding to the key
	 */
	public static Direction toDir(KeyboardKey key) {
		if(key == KeyboardKey.UP)
			return Direction.UP;
		if(key == KeyboardKey.DOWN)
			return Direction.DOWN;
		if(key == KeyboardKey.LEFT)
			return Direction.LEFT;
		if(key == KeyboardKey.RIGHT) 
			return Direction.RIGHT;
		return null;
	}
	
	/**
	 * @return the line direction value (UP:-1, DOWN:1 , 0)
	 */
	public int toVectLine(){
		if(this.equals(Direction.DOWN)) 
			return 1;	
		if(this.equals(Direction.UP)) 
			return -1;				
		return 0;
		
	}
	
	/**
	 * @return the column direction value (LEFT:-1, RIGHT:1 , 0)
	 */
	public int toVectColumn(){
		if(this.equals(Direction.LEFT)) 
			return -1;
		if(this.equals(Direction.RIGHT)) 
			return 1;
		return 0;		
	}
}
