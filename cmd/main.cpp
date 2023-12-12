#include <Candidate.hpp>
#include <PoliticalParty.hpp>
#include <iostream>
#include <set>
#include <string>

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "usage: " << argv[0]
                  << " [--estadual/--federal] [file of candidates] [file of "
                     "voting] dd/mm/yyyy]\n";
        exit(1);
    }

    return 0;
}