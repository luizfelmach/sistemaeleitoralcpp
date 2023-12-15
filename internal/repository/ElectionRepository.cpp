#include <AppConfig.hpp>
#include <CsvReader.hpp>
#include <ElectionRepository.hpp>
#include <iostream>

/**
 * @brief Evaluates if the candidate's position is invalid (true) or not (false).
 * @returns A bool for invalid candidate's position.  
 */
bool isCandidatePositionInvalid(int candidatePosition) {
    if (candidatePosition == 6 && AppConfig::electionType == Federal) {
        return false;
    }
    if (candidatePosition == 7 && AppConfig::electionType == State) {
        return false;
    }
    return true;
}

/**
 * @brief Determines the gender.
 * @param code A code for the gender.
 * @returns The gender that corresponds to the code.  
 */
Gender getCandidateGender(int code) {
    if (code == 4) {
        return Female;
    }
    return Male;
}

/**
 * @brief Determines if a candidate was elected.
 * @param code A code for the election status of the candidate.
 * @returns If a candidate was elected (true) or not (false).  
 */
bool isCandidateElected(int code) {
    if (code == 2 || code == 3) {
        return true;
    }
    return false;
}

ElectionRepository::ElectionRepository() {
    setupCandidates();
    setupPoliticalParties();
}

ElectionRepository::~ElectionRepository() {

for (auto [key, val] : candidates) {
    delete val;
}


for (auto [key, val] : politicalParties) {
    delete val;
}


for (auto [key, val] : rejectedCandidates) {
    delete val;
}


for (auto [key, val] : captionCandidates) {
    delete val;
}

}

/**
 * @brief Determines the list vote's destination.
 * @param code A code for the list vote's destination.
 * @returns A bool if the votes will be counted as list votes (true) or not (false).  
 */
bool destListVote(std::string code) {
    if (code == "Válido (legenda)") {
        return true;
    }
    return false;
}

/**
 * @brief Determines if a candidate was rejected.
 * @param code A code for the election status of the candidate.
 * @returns If a candidate was rejected (true) or not (false).  
 */
bool isCandidateRejected(int code) {
    if (code == 16 || code == 2) {
        return false;
    }
    return true;
}

/**
 * @brief Determines if a vote is invalid.
 * @param number A code for a vote's validity.
 * @returns If a vote is invalid (true) or not (false).  
 */
bool isInvalidVote(int number) {
    if (number >= 95 && number <= 98) {
        return true;
    }
    return false;
}

/**
 * @brief Determines if a vote is valid.
 * @param CD_CARGO The candidate's position code.
 * @param NR_VOTAVEL The vote's validity code.
 * @returns If a vote is valid (true) or not (false).  
 */
bool isValidVote(int CD_CARGO, int NR_VOTAVEL) {
    if (isCandidatePositionInvalid(CD_CARGO)) {
        return false;
    }
    if (isInvalidVote(NR_VOTAVEL)) {
        return false;
    }
    return true;
}

void ElectionRepository::setupCandidates() {
    CsvReader file(std::string(AppConfig::fileOfCandidates));
    CsvField fields;

    while (file.hasNext()) {
        file >> fields;
        int NR_PARTIDO = fields.getColumn<int>(27);
        int NR_CANDIDATO = fields.getColumn<int>(16);
        int CD_CARGO = fields.getColumn<int>(13);
        int CD_GENERO = fields.getColumn<int>(45);
        int NR_FEDERACAO = fields.getColumn<int>(30);
        int CD_SIT_TOT_TURNO = fields.getColumn<int>(56);
        int CD_SITUACAO_CANDIDATO_TOT = fields.getColumn<int>(68);
        std::string SG_PARTIDO = fields.getColumn<std::string>(28);
        std::string DT_NASCIMENTO = fields.getColumn<std::string>(42);
        std::string NM_TIPO_DESTINACAO_VOTOS =
            fields.getColumn<std::string>(67);
        std::string NM_URNA_CANDIDATO = fields.getColumn<std::string>(18);

        auto it = politicalParties.find(NR_PARTIDO);
        PoliticalParty *politicalParty = it->second;
        if (it == politicalParties.end()) {
            politicalParty = new PoliticalParty(NR_PARTIDO, SG_PARTIDO);
            politicalParties.insert({NR_PARTIDO, politicalParty});
        }

        if (isCandidatePositionInvalid(CD_CARGO)) {
            continue;
        }

        Gender gender = getCandidateGender(CD_GENERO);
        bool isElected = isCandidateElected(CD_SIT_TOT_TURNO);
        Date birthDate =
            DT_NASCIMENTO == "" ? Date("01/01/2001") : Date(DT_NASCIMENTO);

        Candidate *candidate =
            new Candidate(NM_URNA_CANDIDATO, NR_CANDIDATO, birthDate, politicalParty,
                          gender, NR_FEDERACAO, isElected);

        if (destListVote(NM_TIPO_DESTINACAO_VOTOS)) {
            captionCandidates.insert({NR_CANDIDATO, candidate});
            candidate->setListCandidate(true);
        } else if (isCandidateRejected(CD_SITUACAO_CANDIDATO_TOT)) {
            rejectedCandidates.insert({NR_CANDIDATO, candidate});
            candidate->setRejected(true);
        } else {
            candidates.insert({NR_CANDIDATO, candidate});
        }
    }

    file.close();
}

void ElectionRepository::setupPoliticalParties() {
    CsvReader file(std::string(AppConfig::fileOfVoting));
    CsvField fields;

    while (file.hasNext()) {
        file >> fields;
        int CD_CARGO = fields.getColumn<int>(17);
        int NR_VOTAVEL = fields.getColumn<int>(19);
        int QT_VOTOS = fields.getColumn<int>(21);
        if (isValidVote(CD_CARGO, NR_VOTAVEL)) {
            auto it1 = candidates.find(NR_VOTAVEL);
            auto it2 = captionCandidates.find(NR_VOTAVEL);
            auto it3 = politicalParties.find(NR_VOTAVEL);

            if (it1 != candidates.end()) {
                candidates[NR_VOTAVEL]->addVotes(QT_VOTOS);
            } else if (it2 != captionCandidates.end()) {
                captionCandidates[NR_VOTAVEL]
                    ->getPoliticalParty()
                    ->addListVote(QT_VOTOS);
            } else if (it3 != politicalParties.end()) {
                it3->second->addListVote(QT_VOTOS);
            }
        }
    }

    file.close();
}

std::vector<Candidate *> ElectionRepository::getAllCandidates() {
    std::vector<Candidate *> v;
    for (const auto [key, val] : candidates) {
        v.push_back(val);
    }
    return v;
}

std::vector<Candidate *> ElectionRepository::getElectedCandidates() {
    std::vector<Candidate *> v;
    for (auto &[key, val] : candidates) {
        if (val->isElected()) {
            v.push_back(val);
        }
    }
    return v;
}

int ElectionRepository::getNumberOfElectedCandidates() {
    return getElectedCandidates().size();
}

std::vector<PoliticalParty *> ElectionRepository::getAllPoliticalParty() {
    std::vector<PoliticalParty *> v;
    for (const auto [key, val] : politicalParties) {
        v.push_back(val);
    }
    return v;
}
