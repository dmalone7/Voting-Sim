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

// -----
// Ballot
// -----

TEST(VotingFixture, ballot_1) {
  Ballot b = Ballot();
  ASSERT_EQ(b.getVotesLeft(), 0);
}

TEST(VotingFixture, add_1) {
   Ballot b({1, 2});
   b.addVote(3);
   ASSERT_EQ(b.getVotesLeft(), 3);
}

// ---------
// Candidate
// ---------

// -----
// solve
// -----

TEST(VotingFixture, solve_1) {
  string in ("1\n\n0");
  string out("no candidates\n\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

TEST(VotingFixture, solve_2) {
  string in ("1\n\n2\nA\nB\n1 2\n2 1");
  string out("A\nB\n\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

TEST(VotingFixture, solve_3) {
  string in ("1\n\n4\nA\nB\nC\nD\n1 2 3 4\n1 2 3 4\n2 1 3 4\n2 1 3 4\n3 1 2 4\n4 1 2 3");
  string out("A\n\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

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

/*
 % g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread
*/
