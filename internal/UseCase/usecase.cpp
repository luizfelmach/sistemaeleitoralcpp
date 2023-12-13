#include <iostream>
#include <usecase.hpp>

UseCase::UseCase(ElectionRepository& electionRepository) {
    this->electionRepository = &electionRepository;
}

int UseCase::numberOfVacancies() { return 21312313; }

std::vector<Candidate*> UseCase::electedCandidates() {
    return std::vector<Candidate*>();
}

std::vector<Candidate*> UseCase::MostVotedCandidates() {
    return std::vector<Candidate*>();
}

std::vector<Candidate*> UseCase::candidatesWouldBeElectedInMajority() {
    return std::vector<Candidate*>();
}

std::vector<Candidate*> UseCase::ElectedCandidatesInProportionalSystem() {
    return std::vector<Candidate*>();
}

std::vector<PoliticalParty*> UseCase::VotesByPartyAndElectedCandidates() {
    return std::vector<PoliticalParty*>();
}

std::vector<PoliticalParty*> UseCase::FirstAndLastCandidatesOfEachParty() {
    return std::vector<PoliticalParty*>();
}

AgeDistributionResult UseCase::ElectedCandidatesAgeDistribution() {
    return AgeDistributionResult({
        .lessThan30 = 10,
        .between30and40 = 10,
        .between40and50 = 10,
        .between50and60 = 10,
        .greaterThan60 = 10,
        .total = 50,
    });
}

GenderDistributionResult UseCase::ElectedCandidatesGenderDistribution() {
    return GenderDistributionResult({
        .female = 20,
        .male = 10,
        .total = 30,
    });
}

TotalVotesResult UseCase::TotalVotes() {
    return TotalVotesResult({
        .rollCallVotes = 10,
        .captionVotes = 50,
        .totalVotes = 60,
    });
}
