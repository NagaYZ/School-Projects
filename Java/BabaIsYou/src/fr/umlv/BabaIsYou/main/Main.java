package fr.umlv.BabaIsYou.main;

import java.awt.Color;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import fr.umlv.BabaIsYou.src.*;

import fr.umlv.zen5.Application;
import fr.umlv.zen5.Event;
import fr.umlv.zen5.KeyboardKey;
import fr.umlv.zen5.Event.Action;


/**
 * Main.
 * @author Yassine Abder
 *
 */
public class Main{	

	public static void main(String[] args) {
		//RUN 		
		Application.run(new Color(28,28,46), context -> {	
			//COMMAND LINE ARGUMENTS , and LEVEL INIT
			Set<Map<Name, Property>> argSet = new HashSet<>();
			ArrayList<Level> listLevel = new ArrayList<>();				
			try {
				Arguments.parseArgs(args, argSet, listLevel, context);
			} catch (IOException e1) {
				System.err.println(e1.getMessage());
				System.exit(1);
			}	
			var levelIterator = listLevel.iterator();
			
			//START
			while(levelIterator.hasNext()) {				
				var level = levelIterator.next();				
				level.refresh();//draw first to avoid having to make a move to see the level		
				//WIN or LOSE
				if(level.getBoard().win() || level.getBoard().lose())//here in case of instant win/loss when command line are used.
				{						
					try { //pause a little to see the move before applying the action (for esthetic purpose only).
						Thread.sleep(400);									
					} catch (InterruptedException e) {e.printStackTrace();}	
					level.clear();
					continue;
				}	
				//MAIN LOOP
				for(;;) {
					Event event = context.pollOrWaitEvent(1000);
					if (event != null) { 								
						Action action = event.getAction();
						var key = event.getKey();
						if (action == Action.KEY_PRESSED) {					
							if(key == KeyboardKey.Q) {/*press Q to exit*/
								System.out.println("Exited manually");
								level.clear();
								break;
							}		
							//MOVEMENT
							if(level.getBoard().move(key)) {//if a move has been made refresh/redraw, execute action...
								//REFRESH / REDRAW	
								level.refresh();					
								//WIN or LOSE
								if(level.getBoard().win() || level.getBoard().lose())
								{						
									try { //pause a little to see the move before applying the action (for esthetic purpose only).
										Thread.sleep(400);									
									} catch (InterruptedException e) {e.printStackTrace();}	
									level.clear();
									break;
								}
							}					
						}
					}
				}
			}
			context.exit(0);
		});		
	}	
}
