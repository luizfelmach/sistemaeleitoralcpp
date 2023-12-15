#include <Candidate.hpp>

Candidate::Candidate(const std::string &name, int number, Date birthDate,
                     PoliticalParty *politicalParty, Gender gender, 
                     int federationNumber, bool isElected){
    this->name = name;
    this->number = number;
    this->politicalParty = politicalParty;
    this->elected = isElected;
    this->gender = gender;
    this->date = birthDate;
    this->federationNumber = federationNumber;
    this->totalVotes = 0;
    this->rejected = false;
    this->captionCandidate = false;
    this->rankingMostVoted = 0;
    politicalParty->addCandidate(this);
}

int Candidate::getNumber() { return number; }

std::string Candidate::getName() { return name; }

int Candidate::getTotalVotes() { return totalVotes; }

void Candidate::addVotes(const int& partial) {
    totalVotes += partial;
    politicalParty->addRollCallVote(partial);
}

PoliticalParty* Candidate::getPoliticalParty() { return politicalParty; }

void Candidate::setRejected(const bool& rejected) { this->rejected = rejected; }

bool Candidate::isRejected() { return rejected; }

void Candidate::setCaptionCandidate(const bool& captionCandidate) {
    this->captionCandidate = captionCandidate;
}

bool Candidate::isCaptionCandidate() { return captionCandidate; }

void Candidate::setIsElected(const bool& isElected) {
    this->elected = isElected;
}

bool Candidate::isElected() { return elected; }

void Candidate::setRankingMostVoted(const int rankingMostVoted) {
    this->rankingMostVoted = rankingMostVoted;
}

int Candidate::getRankingMostVoted() { return rankingMostVoted; }

int Candidate::getFederationNumber() { return federationNumber; }

Gender Candidate::getGender() { return gender; }

Date Candidate::getBirthDate() { return date; }
