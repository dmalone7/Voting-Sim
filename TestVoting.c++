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
  Ballot b;
  ASSERT_EQ(b.getVotesLeft(), 0);
}

TEST(VotingFixture, ballot_2) {
  Ballot b({2});
  ASSERT_EQ(b.getVotesLeft(), 1);
}

TEST(VotingFixture, ballot_3) {
  Ballot b({1, 2, 3, 4, 5, 16, 32, 64, 128, 999999});
  ASSERT_EQ(b.getVotesLeft(), 10);
}

// ----
// addVote
// ----

TEST(VotingFixture, ballotAdd_1) {
   Ballot b({1, 2});
   b.addVote(3);
   ASSERT_EQ(b.getVotesLeft(), 3);
}

TEST(VotingFixture, ballotAdd_2) {
   Ballot b;
   b.addVote(3);
   ASSERT_EQ(b.getVotesLeft(), 1);
}

TEST(VotingFixture, ballotAdd_3) {
   Ballot b({1, 2, 3, 5, 6});
   b.addVote(4);
   ASSERT_EQ(b.getVotesLeft(), 6);
}

// ----
// getVotesLeft
// ----

TEST(VotingFixture, ballotVotes_1) {
  Ballot b;
  b.addVote(1);
  b.addVote(2);
  int v = b.getVotesLeft();
  ASSERT_EQ(v, 2);
}

TEST(VotingFixture, ballotVotes_2) {
  Ballot b;
  int v = b.getVotesLeft();
  ASSERT_EQ(v, 0);
}

TEST(VotingFixture, ballotVotes_3) {
  Ballot b;
  for(int i = 0; i < 1000; i++)
    b.addVote(i);
  int v = b.getVotesLeft();
  ASSERT_EQ(v, 1000);
}

// ----
// peekVote
// ----

TEST(VotingFixture, ballotPeek_1) {
  Ballot b({1, 2, 3, 4});
  ASSERT_EQ(b.peekVote(), 1);
}

TEST(VotingFixture, ballotPeek_2) {
  Ballot b;
  b.addVote(1);
  b.nextVote();
  ASSERT_EQ(b.peekVote(), -1);
}

TEST(VotingFixture, ballotPeek_3) {
  Ballot b({1, 4, 9, 7});
  b.nextVote();
  ASSERT_EQ(b.peekVote(), 4);
}

// ----
// nextVote
// ----

TEST(VotingFixture, ballotNext_1) {
  Ballot b;
  ASSERT_EQ(b.nextVote(), -1);
}

TEST(VotingFixture, ballotNext_2) {
  Ballot b;
  b.addVote(12);
  b.addVote(10);
  ASSERT_EQ(b.nextVote(), 12);
}

TEST(VotingFixture, ballotNext_3) {
  Ballot b({1, 5, 10, 20});
  b.nextVote();
  b.nextVote();
  ASSERT_EQ(b.nextVote(), 10);
}

// ----
// Candidate
// ----

// ----
// addBallot
// ----

