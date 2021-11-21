package fr.umlv.BabaIsYou.src;

import java.io.IOException;

import java.nio.file.DirectoryStream; //to get folder
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path; 
import java.nio.file.Paths; //to get path of file

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import fr.umlv.zen5.ApplicationContext;

/**
 * Class that manages command line arguments.
 * @author Yassine
 *
 */
public class Arguments {

	/**
	 * Read arguments, if --execute option is used, read the 3 next argument, if syntax is valid then add it
	 * to argSet else ignore the argument and continue reading.
	 *  <br> example : (--execute ROCK IS PUSH), ROCK will always be pushable.
	 * @param argSet
	 * @param args 
	 */
	public static void parseArgsExecute(Set<Map<Name, Property>> argSet, String[] args) {		
		Map<Name, Property> argMap = new HashMap<>();
		for(int i = 0; i < args.length; i++) {
			if(args[i].equals("--execute")){
				try {
					Name.valueOf(args[i + 1]);	
					Operator.valueOf(args[i + 2]);
					i++;
					Property.valueOf(args[i + 2]);	
					i++;
					argMap.put(Name.valueOf(args[i - 1]), Property.valueOf(args[i + 1]));					
					argSet.add(Map.copyOf(argMap));	
					argMap.clear();
				}catch(IllegalArgumentException e) {
					System.err.println("Invalid --execute argument : " + args[i] + " " + args[i + 1] + " " + args[i + 2]); 
				}catch(ArrayIndexOutOfBoundsException e) {
					//read rest of arguments if the syntax of current argument is not valid.
				}
			}
		}	
	}

	/**
	 * read a file ,create a level, create a board,add command line rules if any, add the level to the listLevel if everything went well.
	 * @param fileName
	 * @param listLevel
	 * @param context
	 * @param argSet
	 * @return true if the file was read completely successfully, false else
	 * @throws IOException 
	 */
	public static boolean readFile(Path fileName, ArrayList<Level> listLevel, ApplicationContext context, Set<Map<Name, Property>> argSet) throws IOException {	
		try {
			var fileAllLines = Files.readAllLines(fileName);			
			Parser parse = new Parser(fileAllLines);
			Board board = parse.createBoard();
			if(board == null) 
				return false;
			
			Level level = new Level(context, board);			
			level.getBoard().getRules().setArgRule(argSet);//add command line rules
			listLevel.add(level);	//if level was parsed successfully then add it to the list of Level	
		}catch(IllegalArgumentException |  ArrayIndexOutOfBoundsException e) { //catch exceptions that can be thrown while reading a file and return false 
			return false;
		}		
		return true;
	}
	
	/**
	 * Read arguments, if --levels option is used, open the folder and read all file in folder.
	 * @param listLevel
	 * @param args
	 * @param context
	 * @param argSet
	 * @return false if invalid argument (non existent/not a folder) after --levels .
	 */
	public static boolean parseArgsLevels(ArrayList<Level> listLevel, String[] args, ApplicationContext context, Set<Map<Name, Property>> argSet) {
		for(int i = 0; i < args.length; i++) {
			if(args[i].equals("--levels")){
				try { // try to open and read folders file					
					Path folderPath = Paths.get(System.getProperty("user.dir") + "/src/fr/umlv/BabaIsYou/" + args[i + 1]);				
					DirectoryStream<Path> folderStream = Files.newDirectoryStream(folderPath); 
				    for (var file: folderStream) {
				    	if(!readFile(file, listLevel, context, argSet)) //if file error 
							System.err.println("Error while reading file : " + file.getFileName().toString());	        
				    }	
				    return true;
				} catch (InvalidPathException | IOException e) {//if invalid path file, IOException catched here to continue because default level is used as last resort
					System.err.println("Error while reading file : " + args[i + 1]);
				}
			}			
		}		
		return false;
	}
	
	/**
	 * read arguments, if --level option is used, read the file <br> example : ( --level level1.txt )
	 * @param listLevel
	 * @param args
	 * @param context
	 * @param argSet
	 * @return false if invalid or non-existent argument after --level .
	 */
	public static boolean parseArgsLevel(ArrayList<Level> listLevel, String[] args, ApplicationContext context, Set<Map<Name, Property>> argSet) {	
		for(int i = 0; i < args.length; i++) {
			if(args[i].equals("--level")){
				try {					
					Path filePath = Paths.get(System.getProperty("user.dir") + "/src/fr/umlv/BabaIsYou/levels/" + args[i + 1]);
					if(!readFile(filePath, listLevel, context, argSet)) { // if file error
						System.err.println("Error while reading file maybe corrupted: " + args[i + 1]);	
						break;
					}
					return true;
				}catch (InvalidPathException | IOException e) {//if invalid path file, IOException catched here to continue because default level is used as last resort
					System.err.println("Invalid level file : " + args[i + 1]);
					break;
				}
			}
		}	
		return false;
	}
	
	/**
	 * read arguments and execute possible option,
	 *  if no level option used or if they are invalid, default level is added to listLevel .
	 *  <br> Print the enabled command.
	 * @param args
	 * @param argSet
	 * @param listLevel
	 * @param context
	 * @throws IOException
	 */
	public static void parseArgs(String[] args, Set<Map<Name, Property>> argSet, ArrayList<Level> listLevel, ApplicationContext context) throws IOException {	
		parseArgsExecute(argSet, args);
		if(!parseArgsLevels(listLevel, args, context, argSet) && !parseArgsLevel(listLevel, args, context, argSet)) {  
			// no need to check --level if --levels is valid all level are already in the List.			
			// if --levels and --level failed then add default level		
			try {
				Path defaultLevelDest = Paths.get(System.getProperty("user.dir") + "/src/fr/umlv/BabaIsYou/levels/default-level.txt");
				if(!readFile(defaultLevelDest, listLevel, context, argSet))
					System.err.println("Error while reading file maybe corrupted: default-level.txt" );	
			} catch (InvalidPathException | NullPointerException  e) { 
				System.err.println("Invalid default level path");
			}				
		}			
		//DISPLAY ENABLED COMMAND.
		System.out.print("Command enabled:");
		if(argSet.isEmpty())
			System.out.println("  None.");
		argSet.forEach(map -> map.entrySet().forEach(e -> System.out.println("\t-" + e.getKey() + " IS " + e.getValue())));		
	}	
	
}
