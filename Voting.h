// ----------------------------
// cs371p-collatz/Voting.h
// Copyright (C) 2016
// Alex and David
// ----------------------------

#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <vector>   // vector
#include <string>   // getline, string, string

using namespace std;

/**
 * A single ballot that contains an ordered list of Candidate indices.
 */
class Ballot {
private:
  vector<int> votes;
  int index = 0;
public:
  /**
   * Create an empty ballot.
   */
  Ballot();

  /**
   * Create a ballot from a pre-existing vector of indices
   * @param v the vector
   */
  Ballot(vector<int> v);

  /**
   * @return the number of votes left in the ballot
   */
  int getVotesLeft(void);

  /**
   * removes the first candidate index in the ballot 
   * @return the first candidate number, -1 if none left
   */
  int nextVote(void);    

  /**
   * @param the vote to add
   */
  void addVote(int v);   

  /**
   * gets the next vote without removing it
   * @return the next candidate index, -1 if none left
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
  int index = 0;
  string name;          
public:
  /** 
   * @param n name of the Candidate
   * @param i the index of the Candidate
   */
  Candidate(string n);

  /** 
   * @return the next removed ballot 
   */
  Ballot removeBallot(void);

  /** 
   * Add a ballot and increase numVotes
   * @param b the ballot to add
   */
  void addBallot(Ballot b); 

  /**
   * Reset the number of votes to 0
   */
  void resetNumVotes(void);

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
 * Reads from an input stream and finds the winner of an Australian election.
 * @param r the reading stream
 * @param w the writing stream
 */
void voting_solve(istream &r, ostream &w);
