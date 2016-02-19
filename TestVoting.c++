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
/*
TEST(VotingFixture, add_1) {
   Ballot b();
   b.addVote(1);
   ASSERTEQ(b.nextVote()
}
*/
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

TEST(VotingFixture, solve_1) {
  string in ("2\n\nA\nB\n1 2\n2 1");
  string out("A\nB\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

TEST(VotingFixture, solve_1) {
  string in ("1\n\n0");
  string out("no candidates\n\n");

  istringstream r(in);
  ostringstream w;
  
  voting_solve(r, w);
  
  ASSERT_EQ(out, w.str());
}

/*
 % g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread

