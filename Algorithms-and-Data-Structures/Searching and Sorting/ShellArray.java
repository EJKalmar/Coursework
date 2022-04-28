/**
 * Assignment 1: Analysis of Algorithms, Searching, and Sorting.
 * Part 1a: ShellArray.java
 * Erik Jonathan Kalmar T00651562
 * May 20th, 2019
 */
import java.io.*;
import java.util.Random;
import java.util.Arrays;

public class ShellArray
{
    int[] ShellArray;

    //Constructor for objects of class ShellArray
    public ShellArray(int size)
    {
        ShellArray=new int[size];
        System.out.println("Creating a random array of " + size + " integers...");
        Random rand = new Random();
        for(int i=0;i<size;i++)
            ShellArray[i]=rand.nextInt(1000);
    }

    //converts a ShellArray into a string
    public String toString()
    {
        String s="[";
        for(int i=0;i<ShellArray.length;i++)
        {
            s=s+ShellArray[i];
            if (i!=ShellArray.length-1)
                s=s+", ";
            }
        s=s+"]";
        return s;
    }
    
    //swaps two elements of the specified array.
    private static void swap (int[] arr, int x, int y)
    {
        int temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;
    }

    //sorts the specified ShellArray using a shell sort algorithm.
    public void ShellSort ()
    {
        int gap = ShellArray.length/2;
        System.out.println("Sorting...");
        while(gap>0)
        {
            boolean swapflag = true;
            while (swapflag)        
            {
                swapflag = false;
                for (int s = 0; s < (ShellArray.length - gap); s++)
                    if (ShellArray[s]>ShellArray[s+gap])
                    {
                        swap (ShellArray, s, s+gap);
                        swapflag = true;
                    }
            }
            gap = gap/2;
        }
    }
}
