/**
 * COMP 2231 Assignment 4 Trees
 * DecisionTree demonstration
 * @author Erik Jonathan Kalmar T00651562
 * @date June 1, 2019
 */

import java.io.*;

/**
 * Demonstrates the use of a decision tree to analyze eating disorders.
 */
public class EatingDisorderAnalyzer
{
	/**
	 *  Asks questions of the user to diagnose a medical problem.
	 */
	public static void main(String[] args) throws FileNotFoundException
	{
		System.out.println("So, you think you have an eating disorder.");

		DecisionTree expert = new DecisionTree("EatingDisorder.txt");
		expert.evaluate();
	}
}