TEST(VotingFixture, cand_addBallot1) {
  Candidate c("one");
  c.addBallot(Ballot({1, 2, 3}));
  int v = c.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot2) {
  Candidate c("two");
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  int v = c.getNumVotes();
  int r = 3;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot3) {
  Candidate c("three");
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

// ----
// removeBallot
// ----

TEST(VotingFixture, cand_addRemoveBallot1) {
  Candidate c("foo");
  c.addBallot(Ballot({3, 2, 1}));
  c.removeBallot();
  int v = c.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addRemoveBallot2) {
  Candidate c("foo");
  c.addBallot(Ballot({3, 2, 1}));
  c.addBallot(Ballot({3, 2, 1}));
  c.removeBallot();
  int v = c.getNumVotes();
  int r = 2;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_removeOnlyBallot1) {
  Candidate c("foo");
  c.removeBallot();
  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_removeTooMany1) {
  Candidate c("foo");
  c.addBallot(Ballot({3, 2, 1}));
  c.removeBallot();
  c.removeBallot();
  int v = c.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

// ----
// resetNumVotes
// ----

TEST(VotingFixture, cand_reset1) {
  Candidate c("foo");

  c.addBallot(Ballot({3, 2, 1}));
  c.resetNumVotes();
  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_reset2) {
  Candidate c("foo");

  c.addBallot(Ballot({3, 2, 1}));
  c.removeBallot();
  c.resetNumVotes();
  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_resetNone) {
  Candidate c("foo");

  c.resetNumVotes();
  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_resetAfterRemove) {
  Candidate c("foo");

  c.addBallot(Ballot({3, 2, 1}));
  c.removeBallot();
  c.resetNumVotes();

  c.resetNumVotes();
  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_resetAfterRemoveEmpty) {
  Candidate c("foo");

  c.removeBallot();
  c.resetNumVotes();

  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_resetBeforeRemoveEmpty) {
  Candidate c("foo");

  c.resetNumVotes();
  c.removeBallot();

  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_resetTwice) {
  Candidate c("foo");

  c.resetNumVotes();
  c.resetNumVotes();

  int v = c.getNumVotes();
  int r = 0;
  ASSERT_EQ(v, r);
}

// ----
// getName
// ----

TEST(VotingFixture, cand_getName1) {
  Candidate c("foo");

  c.resetNumVotes();
  c.resetNumVotes();

  string v = c.getName();
  string r = "foo";
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_getName2) {
  Candidate c("GIMLI");

  c.resetNumVotes();
  c.resetNumVotes();

  string v = c.getName();
  string r = "GIMLI";
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_getName3) {
  Candidate c = Candidate("");

  c.resetNumVotes();
  c.resetNumVotes();

  string v = c.getName();
  string r = "";
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_get2SameName) {
  Candidate c = Candidate("BEAR");
  Candidate d = Candidate("BEAR");

  c.resetNumVotes();
  c.resetNumVotes();

  string c_n = c.getName();
  string d_n = d.getName();
  ASSERT_EQ(c_n, d_n);
}

TEST(VotingFixture, cand_exchangeBallots1) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  grills.addBallot(bear.removeBallot());

  int v = grills.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeBallots2) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  bear.addBallot(Ballot({1,2}));
  grills.addBallot(bear.removeBallot());

  int v = grills.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeBallots3) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  bear.addBallot(Ballot({1,2}));
  grills.addBallot(bear.removeBallot());
  grills.addBallot(Ballot({1,2}));

  int v = grills.getNumVotes();
  int r = 2;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeDifferentBallotsPeek) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  bear.addBallot(Ballot({2,1}));
  grills.addBallot(bear.removeBallot());

  int v = grills.removeBallot().peekVote();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeDifferentBallotsNext) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  bear.addBallot(Ballot({2,1}));
  grills.addBallot(bear.removeBallot());

  int v = grills.removeBallot().nextVote();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeDifferentBallotsIntermediateReset) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot({1,2}));
  bear.addBallot(Ballot({2,1}));
  bear.resetNumVotes();
  grills.addBallot(bear.removeBallot());

  int v = grills.removeBallot().nextVote();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeDifferentBallotsEmptyIntermediateReset) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot());
  bear.resetNumVotes();
  grills.addBallot(bear.removeBallot());

  int v = grills.removeBallot().nextVote();
  int r = -1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_exchangeDifferentBallotsEmptyIntermediateResetRemoveTooMany) {
  Candidate bear = Candidate("BEAR");
  Candidate grills = Candidate("GRILLS");

  bear.addBallot(Ballot());
  bear.resetNumVotes();
  grills.addBallot(bear.removeBallot());
  grills.addBallot(bear.removeBallot());

  int v = grills.removeBallot().nextVote();
  int r = -1;
  ASSERT_EQ(v, r);
}

// ----
// Election
// ----

// -----
// electionInsert
// -----

TEST(VotingFixture, electionInsert_1) {
  Election e;
  Candidate c("David");
  e.insert(c);
  ASSERT_EQ(e.getNumCandidates(), 1);
}

TEST(VotingFixture, electionInsert_2) {
  Election e;
  ASSERT_EQ(e.getNumCandidates(), 0);
}

TEST(VotingFixture, electionInsert_3) {
  Election e;
  for(int i = 0; i < 10; i++) {
    Candidate c("David");
    e.insert(c);
  }
  ASSERT_EQ(e.getNumCandidates(), 10);
}

// -----
// electionNumCandidates
// -----

TEST(VotingFixture, electionNumCand_1) {
  Election e;
  Candidate a("Alex");
  e.insert(a);
  Candidate d("David");
  e.insert(d);
  ASSERT_EQ(e.getNumCandidates(), 2);
}

