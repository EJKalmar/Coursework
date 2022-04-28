/**
 * COMP 2231 Assignment 5.
 * @author Erik Jonathan Kalmar 
 * T00651562
 * June 6th, 2019
 */

import java.util.*;

/**
 * HeapSort sorts a given array of Comparable objects using an in-place heap.
 */
public class HeapSort<T>
{
    /**
     * Sorts the specified array using an in-place heap sort
     *
     * @param data the data to be sorted
     */
    public void heapSort(T[] data) 
    {
        for(int i=data.length-1;i>0;i--)
        {
            constructMaxHeap(data,i);//create a max heap from the unsorted portion of the array
            if(((Comparable<T>)data[0]).compareTo(data[i])>0)
                swap(data,0,i);//Add the first (maximum) element to the front of the sorted array              
        }        
    }
    
    /**
     * Creates a maxHeap out of the specified array from 0-index
     * @param data the data to alter
     * @param index the position in the array of the last element to be sorted
     */
    public void constructMaxHeap (T[] data,int index) 
    {
        for(int i=index/2-1;i>=0;i--)//starting at the first non-leaf node and working backwards
        {
            int current = i;
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            
            if(left < index && ((Comparable<T>)data[left]).compareTo(data[current])>0)
                swap(data,left,current);
                
            if(right < index && ((Comparable<T>)data[right]).compareTo(data[current])>0)
                swap(data,right,current);
            }
    }

    /**
     * swaps two values in an array
     * @param data the data containing the values to be swapped
     * @param i the index of the first value to be swapped
     * @param j the index of the second value to be swapped
     */
    public void swap(T[] data, int i, int j)
    {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}