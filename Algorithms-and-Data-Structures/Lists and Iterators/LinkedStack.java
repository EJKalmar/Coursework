/**
 * COMP 2231 Assignment 3. Lists and Iterators
 * Part 1. Implement a stack using java.util.LinkedList
 * Erik Jonathan Kalmar T00651562
 * May 29th 2019
 */

import java.util.LinkedList;
import java.util.Iterator;

/**
 * A linked implementation of a stack using methods found in java.util.LinkedList
 */
public class LinkedStack<T>
{ 
    LinkedList<T> stack;
    /**
     * Creates an empty stack.
     */
    public LinkedStack()
    {
        stack = new LinkedList();
    }
    
    /**
     * Adds the specified element to the top of this stack.
     * @param element element to be pushed on stack
     */
    public void push(T element)
    {
        stack.push(element);
    }

    /**
     * Removes the element at the top of this stack and returns a
     * reference to it. 
     * @return element from top of stack
     * @throws EmptyCollectionException if the stack is empty
     */
    public T pop()
    {
        return stack.pop();
    }

    /**
     * Returns a reference to the element at the top of this stack.
     * The element is not removed from the stack.  
     * @return element on top of stack
     * @throws EmptyCollectionException if the stack is empty  
     */
    public T peek()
    {   
        return stack.peek();
    }

    /**
     * Returns true if this stack is empty and false otherwise. 
     * @return true if stack is empty
     */
    public boolean isEmpty()
    {
        return stack.isEmpty();
    }

    /**
     * Returns the number of elements in this stack.
     * @return number of elements in the stack
     */
    public int size()
    {
        return stack.size();
    }

   
    /**
     * Returns a string representation of this stack. 
     * @return string representation of the stack
     */
    public String toString()
    {
        Iterator<T> itr = stack.listIterator(0);
        String result = "";
        while(itr.hasNext())
            result = result + itr.next() + "\n";

        return result;
    }
}
