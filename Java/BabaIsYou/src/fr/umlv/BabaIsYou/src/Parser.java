package fr.umlv.BabaIsYou.src;

import java.util.List;
import java.util.Objects;

/**
 * Class that manages parsing of files.
 * @author Yassine 
 *
 */
public class Parser {
	private List<String> input;
	
	/**
	 * Store file input in a List.
	 * @param list
	 */
	public Parser(List<String> list) {
		Objects.requireNonNull("File content cannot be null.");
		this.input = list;
	}

	/**
	 * Create a board with the content of a file.
	 * @return a Board made from parsing the lines of a file
	 * @throws ArrayIndexOutOfBoundsException if first line is not valid.
	 * @throws IllegalArgumentException if other line is not valid.
	 */
	public Board createBoard() {
		var firstLine = input.get(0).split("[ ]+");
		if(firstLine.length != 2)
			throw new ArrayIndexOutOfBoundsException("Invalid first line of file.");
		
		//get first line to initialize board number of column/line			
		int column = Integer.parseInt(firstLine[0]);
		int line = Integer.parseInt(firstLine[1]);		
		Board board = new Board(line, column);
		
		var iterator = input.listIterator(1);
		while(iterator.hasNext())// parse rest of lines	
			parseLine(board, iterator.next().split("[ ]+"));
		
		return board;		
	}
	
	/**
	 * parse a file line, add its content to the map of the board if parsing is successful
	 * @param board
	 * @param blockLine
	 * @return false is line is not valid
	 * @throws IllegalArgumentException if line is not valid.
	 */
	private void parseLine(Board board, String[] blockLine) {				
		Coordinates coord = new Coordinates(Integer.parseInt(blockLine[2]), Integer.parseInt(blockLine[3]));
		
		if(!board.outOfBounds(coord)) 
			board.getMap().get(coord).add(getBlockFromString(blockLine[0], blockLine[1]));		
		else throw new IllegalArgumentException("Coordinates out of range.");
	}

	/**
	 * get the Block part of the line
	 * @param blockType
	 * @param blockName
	 * @return a Block made from the content of the line
	 * @throws IllegalArgumentException if the Block part of the line is not valid.
	 */
	private Block getBlockFromString(String blockType, String blockName) {
		BlockType Type = BlockType.valueOf(blockType.toUpperCase());
		
		if(Type.equals(BlockType.NAME)) 
			return new Block(Name.valueOf(blockName));			
		else if(Type.equals(BlockType.PROPERTY)) 
			return new Block(Property.valueOf(blockName));			
		else if(Type.equals(BlockType.OPERATOR)) 
			return new Block(Operator.valueOf(blockName));			
		else if(Type.equals(BlockType.TEXT))
			return new Block(Text.valueOf(blockName));
		
		return new Block(Decor.valueOf(blockName));	//else decor
	}
	
}
