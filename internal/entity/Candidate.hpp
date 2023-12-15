#pragma once

#include <PoliticalParty.hpp>
#include <date.hpp>
#include <string>

class PoliticalParty;

enum Gender { Male, Female };

class Candidate {
    std::string name;
    int number;
    PoliticalParty *politicalParty;
    int totalVotes;
    int rankingMostVoted;
    Gender gender;
    bool elected;
    Date date;
    int federationNumber;
    bool rejected;
    bool listCandidate;

   public:

    /**
     * @brief Candidate's constructor.
     *
     * @param name           The candidate's name.
     * @param number           The candidate's number.
     * @param birthDate        The candidate's birth date.
     * @param politicalParty       The candidate's political party.
     * @param gender     The gender of the candidate (Male or Female).
     * @param federationNumber The candidate's federation number.
     * @param isElected      A bool that defines wether or not the candidate was elected.
     * 
     */
    Candidate(const std::string &name, int number, Date birthDate,
              PoliticalParty *politicalParty, Gender gender, 
              int federationNumber, bool isElected);

    /**
     * @brief Getter for the candidate's number.
     * @returns Candidate's number. 
     */
    int getNumber();

    /**
     * @brief Getter for the candidate's name.
     * @returns Candidate's name. 
     */
    std::string getName();

    /**
     * @brief Getter for the number of votes received by the candidate.
     * @returns Candidate's total votes. 
     */
    int getTotalVotes();

    /**
     * @brief Increases the number of votes received by the candidate.
     * @param partial Number of votes to be added.
     */
    void addVotes(const int &partial);

    /**
     * @brief Getter for the candidate's political party.
     * @returns Candidate's political party. 
     */
    PoliticalParty *getPoliticalParty();

    /**
     * @brief Configures if a candidate's candidacy was rejected or not.
     * @param rejected A bool that defines if a cadidate was rejected (1) or not (0).
     */
    void setRejected(const bool &rejected);

    /**
     * @brief Getter for the candidate's candidacy status.
     * @returns A bool that defines if a cadidate was rejected (1) or not (0). 
     */
    bool isRejected();

    /**
     * @brief Sets if a candidate is a list candidate (1) or not (0).
     * @param ListCandidate A bool for list candidate.
     */
    void setListCandidate(const bool &listCandidate);

    /**
     * @brief Returns if a candidate is a list candidate (1) or not (0).
     * @returns A bool for list candidate.
     */
    bool isListCandidate();

    /**
     * @brief Configures the candidate's election status.
     * @param isElected A bool that defines if a cadidate was elected (1) or not (0).
     */
    void setIsElected(const bool &isElected);

    /**
     * @brief Getter for the candidate's election status.
     * @returns A bool that defines if a cadidate was elected (1) or not (0). 
     */
    bool isElected();

    /**
     * @brief Configures
     * @param rankingMostVoted 
     */
    void setRankingMostVoted(const int rankingMostVoted);

    /**
     * @brief Getter for the 
     * @returns  
     */
    int getRankingMostVoted();

    /**
     * @brief Getter for the candidate's federation number.
     * @returns Candidate's federation number. 
     */
    int getFederationNumber();

    /**
     * @brief Getter for the candidate's gender.
     * @returns Candidate's gender. 
     */
    Gender getGender();

    /**
     * @brief Getter for the candidate's birth date.
     * @returns Candidate's birth date. 
     */
    Date getBirthDate();
};
