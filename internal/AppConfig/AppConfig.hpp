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

    static void setupElectionType(std::string electionType);
    static void setupFileOfCandidates(std::string fileOfCandidates);
    static void setupFileOfVoting(std::string fileOfVoting);
    static void setupElectionDate(std::string electionDate);

    static void show();
};

std::ostream& operator<<(std::ostream& os, ElectionType electionType);