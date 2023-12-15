#pragma once

#include <Candidate.hpp>
#include <PoliticalParty.hpp>
#include <map>
#include <vector>

class ElectionRepository {
    std::map<int, Candidate *> candidates;
    std::map<int, Candidate *> captionCandidates;
    std::map<int, Candidate *> rejectedCandidates;
    std::map<int, PoliticalParty *> politicalParties;

    /**
     * @brief Configures the candidates through informations extracted from the Candidates CSV File.
     */
    void setupCandidates();
    
    /**
     * @brief Configures the political parties through informations extracted from the Voting CSV File.
     */
    void setupPoliticalParties();

   public:
    
    /**
     * @brief Stores all the election data.
     */
    ElectionRepository();

    /**
     * @brief Getter for the set that contains all the candidates.
     * @returns Set of all the candidates. 
     */
    std::vector<Candidate *> getAllCandidates();

    /**
     * @brief Getter for the set that contains the elected candidates.
     * @returns Set of the elected candidates. 
     */
    std::vector<Candidate *> getElectedCandidates();

    /**
     * @brief Getter for the number of elected candidates.
     * @returns Number of elected candidates.
     */
    int getNumberOfElectedCandidates();

    /**
     * @brief Getter for all the parties.
     * @returns Vector of all the parties. 
     */
    std::vector<PoliticalParty *> getAllPoliticalParty();
};