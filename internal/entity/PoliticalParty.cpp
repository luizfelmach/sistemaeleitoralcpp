#include <PoliticalParty.hpp>

PoliticalParty::PoliticalParty(const int& number, const std::string& name) {
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