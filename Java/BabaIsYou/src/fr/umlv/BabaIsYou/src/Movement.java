package fr.umlv.BabaIsYou.src;

import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

/**
 * Class that manages the movements in the board.
 * @author Yassine
 *
 */
public class Movement {
	private Map<Coordinates, Set<Block>> mapMoveable = new LinkedHashMap<>();//LinkedHashMap to keep order of insertion
	
	/**
	 * clear the map.
	 */
	private void resetMapMoveable() {
		mapMoveable.clear();
	}
	
	/**
	 * Add a block to mapMoveable
	 * @param coord
	 * @param listblock
	 */
	private void addMoveable(Coordinates coord, Block block) {
		mapMoveable.putIfAbsent(coord, new HashSet<Block>());
		mapMoveable.get(coord).add(block);
	}
	
	/**
	 * Add all the blocks that can be moved in mapMoveable and move them at the same time to avoid staggered movements.
	 * <br> for example if two Block with PUSH property are on top of each other they are moved at the same time.
	 * @param board
	 * @param dir
	 * @return true if a move has been made.
	 */
	public boolean move(Board board, Direction dir) {
		if(dir.toVectLine() == 0 && dir.toVectColumn() == 0)
			return false;		
		resetMapMoveable();
		board.getRules().updateRules(board);
		board.getMap().entrySet().forEach(entry -> entry.getValue().stream()
				.filter(b -> board.getRules().getRule(Property.YOU, b))
				.forEach(block -> canMove(board, block, entry.getKey(), dir))); 
		return moveMoveable(board, dir);
	}

	/**
	 * Look if a block can move, if the block can move add all block to be moved to mapMoveable.
	 * @param board
	 * @param block
	 * @param coord
	 * @param dir
	 * @return true if a block can move
	 */
	private boolean canMove(Board board, Block block, Coordinates coord, Direction dir) {
		if(board.outOfBounds(coord))
			return false;

		var iterator = board.getMap().entrySet().stream()
		.filter(nextCoord -> nextCoord.getKey().getLine() == coord.getLine() + dir.toVectLine() && // get new Coordinate
							 nextCoord.getKey().getCol()  == coord.getCol()  + dir.toVectColumn())
		.map(entry -> entry.getKey())
		.filter(p -> board.getMap().get(p).stream()//look if block can move
				.allMatch(r -> board.getRules().isMoveable(board, r, p) || //recursive if Block has PUSH or YOU property
						(board.getRules().isPushable(board, r, p) && canMove(board, r, p, dir)))).iterator();
		if(!iterator.hasNext())
			return false;	
		addMoveable(coord, block);
		return true;
	}	
	
	/**
	 * Move all moveable block.
	 * @param board
	 * @param dir
	 * @return false if mapMoveable empty
	 */
	private boolean moveMoveable(Board board, Direction dir) {	
		if(mapMoveable.isEmpty())
			return false;
		mapMoveable.entrySet().stream()
		.forEach(key -> key.getValue().forEach(block ->	translate(board, key.getKey(), block, dir)));
		return true;
	}
	
	/**
	 * Translate the Coordinates of the Block in the Direction.
	 * @param board
	 * @param coord
	 * @param block
	 * @param dir
	 */
	private void translate(Board board, Coordinates coord, Block block, Direction dir) {
		board.getMap().get(coord).remove(block);//remove
		board.getMap().entrySet().stream()
		.filter(nextCoord -> nextCoord.getKey().getLine() == coord.getLine() + dir.toVectLine() && // get new Coordinate
							 nextCoord.getKey().getCol()  == coord.getCol()  + dir.toVectColumn()) 
		.forEach(entry -> board.addBlock(entry.getKey(), block));// add
	}
	
}
