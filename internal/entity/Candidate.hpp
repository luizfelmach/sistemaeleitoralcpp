#pragma once

#include <string>

class Candidate {
    std::string name;
    int number;
    // Political Party
    int totalVotes;
    int rankingMostVoted;
    // Gender
    bool isElected;
    // Date
    int federationNumber;
    bool rejected;
    bool captionCandidate;

   public:
    std::string getName();
    int getTotalVotes();
    void addVotes(const int &partial);
    void setRejected(const bool &rejected);
    bool isRejected();
    void setCaptionCandidate(const bool &captionCandidate);
    bool isCaptionCandidate();
    void setIsElected(const bool &isElected);
    bool isElected();
    void setRankingMostVoted(const int &rankingMostVoted);
    int getRankingMostVoted();
    int getFederationNumber();
};
