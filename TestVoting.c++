// ----------------------------
// cs371p-collatz/Voting.h
// Copyright (C) 2016
// Alex and David
// ----------------------------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <sstream>  // istringstream

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// ----
// Ballot
// ----

TEST(VotingFixture, ballot_1) {
  Ballot b = Ballot();
  ASSERT_EQ(b.getVotesLeft(), 0);
}

TEST(VotingFixture, add_1) {
   Ballot b({1, 2});
   b.addVote(3);
   ASSERT_EQ(b.getVotesLeft(), 3);
}

// ----
// Candidate
// ----

// ----
// addBallot
// ----

TEST(VotingFixture, cand_addBallot1) {
  Candidate c("one", 1);
  c.addBallot(Ballot({1, 2, 3}));
  int v = c.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot2) {
  Candidate c("two", 2);
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  int v = c.getNumVotes();
  int r = 3;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot3) {
  Candidate c("three", 3);
  c.addBallot(Ballot({3, 2, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  int v = c.getNumVotes();
  int r = 7;
  ASSERT_EQ(v, r);
}

// -----
// solve
// -----

TEST(VotingFixture, solve_1) {
  string in ("1\n\n0");
  string out("no candidates\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

TEST(VotingFixture, solve_2) {
  string in ("1\n\n2\nA\nB\n1 2\n2 1");
  string out("A\nB\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

TEST(VotingFixture, solve_3) {
  string in ("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 1 2 4\n4 1 2 3");
  string out("A\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

/*
 % g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread

==16943== Memcheck, a memory error detector
==16943== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==16943== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==16943== Command: ./TestVoting
==16943== 
Running main() from gtest_main.cc
[==========] Running 8 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 8 tests from VotingFixture
[ RUN      ] VotingFixture.ballot_1
[       OK ] VotingFixture.ballot_1 (9 ms)
[ RUN      ] VotingFixture.add_1
[       OK ] VotingFixture.add_1 (22 ms)
[ RUN      ] VotingFixture.solve_1
[       OK ] VotingFixture.solve_1 (25 ms)
[ RUN      ] VotingFixture.solve_2
[       OK ] VotingFixture.solve_2 (45 ms)
[ RUN      ] VotingFixture.solve_3
[       OK ] VotingFixture.solve_3 (15 ms)
[ RUN      ] VotingFixture.cand_addBallot1
[       OK ] VotingFixture.cand_addBallot1 (3 ms)
[ RUN      ] VotingFixture.cand_addBallot2
[       OK ] VotingFixture.cand_addBallot2 (5 ms)
[ RUN      ] VotingFixture.cand_addBallot3
[       OK ] VotingFixture.cand_addBallot3 (8 ms)
[----------] 8 tests from VotingFixture (139 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test case ran. (164 ms total)
[  PASSED  ] 8 tests.
==16943== 
==16943== HEAP SUMMARY:
==16943==     in use at exit: 0 bytes in 0 blocks
==16943==   total heap usage: 551 allocs, 551 frees, 63,853 bytes allocated
==16943== 
==16943== All heap blocks were freed -- no leaks are possible
==16943== 
==16943== For counts of detected and suppressed errors, rerun with: -v
==16943== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Voting.c++'
Lines executed:93.28% of 134
Branches executed:98.75% of 160
Taken at least once:64.38% of 160
Calls executed:79.85% of 134
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 55
Branches executed:78.52% of 298
Taken at least once:39.26% of 298
Calls executed:62.31% of 390
Creating 'TestVoting.c++.gcov'
*/