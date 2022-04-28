package jsjf;

import jsjf.exceptions.*;

/**
 * COMP 2231 Assignment 2 Stacks and Queues
 * Part 2. LinkedStack.java
 * Erik Jonathan Kalmar T00651562
 * May 26th, 2019
 * Modified original code from Java Foundations
 */

//Represents a linked implementation of a stack
//Modified such that, when an element is added that would exceed stack size, 
//the bottom element is lost
public class LinkedStack<T> implements StackADT<T>
{
    private int count;  
    private LinearNode<T> top;
    private LinearNode<T> bottom;
    private final static int MAX_SIZE = 100;

    /**
     * Creates an empty stack.
     */
    public LinkedStack()
    {
        count = 0;
        top = null;
        bottom = top;
    }

    /**
     * Adds the specified element to the top of this stack.
     * @param element element to be pushed on stack
     */
    public void push(T element)
    {
        LinearNode<T> temp = new LinearNode<T>(element);

        temp.setNext(top);
        if (top!=null)
            top.setPrevious(temp);
        top = temp;
        count++;

        if(count==MAX_SIZE +1) //if exceeding max size, remove bottom element
        {
            bottom=bottom.getPrevious();
            bottom.setNext(null);
        }
        if (count==1)
            bottom = top;
    }

    /**
     * Removes the element at the top of this stack and returns a
     * reference to it. 
     * @return element from top of stack
     * @throws EmptyCollectionException if the stack is empty
     */
    public T pop() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("stack");

        T result = top.getElement();
        top = top.getNext();
        top.setPrevious(null);
        count--;

        return result;
    }

    /**
     * Returns a reference to the element at the top of this stack.
     * The element is not removed from the stack.  
     * @return element on top of stack
     * @throws EmptyCollectionException if the stack is empty  
     */
    public T peek() throws EmptyCollectionException
    {   
        if (isEmpty())
            throw new EmptyCollectionException("stack");

        return top.getElement();
    }

    /**
     * Returns true if this stack is empty and false otherwise. 
     * @return true if stack is empty
     */
    public boolean isEmpty()
    {
        return (count==0);
    }

    /**
     * Returns the number of elements in this stack.
     * @return number of elements in the stack
     */
    public int size()
    {
        return count;
    }

    /**
     * Returns a string representation of this stack. 
     * @return string representation of the stack
     */
    public String toString()
    {
        String result = "";
        LinearNode current = top;

        while(current!=null)
        {
            result = result + current.getElement() + "\n";
            current = current.getNext();
        }

        return result;
    }
}
