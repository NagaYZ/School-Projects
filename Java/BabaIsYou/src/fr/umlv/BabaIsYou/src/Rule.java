package fr.umlv.BabaIsYou.src;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

/**
 * Class that manages the rules in the board.
 * @author Yassine Abder
 */

public class Rule {
	private Map<Property, Set<Name>> ruleMap = new HashMap<>();	
	private Set<Map<Name, Property>> argRule = new HashSet<>();
	
	/**
	 * init ruleMap with all Properties
	 */
	public Rule(){
		for(Property prop: Property.values()) 
			ruleMap.put(prop, new HashSet<Name>());	
	}

	/**
	 * set argRule 
	 * @param argRule
	 */
	public void setArgRule(Set<Map<Name, Property>> argRule) {
		this.argRule = argRule;
	}

	/**
	 * get the property of the block
	 * @param property
	 * @param block
	 * @return true if the block has the property
	 */
	public boolean getRule(Property property, Block block) {
		if(block.getType().equals(BlockType.NAME))
			return ruleMap.get(property).contains(Name.valueOf(block.toString()));
		return property.equals(Property.PUSH) && !block.getType().equals(BlockType.DECOR);
	}
	
	/**
	 * @param board
	 * @param block
	 * @param coord
	 * @return true if a Block is Pushable
	 */
	public boolean isPushable(Board board, Block block, Coordinates coord){		
		if(getRule(Property.PUSH, block) || getRule(Property.YOU, block))
			return true;
		return  !getRule(Property.STOP, block) && !block.getType().equals(BlockType.DECOR);
		
	}
	
	/**
	 * @param board
	 * @param block
	 * @param coord
	 * @return true if a Block can be moved to the coord Coordinates
	 */
	public boolean isMoveable(Board board, Block block, Coordinates coord){
		return block.getType().equals(BlockType.DECOR) || (!getRule(Property.PUSH, block) && !getRule(Property.STOP, block) && !getRule(Property.YOU, block))  ;
	}
	
	/**
	 * Set the property to every block in the list.
	 * @param listTextBlock
	 * @param prop
	 */
	private void setProp(Name block, Property prop) {
		Objects.requireNonNull(prop);		
		ruleMap.get(prop).add(block);			
	}
	
	/**
	 * Reset the rule, search rules in the Board and update ruleMap with them.
	 * <br>also set the command line rules if any.
	 * @param board
	 */
	public void updateRules(Board board) {	
		resetRule();
		for(var elem : board.getMap().entrySet()) {		
			var iteratorTextBlock = elem.getValue().stream().filter(block -> block.getType().equals(BlockType.TEXT)).iterator();
			if(iteratorTextBlock.hasNext())
				getallRules(board, iteratorTextBlock.next(), elem.getKey());																
		}	
		setArgsRules();
	}
	
	/**
	 * Set all command line rules.
	 */
	private void setArgsRules() {		
		for(var map: argRule) {
			for(var entry: map.entrySet())
				setProp(entry.getKey(), entry.getValue());		
		}	
	}

	/**
	 * get Vertical/Horizontal Rule in board, and add them to ruleMap
	 * @param board
	 * @param TextBlock
	 * @param coord
	 */
	private void getallRules(Board board, Block TextBlock, Coordinates coord){
		if(board.getMap().entrySet().stream() //if an Operator is next to a Text Block (vertically or horizontally) 
				.filter(opeCoord -> opeCoord.getKey().getLine() == coord.getLine() + 1 && opeCoord.getKey().getCol()  == coord.getCol()
								 || opeCoord.getKey().getCol()  == coord.getCol()  + 1 && opeCoord.getKey().getLine() == coord.getLine())
				.filter(ope -> ope.getValue().stream()
						.anyMatch(block -> block.getType().equals(BlockType.OPERATOR)))
				.iterator().hasNext())
		{
			board.getMap().entrySet().stream()//look for Properties next to Operator (vertically or horizontally) , and add them to the map
			.filter(propCoord -> propCoord.getKey().getLine() == coord.getLine() + 2 && propCoord.getKey().getCol()  == coord.getCol()
							  || propCoord.getKey().getCol()  == coord.getCol()  + 2 && propCoord.getKey().getLine() == coord.getLine())
			.map(allProp -> allProp.getValue())
			.forEach(set -> set.stream().filter(isProp -> isProp.getType().equals(BlockType.PROPERTY))
					.forEach(prop ->
						setProp(Name.valueOf(TextBlock.toString().substring(5)), Property.valueOf(prop.toString()))
						));
		}		
	}
	
	/**
	 * clear all values of ruleMap
	 */
	private void resetRule() {
		ruleMap.values().forEach(Set::clear);
	}
}
