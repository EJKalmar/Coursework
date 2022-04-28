/**
 * Assignment 1: Analysis of Algorithms, Searching, and Sorting.
 * Part 2: Sorting.java
 * Erik Jonathan Kalmar T00651562
 * May 20th, 2019
 */

import java.io.*;
import java.util.Arrays;

public class Sorting 
{
    static int n; //global counter, reset inside each method

    //Sorts the specified array using a selection sort algorithm
    //@param data - the array to be sorted
    public static void selectionSort(Comparable[] data)
    {
        int min;

        System.out.println("Running selectionSort...");
        n=0; //number of comparisons
        long start = System.nanoTime(); //starting time
        for (int index = 0; index < data.length - 1; index++)
        {
            min = index;
            for (int scan = index + 1; scan < data.length; scan++)
            {
                n++;
                if (data[scan].compareTo(data[min]) < 0)
                    min = scan;
            }
            swap(data, min, index);

        }
        long end = System.nanoTime(); //end time
        long elapsed = end - start; //elapsed time
        System.out.println("Number of comparisons: " + n);
        System.out.println("Time elapsed: " + elapsed + " nanoseconds\n");
    }

    //Swaps two elements in an array. Used by various sorting algorithms.
    //@param data   the array in which the elements are swapped
    //@param index1 the index of the first element to be swapped
    //@param index2 the index of the second element to be swapped
    private static void swap(Comparable[] data, int index1, int index2)
    {
        Comparable temp = data[index1];
        data[index1] = data[index2];
        data[index2] = temp;
    }

    //Sorts the specified array of objects using an insertion sort algorithm
    //@param data - the array to be sorted
    public static void insertionSort(Comparable[] data)
    {
        System.out.println("Running insertionSort...");
        n=0; //number of comparisons
        long start = System.nanoTime(); //starting time
        for (int index = 1; index < data.length; index++)
        {
            Comparable key = data[index];
            int position = index;
            // shift larger values to the right 
            n++;
            while (position > 0 && data[position-1].compareTo(key) > 0)
            {
                data[position] = data[position - 1];
                position--;
                n++;
            }
            data[position] = key;
        }
        long end = System.nanoTime(); //end time
        long elapsed = end - start; //elapsed time
        System.out.println("Number of comparisons: " + n);
        System.out.println("Time elapsed: " + elapsed + " nanoseconds\n");
    }

    //Sorts the specified array using a bubble sort algorithm
    //@param data - the array to be sorted
    public static void bubbleSort(Comparable[] data)
    {
        System.out.println("Running bubbleSort...");
        int scan;
        boolean swapflag = true;

        n=0; //number of comparisons
        long start = System.nanoTime(); //starting time

        while(swapflag)
        {
            swapflag = false;
            for (scan = 0; scan < data.length -1; scan++)
            {
                n++;
                if (data[scan].compareTo(data[scan + 1]) > 0)
                {
                    swap(data, scan, scan + 1);
                    swapflag = true;
                }
            }
        }
        long end = System.nanoTime(); //end time
        long elapsed = end - start; //elapsed time
        System.out.println("Number of comparisons: " + n);
        System.out.println("Time elapsed: " + elapsed + " nanoseconds\n");
    }

    //Sorts the specified array using a quick sort algorithm
    //@param data - the array to be sorted
    public static void quickSort(Comparable[] data)
    {
        System.out.println("Running quickSort...");
        n=0; //number of comparisons
        long start = System.nanoTime(); //start time
        quickSort(data, 0, data.length - 1);
        long end = System.nanoTime(); //end time
        long elapsed = end - start; //elapsed time
        System.out.println("Number of comparisons: " + n);
        System.out.println("Time elapsed: " + elapsed + " nanoseconds\n");
    }

