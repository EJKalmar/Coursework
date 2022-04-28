/**
 * COMP 2231 Assignment 3. Lists and Iterators
 * Part 4. Implement a queue using java.util.ArrayList
 * Erik Jonathan Kalmar T00651562
 * May 29th 2019
 */

import java.util.ArrayList;
import java.util.Iterator;

/**
 * An array implementation of a queue using methods found in java.util.ArrayList
 */
public class ArrayQueue<T>
{
    ArrayList<T> queue;
    /**
     * Creates an empty queue.
     */
    public ArrayQueue()
    {
        queue = new ArrayList();
    }

    /**
     * Adds the specified element to the tail of this queue.
     * @param element the element to be added to the tail of the queue
     */
    public void enqueue(T element)
    {
        queue.add(element);
    }

    /**
     * Removes the element at the head of this queue and returns a
     * reference to it. 
     * @return the element at the head of this queue
     * @throws EmptyCollectionException if the queue is empty
     */
    public T dequeue()
    {
        return queue.remove(0);
    }

    /**
     * Returns a reference to the element at the head of this queue.
     * The element is not removed from the queue.  
     * @return a reference to the first element in this queue
     * @throws EmptyCollectionsException if the queue is empty
     */
    public T first()
    {
        return queue.get(0);
    }

    /**
     * Returns true if this queue is empty and false otherwise. 
     * @return true if this queue is empty 
     */
    public boolean isEmpty()
    {
        return queue.isEmpty();
    }

    /**
     * Returns the number of elements currently in this queue.
     * @return the number of elements in the queue
     */
    public int size()
    {
        return queue.size();
    }

    /**
     * Returns a string representation of this queue. 
     * @return the string representation of the queue
     */
    public String toString()
    {
        Iterator<T> itr = queue.iterator();
        String result = "";
        while(itr.hasNext())
            result = result + itr.next() + "\n";

        return result;
    }
}
