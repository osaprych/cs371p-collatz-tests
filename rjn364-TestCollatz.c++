// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// Robby J. Nevels
// --------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}
    
TEST(Collatz, correctly_read_fail) {
    std::istringstream r("\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
    
TEST(Collatz, correctly_read_partial_fail) {
    std::istringstream r("1 10 2 12\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);
    const bool c = collatz_read(r, i, j);
    ASSERT_TRUE(c == true);
    ASSERT_TRUE(i ==    2);
    ASSERT_TRUE(j ==   12);}
        
// ----
// calcCycleLength
// ----

// int calcCycleLength(int value);

TEST(Collatz, calcCycleLength1) {
    int r = calcCycleLength(1);
    ASSERT_TRUE(r == 1);}
    
    
TEST(Collatz, calcCycleLength2) {
    int r = calcCycleLength(100);
    ASSERT_TRUE(r == 26);}
    
    
TEST(Collatz, calcCycleLength3) {
    int r = calcCycleLength(999999);
    ASSERT_TRUE(r == 259);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
    
TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, -1, 10, 20);
    ASSERT_TRUE(w.str() == "-1 10 20\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 1, 99999999, 20);
    ASSERT_TRUE(w.str() == "1 99999999 20\n");}

// -----
// solve
// -----

TEST(Collatz, solve1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
TEST(Collatz, solve2) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, solve3) {
    std::istringstream r("1 100\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 100 119\n");}
