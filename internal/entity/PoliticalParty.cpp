#include <Candidate.hpp>
#include <PoliticalParty.hpp>
#include <iostream>

PoliticalParty::PoliticalParty(const int number, const std::string name) {
    this->number = number;
    this->name = name;
    this->rollCallVotes = 0;
    this->captionVotes = 0;
}

const std::string& PoliticalParty::getName() const { return name; }

const int& PoliticalParty::getRollCallVotes() const { return rollCallVotes; }

const int& PoliticalParty::getCaptionVotes() const { return captionVotes; }

const int PoliticalParty::getTotalVotes() const {
    return captionVotes + rollCallVotes;
}

const std::set<Candidate*>& PoliticalParty::getCandidates() const {
    return candidates;
}

void PoliticalParty::addCandidate(Candidate* candidate) {
    candidates.insert(candidate);
}

void PoliticalParty::addRollCallVote(const int& partial) {
    rollCallVotes += partial;
}

void PoliticalParty::addCaptionVote(const int& partial) {
    captionVotes += partial;
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
                if (candidateMostVoted->getBirthdayDate() >
                    candidate->getBirthdayDate()) {
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
        if (!candidate->isRejected() && !candidate->isCaptionCandidate()) {
            if (candidateLeastVoted == nullptr) {
                candidateLeastVoted = candidate;
                continue;
            }
            if (candidateLeastVoted->getTotalVotes() ==
                candidate->getTotalVotes()) {
                if (candidateLeastVoted->getBirthdayDate() <
                    candidate->getBirthdayDate()) {
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
