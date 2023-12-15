#include <AppConfig.hpp>
#include <iostream>
#include <views.hpp>

/**
 * @brief Formats the candidate as a string to be printed.
 * 
 * @param candidate Candidate to be printed.
 * @returns The string formatted.
 */
std::string showCandidateName(Candidate* candidate) {
    std::string withoutFederation = "*";
    if (candidate->getFederationNumber() == -1) {
        withoutFederation = "";
    }
    return withoutFederation + candidate->getName();
}

/**
 * @brief Formats the votes as a string to be printed.
 * 
 * @param votes votes to be printed.
 * @returns The string formatted.
 */
std::string getSlugVotes(int votes) {
    if (votes <= 1) return "voto";
    return "votos";
}

/**
 * @brief Defines wether to use plural or singular.
 * 
 * @param votes Number of votes to determine the string.
 * @returns The string formatted.
 */
std::string getSlugNominalVote(int votes) {
    if (votes <= 1) return "nominal";
    return "nominais";
}

/**
 * @brief Defines wether to use plural or singular.
 * 
 * @param votes Number of votes to determine the string.
 * @returns The string formatted.
 */
std::string getSlugCandidate(int votes) {
    if (votes <= 1) return "candidato";
    return "candidatos";
}

/**
 * @brief Defines wether to use plural or singular.
 * 
 * @param vote Number of votes to determine the string.
 * @returns The string formatted.
 */
std::string getSlugElected(int votes) {
    if (votes <= 1) return "eleito";
    return "eleitos";
}

TerminalView::TerminalView(UseCase& useCase) { this->useCase = &useCase; }

void TerminalView::NumberOfVacancies() {
    std::cout << "Número de vagas: " << useCase->NumberOfVacancies() << "\n\n";
}

void TerminalView::ElectedCandidates() {
    auto candidates = useCase->ElectedCandidates();

    std::cout << "Deputados " << AppConfig::electionType << " eleitos:\n";
    int i = 1;
    for (auto candidate : candidates) {
        std::cout << i;
        std::cout << " - " << showCandidateName(candidate);
        std::cout << " (" << candidate->getPoliticalParty()->getName() << ", ";
        std::cout << candidate->getTotalVotes();
        std::cout << " " << getSlugVotes(candidate->getTotalVotes()) << ")\n";
        i += 1;
    }
    std::cout << "\n";
}

void TerminalView::MostVotedCandidates() {
    auto candidates = useCase->MostVotedCandidates();

    std::cout << "Candidatos mais votados (em ordem decrescente de votação e "
                 "respeitando número de vagas):\n";
    int i = 1;
    for (auto candidate : candidates) {
        std::cout << candidate->getRankingMostVoted();
        std::cout << " - " << showCandidateName(candidate);
        std::cout << " (" << candidate->getPoliticalParty()->getName() << ", ";
        std::cout << candidate->getTotalVotes();
        std::cout << " " << getSlugVotes(candidate->getTotalVotes()) << ")\n";
        i += 1;
    }
    std::cout << "\n";
}

void TerminalView::CandidatesWouldBeElectedInMajority() {
    auto candidates = useCase->CandidatesWouldBeElectedInMajority();

    std::cout << "Teriam sido eleitos se a votação fosse majoritária, e não "
                 "foram eleitos:\n";
    std::cout << "(com sua posição no ranking de mais votados)\n";
    int i = 1;
    for (auto candidate : candidates) {
        std::cout << candidate->getRankingMostVoted();
        std::cout << " - " << showCandidateName(candidate);
        std::cout << " (" << candidate->getPoliticalParty()->getName() << ", ";
        std::cout << candidate->getTotalVotes();
        std::cout << " " << getSlugVotes(candidate->getTotalVotes()) << ")\n";
        i += 1;
    }
    std::cout << "\n";
}

void TerminalView::ElectedCandidatesInProportionalSystem() {
    auto candidates = useCase->ElectedCandidatesInProportionalSystem();

    std::cout << "Eleitos, que se beneficiaram do sistema proporcional:\n";
    std::cout << "(com sua posição no ranking de mais votados)\n";
    int i = 1;
    for (auto candidate : candidates) {
        std::cout << candidate->getRankingMostVoted();
        std::cout << " - " << showCandidateName(candidate);
        std::cout << " (" << candidate->getPoliticalParty()->getName() << ", ";
        std::cout << candidate->getTotalVotes();
        std::cout << " " << getSlugVotes(candidate->getTotalVotes()) << ")\n";
        i += 1;
    }
    std::cout << "\n";
}

