#include <string> // string, u16string

class Candidate {
private:
  u16string name;
  int votes;
public:
  Candidate(u16string n);
  ustring16 getName(void);
  int getVotes(void);
  void addVote(void);
}
