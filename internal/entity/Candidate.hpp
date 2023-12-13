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
    bool captionCandidate;

   public:
    Candidate(const std::string &name, int number,
              PoliticalParty *politicalParty, bool isElected, Gender gender,
              Date birthdayDate, int federationNumber);
    int getNumber();
    std::string getName();
    int getTotalVotes();
    void addVotes(const int &partial);
    PoliticalParty *getPoliticalParty();
    void setRejected(const bool &rejected);
    bool isRejected();
    void setCaptionCandidate(const bool &captionCandidate);
    bool isCaptionCandidate();
    void setIsElected(const bool &isElected);
    bool isElected();
    void setRankingMostVoted(const int rankingMostVoted);
    int getRankingMostVoted();
    int getFederationNumber();
    Gender getGender();
    Date getBirthdayDate();
};
