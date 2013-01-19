// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

const int CACHE_SIZE = 500000;

// ------------
// collatz_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream&, int&, int&);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int, int, int []);

// -------------
// collatz_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream&, int, int, int);

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream&, std::ostream&);

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    /*
    reads two ints into i and j
    r is a reader
    i stores the beginning of the range as an int
    j stores the end of the range as an int
    return true if that succeeds, false otherwise
    */
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j, int *c) {
    /*
    i is the beginning of the range, inclusive
    j is the end of the range, inclusive
    return the max cycle length in the range [i, j]
    */
    assert(i > 0);
    assert(j > 0);
    int v = 1;
    
    // Swap i and j if necessary
    if (i > j) {
        i ^= j;
        j ^= i;
        i ^= j;
    }
    // Iterative loop over the input range using the max_range / 2 trick
    for (int x = (i < (j/2) ? (j/2) : i); x <= j; ++x) {
        int count = 1;
        int xprime = x;
        // Loop to calculate cycle length, update longest cycle
        while (xprime != 1) {
            if (xprime < CACHE_SIZE && c[xprime] != 0) {
                count += c[xprime] - 1;
                xprime = 1;
            }
            else if ((xprime & 1) == 0) {
                xprime >>= 1;
                ++count;
            }
            else {
                xprime = xprime + (xprime >> 1) + 1; // Equivalent to (3x + 1) / 2, an invariant sequence for odd numbers
                count += 2;
            }
        }
        assert(count > 0);
        c[x] = count;
        if (count > v) {
            v = count;
        }
    }
    
    assert(v > 0);
    return v;}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    /*
    prints the values of i, j, and v
    w is a writer
    i is the beginning of the range, inclusive
    j is the end of the range, inclusive
    v is the max cycle length
    */
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    /*
    read, eval, print loop
    r is a reader
    w is a writer
    */
    int i;
    int j;
    int cycleCache[CACHE_SIZE];
    for (int x = 2; x < CACHE_SIZE; ++x) {
        cycleCache[x] = 0;
    }
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j, cycleCache);
        collatz_print(w, i, j, v);}}

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}
