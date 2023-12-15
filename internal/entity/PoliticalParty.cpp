#include <Candidate.hpp>
#include <PoliticalParty.hpp>
#include <iostream>

PoliticalParty::PoliticalParty(const int number, const std::string name) {
    this->number = number;
    this->name = name;
    this->nominalVotes = 0;
    this->listVotes = 0;
}

const std::string& PoliticalParty::getName() const { return name; }

const int& PoliticalParty::getNominalVotes() const { return nominalVotes; }

const int& PoliticalParty::getListVotes() const { return listVotes; }

const int PoliticalParty::getTotalVotes() const {
    return listVotes + nominalVotes;
}

const std::set<Candidate*>& PoliticalParty::getCandidates() const {
    return candidates;
}

void PoliticalParty::addCandidate(Candidate* candidate) {
    candidates.insert(candidate);
}

void PoliticalParty::addNominalVote(const int& partial) {
    nominalVotes += partial;
}

void PoliticalParty::addListVote(const int& partial) {
    listVotes += partial;
}

const int& PoliticalParty::getNumber() const { return number; }

const int PoliticalParty::numberElected() const {
    int result = 0;
    for (auto candidate : candidates) {
        if (candidate->isElected()) {
            result += 1;
        }
    }
    return result;
}

Candidate* PoliticalParty::getMostVoted() const {
    Candidate* candidateMostVoted = nullptr;
    for (Candidate* candidate : candidates) {
        if (!candidate->isRejected()) {
            if (candidateMostVoted == nullptr) {
                candidateMostVoted = candidate;
                continue;
            }
            if (candidateMostVoted->getTotalVotes() ==
                candidate->getTotalVotes()) {
                if (candidateMostVoted->getBirthDate() >
                    candidate->getBirthDate()) {
                    candidateMostVoted = candidate;
                }
            }
            if (candidateMostVoted->getTotalVotes() <
                candidate->getTotalVotes()) {
                candidateMostVoted = candidate;
            }
        }
    }
    return candidateMostVoted;
}

Candidate* PoliticalParty::getLeastVoted() const {
    Candidate* candidateLeastVoted = nullptr;
    for (Candidate* candidate : candidates) {
        if (!candidate->isRejected() && !candidate->isListCandidate()) {
            if (candidateLeastVoted == nullptr) {
                candidateLeastVoted = candidate;
                continue;
            }
            if (candidateLeastVoted->getTotalVotes() ==
                candidate->getTotalVotes()) {
                if (candidateLeastVoted->getBirthDate() <
                    candidate->getBirthDate()) {
                    candidateLeastVoted = candidate;
                }
            }
            if (candidateLeastVoted->getTotalVotes() >
                candidate->getTotalVotes()) {
                candidateLeastVoted = candidate;
            }
        }
    }
    return candidateLeastVoted;
}
