#include <AppConfig.hpp>
#include <iostream>

ElectionType AppConfig::electionType = State;
std::string AppConfig::fileOfCandidates = "";
std::string AppConfig::fileOfVoting = "";
Date AppConfig::electionDate = Date("01/01/2001");

void AppConfig::setupElectionType(const std::string& electionType) {
    if (electionType == "--estadual") {
        AppConfig::electionType = State;
        return;
    }
    if (electionType == "--federal") {
        AppConfig::electionType = Federal;
        return;
    }
    exit(1);
}

void AppConfig::setupFileOfCandidates(const std::string& fileOfCandidates) {
    AppConfig::fileOfCandidates = fileOfCandidates;
}

void AppConfig::setupFileOfVoting(const std::string& fileOfVoting) {
    AppConfig::fileOfVoting = fileOfVoting;
}

void AppConfig::setupElectionDate(const std::string& electionDate) {
    AppConfig::electionDate = Date(electionDate);
}

void AppConfig::show() {
    std::cout << "Election Type: " << AppConfig::electionType << "\n";
    std::cout << "Election Date: " << AppConfig::electionDate << "\n";
    std::cout << "File of Candidates: " << AppConfig::fileOfCandidates << "\n";
    std::cout << "File of Voting: " << AppConfig::fileOfVoting << "\n";
}

std::ostream& operator<<(std::ostream& os, const ElectionType& electionType) {
    if (electionType == State) {
        os << "estaduais";
    }
    if (electionType == Federal) {
        os << "federais";
    }
    return os;
}
