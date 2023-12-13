#pragma once

#include <Candidate.hpp>
#include <PoliticalParty.hpp>
#include <map>
#include <vector>

class ElectionRepository {
    std::map<int, Candidate *> candidates;
    std::map<int, Candidate *> captionCandidates;
    std::map<int, Candidate *> rejectedCandidates;
    std::map<int, PoliticalParty *> politicalParties;

    void setupCandidates();
    void setupPoliticalParties();

   public:
    ElectionRepository();
    std::vector<Candidate *> getAllCandidates();
    std::vector<Candidate *> getElectedCandidates();
    int getNumberOfElectedCandidates();
    std::vector<PoliticalParty *> getAllPoliticalParty();
};