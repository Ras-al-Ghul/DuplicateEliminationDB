# Duplicate Elimination DB

Code to perform duplicate elimination for a given relation.  
(Refer to `Database Systems: The Complete Book by Garcia-Molina, Ullman and Widom` for a detailed description)  

To compile: `g++ filename.cpp -o ./filename`  
Do the above for `main.cpp`, `findunique.cpp` and `randomnumgen.cpp`  

**FUNCTION PROTOTYPE** : `​distinct(R, n, M, type_of_index)`  
- R is a name of relation  
- n the number of attributes  
- M is the number of blocks. Note that B(R) > M and M > 2  
- Type_of_index takes two values: hash - 0 or btree - 1  
  
We have to remove the duplicates. We'll need to write three routines `open()`, `Getnext()` and​ ​ `close()`​. The program should call above routines to eliminate the duplicates. One can create indexes​​ as a part of open(). To search whether the record is duplicate or not, we use B+ Tree and Hashing main memory structures for inserting and checking.  

**To run:**`./main <inputfile> <numofattributes> <numofmainmemblocks> <0/1index>`  
Output is the number of unique tuples and the time taken. The unique tuples are printed to `output.txt`  
`Sample.txt` is a sample input file  
`numbers.txt` is the generated input file  
`btree.h` contains code for the BTree indexing  
`hash.h` contains code for the Hash indexing  

We can specify the minimum and maximum size of each block in `main.cpp`  

Out of the `M` buffers, `M-1` Buffers will be used as `input buffers` (which will hold the records from the input file). `1` buffer will be used as `output buffer` (holds the distinct records). If the output buffer gets filled, it should be flushed to the output file. If the input buffers get empty, next chunk of records should be read from the input file.  
`Getnext()` function when called should always return one of the following:  
1. Record : This needs to be forwarded to the output buffer (If it's a distinct record)  
2. Null : The input file is completely processed. Proceed for close() routine  

Two assumptions have been made here:  
1. For the `BTree`, it is assumed that the number of unique tuples is not larger than what can fit into the main memory's M-1 blocks. If the number is larger than that, an error is thrown. Ideally we should be using the B+ Tree for indexing as it doesn't store the entire tuple of the relation as a key in its non leaf nodes. Another difference would be the chain of pointers amongst the leaf nodes for a linear full scan which is not possible in a BTree. But to make things simple, a BTree has been used here instead of the B+ Tree.  
2. For `Hashing`, there are M - 1 blocks to which the tuples can hash to. The maximum number of unique tuples which can hash to a block (amongst the M - 1 blocks) is the number which can fit in M - 1 blocks since we employ a two pass algorithm here if overflow occurs, and the entire content of each of those M-1 hash blocks needs to fit into the main memory at once during the second pass.  

**Output:** Vary from `M >= B(R)` to `M= (3/4)(B(R))` and calculate the execution time by employing
BTree and Hashing for inserting and checking duplicate entry.  

For a filesize of ~1.6 GB, hashing was taking around 90 secs while BTrees was taking around 140 secs.  

**Generation of R:** ​ Generate R of 1GB size. Generate R using random number function with r% duplication (r is an integer). To do this: `./randomnumgen <numofattributes> <percentageduplication>` This generates `numbers.txt`  

**To find the number of unique tuples in R:** `./findunique`  

