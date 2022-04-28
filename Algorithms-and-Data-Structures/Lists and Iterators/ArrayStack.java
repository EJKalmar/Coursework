/**
 * COMP 2231 Assignment 3. Lists and Iterators
 * Part 2. Implement a stack using java.util.ArrayList
 * Erik Jonathan Kalmar T00651562
 * May 29th 2019
 */

import java.util.ArrayList;
import java.util.Iterator;

/**
 * An array implementation of a stack using methods found in java.util.ArrayList
 */
public class ArrayStack<T>
{
    private final static int DEFAULT_CAPACITY = 100;
    ArrayList<T> stack;

    /**
     * Creates an empty stack using the default capacity.
     */
    public ArrayStack()
    {
        this(DEFAULT_CAPACITY);
    }

    /**
     * Creates an empty stack using the specified capacity.
     * @param initialCapacity the initial size of the array 
     */
    public ArrayStack(int initialCapacity)
    {
        stack = new ArrayList(initialCapacity);      
    }

    /**
     * Adds the specified element to the top of this stack, expanding
     * the capacity of the array if necessary.
     * @param element generic element to be pushed onto stack
     */
    public void push(T element)
    {
        stack.add(element);
    }

    /**
     * Removes the element at the top of this stack and returns a
     * reference to it. 
     * @return element removed from top of stack
     * @throws EmptyCollectionException if stack is empty 
     */
    public T pop()
    {
        return stack.remove(stack.size());
    }

    /**
     * Returns a reference to the element at the top of this stack.
     * The element is not removed from the stack.  
     * @return element on top of stack
     * @throws EmptyCollectionException if stack is empty
     */
    public T peek()
    {
        return stack.get(stack.size());
    }

    /**
     * Returns true if this stack is empty and false otherwise. 
     * @return true if this stack is empty
     */
    public boolean isEmpty()
    {       
        return stack.isEmpty();
    }

    /**
     * Returns the number of elements in this stack.
     * @return the number of elements in the stack
     */
    public int size()
    {
        return stack.size();
    }

    /**
     * Returns a string representation of this stack. 
     * @return a string representation of the stack
     */
    public String toString()
    {
        String result = "";
        Iterator<T> itr = stack.iterator();
        while(itr.hasNext())
            result = result + itr.next() + "\n";
        return result;
    }
}
