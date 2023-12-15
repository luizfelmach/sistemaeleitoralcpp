#pragma once

#include <set>
#include <string>

class Candidate;

class PoliticalParty {
    std::string name;
    int number;
    int nominalVotes;
    int listVotes;
    std::set<Candidate*> candidates;

   public:
   
    /**
     * @brief Party's constructor.
     * 
     * @param number Party's number.
     * @param name Party's name.
     */
    PoliticalParty(const int number, const std::string name);

    /**
     * @brief Getter for the party's name.
     * 
     * @returns Party's name.
     */
    const std::string& getName() const;

    /**
     * @brief Getter for the party's nominal votes.
     * 
     * @returns Party's nominal votes.
     */
    const int& getNominalVotes() const;

    /**
     * @brief Getter for the party's number of list votes.
     * 
     * @returns Number of list votes.
     */
    const int& getListVotes() const;

    /**
     * @brief Getter for the party's total votes.
     * 
     * @returns Party's total votes.
     */
    const int getTotalVotes() const;

    /**
     * @brief Getter for the party's set of candidates.
     * 
     * @returns Party's set of Candidates.
     */
    const std::set<Candidate*>& getCandidates() const;

    /**
     * @brief Adds a candidate to the party's candidates's set.
     * 
     * @param candidate Candidate to be added.
     */
    void addCandidate(Candidate* candidate);

    /**
     * @brief Increases the number of nominal votes.
     * 
     * @param partial Number of nominal votes to be added.
     */
    void addNominalVote(const int& partial);

    /**
     * @brief Increases the number of list votes.
     * 
     * @param partial Number of list votes to be added.
     */
    void addListVote(const int& partial);

    /**
     * @brief Getter for the party's number.
     * 
     * @returns Party's number.
     */
    const int& getNumber() const;

    /**
     * @brief Counter for the elected candidates in a party.
     * 
     * @returns Number of elected candidates in a party.
     */
    const int numberElected() const;

    /**
     * @brief Getter for the party's most voted Candidate.
     * 
     * @returns Party's most voted Candidate.
     */
    Candidate* getMostVoted() const;

    /**
     * @brief Getter for the party's least voted Candidate.
     * 
     * @returns Party's least voted Candidate.
     */
    Candidate* getLeastVoted() const;
};
