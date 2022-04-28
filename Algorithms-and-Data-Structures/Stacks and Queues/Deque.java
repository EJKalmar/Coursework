package jsjf;

import jsjf.exceptions.*;

/**
 * COMP 2231 Assignment 2 Stacks and Queues
 * Part 3. Deque.java
 * Erik Jonathan Kalmar T00651562
 * May 26th, 2019
 * Modified Original code from Java Foundations
 */

//Represents an array implementation of a double ended queue
public class Deque<T>
{
    private final static int DEFAULT_CAPACITY = 100;
    private int front, rear, count;
    private T[] queue; 

    /**
     * Creates an empty queue using the specified capacity.
     * @param initialCapacity the initial size of the circular array queue
     */
    public Deque(int initialCapacity)
    {
        front = rear = count = 0;
        queue = (T[]) (new Object[initialCapacity]);
    }

    /**
     * Creates an empty queue using the default capacity.
     */
    public Deque()
    {
        this(DEFAULT_CAPACITY);
    }    

    /**
     * Adds the specified element to the rear of this queue, expanding
     * the capacity of the queue array if necessary.
     * @param element the element to add to the rear of the queue
     * @param position - add to front or rear of the queue?
     */
    public void enqueueRear(T element)
    {
        if (size() == queue.length) 
            expandCapacity();

        queue[rear] = element;
        rear = (rear + 1) % queue.length;
        count++;
    }

    public void enqueueFront(T element)
    {
        if (size() == queue.length) 
            expandCapacity();

        for(int i=count-1;i>=front;i--) //shift all elements to the right
            queue[i+1]=queue[i];

        queue[front]=element; //set first element
        rear = (rear + 1) % queue.length;
        count++;
    }

    /**
     * Creates a new array to store the contents of this queue with
     * twice the capacity of the old one.
     */
    private void expandCapacity()
    {
        T[] larger = (T[]) (new Object[queue.length * 2]);

        for (int scan = 0; scan < count; scan++)
        {
            larger[scan] = queue[front];
            front = (front + 1) % queue.length;
        }

        front = 0;
        rear = count;
        queue = larger;
    }

    /**
     * Removes the element at the front of this queue and returns a
     * reference to it. 
     * @return the element removed from the front of the queue
     * @throws EmptyCollectionException  if the queue is empty
     */
    public T dequeueFront() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("queue");

        T result = queue[front];
        queue[front] = null;
        front = (front + 1) % queue.length;

        count--;

        return result;
    }

    public T dequeueRear() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("queue");

        T result = queue[rear-1];
        queue[rear-1] = null;
        rear = (rear - 1) % queue.length;

        count--;

        return result;
    }

    /** 
     * Returns a reference to the element at the front of this queue.
     * The element is not removed from the queue.  
     * @return the first element in the queue
     * @throws EmptyCollectionException if the queue is empty
     */
    public T first() throws EmptyCollectionException
    {
        if (isEmpty())
            throw new EmptyCollectionException("queue");

        return queue[front];
    }

    /**
     * Returns true if this queue is empty and false otherwise.
     * @return true if this queue is empty 
     */
    public boolean isEmpty()
    {
        return (count==0);
    }

    /**
     * Returns the number of elements currently in this queue.
     * @return the size of the queue
     */
    public int size()
    {
        return count;
    }

    /**
     * Returns a string representation of this queue. 
     * @return the string representation of the queue
     */
    public String toString()
    {
        String result = "";
        for(int i=front;i<count+front;i++)
            result = result + queue[i] + "\n";

        return result;
    }
}
