run with ./cache-sim <input-file> <output-file>

trace2.txt and trace3.txt are supplied as simulated cache accesses

output will be in the form of <number of hits>, <number of accesses>;

cache sim will test the following architectures:

Direct mapped: cache sizes of: 1024, 4096, 16384, 32768

Set Associative: cache size of 16384: sets of 2, 4, 8, 16

Fully Associate: cache size of 16384

No Allocation of write: cache size of 16384: sets of 2, 4, 8, 16

Pre On Miss: cache size of 16384: set of 2, 4, 8, 16