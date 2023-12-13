#pragma once

#include <Candidate.hpp>
#include <ElectionRepository.hpp>
#include <PoliticalParty.hpp>
#include <vector>

struct AgeDistributionResult {
    int lessThan30;
    int between30and40;
    int between40and50;
    int between50and60;
    int greaterThan60;
    int total;
};

struct GenderDistributionResult {
    int female, male, total;
};

struct TotalVotesResult {
    int rollCallVotes, captionVotes, totalVotes;
};

class UseCase {
    ElectionRepository *electionRepository;

   public:
    UseCase(ElectionRepository &electionRepository);
    int NumberOfVacancies();
    std::vector<Candidate *> ElectedCandidates();
    std::vector<Candidate *> MostVotedCandidates();
    std::vector<Candidate *> CandidatesWouldBeElectedInMajority();
    std::vector<Candidate *> ElectedCandidatesInProportionalSystem();
    std::vector<PoliticalParty *> VotesByPartyAndElectedCandidates();
    std::vector<PoliticalParty *> FirstAndLastCandidatesOfEachParty();
    AgeDistributionResult ElectedCandidatesAgeDistribution();
    GenderDistributionResult ElectedCandidatesGenderDistribution();
    TotalVotesResult TotalVotes();
};