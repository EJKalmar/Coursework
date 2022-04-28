/**
 * COMP 2231 Assignment 5.
 * @author Erik Jonathan Kalmar 
 * T00651562
 * June 6th, 2019
 */

import java.util.*;

/**
 * Implements a dynamicly resizable hash table to store people's names and social security numbers.
 */
public class HashTable
{
    private final static int initialSize = 31;
    private final static double loadfactor = 0.8;

    Info[] table;
    int count;

    public HashTable()
    {
        table = new Info[initialSize];
        count=0;
    }
    
    /**
     * Adds a new entry to the HashTable
     * @param key the social security number of the person
     * @param name the name of the person
     */
    public void put(int key, String name)
    {
        if(count>=loadfactor*table.length)//if load factor is reached, expand table
            expand();

        int hash = getHash(key);
        Info info = new Info(key, name);//create new Info

        if(table[hash]==null)//if the appropriate index is empty, simply put in the Info
            table[hash] = info;
        else //otherwise we need to use open addressing
        {
            Info temp = null;
            for(int i=1;table[hash]!=null;i++)//while the next position is occupied
            {
                temp = table[hash];//keep a reference to the previous Info
                hash = hash + i * doubleHash(key);//look to the next position using double hashing
            }
            table[hash] = info;
            temp.next = info; //set a reference to the info so we can find it from the original hash index
        }
        count++;
    }
    
    /**
     * Finds the name associated with the particular key (or social security number)
     * @return the name associated with the given key
     */
    public String get(int key)
    {
        int hash = getHash(key);
        Info result = null;

        if(table[hash]!=null)
        {
            result = table[hash];
            while(result.key!=key)
                result = result.next;

            return result.name;
        }           
        return null;    
    }

    /**
     * doubles the size of the array
     */
    private void expand()
    {
        table = Arrays.copyOf(table,table.length*2);
    }

    /**
     * extracts the last 4 digits of the key and applies the division method with table size
     * @return the hash code of the key
     */
    private int getHash(int key)
    {
        return (key % 10000) % initialSize;
    }

    /**
     * used to create a new hash if the getHash index is occupied
     * extracts the first 3 digits of the key and applies division method with table size
     * assumes key is 9 digits
     * @return the secondary hash code of the key
     */
    private int doubleHash(int key)
    {
        return (key / 1000000) % initialSize;
    }

    /**
     * converts the Hashtable into a string
     * @return the string representation of the Hashtable
     */
    public String toString()
    {
        String result = "";
        int index=0;
        for (Info info: table)
        {
            if (info!=null)
                result = result + "[" + index + "] " + info.toString() + "\n";
            index++;
        }
        return result;
    }

    public class Info
    {
        private String name;
        private int key;
        private Info next;//points to next address if the keys share a hash

        public Info(int key, String name)
        {
            this.name = name;
            this.key = key;
            this.next=null;
        }

        public int getKey()
        {
            return key;
        }

        public String toString()
        {
            return key + ", " + name;
        }
    }
}
