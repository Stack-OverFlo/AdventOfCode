import java.io.*;
import java.nio.file.*;
import java.util.*;

public class day05_part1 {

    public static int findMidList(int[] updates) {
	int len = (updates.length / 2) + 1;
	return updates[len - 1];
    }

    public static boolean checkRuleInList(int[] pages, int[] updates)
    {
	int r1 = pages[0];
	int r2 = pages[1];
	int posR1 = -1;
	int posR2 = -1;
	for (int i = 0 ; i < updates.length ; i++) {
	    if (updates[i] == r1)
		posR1 = i;
	    if (updates[i] == r2)
		posR2 = i;
	}
	return posR1 < posR2;
	
    }
    
    public static boolean checkValidList(List<int[]> rules, int[] updates) {

	for (int[] pageRules : rules) {
	    boolean foundRule =
		Arrays.stream(pageRules).allMatch(num ->
						   Arrays.stream(updates).anyMatch(x -> x == num));
	    if (foundRule) {
		if (checkRuleInList(pageRules, updates) == false)
		    return false;
	    }
	}
	return true;
    }
    
    public static int checkRules(List<int[]> rules, List<String> updates)
    {
	int midLine = 0;
	String[] updateParts;
	int[] updatesInt;
	for (String update : updates) {
	    updateParts = update.split(",");
	    updatesInt = new int[updateParts.length];
	    for (int i = 0; i < updateParts.length; i++)
		updatesInt[i] = Integer.parseInt(updateParts[i]);
	    if (checkValidList(rules, updatesInt) == true)
		midLine += findMidList(updatesInt);
	}
	System.out.println(midLine);
	return midLine;
    }

    public static void parseInput(String input) {
	String[] resSplit = input.split("\n\n");
	if (resSplit.length != 2) {
	    System.out.println("Wrong input file format");
	    return ;
	}
	String[] pageRules = resSplit[0].split("\n");
	String[] updateLine = resSplit[1].split("\n");
	List<int[]> rules = new ArrayList<>();
	List<String> updates = Arrays.asList(updateLine);
	for (String line : pageRules) {
	    String[] nbs = line.split("\\|");
	    rules.add(new int[]{Integer.parseInt(nbs[0]), Integer.parseInt(nbs[1])});
	}
	checkRules(rules, updates);
    }

    public static void main(String[] args) {
        if (args.length < 1) {                            
            System.out.println("Usage: java day05_part1 <inputFile>");
            return ;
        }                                                                
        String inputFile = args[0];                                                   
        List<String> lines = new ArrayList<>();
        try {                                     
            lines = Files.readAllLines(Paths.get(inputFile));
	    String fileContent = String.join("\n", lines);
	    parseInput(fileContent);
        } catch (IOException e) {                     
            System.out.println("Error can't read fuile : " + e.getMessage());
            return ;
        }
    }
}
