#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <sstream>  // istringstream

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

TEST(VotingFixture, solve_1) {
  string in ("1\n\n0");
  string out("1\n0\nno candidates\n\n");

  istringstream r(in);
  ostringstream w;

  voting_solve(r, w);

  ASSERT_EQ(out, w.str());
}
