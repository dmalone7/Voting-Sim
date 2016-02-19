#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <vector>   // vector
#include <string>   // getline, string, u16string

using namespace std;

const int MAX_CANDIDATES = 20;
const int MAX_BALLOTS = 1000;

class Ballot {
private:
  vector<int> votes;
public:
  /**
   * Create an empty ballot.
   */
  Ballot();

  /**
   * Copies the votes from a ballot
   * @param source the source ballot
   */
  Ballot(const Ballot &source);

  /**
   * @return the number of votes left in the ballot
   */
  int getVotesLeft(void);

  /**
   * removes the first candidate index in the ballot 
   * @return the first candidate number
   */
  int nextVote(void);    

  /**
   * 
   */
  void addVote(int v);   

  /**
   * 
   */
  int peekVote(void);     
};

class Candidate {
private:
  vector<Ballot> ballots; 
  int numVotes = 0;           
  int candidateIndex;         
  u16string name;          
public:
  Candidate(u16string n, int i);
  Ballot removeBallot(void);
  void addBallot(Ballot b); 
  int getIndex(void);       
  int getNumVotes(void);
  u16string getName(void);
};

class Election {
private:
  vector<Candidate> candidates;
  int numBallots = 0;
public:
  void insert(Candidate c);
  int getNumCandidates(void);
  vector<Candidate> findWinners(void);
  void addBallot(Ballot b);             // Calls
  int getNumBallots(void);
};

/* creates vector of candidates - LATER VERSION */
// vector<Candidate> voting_read(const u16string &s);

/* given vector of candidates and determines winner */
// vector<Candidate> voting_eval(vector<Candidate> c);

/* prints the winner(s) */
// void voting_print(ostream &w, const u16string &s);


/* given all test cases as a u16string, read and return the winners as a u16string */
u16string voting_read(const u16string &s);

/* calls voting_read given reading and writing streams and prints the winners */
void voting_solve(istream &r, ostream &w);
