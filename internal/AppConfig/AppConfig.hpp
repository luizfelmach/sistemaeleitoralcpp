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

    /**
     * @brief Defines whether the election analysis will be for state or federal deputies.
     * 
     * @param electionType Command-line string that defines the Election Type.
     */
    static void setupElectionType(const std::string& electionType);

    /**
     * @brief Stores the path to the Candidates CSV File.
     * 
     * @param fileOfCandidates Command-line string that contains the path to the Candidates CSV file.
     */
    static void setupFileOfCandidates(const std::string& fileOfCandidates);

    /**
     * @brief Stores the path to the Voting CSV File.
     * 
     * @param fileOfVoting Command-line string that contains the path to the Voting CSV file.
     */
    static void setupFileOfVoting(const std::string& fileOfVoting);

    /**
     * @brief Stores the election date.
     * 
     * @param electionDate Command-line string that contains the date of the election.
     */
    static void setupElectionDate(const std::string& electionDate);

    /**
     * @brief Prints what's stored in AppConfig.
     */
    static void show();
};

    /**
     * @brief Formats print according to the Election Type.
     * 
     * @param os String to be printed.
     * @param electionType Election type (state or federal).
     */
    std::ostream& operator<<(std::ostream& os, const ElectionType& electionType);