package fr.umlv.BabaIsYou.src;

import java.util.Objects;

import fr.umlv.zen5.ApplicationContext;

/**
 * Class that represents a Level.
 * @author Yassine Abder
 *
 */
public class Level{
	private final float levelHeight;
	private final float levelWidth;
	private final int cellSize;
	private Board board;
	private ApplicationContext context;
	private Draw draw;
	
	/**
	 * @param context
	 * @param board
	 */
	public Level(ApplicationContext context, Board board) {		
		Objects.requireNonNull(board);
		this.levelWidth = context.getScreenInfo().getWidth();
		this.levelHeight = context.getScreenInfo().getHeight();
		this.board = board;
		this.board.getRules().updateRules(board);
		this.cellSize = initCellSize();		
		this.context = context;
		this.draw = new Draw(board);
	}
	
	/**
	 * draw the level
	 */
	public void refresh() {
		draw.draw(this);
	}
	
	/**
	 * @return the board 
	 */
	public Board getBoard() {
		return board;
	}

	/**
	 * @return the size of a cell, calculated so we have squares and not rectangles.
	 */
	private int initCellSize() {
		return (int) ((levelHeight / board.getHeight() > levelWidth / board.getWidth()) ? levelWidth / board.getWidth() : levelHeight / board.getHeight());
	}
	
	/**
	 * @return cellSize
	 */
	public int getCellSize() {
		return cellSize;
	}
	
	/**
	 * @return verticalMargin of the level
	 */
	public int getVerticalMargin(){
		return (int) ((levelHeight - cellSize * board.getHeight()) / 2);
	}
	
	/**
	 * @return horizontalMargin of the level
	 */
	public int getHorizontalMargin(){
		return (int) ((levelWidth - cellSize * board.getWidth()) / 2);
	}
	
	/**
	 * @return levelHeight
	 */
	public float getLevelHeight() {
		return levelHeight;
	}

	/**
	 * @return levelWidth
	 */
	public float getLevelWidth() {
		return levelWidth;
	}

	/**
	 * @return context
	 */
	public ApplicationContext getContext() {
		return context;
	}
	
	/**
	 * clear level
	 */
	public void clear() {		
		draw.clear(this);
	}

}
