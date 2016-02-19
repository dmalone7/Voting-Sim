#include <cassert>
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector
#include "Voting.h"

using namespace std;

Ballot::Ballot() { }

Ballot::Ballot(const Ballot &source) {
  votes = source.votes;
}

Ballot::Ballot(vector<int> v) {
  votes = v;
}

int Ballot::getVotesLeft(void) {
  return votes.size() - index;
}

int Ballot::nextVote(void) {
  // No votes left for this candidate.
  if(getVotesLeft() == 0)
    return 0;

  int ret = votes[index++];
  return ret;
} 

void Ballot::addVote(int v) {
  votes.push_back(v);
}

int Ballot::peekVote(void) {
  if (getVotesLeft() == 0)
    return -1;

  return votes[index];
}

////////////////////////////////////

Candidate::Candidate(string n, int i) {
  name = n;
  candidateIndex = i;
}

// remove a ballot from a candidate, removing that Candidate from the Ballot
Ballot Candidate::removeBallot(void) {
  if(index == (int) ballots.size())
    return Ballot();

  return ballots[index++];
}

void Candidate::resetNumVotes(void) {
  numVotes = 0;
}

void Candidate::addBallot(Ballot b) {
  ++numVotes;
  ballots.push_back(b);
}

int Candidate::getIndex(void) {
  return candidateIndex;
}

int Candidate::getNumVotes(void) {
  return numVotes;
}

string Candidate::getName(void) {
  return name;
}

////////////////////////////////////

void Election::insert(Candidate c) {
  candidates.push_back(c);
}

int Election::getNumCandidates(void) {
  return candidates.size();
}

vector<Candidate> Election::findWinners(void) {
  vector<Candidate> winners;
  int numCandidates = candidates.size();

  if(numCandidates == 0)
    return candidates;

  int max, currentVotes, min;
  bool mustRedistribute;

  while(1) {
    min = 10000; 
    max = -1;
    mustRedistribute = true;

    for(int i = 0; i < numCandidates; ++i) {
      Candidate c = candidates[i];
      currentVotes = c.getNumVotes();
      if(max < currentVotes) {
        max = currentVotes;

        if(currentVotes >= (numBallots / 2 + 1))  
          {
            mustRedistribute = false;
          }
      }

      if(currentVotes > 0 && min > currentVotes) {
        min = currentVotes;
      }
    }

    if(max == min) {
      mustRedistribute = false;
    }

    if(mustRedistribute) {
      for(int i = 0; i < numCandidates; ++i) {
        Candidate &c = candidates[i];
        if(c.getNumVotes() == min) {
          Ballot loserBallot;
          while((loserBallot = c.removeBallot()).getVotesLeft() != 0) {
            // have a loser now, c === loser
            bool foundLoser = false;
            while(!foundLoser && loserBallot.getVotesLeft() > 0) {
              int receiverIndex = loserBallot.nextVote() - 1;
              Candidate &receiver = candidates[receiverIndex];
              if(receiver.getNumVotes() > min) {
                foundLoser = true;
                // receiver is not a loser
                receiver.addBallot(loserBallot);
                // candidates[receiverIndex] = receiver;
              }
            }
            c.resetNumVotes();
            // candidates[i] = c;
            assert(candidates[i].getNumVotes() == 0);
          }
        }
      }
    }

    else {
      for(int i = 0; i < numCandidates; ++i) {
        Candidate c = candidates[i];
        if(c.getNumVotes() == max) {
          winners.push_back(c);
        }
      }
      return winners;
    }
  }
  return candidates;
}

void Election::addBallot(Ballot b) {
  int candIndex = b.peekVote();
  ++numBallots;
  candidates[candIndex - 1].addBallot(b);
}

int Election::getNumBallots(void) { 
  return numBallots;
}

////////////////////////////////////

/* calls voting_read given reading and writing streams and prints the winners */
void voting_solve(istream &r, ostream &w) {
  int num_cases, num_candidates;
  string s, end("");

  num_cases = -1;
  num_candidates = -1;

  getline(r, s);
  num_cases = stoi(s);

  getline(r, s); // consume new line character

  // if num_cases == 1, look for EOF instead of '\n'
  while(num_cases > 0) {
    Election election;
    getline(r, s);
    num_candidates = stoi(s);

    if(num_cases == 1) {
      end = string(1, EOF);
    }

    if(num_candidates == 0) {
      w << "no candidates" << endl;
    }

    else {
      // Look for candidate names
      for(int j = 0; j < num_candidates; ++j) {
        getline(r, s);
        //
        Candidate cand(s, j + 1);
        election.insert(cand);
        //
      }
    }

    // while still lines in the test case
    while(getline(r, s) && s.compare(end) != 0) {
      istringstream sin(s);

      Ballot b = Ballot();
      int num = -1;
      for(int i = 0; i < num_candidates; ++i) {
        sin >> num;
        //if(num >= 10)
        //  w << "we aren't shitters\n";
        b.addVote(num);
      }

      //
      election.addBallot(b);
      //
    }
    vector<Candidate> winners = election.findWinners();

    for(int i = 0; i < (int) winners.size(); ++i) {
      w << winners[i].getName() << endl;
    }

    // reset vector
    --num_cases;
    w << endl;
  }
}
