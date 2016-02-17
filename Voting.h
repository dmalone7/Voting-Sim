#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector

using namespace std;

const int MAX_CANDIDATES = 20;
const int MAX_BALLOTS = 1000;

class Candidate {
  // Holds ballots and candidate name
};

class Ballot {
  // Holds ordered data about which candidate is currently being voted for
};

/* creates vector of candidates - LATER VERSION */
// vector<Candidate> voting_read(const string &s);

/* given vector of candidates and determines winner */
// vector<Candidate> voting_eval(vector<Candidate> c);

/* prints the winner(s) */
// void voting_print(ostream &w, const string &s);


/* given all test cases as a string, read and return the winners as a string */
string voting_read(const string &s);

/* calls voting_read given reading and writing streams and prints the winners */
void voting_solve(istream &r, ostream &w);
