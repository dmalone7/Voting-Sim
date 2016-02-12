#include "Candidate.h" // Candidate
#include <string>      // string, u16string

using namespace std;

Candidate::Candidate(u16string n) {
  name = n;
  votes = 0;
}

ustring16 Candidate::getName(void) {
  return name;
}

int Candidate::getVotes(void) {
  return votes;
}

void Candidate::addVote(void) {
  ++votes;
}
