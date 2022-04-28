package jsjf;

import java.util.*;
/**
 * COMP 2231 Assignment 2 Stacks and Queues
 * Part 4. PalindromeTest.java
 * Erik Jonathan Kalmar T00651562
 * May 26th, 2019
 */

//checks to see if a given string is a palindrome
public class PalindromeTest
{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        boolean result=false;
        int size;

        System.out.println("Enter a string: ");
        String string = scan.nextLine(); //get input as string
        char[] StringArray = string.toCharArray(); //converts input to an array of char
        size = StringArray.length;

        Stack stack = new Stack(); //creates a stack from the input array
        for(int i=0;i<size;i++)
            stack.push(StringArray[i]);

        Queue queue = new LinkedList(); //creates a queue from the input array
        for(int i=0;i<size;i++)
            queue.add(StringArray[i]);

        //compares top of stack to front of queue and removes each one respectively
        while(stack.pop() == queue.remove())
        {
            if (stack.isEmpty() && queue.isEmpty())//if the stack and queue are empty
            {
                result = true; //then the string is a palindrome
                break;
            }           
        }

        if (result == true)
            System.out.println("The string is a palindrome!");
        else
            System.out.println("The string is not a palindrome");

    }
}
