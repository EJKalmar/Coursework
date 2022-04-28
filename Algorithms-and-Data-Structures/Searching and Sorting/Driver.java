/**
 * Assignment 1: Analysis of Algorithms, Searching, and Sorting.
 * Part 1b: Driver.java
 * Erik Jonathan Kalmar T00651562
 * May 20th, 2019
 */
public class Driver
{       
    //Creates 3 new ShellArrays of various sizes and applies the shell short algorithm to them
    public static void main(String[] Args)
    {
        ShellArray Array1 = new ShellArray(10);
        System.out.println(Array1);
        Array1.ShellSort();
        System.out.println(Array1.toString()+"\n");

        ShellArray Array2 = new ShellArray(18);
        System.out.println(Array2.toString());
        Array2.ShellSort();
        System.out.println(Array2.toString()+"\n");

        ShellArray Array3 = new ShellArray(6);
        System.out.println(Array3.toString());
        Array3.ShellSort();
        System.out.println(Array3.toString()+"\n");
    }
}
