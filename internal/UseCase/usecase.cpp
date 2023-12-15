#include <AppConfig.hpp>
#include <algorithm>
#include <iostream>
#include <usecase.hpp>

bool candidateMostVoted(Candidate *c1, Candidate *c2) {
    int t1 = c1->getTotalVotes();
    int t2 = c2->getTotalVotes();
    if (t1 > t2) {
        return true;
    } else if (t1 < t2) {
        return false;
    } else if (c1->getBirthDate() < c2->getBirthDate()) {
        return true;
    }
    return false;
}

bool politicalPartyMostVoted(PoliticalParty *p1, PoliticalParty *p2) {
    int t1 = p1->getTotalVotes();
    int t2 = p2->getTotalVotes();
    if (t1 > t2) {
        return true;
    } else if (t1 < t2) {
        return false;
    } else if (p1->getNumber() < p2->getNumber()) {
        return true;
    }
    return false;
}

bool politicalPartyMostVotedCandidate(PoliticalParty *p1, PoliticalParty *p2) {
    int t1 = p1->getMostVoted()->getTotalVotes();
    int t2 = p2->getMostVoted()->getTotalVotes();
    if (t1 > t2) {
        return true;
    } else if (t1 < t2) {
        return false;
    }
    return true;
}

UseCase::UseCase(ElectionRepository &electionRepository) {
    this->electionRepository = &electionRepository;
}

int UseCase::NumberOfVacancies() {
    return electionRepository->getNumberOfElectedCandidates();
}

std::vector<Candidate *> UseCase::ElectedCandidates() {
    auto result = electionRepository->getElectedCandidates();
    std::sort(result.begin(), result.end(), candidateMostVoted);
    return result;
}

std::vector<Candidate *> UseCase::MostVotedCandidates() {
    std::vector<Candidate *> result;
    std::vector<Candidate *> mostVotedCandidates =
        electionRepository->getAllCandidates();
    std::sort(mostVotedCandidates.begin(), mostVotedCandidates.end(),
              candidateMostVoted);
    int numberOfElectedCandidates =
        electionRepository->getNumberOfElectedCandidates();
    for (int i = 0; i < numberOfElectedCandidates; i++) {
        Candidate *candidate = mostVotedCandidates[i];
        candidate->setRankingMostVoted(i + 1);
        result.push_back(candidate);
    }
    return result;
}

std::vector<Candidate *> UseCase::CandidatesWouldBeElectedInMajority() {
    std::vector<Candidate *> result;
    std::vector<Candidate *> mostVotedCandidates =
        electionRepository->getAllCandidates();
    std::sort(mostVotedCandidates.begin(), mostVotedCandidates.end(),
              candidateMostVoted);
    int numberOfElectedCandidates =
        electionRepository->getNumberOfElectedCandidates();
    for (int i = 0; i < numberOfElectedCandidates; i++) {
        Candidate *candidate = mostVotedCandidates[i];
        candidate->setRankingMostVoted(i + 1);
        if (!candidate->isElected()) {
            result.push_back(candidate);
        }
    }
    return result;
}

std::vector<Candidate *> UseCase::ElectedCandidatesInProportionalSystem() {
    std::vector<Candidate *> result;
    std::vector<Candidate *> mostVotedCandidates =
        electionRepository->getAllCandidates();
    std::sort(mostVotedCandidates.begin(), mostVotedCandidates.end(),
              candidateMostVoted);
    int start = electionRepository->getNumberOfElectedCandidates();
    int size = mostVotedCandidates.size();
    for (int i = start; i < size; i++) {
        Candidate *candidate = mostVotedCandidates[i];
        candidate->setRankingMostVoted(i + 1);
        if (candidate->isElected()) {
            result.push_back(candidate);
        }
    }
    return result;
}

std::vector<PoliticalParty *> UseCase::VotesByPartyAndElectedCandidates() {
    auto result = electionRepository->getAllPoliticalParty();
    std::sort(result.begin(), result.end(), politicalPartyMostVoted);
    return result;
}

std::vector<PoliticalParty *> UseCase::FirstAndLastCandidatesOfEachParty() {
    auto allParties = electionRepository->getAllPoliticalParty();
    std::vector<PoliticalParty *> result;
    for (auto party : allParties) {
        if (party->getMostVoted() != nullptr) {
            result.push_back(party);
        }
    }
    std::sort(result.begin(), result.end(), politicalPartyMostVotedCandidate);
    return result;
}

AgeDistributionResult UseCase::ElectedCandidatesAgeDistribution() {
    auto candidates = electionRepository->getElectedCandidates();
    int lessThan30 = 0;
    int between30and40 = 0;
    int between40and50 = 0;
    int between50and60 = 0;
    int greaterThan60 = 0;
    for (Candidate *candidate : candidates) {
        int age = candidate->getBirthDate().until(AppConfig::electionDate);
        if (age < 30) {
            lessThan30 += 1;
            continue;
        }
        if (age < 40) {
            between30and40 += 1;
            continue;
        }
        if (age < 50) {
            between40and50 += 1;
            continue;
        }
        if (age < 60) {
            between50and60 += 1;
            continue;
        } else {
            greaterThan60 += 1;
        }
    }

    return AgeDistributionResult({
        .lessThan30 = lessThan30,
        .between30and40 = between30and40,
        .between40and50 = between40and50,
        .between50and60 = between50and60,
        .greaterThan60 = greaterThan60,
        .total = (int)candidates.size(),
    });
}

GenderDistributionResult UseCase::ElectedCandidatesGenderDistribution() {
    int totalFemale = 0;
    int totalMale = 0;
    for (Candidate *candidate : electionRepository->getElectedCandidates()) {
        if (candidate->getGender() == Female) {
            totalFemale += 1;
        } else {
            totalMale += 1;
        }
    }
    return GenderDistributionResult({
        .female = totalFemale,
        .male = totalMale,
        .total = totalFemale + totalMale,
    });
}

TotalVotesResult UseCase::TotalVotes() {
    int totalRollCallVotes = 0;
    int totalCaptionVotes = 0;
    for (PoliticalParty *politicalParty :
        electionRepository->getAllPoliticalParty()) {
        totalRollCallVotes += politicalParty->getNominalVotes();
        totalCaptionVotes += politicalParty->getListVotes();
    }
    return TotalVotesResult({
        .rollCallVotes = totalRollCallVotes,
        .captionVotes = totalCaptionVotes,
        .totalVotes = totalRollCallVotes + totalCaptionVotes,
    });
}
