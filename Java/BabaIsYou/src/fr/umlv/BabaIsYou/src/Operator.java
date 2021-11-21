package fr.umlv.BabaIsYou.src;

/**
 * Enum class that represents operator Blocks.
 * @author Abder
 */
public enum Operator implements BlockInter{
	IS;

	/**
	 * @return Operator BlockType
	 */
	@Override
	public BlockType getType() {
	
		return BlockType.OPERATOR;
	}
}
