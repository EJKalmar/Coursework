package jsjf;

/**
 * Write a description of class LinkedStackTest here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class LinkedStackTest<T> extends LinkedStack<T>
{
    public static void main (String[] args)
    {
        LinkedStack stack = new LinkedStack();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);
        System.out.println(stack.toString());
        stack.push(6);
        System.out.println(stack.toString());
    }
}
