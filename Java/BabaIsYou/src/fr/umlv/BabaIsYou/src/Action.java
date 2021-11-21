package fr.umlv.BabaIsYou.src;

/**
 * Class that manages the actions in the board.
 * @author Yassine Abder
 */
public class Action {

	/**
	 * execute actions , Break, Sink, Melt, Defeat.
	 * @param board
	 */
	public void executeAction(Board board) {
		for(var entry : board.getMap().entrySet()) {
			var key = entry.getKey();
			Break(board, key);
			Sink(board, key);
			Hot(board, key);
			Defeat(board, key);				
		}		
	}
	
	/**	
	 * remove all "NAME" Block on Block with SINK property
	 * @param board
	 * @param coord
	 */
	public void Sink(Board board, Coordinates coord) {
		var list = board.getMap().get(coord);
		if( list.stream().anyMatch(block -> board.getRules().getRule(Property.SINK, block)) &&
			list.stream().filter(block -> block.name().getType().equals(BlockType.NAME)).count() > 1 )			
			list.removeIf(block -> block.name().getType().equals(BlockType.NAME));		
	}
	
	/**	
	 * remove all "NAME" Block with MELT property on Block with HOT property
	 * @param board
	 * @param coord
	 */
	public void Hot(Board board, Coordinates coord) {
		var list = board.getMap().get(coord);
		if( list.stream().anyMatch(block -> board.getRules().getRule(Property.HOT, block)))
			list.removeIf(block ->  board.getRules().getRule(Property.MELT, block));		
	}
	
	/**
	 * remove all "NAME" Block without the BREAK property on a Block with BREAK property
	 * @param board
	 * @param coord
	 */
	public void Break(Board board, Coordinates coord) {
		var list = board.getMap().get(coord);
		if( list.stream().anyMatch(block -> board.getRules().getRule(Property.BREAK, block)))		
			list.removeIf(block -> block.name().getType().equals(BlockType.NAME) && !board.getRules().getRule(Property.BREAK, block));		
	}
	
	/**
	 * @param board
	 * @return true if a "NAME" Block with YOU property is in the same list as a "NAME" Block with WIN property
	 */	
	public boolean Win(Board board) {
		return board.getMap().entrySet().stream()
				.filter(entry -> !entry.getValue().isEmpty() && entry.getValue().stream()
						.anyMatch(block ->  board.getRules().getRule(Property.YOU, block)))
				.filter(entry -> entry.getValue().stream()
						.anyMatch(block -> board.getRules().getRule(Property.WIN, block)))
				.findFirst()
				.isPresent();		
	}
	
	/** 
	 * remove Block with YOU property on Block with DEFEAT property
	 * @param board
	 * @param coord
	 */
	public void Defeat(Board board, Coordinates coord) {
		var list = board.getMap().get(coord);
		if( list.stream().anyMatch(block -> board.getRules().getRule(Property.DEFEAT, block)))
			list.removeIf(block ->  board.getRules().getRule(Property.YOU, block));		
	}
	
	/** 
	 * @param board
	 * @return true if there is no Block with YOU property
	 */
	public boolean Death(Board board) {
		return board.getMap().entrySet().stream()
			.filter(entry -> !entry.getValue().isEmpty() && entry.getValue().stream()
					.anyMatch(block ->  board.getRules().getRule(Property.YOU, block)))
			.findFirst()
			.isEmpty();
	}
	
}
