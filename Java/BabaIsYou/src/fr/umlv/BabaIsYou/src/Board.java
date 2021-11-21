package fr.umlv.BabaIsYou.src;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import fr.umlv.zen5.KeyboardKey;


/**
 * Class that represent the game board.
 * @author Yassine
 *
 */
public class Board{
	private Rule rules;
	private int width;
	private int height;
	private Map<Coordinates, Set<Block>> map = new HashMap<>();
	private Movement movements;
	private Action actions;
	
	/**
	 * @param line
	 * @param column
	 */
	public Board(int line, int column){
		this.height = line;
		this.width = column;		
		initBoard();
		this.rules = new Rule();
		this.movements = new Movement();
		this.actions = new Action();
	}
	
	/**
	 * initialize the Board with its height and width, use a TreeSet to store Block to maintain order when displaying.
	 * <br>When 2 Blocks are on top of each other, the "smallest" image is displayed last, so it is not hidden by a larger image.
	 */
	private void initBoard() {
		for (int x = 0; x < height; x++) {
			for (int y = 0; y < width; y++) {
				map.put(new Coordinates(x, y), 
						new TreeSet<>(Comparator.comparing(Block::getType).reversed().thenComparing(Block::toString).reversed()));	
			}
		}
	}
	
	/**
	 * add the block to the 'coord' coordinates of the map.
	 * @param coord
	 * @param block
	 */
	public void addBlock(Coordinates coord, Block block){
		Objects.requireNonNull(coord);	
		Objects.requireNonNull(block);
		if(!outOfBounds(coord)) 
			map.get(coord).add(block);		
		else
			throw new IllegalArgumentException("Block position too big, out of Level's range.");		
	}
	
	/**
	 * @param coord
	 * @return true if the Coordinates is outside boards range
	 */
	public boolean outOfBounds(Coordinates coord) {		
		return (coord.getLine() < 0 || coord.getCol() < 0 || coord.getLine() >= height || coord.getCol() >= width);
	}
	
	/**
	 * @return boards width
	 */
	public int getWidth() {
		return width;
	}

	/**
	 * @return boards height
	 */
	public int getHeight() {
		return height;
	}	

	/**
	 * @return boards map
	 */
	public Map<Coordinates, Set<Block>> getMap() {
		return map;
	}
	
	/**
	 * @return boards rules
	 */
	public Rule getRules() {
		return rules;
	}	

	/**
	 * Apply the move function to the board of the level according to the value of the KeyboardKey.
	 * <br>If a move has been made, execute actions and update rules.
	 * @param key
	 * @return true if a move has been made
	 */
	public boolean move(KeyboardKey key) {
		Direction dir = Direction.toDir(key);
		if(dir == null)
			return false;
		
		if(movements.move(this, dir)) { // if move has been made, execute actions and update rules
			actions.executeAction(this);
			rules.updateRules(this);
			return true;
		}			
		return false;
	}
	
	/**
	 * check if win.
	 * @return true if win.
	 */
	public boolean win() {
		return actions.win(this);
		
	}
	
	/**
	 * check if lose.
	 * @return true if lose.
	 */
	public boolean lose() {
		return actions.death(this);
	}
	
}
