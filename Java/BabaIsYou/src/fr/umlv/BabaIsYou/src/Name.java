package fr.umlv.BabaIsYou.src;


/**
 * Enum class that represents playable Blocks.
 * @author Yassine
 *
 */
public enum Name implements BlockInter {
	WATER, LAVA, ROCK, WALL, SKULL, FLAG, BABA, PICKAXE ;

	@Override
	public BlockType getType() {
		// TODO Auto-generated method stub
		return BlockType.NAME;
	}	

}
