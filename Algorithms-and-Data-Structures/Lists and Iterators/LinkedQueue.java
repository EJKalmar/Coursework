
/**
 * COMP 2231 Assignment 3. Lists and Iterators
 * Part 3. Implement a queue using java.util.LinkedList
 * Erik Jonathan Kalmar T00651562
 * May 29th 2019
 */
import java.util.LinkedList;
import java.util.Iterator;

/**
 * A linked implementation of a queue using methods found in java.util.LinkedList
 */
public class LinkedQueue<T>
{ 
    LinkedList<T> queue;
    /**
     * Creates an empty queue.
     */
    public LinkedQueue()
    {
        queue = new LinkedList();
    }

    /**
     * Adds the specified element to the tail of this queue.
     * @param element the element to be added to the tail of the queue
     */
    public void enqueue(T element)
    {
        queue.addLast(element);
    }

    /**
     * Removes the element at the head of this queue and returns a
     * reference to it. 
     * @return the element at the head of this queue
     * @throws EmptyCollectionException if the queue is empty
     */
    public T dequeue()
    {
        return queue.removeFirst();
    }

    /**
     * Returns a reference to the element at the head of this queue.
     * The element is not removed from the queue.  
     * @return a reference to the first element in this queue
     * @throws EmptyCollectionsException if the queue is empty
     */
    public T first()
    {
        return queue.getFirst();
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
        Iterator<T> itr = queue.listIterator(0);
        String result = "";
        while(itr.hasNext())
            result = result + itr.next() + "\n";

        return result;
    }
}
