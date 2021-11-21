package fr.umlv.BabaIsYou.src;

import java.util.Objects;

/**
 * Record that represents a Block.
 * @author Yassine
 *
 */
public record Block(BlockInter name){

	public Block(BlockInter name) {
		this.name = Objects.requireNonNull(name, "a Block cannot be null");
	}
	
	/**
	 * @return the type of the block
	 */
	public BlockType getType() {
		return name.getType();
	}

	/**
	 * @return String value of name
	 */
	@Override
	public String toString() {
		return name.toString();
	}
	
}
