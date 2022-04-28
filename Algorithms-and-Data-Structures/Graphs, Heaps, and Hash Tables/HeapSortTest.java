/**
 * COMP 2231 Assignment 5.
 * @author Erik Jonathan Kalmar 
 * T00651562
 * June 6th, 2019
 */

/**
 * Tests and demonstrates implementation of class HeapSort
 */
import java.util.*;
public class HeapSortTest<T> extends HeapSort<T>
{
    public static void main (String[] Args)
    {
        Integer[] array = {8, 5, 23, 65, 43, 17, 87, 54, 56, 91, 6, 42};
        System.out.println(Arrays.toString(array));
        HeapSort sort = new HeapSort();
        sort.heapSort(array);
        
        System.out.println(Arrays.toString(array));
    }
}
