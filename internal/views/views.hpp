#pragma once

#include <usecase.hpp>

class TerminalView {
    UseCase *useCase;

   public:

    /**
     * @brief TerminalView's constructor.
     * 
     * @param useCase
     */
    TerminalView(UseCase &useCase);

    //All the functions below format and print strings.

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

    /**
     * @brief Prints the reports.
     * 
     * @param useCase
     */
    void showAll();
};