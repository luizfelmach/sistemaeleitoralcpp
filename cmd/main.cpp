#include <AppConfig.hpp>
#include <ElectionRepository.hpp>
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "usage: " << argv[0]
                  << " [--estadual/--federal] [file of candidates] [file of "
                     "voting] dd/mm/yyyy]\n";
        exit(1);
    }

    AppConfig::setupElectionType(std::string(argv[1]));
    AppConfig::setupFileOfCandidates(std::string(argv[2]));
    AppConfig::setupFileOfVoting(std::string(argv[3]));
    AppConfig::setupElectionDate(std::string(argv[4]));

    // AppConfig::show();

    ElectionRepository repository;

    return 0;
}