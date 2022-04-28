package jsjf;

/**
 * Write a description of class DequeTest here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class DequeTest extends Deque
{
    public static void main(String[] args)
    {
        Deque queue = new Deque();
        queue.enqueueRear(1);
        queue.enqueueRear(2);
        queue.enqueueRear(3);
        queue.enqueueRear(4);
        queue.enqueueRear(5);
        queue.enqueueRear(6);
        queue.enqueueRear(7);
        queue.enqueueRear(8);
        queue.enqueueRear(9);
        queue.enqueueRear(10);
        queue.enqueueRear(11);
        queue.enqueueRear(12);
        System.out.println(queue.toString());
        queue.enqueueFront(3);
        System.out.println(queue.toString());
        queue.enqueueFront(4);
        System.out.println(queue.toString());
        queue.dequeueFront();
        System.out.println(queue.toString());
        queue.dequeueRear();
        System.out.println(queue.toString());
    }
}
