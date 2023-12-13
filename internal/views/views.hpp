#pragma once

#include <usecase.hpp>

class TerminalView {
    UseCase *useCase;

   public:
    TerminalView(UseCase &useCase);
    void numberOfVacancies();
    void electedCandidates();
    void MostVotedCandidates();
    void candidatesWouldBeElectedInMajority();
    void ElectedCandidatesInProportionalSystem();
    void VotesByPartyAndElectedCandidates();
    void FirstAndLastCandidatesOfEachParty();
    void ElectedCandidatesAgeDistribution();
    void ElectedCandidatesGenderDistribution();
    void TotalVotes();
    void showAll();
};