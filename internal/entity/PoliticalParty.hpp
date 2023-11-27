#pragma once

#include <Candidate.hpp>
#include <set>
#include <string>

class PoliticalParty {
    std::string name;
    int number;
    int rollCallVotes;
    int captionVotes;
    std::set<Candidate> candidates;

   public:
    std::string getName();
    const int& getRollCallVotes();
    const int& getCaptionVotes();
    const int& getTotalVotes();
    const std::set<Candidate>& getCandidates();
    void addCandidate(const Candidate& candidate);
    void addRollCallVote(const int& partial);
    void addCaptionVote(const int& partial);
    const int& getNumber();
};
