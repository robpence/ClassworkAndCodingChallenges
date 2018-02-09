//Created by: Robert Pence
//Date: 1/18/2018

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

public class solution {

	public static void main(String[] args) {

		//Input Parsing
		System.out.println("Enter input: ");
		Scanner sc = new Scanner(System.in);
		String input = sc.nextLine();
		String[] costs = input.split(" ");
		String word1 = sc.next().toLowerCase();
		String word2 = sc.next().toLowerCase();
		sc.close();
		
		//check if inputs are valid
		if(costs.length != 4){
			System.out.println("Invalid input: need 4 costs.");
			System.out.println("Sample Input: ");
			System.out.println("1 2 3 4");
			System.out.println("riddle");
			System.out.println("fiddle");
			return;
		}
		if(word1.length() <= 2 || word2.length() <= 2){
			System.out.println("Invalid input: words must be equal to or longer than 3 letters.");
			System.out.println("Sample Input: ");
			System.out.println("1 2 3 4");
			System.out.println("riddle");
			System.out.println("fiddle");
			return;
		}
		if(word1.equals(word2)){
			System.out.println("Invalid input: words must be different.");
			return;
		}
		
		//read in words
		solution ladder = new solution();
        List<String> dictionary = ladder.readWords();
        dictionary.add(word1);
        dictionary.add(word2);
        
        //convert words to nodes
        List<Node> nodes = new ArrayList<Node>();
        for (String word : dictionary) {
        	Node newNode = new Node(word);
        	nodes.add(newNode);
        }
        
        //add edges between words
        for(Node node1: nodes){
        	for(Node node2: nodes){
        		//adding a letter
        		if(canAddLetter(node1.value, node2.value)){
        			Edge e = new Edge(node2, Integer.parseInt(costs[0]));
        			node1.adjacencies.add(e);
        		}
        		//removing a letter
        		if(canRemoveLetter(node1.value, node2.value)){
        			Edge e = new Edge(node2, Integer.parseInt(costs[1]));
        			node1.adjacencies.add(e);
        		}
        		//change one letter
        		if (canChangeOneLetter(node1.value, node2.value)) {
        			Edge e = new Edge(node2, Integer.parseInt(costs[2]));
        			node1.adjacencies.add(e);
        		}
        		//is an anagram
        		if(isAnagram(node1.value, node2.value)) {
        			Edge e = new Edge(node2, Integer.parseInt(costs[3]));
        			node1.adjacencies.add(e);
        		}
        	}
        }
        
		//Run Dijkstra on graph
  		computePaths(nodes.get(nodes.size() - 2));
  		List<Node> path = getShortestPathTo(nodes.get(nodes.size() - 1));
  		
  		//Print formatted output
  		if(path.get(path.size() - 1).shortestDistance == Double.POSITIVE_INFINITY){
  			System.out.println("(ouput: -1)");
  		}else{
  			System.out.print("(output: " + path.get(path.size() - 1).shortestDistance + ")");
  			System.out.print("(");
  			int i = 0;
  			for(Node node: path){
  				System.out.print(node.value);
  				if(i++ != path.size() - 1){
  					System.out.print(" - ");
  			    }
  			}
  			System.out.print(")");
  		}
	}
	
	//Runs Dijkstra's algorithm on the graph.
	public static void computePaths(Node startWord){
		startWord.shortestDistance=0;

		PriorityQueue<Node> queue = new PriorityQueue<Node>();
		queue.add(startWord);

		while(!queue.isEmpty()){
			Node word1 = queue.poll();
			/*visit the adjacencies, starting from 
			the nearest node(smallest shortestDistance)*/
			for(Edge e: word1.adjacencies){
				Node word2 = e.target;
				double weight = e.weight;
				double distanceFromWord1 = word1.shortestDistance+weight;
				if(distanceFromWord1<word2.shortestDistance){
					/*remove v from queue for updating 
					the shortestDistance value*/
					queue.remove(word2);
					word2.shortestDistance = distanceFromWord1;
					word2.parent = word1;
					queue.add(word2);

				}
			}
		}
	}

	//Returns list of nodes that are the shortest path.
	public static List<Node> getShortestPathTo(Node target){
		//trace path from target to source
		List<Node> path = new ArrayList<Node>();
		for(Node node = target; node!=null; node = node.parent){
			path.add(node);
		}
		//reverse the order so that it will be from source to target
		Collections.reverse(path);
		return path;
	}
	
	//Easiest way I know to check for anagrams.
	private static boolean isAnagram(String s1, String s2) {
		if(s1.equals(s2)) return false;
		char[] word1 = s1.replaceAll("[\\s]", "").toCharArray();
	    char[] word2 = s2.replaceAll("[\\s]", "").toCharArray();
	    Arrays.sort(word1);
	    Arrays.sort(word2);
	    return Arrays.equals(word1, word2);
	}
	
	//Checks if string1 can be turned into string2 by removing a letter.
	private static boolean canRemoveLetter(String s1, String s2){
		if (s1.length() == s2.length()){
			return false;
		}
		//make sure s2 is smaller
		if(s1.length() > s2.length()){
			for(int i = 0; i < s1.length(); i++) {
				String newString = new StringBuilder(new String(s1)).deleteCharAt(i).toString();
				if(newString.equals(s2)){
					return true;
				}
			}
		}
        return false;
	}
	
	//Checks if string1 can be transformed into string2 by adding a letter.
	private static boolean canAddLetter(String s1, String s2){
		if (s1.length() == s2.length()){
			return false;
		}
		//make sure s1 is smaller
		if(s1.length() < s2.length()){
			for (char alphabet = 'a'; alphabet <= 'z'; alphabet++) {
				for(int i = 0; i < s1.length() + 1; i++) {
					String newString = new StringBuilder(new String(s1)).insert(i, alphabet).toString();
					if(newString.equals(s2)){
						return true;
					}
				}
			}
		}
        return false;
	}
	
	//Checks to see if string1 can be transformed into string2 by changing a single letter.
	private static boolean canChangeOneLetter(String s1, String s2) {
		if (s1.length() != s2.length()){ 
			return false;
		}
		int diff = 0;
		//loop through both strings, if they are only different by one letter return true.
		for (int i=0; i<s1.length() && diff < 2; ++i){
			if (s1.charAt(i) != s2.charAt(i)) ++diff;
		}
		return (diff == 1);  
	}
	
	//read in words from a text file that form the dictionary to check for valid words.
	//text file must be named "words.txt"
    private List<String> readWords() {
        List<String> words = new ArrayList<String>();
        try {
            BufferedReader br = new BufferedReader(new FileReader(new File("words.txt")));
            String word = null;
            while ((word = br.readLine()) != null) {
                words.add(word.toLowerCase());
            }
            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return words;
    }

}

//define Node
class Node implements Comparable<Node>{
	public final String value;
	public List<Edge> adjacencies = new ArrayList<Edge>();
	public double shortestDistance = Double.POSITIVE_INFINITY;
	public Node parent;

	public Node(String val){
		value = val;
	}

	public String toString(){
			return value;
	}

	public int compareTo(Node other){
		return Double.compare(shortestDistance, other.shortestDistance);
	}
}

//define Edge
class Edge{
	public final Node target;
	public final double weight;
	public Edge(Node targetNode, double weightVal){
		target = targetNode;
		weight = weightVal;
	}
}
