Final project for UVic's CSC 428c: Bioinformatics and Clinical Applications, taken with Ibrahim Numanagic in the fall of 2020. This project is a reimplementation of Picard's MarkDuplicates algorithm, written in the Seq programming language. To get Seq on your system or learn about the language, visit https://seq-lang.org/.

This program locates and tags duplicate reads in a SAM file, where duplicate reads are considered to be originating from the same fragment of DNA. It works by comparing sequences in the 5-prime positions of both reads and read-pairs, and differentiating primary and duplicate reads by the sums of their quality scores.

The program will output a new SAM file, in which duplicates have been marked with the hexadecimal value of 0x0400, corresponding to a decimal value of 1024.

usage: seqc -d MDSeq.seq input.sam output.sam