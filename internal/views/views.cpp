#include <iostream>
#include <views.hpp>

TerminalView::TerminalView(UseCase& useCase) { this->useCase = &useCase; }

void TerminalView::numberOfVacancies() {
    std::cout << "Número de vagas: " << useCase->numberOfVacancies() << "\n\n";
}

void TerminalView::electedCandidates() {}

void TerminalView::MostVotedCandidates() {}

void TerminalView::candidatesWouldBeElectedInMajority() {}

void TerminalView::ElectedCandidatesInProportionalSystem() {}

void TerminalView::VotesByPartyAndElectedCandidates() {}

void TerminalView::FirstAndLastCandidatesOfEachParty() {}

void TerminalView::ElectedCandidatesAgeDistribution() {}

void TerminalView::ElectedCandidatesGenderDistribution() {}

void TerminalView::TotalVotes() {}

void TerminalView::showAll() {
    numberOfVacancies();
    electedCandidates();
    MostVotedCandidates();
    candidatesWouldBeElectedInMajority();
    ElectedCandidatesInProportionalSystem();
    VotesByPartyAndElectedCandidates();
    FirstAndLastCandidatesOfEachParty();
    ElectedCandidatesAgeDistribution();
    ElectedCandidatesGenderDistribution();
    TotalVotes();
}
