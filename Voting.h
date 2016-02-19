#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <vector>   // vector
#include <string>   // getline, string, string

using namespace std;

const int MAX_CANDIDATES = 20;
const int MAX_BALLOTS = 1000;

/**
 * A single ballot that contains an ordered list of Candidate indices.
 */
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
   * Create a ballot from a pre-existing vector of indices
   * @param votes the vector
   */
  Ballot(vector<int> votes);

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
   * @param the vote to add
   */
  void addVote(int v);   

  /**
   * @return the next vote (not removed)
   */
  int peekVote(void);     
};

/**
 * A candidate in an election that holds a number of Ballots and votes
 */
class Candidate {
private:
  vector<Ballot> ballots; 
  int numVotes = 0;           
  int candidateIndex;         
  string name;          
public:
  /** 
   * @param n name of the Candidate
   * @param i the index of the Candidate
   */
  Candidate(string n, int i);

  /** 
   * @return the removed ballot which has had the first Candidate index removed
   */
  Ballot removeBallot(void);

  /** 
   * @param b the ballot to add
   */
  void addBallot(Ballot b); 

  /** 
   * @return this Candidate's index
   */
  int getIndex(void);       

  /** 
   * @return the number of votes for this Candidate
   */
  int getNumVotes(void);

  /** 
   * @return the name of this Candidate
   */
  string getName(void);
};

/**
 * Represents a number of Candidates in an Aussie election.
 */
class Election {
private:
  vector<Candidate> candidates;
  int numBallots = 0;
public:
  /** 
   * @param c the Candidate to add to this Election
   */
  void insert(Candidate c);

  /** 
   * @return the number of Candidates in this Election
   */
  int getNumCandidates(void);

  /** 
   * @return the Candidate who won (or those who tied, in the order they appear in the input)
   */
  vector<Candidate> findWinners(void);

  /** 
   * @param b the Ballot to give to a Candidate in this Election
   */
  void addBallot(Ballot b); 

  /** 
   * @return the number of Ballots submitted to this Election
   */
  int getNumBallots(void);
};

/**
 * Calls voting_read given reading and writing streams and prints the winners
 * @param r the reading stream
 * @param w the writing stream
 */
void voting_solve(istream &r, ostream &w);
