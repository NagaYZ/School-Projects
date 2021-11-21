package fr.umlv.BabaIsYou.src;

/**
 * Enum class that represents properties.
 * @author Yassine Abder
 */
public enum Property implements BlockInter{
    YOU, WIN, STOP, PUSH, MELT, HOT, DEFEAT, SINK, BREAK;

	/**
	 * @return Property BlockType
	 */
	@Override
	public BlockType getType() {
		return BlockType.PROPERTY;
	}	    
}
