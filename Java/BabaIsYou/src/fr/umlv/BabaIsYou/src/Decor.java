package fr.umlv.BabaIsYou.src;

/**
 * Enum class that represents decorative Blocks.
 * @author Abder
 */
public enum Decor implements BlockInter{
	TILE, GRASS, BRICK, FLOWER;

	/**
	 * @return Decor BlockType
	 */
	@Override
	public BlockType getType() {
		return BlockType.DECOR;
	}
}