    //Recursively sorts a range of objects in the specified array using the quick sort algorithm
    //@param data the array to be sorted
    //@param min  the minimum index in the range to be sorted
    //@param max  the maximum index in the range to be sorted
    public static void quickSort(Comparable[] data, int min, int max)
    {   
        if (min < max)
        {
            // create partitions
            int indexofpartition = partition(data, min, max);

            // sort the left partition (lower values)
            quickSort(data, min, indexofpartition - 1);

            // sort the right partition (higher values)
            quickSort(data, indexofpartition + 1, max);
        }
    }

    //Used by the quick sort algorithm to find the partition.
    //@param data - the array to be sorted
    //@param min - the minimum index in the range to be sorted
    //@param max - the maximum index in the range to be sorted
    private static int partition(Comparable[] data, int min, int max)
    {
        Comparable partitionelement;
        int left, right;
        int middle = (min + max) / 2;

        // use the middle data value as the partition element
        partitionelement = data[middle];

        // move it out of the way for now
        swap(data, middle, min);

        left = min;
        right = max;

        while (left < right)
        {
            n++;
            // search for an element that is > the partition element
            while (left < right && data[left].compareTo(partitionelement) <= 0)
                left++;n++;

            n++;
            // search for an element that is < the partition element
            while (data[right].compareTo(partitionelement) > 0)
                right--;n++;

            // swap the elements
            if (left < right)
                swap(data, left, right);
        }

        // move the partition element into place
        swap(data, min, right);

        return right;
    }

    //Sorts the specified array of objects using the merge sort algorithm
    //@param data the array to be sorted
    public static void mergeSort(Comparable[] data)
    {
        System.out.println("Running mergeSort...");
        long start = System.nanoTime(); //start time
        n=0; //number of comparisons
        mergeSort(data, 0, data.length - 1);
        long end = System.nanoTime(); //end time
        long elapsed = end - start; //elapsed time
        System.out.println("Number of comparisons: " + n);
        System.out.println("Time elapsed: " + elapsed + " nanoseconds\n");
    }

    //Recursively sorts a range of objects in the specified array using the merge sort algorithm.
    //@param data - the array to be sorted
    //@param min - the index of the first element 
    //@param max - the index of the last element
    public static void mergeSort(Comparable[] data, int min, int max)
    {
        if (min < max)
        {
            int mid = (min + max) / 2;
            mergeSort(data, min, mid);
            mergeSort(data, mid+1, max);
            merge(data, min, mid, max);
        }
    }

    /**
    * Merges two sorted subarrays of the specified array.
    *
    * @param data the array to be sorted
    * @param first the beginning index of the first subarray 
    * @param mid the ending index fo the first subarray
    * @param last the ending index of the second subarray
    */
    @SuppressWarnings("unchecked")
    public static void merge(Comparable[] data, int first, int mid, int last)
    {
        Comparable[] temp = (Comparable[])(new Comparable[data.length]);

        int first1 = first, last1 = mid;  // endpoints of first subarray
        int first2 = mid + 1, last2 = last;  // endpoints of second subarray
        int index = first1;  // next index open in temp array

        //  Copy smaller item from each subarray into temp until one
        //  of the subarrays is exhausted
        while (first1 <= last1 && first2 <= last2)
        {
            n++;
            if (data[first1].compareTo(data[first2]) < 0)
            {
                temp[index] = data[first1];
                first1++;
            }
            else
            {
                temp[index] = data[first2];
                first2++;
            }
            index++;
        }

        //  Copy remaining elements from first subarray, if any
        while (first1 <= last1)
        {
            temp[index] = data[first1];
            first1++;
            index++;
        }

        //  Copy remaining elements from second subarray, if any
        while (first2 <= last2)
        {
            temp[index] = data[first2];
            first2++;
            index++;
        }

        //  Copy merged data into original array
        for (index = first; index <= last; index++)
            data[index] = temp[index];
    }

    //creates a copy of a Comparable[]
    //@param data - the array to be copied
    public static Comparable[] copyOf(Comparable[] data)
    {
        Comparable[] x = data.clone();
        return x;
    }
}

