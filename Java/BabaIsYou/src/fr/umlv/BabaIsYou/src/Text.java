package fr.umlv.BabaIsYou.src;

/**
 * Enum class that represents Text Blocks.
 * @author Yassine
 *
 */
public enum Text implements BlockInter{
    Text_BABA, Text_LAVA, Text_ROCK, Text_SKULL, Text_WALL, Text_WATER,
	Text_FLAG, Text_PICKAXE;

	/**
	 * @return Text BlockType
	 */
	@Override
	public BlockType getType() {
		return BlockType.TEXT;
	}	

}
