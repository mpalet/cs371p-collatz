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

#include "Collatz.h"

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
    assert(i <= j);
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j/*, int c[]={}*/) {
    /*
    i is the beginning of the range, inclusive
    j is the end of the range, inclusive
    return the max cycle length in the range [i, j]
    */
    assert(i > 0);
    assert(j > 0);
    int v = 1;
    
    for (int x = (i < (j/2) ? (j/2) : i); x <= j; ++x) {
        int count = 1;
        int xprime = x;
        while (xprime != 1) {
            /*
            if temp < 500000 and c[temp] != 0 :
                count += c[temp] - 1
                temp = 1
            */
            if ((xprime & 1) == 0) {
                xprime >>= 1;
                ++count;
            }
            else {
                xprime = xprime + (xprime >> 1) + 1; // Equivalent to (3x + 1) / 2, an invariant sequence for odd numbers
                count += 2;
            }
        }
        assert(count > 0);
        /*
        if (sizeof(c) > 0) {
            c[x] = count
        }
        */
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
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
