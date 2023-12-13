#include <locale.h>

#include <AppConfig.hpp>
#include <ElectionRepository.hpp>
#include <iomanip>
#include <iostream>
#include <usecase.hpp>
#include <views.hpp>

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    if (argc != 5) {
        std::cerr << "usage: " << argv[0]
                  << " [--estadual/--federal] [file of candidates] [file of "
                     "voting] dd/mm/yyyy]\n";
        exit(1);
    }

    std::locale brazilianLocale("pt_BR.utf8");
    std::locale::global(brazilianLocale);
    std::cout.imbue(brazilianLocale);
    std::cout << std::fixed << std::setprecision(2);

    AppConfig::setupElectionType(argv[1]);
    AppConfig::setupFileOfCandidates(argv[2]);
    AppConfig::setupFileOfVoting(argv[3]);
    AppConfig::setupElectionDate(argv[4]);

    // AppConfig::show();

    ElectionRepository repository;
    UseCase useCase(repository);
    TerminalView views(useCase);

    views.showAll();

    return 0;
}