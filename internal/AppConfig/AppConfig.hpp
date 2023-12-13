#pragma once

#include <date.hpp>
#include <string>

enum ElectionType { Federal, State };

class AppConfig {
   public:
    static ElectionType electionType;
    static std::string fileOfCandidates;
    static std::string fileOfVoting;
    static Date electionDate;

    static void setupElectionType(const std::string& electionType);
    static void setupFileOfCandidates(const std::string& fileOfCandidates);
    static void setupFileOfVoting(const std::string& fileOfVoting);
    static void setupElectionDate(const std::string& electionDate);

    static void show();
};

std::ostream& operator<<(std::ostream& os, const ElectionType& electionType);