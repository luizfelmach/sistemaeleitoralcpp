#pragma once

#include <usecase.hpp>

class TerminalView {
    UseCase *useCase;

   public:
    TerminalView(UseCase &useCase);
    void NumberOfVacancies();
    void ElectedCandidates();
    void MostVotedCandidates();
    void CandidatesWouldBeElectedInMajority();
    void ElectedCandidatesInProportionalSystem();
    void VotesByPartyAndElectedCandidates();
    void FirstAndLastCandidatesOfEachParty();
    void ElectedCandidatesAgeDistribution();
    void ElectedCandidatesGenderDistribution();
    void TotalVotes();
    void showAll();
};