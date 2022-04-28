//Testing of Sorting.java
import java.util.Arrays;

public class SortTest extends Sorting
{
    //creates several arrays to test each sorting method
    public static void main (String[] Args){
        Comparable[] Array1 = {5, 8, 16, 19, 22, 54, 7, 6, 1};
        System.out.println("Array1: " + Arrays.toString(Array1)+"\n");

        selectionSort(Sorting.copyOf(Array1));
        insertionSort(Sorting.copyOf(Array1));
        bubbleSort(Sorting.copyOf(Array1));
        quickSort(Sorting.copyOf(Array1));
        mergeSort(Sorting.copyOf(Array1));

        Comparable[] Array2 = {945, 231, 493, 90, 22, 981, 632, 137, 429};
        System.out.println("Array2: " + Arrays.toString(Array2)+"\n");

        selectionSort(Sorting.copyOf(Array2));
        insertionSort(Sorting.copyOf(Array2));
        bubbleSort(Sorting.copyOf(Array2));
        quickSort(Sorting.copyOf(Array2));
        mergeSort(Sorting.copyOf(Array2));

        Comparable[] Array3 = {5,18,54,87,124,187,367,546,768,888,972};
        System.out.println("Array3: " + Arrays.toString(Array3)+"\n");

        selectionSort(Sorting.copyOf(Array3));
        insertionSort(Sorting.copyOf(Array3));
        bubbleSort(Sorting.copyOf(Array3));
        quickSort(Sorting.copyOf(Array3));
        mergeSort(Sorting.copyOf(Array3));       
    }
}
