/**
 * COMP 2231 Assignment 5.
 * @author Erik Jonathan Kalmar 
 * T00651562
 * June 6th, 2019
 */

/**
 * Tests and demonstrates implementation of HashTable
 */
public class HashTableTest extends HashTable
{
    public static void main(String[] Args)
    {
        HashTable table = new HashTable();
        table.put(847529384, "Jane" );
        table.put(394851230, "John");
        table.put(123453948, "Erik");
        table.put(341254389, "Jacob");
        table.put(356483203, "Marie");
        table.put(356483234, "Ashley");
        
        System.out.println(table.toString());
        System.out.println();               
        System.out.println(table.get(356483234));
        System.out.println(table.get(356483203));
        
    }
}