TEST(VotingFixture, electionNumCand_2) {
  Election e;
  e.findWinners();
  ASSERT_EQ(e.getNumCandidates(), 0);
}

TEST(VotingFixture, electionNumCand_3) {
  Election e;
  for(int i = 0; i < 10; i++) {
    Candidate c("Candidate");
    e.insert(c);
  }
  ASSERT_EQ(e.getNumCandidates(), 10);
}

// -----
// findWinners 
// -----

TEST(VotingFixture, election_winner1) {
  Election e;
  ASSERT_EQ(e.findWinners().size(), 0);
}

TEST(VotingFixture, election_winner2) {
  Election e;
  e.insert(Candidate("1"));
  e.insert(Candidate("2"));
  e.addBallot(Ballot({1}));
  e.addBallot(Ballot({1}));
  ASSERT_EQ(e.findWinners().size(), 1);
}

TEST(VotingFixture, election_winner3) {
  Election e;
  e.insert(Candidate("1"));
  e.insert(Candidate("2"));
  e.addBallot(Ballot({1}));
  e.addBallot(Ballot({1}));
  
  string winnerName = e.findWinners()[0].getName();
  string v = "1";
  ASSERT_EQ(winnerName, v);
}

TEST(VotingFixture, election_winner4) {
  Election e;
  e.insert(Candidate("1"));
  e.insert(Candidate("2"));
  e.addBallot(Ballot({1}));
  e.addBallot(Ballot({2}));
  ASSERT_EQ(e.findWinners().size(), 2);
}

TEST(VotingFixture, election_winnerNoBallotsNoCandidates) {
  Election e;
  ASSERT_EQ(e.findWinners().size(), 0);
}

TEST(VotingFixture, election_winnerNoBallots) {
  Election e;
  e.insert(Candidate("1"));
  ASSERT_EQ(e.findWinners().size(), 1);
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

==17871== Memcheck, a memory error detector
==17871== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==17871== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==17871== Command: ./TestVoting
==17871== 
Running main() from gtest_main.cc
[==========] Running 12 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 12 tests from VotingFixture
[ RUN      ] VotingFixture.ballot_1
[       OK ] VotingFixture.ballot_1 (10 ms)
[ RUN      ] VotingFixture.ballot_2
[       OK ] VotingFixture.ballot_2 (13 ms)
[ RUN      ] VotingFixture.ballot_3
[       OK ] VotingFixture.ballot_3 (2 ms)
[ RUN      ] VotingFixture.ballotAdd_1
[       OK ] VotingFixture.ballotAdd_1 (10 ms)
[ RUN      ] VotingFixture.ballotAdd_2
[       OK ] VotingFixture.ballotAdd_2 (2 ms)
[ RUN      ] VotingFixture.ballotAdd_3
[       OK ] VotingFixture.ballotAdd_3 (2 ms)
[ RUN      ] VotingFixture.cand_addBallot1
[       OK ] VotingFixture.cand_addBallot1 (14 ms)
[ RUN      ] VotingFixture.cand_addBallot2
[       OK ] VotingFixture.cand_addBallot2 (6 ms)
[ RUN      ] VotingFixture.cand_addBallot3
[       OK ] VotingFixture.cand_addBallot3 (9 ms)
[ RUN      ] VotingFixture.solve_1
[       OK ] VotingFixture.solve_1 (24 ms)
[ RUN      ] VotingFixture.solve_2
[       OK ] VotingFixture.solve_2 (35 ms)
[ RUN      ] VotingFixture.solve_3
[       OK ] VotingFixture.solve_3 (15 ms)
[----------] 12 tests from VotingFixture (148 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 1 test case ran. (173 ms total)
[  PASSED  ] 12 tests.
==17871== 
==17871== HEAP SUMMARY:
==17871==     in use at exit: 0 bytes in 0 blocks
==17871==   total heap usage: 621 allocs, 621 frees, 70,399 bytes allocated
==17871== 
==17871== All heap blocks were freed -- no leaks are possible
==17871== 
==17871== For counts of detected and suppressed errors, rerun with: -v
==17871== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
File 'Voting.c++'
Lines executed:93.28% of 134
Branches executed:98.75% of 160
Taken at least once:64.38% of 160
Calls executed:79.85% of 134
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 69
Branches executed:75.76% of 396
Taken at least once:37.88% of 396
Calls executed:61.37% of 510
Creating 'TestVoting.c++.gcov'
*/
