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
  Ballot b();
  ASSERT_EQ(b., 0);
}

TEST(VotingFixture, add_1) {
   Ballot b({1, 2});
   b.addVote(3);
   //ASSERTEQ(
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
  Candidate c("one", "1");
  c.addBallot(Ballot({1, 2, 3}));
  int v = c.getNumVotes();
  int r = 1;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot2) {
  Candidate c("two", "2");
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  int v = c.getNumVotes();
  int r = 3;
  ASSERT_EQ(v, r);
}

TEST(VotingFixture, cand_addBallot3) {
  Candidate c("three", "3");
  c.addBallot(Ballot({3, 2, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  c.addBallot(Ballot({2, 3, 1}));
  int v = c.getNumVotes();
  int r = 6;
  ASSERT_EQ(v, r);
}
/*
 % g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread
*/
