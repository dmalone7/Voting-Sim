#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <vector>   // vector

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
     * @param v the vector
     */
    Ballot(vector<int> v);

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
 * Reads from an input stream and finds the winner of an Australian election.
 * @param r the reading stream
 * @param w the writing stream
 */
void voting_solve(istream &r, ostream &w);

using namespace std;

Ballot::Ballot() { }

Ballot::Ballot(const Ballot &source) {
  votes = source.votes;
}

Ballot::Ballot(vector<int> v) {
  votes = v;
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

  //int oldsize = ballots.size();
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
    }

    if(tieFound) {
      for(int i = 0; i < numCandidates; ++i) {
        Candidate c = candidates[i];
        if(c.getNumVotes() < max) {
          tieFound = false;
          // they are a loser, remove all of their ballots and try to give them to a winner
          Ballot loserBallot;
          while((loserBallot = c.removeBallot()).getVotesLeft() != 0) {
            int nextIndex;
            // still finding losers in the Ballot
            nextIndex = loserBallot.peekVote();
            while(nextIndex > -1 && candidates[nextIndex - 1].getNumVotes() < max) {
              nextIndex = loserBallot.nextVote();
            }
            if(nextIndex > -1) {
              Candidate d = candidates[nextIndex - 1];
              Candidate b = candidates[nextIndex];
              candidates[nextIndex - 1].addBallot(loserBallot);
              //cout << "after: " << d.getName() << ", votes = " << d.getNumVotes() << endl;
              //cout << "after: " << b.getName() << ", votes = " << b.getNumVotes() << endl;
              numLosers = 0;
            }
          }
        }
        else {
          // they should be someone who tied 
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

/* calls voting_read given reading and writing streams and prints the winners */
void voting_solve(istream &r, ostream &w) {
  vector<string> candidates;
  int num_cases, num_candidates, loop_candidates, current_ballot;
  int ballots[MAX_BALLOTS][MAX_CANDIDATES];
  string s, end("");

  num_cases = -1;
  num_candidates = -1;
  loop_candidates = -1;
  current_ballot = 0;

  getline(r, s);
  num_cases = stoi(s);
  //w << num_cases << endl;

  getline(r, s); // consume new line character

  // if num_cases == 1, look for EOF instead of '\n'
  while(num_cases > 0) {
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
      loop_candidates = num_candidates;
      // Look for candidate names
      int j = 0;
      while(loop_candidates > 0) {
        getline(r, s);
        candidates.push_back(s);
        //
        election.insert(Candidate(s, j + 1));
        //
        //w << candidates[j] << endl;
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
        //w << ballots[current_ballot][i] << " ";
      }

      sin >> ballots[current_ballot][num_candidates - 1];
      b.addVote(ballots[current_ballot][num_candidates - 1]);
      //w << ballots[current_ballot][num_candidates - 1] << endl;
      ++current_ballot;

      //
      election.addBallot(b);
      //
    }
    vector<Candidate> winners = election.findWinners();

    for(int i = 0; i < (int)winners.size(); ++i) {
      w << winners[i].getName() << endl;
    }

    // reset vector
    candidates.clear();
    --num_cases;
    w << endl;
  }
}

int main () {
  using namespace std;
  voting_solve(cin, cout);
  return 0;
}
