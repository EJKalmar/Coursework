package jsjf;

import jsjf.exceptions.*;
import java.util.Arrays;

/**
 * COMP 2231 Assignment 2 Stacks and Queues
 * Part 1. ArrayStack.java
 * Erik Jonathan Kalmar T00651562
 * May 26th, 2019
 * Modified original code from Java Foundations
 */

//An array implementation of a stack in which the bottom of the stack is fixed at index 0
//Modified such that stack[top] points to the top element of the stack
public class ArrayStack<T> implements StackADT<T>
{
    private final static int DEFAULT_CAPACITY = 100;

    private int top;  
    private T[] stack;

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
        top = -1;
        stack = (T[])(new Object[initialCapacity]);
    }

    /**
     * Adds the specified element to the top of this stack, expanding
     * the capacity of the array if necessary.
     * @param element generic element to be pushed onto stack
     */
    public void push(T element)
    {
        if (size() == stack.length) 
            expandCapacity();   
        top++;
        stack[top] = element;
    }

    /**
     * Creates a new array to store the contents of this stack with
     * twice the capacity of the old one.
     */
    private void expandCapacity()
    {
        stack = Arrays.copyOf(stack, stack.length * 2);   
    }

    /**
     * Removes the element at the top of this stack and returns a
     * reference to it. 
     * @return element removed from top of stack
     * @throws EmptyCollectionException if stack is empty 
     */
    public T pop() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("stack");

        T result = stack[top];
        stack[top] = null;
        top--;

        return result;
    }

    /**
     * Returns a reference to the element at the top of this stack.
     * The element is not removed from the stack.  
     * @return element on top of stack
     * @throws EmptyCollectionException if stack is empty
     */
    public T peek() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("stack");

        return stack[top];
    }

    /**
     * Returns true if this stack is empty and false otherwise. 
     * @return true if this stack is empty
     */
    public boolean isEmpty()
    {       
        return (top==-1);
    }

    /**
     * Returns the number of elements in this stack.
     * @return the number of elements in the stack
     */
    public int size()
    {
        return top+1;
    }

    /**
     * Returns a string representation of this stack. 
     * @return a string representation of the stack
     */
    public String toString()
    {
        String result = "";

        for(int i=0;i<=top;i++)
            result = result + stack[i] + "\n";

        return result;
    }
}

