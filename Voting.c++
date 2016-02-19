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
  // return votes.size();
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
  if(index == ballots.size())
    return Ballot();

  return ballots[index++];
}

void Candidate::resetNumVotes(void) {
  numVotes = 0;
  // index = ballots.size()
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

void Election::insert(Candidate *c) {
  candidates.push_back(c);
}

int Election::getNumCandidates(void) {
  return candidates.size();
}

vector<Candidate*> Election::findWinners(void) {
  vector<Candidate*> winners;
  int numCandidates = candidates.size();

  if(numCandidates == 0)
    return candidates;

  int max, currentVotes, min;
  bool mustRedistribute;

  int numLosers = 0;
  while(numLosers == 0) {
    min = 10000; 
    numLosers = 0;
    max = -1;
    mustRedistribute = true;
    for(int i = 0; i < numCandidates; ++i) {
      Candidate *c = candidates[i];
      currentVotes = c->getNumVotes();
      if(max < currentVotes) {
        max = currentVotes;

        if(currentVotes >= (numBallots / 2 + 1))  
          mustRedistribute = false;
      }

      if(min > currentVotes) {
        min = currentVotes;
      }
    }

    printf("min = %d, max = %d\n", min, max);

    if(max == min) {
      cout << "SOULD BE STOPING NOW" << endl;
      mustRedistribute = false;
    }

    if(mustRedistribute) {
      cout << "Looking for losers\n";
      for(int i = 0; i < numCandidates; ++i) {
        Candidate *c = candidates[i];
        if(c->getNumVotes() == min) {
          // have a loser now, c === loser

          cout << "we have a loser. name is " << c->getName() << endl;

          cout << "loser has " << c->getNumVotes() << endl;
          Ballot loserBallot = c->removeBallot();
          while(loserBallot.getVotesLeft() > 0) {
            Candidate *receiver = candidates[loserBallot.nextVote() - 1];
            if(receiver->getNumVotes() > min) {
              // receiver is not a loser
              receiver->addBallot(loserBallot);
            }
          }
          c->resetNumVotes();
          cout << "loser now has " << c->getNumVotes() << endl;
        }
      }
      cout << "STOPPED looking for losers\n";
    }

    else {
      for(int i = 0; i < numCandidates; ++i) {
        Candidate *c = candidates[i];
        if(c->getNumVotes() == max) {
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
  candidates[candIndex - 1]->addBallot(b);
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
  //w << num_cases << endl;

  getline(r, s); // consume new line character

  // if num_cases == 1, look for EOF instead of '\n'
  while(num_cases > 0) {
    static int count = 1;
    w << "Count = " << count++ << endl;
    Election election;
    getline(r, s);
    num_candidates = stoi(s);
    //w << num_candidates << endl;

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
        Candidate toInsert (s, j + 1);
        election.insert(&toInsert);
        //
      }
    }

    // strange case where num_candidates == 0 and num_cases == 1 
    // still works; s != end immediately terminates while

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
    vector<Candidate*> winners = election.findWinners();

    for(int i = 0; i < (int)winners.size(); ++i) {
      w << winners[i]->getName() << endl;
    }

    // reset vector
    --num_cases;
    w << endl;
  }
}
