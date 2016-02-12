#include "Ballot.h" // Ballot

Ballot::Ballot(vector<Candidate> ranks) {
  rankings = ranks;
  position = 0;
}

Candidate Ballot::getCandidate(void) {
  return rankings[position];
}

void Ballot::nextCandidate(void) {
  ++position;
}
