package jsjf;

/**
 * COMP 2231 Assignment 2 Stacks and Queues
 * Part 4. PalindromeTest.java
 * Erik Jonathan Kalmar T00651562
 * May 26th, 2019
 * Modified original code by Java Foundations
 */

//Implementation of a node to be used in LinkedStack
//Modified to include reference and functionality for previous nodes
public class LinearNode<T>
{
    private LinearNode<T> next;
    private LinearNode<T> previous;
    private T element;

    /**
     * Creates an empty node.
     */
    public LinearNode()
    {
        next = null;
        previous = null;
        element = null;
    }

    /**
     * Creates a node storing the specified element.
     * @param elem element to be stored
     */
    public LinearNode(T elem)
    {
        next = null;
        previous = null;
        element = elem;
    }

    /**
     * Returns the node that follows this one.
     * @return reference to next node
     */
    public LinearNode<T> getNext()
    {
        return next;
    }

    /**
     * Returns the node preceding this one.
     * @return reference to the previous node
     */
    public LinearNode<T> getPrevious()
    {
        return previous;
    }

    /**
     * Sets the node that follows this one.
     * @param node node to follow this one
     */
    public void setNext(LinearNode<T> node)
    {
        next = node;
    }

    /**
     * Sets the node before this one
     * @param node preceding this node
     */
    public void setPrevious(LinearNode<T> node)
    {
        previous = node;
    }

    /**
     * Returns the element stored in this node.
     * @return element stored at the node
     */
    public T getElement()
    {
        return element;
    }

    /**
     * Sets the element stored in this node.
     * @param elem element to be stored at this node
     */
    public void setElement(T elem)
    {
        element = elem;
    }
}