void TerminalView::VotesByPartyAndElectedCandidates() {
    auto politicalParties = useCase->VotesByPartyAndElectedCandidates();

    std::cout << "Votação dos partidos e número de candidatos eleitos:\n";
    int i = 1;
    for (auto politicalParty : politicalParties) {
        std::cout << i;
        std::cout << " - " << politicalParty->getName();
        std::cout << " - " << std::to_string(politicalParty->getNumber());
        std::cout << ", " << politicalParty->getTotalVotes();
        std::cout << " " << getSlugVotes(politicalParty->getTotalVotes());
        std::cout << " (" << politicalParty->getNominalVotes() << " ";
        std::cout << getSlugNominalVote(politicalParty->getNominalVotes());
        std::cout << " e " << politicalParty->getListVotes();
        std::cout << " de legenda), ";
        std::cout << politicalParty->numberElected() << " ";
        std::cout << getSlugCandidate(politicalParty->numberElected()) << " ";
        std::cout << getSlugElected(politicalParty->numberElected()) << "\n";
        i += 1;
    }

    std::cout << "\n";
}

void TerminalView::FirstAndLastCandidatesOfEachParty() {
    auto politicalParties = useCase->FirstAndLastCandidatesOfEachParty();

    std::cout << "Primeiro e último colocados de cada partido:\n";
    int i = 1;
    for (auto politicalParty : politicalParties) {
        auto mostVoted = politicalParty->getMostVoted();
        auto leastVoted = politicalParty->getLeastVoted();
        std::cout << i;
        std::cout << " - " << politicalParty->getName();
        std::cout << " - " << politicalParty->getNumber() << ", ";
        std::cout << mostVoted->getName() << " (";
        std::cout << std::to_string(mostVoted->getNumber()) << ", ";
        std::cout << mostVoted->getTotalVotes() << " ";
        std::cout << getSlugVotes(mostVoted->getTotalVotes()) << ") / ";
        std::cout << leastVoted->getName() << " (";
        std::cout << std::to_string(leastVoted->getNumber()) << ", ";
        std::cout << leastVoted->getTotalVotes() << " ";
        std::cout << getSlugVotes(leastVoted->getTotalVotes()) << ")\n";
        i += 1;
    }

    std::cout << "\n";
}

void TerminalView::ElectedCandidatesAgeDistribution() {
    auto result = useCase->ElectedCandidatesAgeDistribution();
    std::cout << "Eleitos, por faixa etária (na data da eleição):\n";
    std::cout << "      Idade < 30: " << result.lessThan30 << " ("
              << (float)result.lessThan30 * 100 / result.total << "%"
              << ")\n";
    std::cout << "30 <= Idade < 40: " << result.between30and40 << " ("
              << (float)result.between30and40 * 100 / result.total << "%"
              << ")\n";
    std::cout << "40 <= Idade < 50: " << result.between40and50 << " ("
              << (float)result.between40and50 * 100 / result.total << "%"
              << ")\n";
    std::cout << "50 <= Idade < 60: " << result.between50and60 << " ("
              << (float)result.between50and60 * 100 / result.total << "%"
              << ")\n";
    std::cout << "60 <= Idade     : " << result.greaterThan60 << " ("
              << (float)result.greaterThan60 * 100 / result.total << "%"
              << ")\n";
    std::cout << "\n";
}

void TerminalView::ElectedCandidatesGenderDistribution() {
    auto result = useCase->ElectedCandidatesGenderDistribution();

    std::cout << "Eleitos, por gênero:\n";
    std::cout << "Feminino: " << result.female << " ("
              << (float)result.female * 100 / result.total << "%)\n";
    std::cout << "Masculino: " << result.male << " ("
              << (float)result.male * 100 / result.total << "%)\n";
    std::cout << "\n";
}

void TerminalView::TotalVotes() {
    auto result = useCase->TotalVotes();
    std::cout << "Total de votos válidos:    " << result.totalVotes << "\n";
    std::cout << "Total de votos nominais:   " << result.rollCallVotes << " ("
              << (float)result.rollCallVotes * 100 / result.totalVotes
              << "%)\n";
    std::cout << "Total de votos de legenda: " << result.captionVotes << " ("
              << (float)result.captionVotes * 100 / result.totalVotes << "%)\n";
}

void TerminalView::showAll() {
    NumberOfVacancies();
    ElectedCandidates();
    MostVotedCandidates();
    CandidatesWouldBeElectedInMajority();
    ElectedCandidatesInProportionalSystem();
    VotesByPartyAndElectedCandidates();
    FirstAndLastCandidatesOfEachParty();
    ElectedCandidatesAgeDistribution();
    ElectedCandidatesGenderDistribution();
    TotalVotes();
}
