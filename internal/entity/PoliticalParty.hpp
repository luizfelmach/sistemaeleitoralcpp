#pragma once

#include <set>
#include <string>

class Candidate;

class PoliticalParty {
    std::string name;
    int number;
    int rollCallVotes;
    int captionVotes;
    std::set<Candidate*> candidates;

   public:
    PoliticalParty(const int& number, const std::string& name);
    const std::string& getName() const;
    const int& getRollCallVotes() const;
    const int& getCaptionVotes() const;
    const int getTotalVotes() const;
    const std::set<Candidate*>& getCandidates() const;
    void addCandidate(Candidate* candidate);
    void addRollCallVote(const int& partial);
    void addCaptionVote(const int& partial);
    const int& getNumber() const;
};
