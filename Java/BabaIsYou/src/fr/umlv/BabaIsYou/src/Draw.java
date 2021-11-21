package fr.umlv.BabaIsYou.src;

import java.awt.Color;
import java.awt.Image;
import java.awt.geom.Rectangle2D;

import java.util.HashMap;
import java.util.Map;

import javax.imageio.ImageIO;
import java.io.IOException;
import java.io.InputStream;

import java.nio.file.Files;
import java.nio.file.Paths;
/**
 * Class that draws a Level.
 * @author Yassine
 *
 */
public class Draw {	
	Map<Block, Image> mapImage = new HashMap<>();

	/**
	 * init a map of image from blocks in the board
	 * @param board
	 */
	public Draw(Board board) {
		initMapImage(board);
	}
	
	/**
	 * fill mapImage with board blocks and their images.
	 * @param board
	 * @return a map which contains a block and its image.
	 */
	private void initMapImage(Board board){
		board.getMap().entrySet().stream()
				.forEach(entry -> entry.getValue().stream()
						.forEach(block -> {							
							if(!mapImage.containsKey(block))
								try {
									mapImage.put(block, getImageFromBlock(block));
								}catch (IOException | IllegalArgumentException e) {
									System.err.println("Image cannot be found : " + block.toString() + ".gif");
								}
							})
						);
	}
	
	/**
	 * get the image associated with the block
	 * @param block
	 * @return the image associated with the block
	 * @throws IOException if image is not found
	 */
	public Image getImageFromBlock(Block block) throws IOException {
		var imagePath = Paths.get(System.getProperty("user.dir") + "/src/fr/umlv/BabaIsYou/img/" + block.toString() + ".gif");
		InputStream imageInput = Files.newInputStream(imagePath);
		Image img = ImageIO.read(imageInput);
		return img;
	}
	
	/**
	 * draw a Level
	 * @param level	 
	 */	
	public void draw(Level level) {
		level.getContext().renderFrame(graphics -> {	
			
			graphics.setColor(Color.BLACK);
			graphics.fill(new  Rectangle2D.Float((level.getLevelWidth() - level.getCellSize() * level.getBoard().getWidth()) / 2,
					(level.getLevelHeight() - level.getCellSize() * level.getBoard().getHeight()) / 2,
					level.getCellSize() * level.getBoard().getWidth(), level.getCellSize() * level.getBoard().getHeight()));
			
			for(var elem : level.getBoard().getMap().entrySet()) {
				for(var block: elem.getValue()) {		
					graphics.drawImage(mapImage.get(block), (elem.getKey().getCol() * level.getCellSize()) + level.getHorizontalMargin(), (elem.getKey().getLine() * level.getCellSize()) + level.getVerticalMargin(),
							level.getCellSize(), level.getCellSize(), null);
				}
			}			
			
		});
	}	
	
	/**
	 * clear a level
	 * @param level
	 */
	public void clear(Level level) {
		level.getContext().renderFrame(graphics -> graphics.clearRect(0, 0,(int)level.getLevelWidth(), (int)level.getLevelHeight()));
	}
	
}
