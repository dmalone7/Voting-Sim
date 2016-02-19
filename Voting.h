#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector

using namespace std;

const int MAX_CANDIDATES = 20;
const int MAX_BALLOTS = 1000;

#include <string> // string, u16string


// Holds ordered data about which candidate is currently being voted for
class Ballot {
private:
  vector<int> votes;
public:
  Ballot();
  Ballot(const Ballot &source);
  int getVotesLeft(void); // Returns the size of the "votes" vector.
  int nextVote(void);     // Remove a vote from the front of the "votes" vector
                          // and returns the candidate index of the removed vote
  void addVote(int v);    // Adds a vote to the back of the "votes" vector
  int peekVote(void);     // Returns the number of the candidate currently at the 
                          // front of the "votes" vector without removing it.
};

class Candidate {
private:
  vector<Ballot> ballots; 
  int numVotes = 0;           // Number of votes for the current cycle
  int candidateIndex;         // The number in which the candidate appeared in the 
                              // input.
  string name;          
public:
  Candidate(string n, int i);
  Ballot removeBallot(void); // Given @param "s" size, find all Ballots with size "s" and
                                     // removes them. @return vector is a list of the ballots which
                                     // were removed.
  void addBallot(Ballot b);         // Adds a ballot to the vector of Ballots - usually called
                                     // from the context of a Ballot being removed from another
                                     // Candidate.
  int getIndex(void);         
  int getNumVotes(void);
  string getName(void);
};

class Election {
private:
  vector<Candidate> candidates;
public:
  void insert(Candidate c);
  int getNumCandidates(void);
  vector<Candidate> findWinners(void);
  void addBallot(Ballot b);             // Calls
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
