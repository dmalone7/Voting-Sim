#include <vector>      // vector
#include "Candidate.h" // Candidate

class Ballot {
private:
  vector<Candidate> rankings;
  int position;
public:
  Ballot(vector<Candidate> ranks);
  Candidate getCandidate(void);
  void nextCandidate(void);
}
