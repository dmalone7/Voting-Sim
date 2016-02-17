#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector
#include "Voting.h"

using namespace std;

/* given all test cases as a string, read and return the winners as a string */
string voting_read(const string &s) {
  return "";
}

/* calls voting_read given reading and writing streams and prints the winners */
void voting_solve(istream &r, ostream &w) {
  vector<string> candidates;
  int num_cases, num_candidates, loop_candidates, current_ballot;
  int ballots[MAX_BALLOTS][MAX_CANDIDATES];
  string s, end;

  num_cases = -1;
  num_candidates = -1;
  loop_candidates = -1;
  current_ballot = 0;
  end = "";

  getline(r, s);
  num_cases = stoi(s);
  w << num_cases << endl;

  getline(r, s); // consume new line character

  // if num_cases == 1, look for EOF instead of '\n'
  while(num_cases > 0) {
    getline(r, s);
    num_candidates = stoi(s);
    w << num_candidates << endl;

    if(num_cases == 1) {
      end = string(1, EOF);
    }

    if(num_candidates == 0) {
      w << "no candidates" << endl;
    }

    else {
      loop_candidates = num_candidates;
      // Look for candidate names
      int j = 0;
      while(loop_candidates > 0) {
        getline(r, s);
        candidates.push_back(s);
        w << candidates[j++] << endl;
        --loop_candidates;
      }
    }

    // strange case where num_candidates == 0 and num_cases == 1 
    // still works; s != end immediately terminates while

    // while still lines in the test case
    while(getline(r, s) && s.compare(end) != 0) {
      istringstream sin(s);

      for(int i = 0; i < num_candidates - 1; ++i) {
        sin >> ballots[current_ballot][i];
        w << ballots[current_ballot][i] << " ";
      }

      sin >> ballots[current_ballot][num_candidates - 1];
      w << ballots[current_ballot][num_candidates - 1] << endl;
      ++current_ballot;
    }

    // reset vector
    candidates.clear();
    --num_cases;
    w << endl;
  }
}
