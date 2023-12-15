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

    /**
     * @brief UseCase's constructor.
     * @param electionRepository The election for which the reports will be generated.
     */
    UseCase(ElectionRepository &electionRepository);

     /**
     * @brief Getter for the number of vacancies in this election.
     * @returns Number of vacancies in this election.
     */
    int NumberOfVacancies();

    //The functions below organize the reports to be printed.

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