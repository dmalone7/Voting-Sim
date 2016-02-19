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

int Ballot::getVotesLeft(void) {
  return votes.size();
}

int Ballot::nextVote(void) {
  // No votes left for this candidate.
  if(votes.empty())
    return 0;

  int ret = votes[0];
  votes.erase(votes.begin());
  return ret;
} 

void Ballot::addVote(int v) {
  votes.push_back(v);
}

int Ballot::peekVote(void) {
  if(votes.size() > 0)
    return votes[0];
  else return -1;
}

////////////////////////////////////

Candidate::Candidate(string n, int i) {
  name = n;
  candidateIndex = i;
}

// remove a ballot from a candidate, removing that Candidate from the Ballot
Ballot Candidate::removeBallot(void) {
  if(ballots.empty())
    return Ballot();

  int oldsize = ballots.size();
  // Make a copy
  ballots[0].nextVote();
  Ballot ballotCopy(ballots[0]);
  ballots.erase(ballots.begin());
  return ballotCopy;
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
  int max, currentVotes;
  bool tieFound;

  int numLosers = 0;
  while(numLosers == 0) {
    int tiedBallots = 0;
    numLosers = 0;
    max = -1;
    tieFound = false;
    for(int i = 0; i < numCandidates; ++i) {
      Candidate c = candidates[i];
      currentVotes = c.getNumVotes();
      if(max < currentVotes) {
        max = currentVotes;
        tieFound = false;
      }

      else if(max == currentVotes) {
        tieFound = true;
      }
      cout << "max is " << max << ", tieFound is " << tieFound << endl;
    }

    if(tieFound) {
      for(int i = 0; i < numCandidates; ++i) {
        Candidate c = candidates[i];
        cout << "found tie\n";
        if(c.getNumVotes() < max) {
          cout << "loser index = " << c.getIndex() << endl;
          tieFound = false;
          // ++numLosers;
          // they are a loser, remove all of their ballots and try to give them to a winner
          Ballot loserBallot;
          while((loserBallot = c.removeBallot()).getVotesLeft() != 0) {
            cout << "removing ballot from candidate " << c.getName() << ", next vote for ";
            int nextIndex;
            // still finding losers in the Ballot
            nextIndex = loserBallot.peekVote();
            while(nextIndex > -1 && candidates[nextIndex - 1].getNumVotes() < max) {
              nextIndex = loserBallot.nextVote();
              cout << nextIndex << ", ";
            }
            cout << endl;
            if(nextIndex > -1) {
              Candidate d = candidates[nextIndex - 1];
              Candidate b = candidates[nextIndex];
              candidates[nextIndex - 1].addBallot(loserBallot);
              cout << "after: " << d.getName() << ", votes = " << d.getNumVotes() << endl;
              cout << "after: " << b.getName() << ", votes = " << b.getNumVotes() << endl;
              assert(candidates[nextIndex - 1].getNumVotes() >= max);
              numLosers = 0;
            }
          }
        }
        else {
          // they should be someone who tied 
          cout << "found a tied person : " << c.getName() << endl;
          tiedBallots += c.getNumVotes();
          // There are no more ballots to give away
          if(tiedBallots == numBallots)
            break;
        }

        if (tieFound) {
          ++numLosers;
        }
      }
    }

    // SINGLE Winner was found.
    else {
      break;
    }
  }

  for(int i = 0; i < numCandidates; ++i) {
    Candidate c = candidates[i];
    if(c.getNumVotes() == max) {
      winners.push_back(c);
    }
  }

  return winners;
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
    Election election;
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
        //
        election.insert(Candidate(s, j + 1));
        //
        w << candidates[j] << endl;
        ++j;
        --loop_candidates;
      }
    }

    // strange case where num_candidates == 0 and num_cases == 1 
    // still works; s != end immediately terminates while

    // while still lines in the test case
    while(getline(r, s) && s.compare(end) != 0) {
      istringstream sin(s);

      Ballot b;
      for(int i = 0; i < num_candidates - 1; ++i) {
        sin >> ballots[current_ballot][i];
        b.addVote(ballots[current_ballot][i]);
        w << ballots[current_ballot][i] << " ";
      }

      sin >> ballots[current_ballot][num_candidates - 1];
      b.addVote(ballots[current_ballot][num_candidates - 1]);
      w << ballots[current_ballot][num_candidates - 1] << endl;
      ++current_ballot;

      //
      election.addBallot(b);
      //
    }
    vector<Candidate> winners = election.findWinners();

    w << "Winners:\n";
    for(int i = 0; i < winners.size(); ++i) {
      w << winners[i].getName() << endl;
    }

    // reset vector
    candidates.clear();
    --num_cases;
    w << endl;
  }
}
