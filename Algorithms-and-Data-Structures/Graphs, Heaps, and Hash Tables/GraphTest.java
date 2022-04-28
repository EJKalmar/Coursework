/**
 * COMP 2231 Assignment 5.
 * @author Erik Jonathan Kalmar T00651562
 * June 6th, 2019
 */

import jsjf.Graph;

/**
 * Tests and demonstrates implementation of class Graph
 */
public class GraphTest
{
    public static void main(String[] args){
        Graph graph = new Graph();
        graph.addVertex(6);
        graph.addVertex(3);
        graph.addVertex(12);
        graph.addVertex(9);
        graph.addVertex(5);
        graph.addVertex(1);
        
        System.out.println(graph.toString());
        
        System.out.println("12 is at index: " + graph.getIndex(12));
        System.out.println("Is the graph connected?" + graph.isConnected());
        System.out.println("Number of vertices: " + graph.size());
        
        graph.addEdge(1,4);
        graph.addEdge(4,3);
        graph.addEdge(4,5);
        graph.addEdge(5,2);
        graph.addEdge(1,2);
        graph.addEdge(0,4);
        
        System.out.println(graph.toString());
        System.out.println("Is the graph connected?" + graph.isConnected());
        
        graph.removeEdge(1,4);
        graph.removeVertex(3);

        System.out.println(graph.toString());
        System.out.println("Is the graph connected?" + graph.isConnected());
        
        
    }
}
