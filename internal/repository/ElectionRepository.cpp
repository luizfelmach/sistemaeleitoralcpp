#include <AppConfig.hpp>
#include <CsvReader.hpp>
#include <ElectionRepository.hpp>
#include <iostream>

bool isCandidatePositionInvalid(int candidatePosition) {
    if (candidatePosition == 6 && AppConfig::electionType == Federal) {
        return false;
    }
    if (candidatePosition == 7 && AppConfig::electionType == State) {
        return false;
    }
    return true;
}

Gender getCandidatGender(int code) {
    if (code == 4) {
        return Female;
    }
    return Male;
}

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

bool destCaptionVote(std::string code) {
    if (code == "Válido (legenda)") {
        return true;
    }
    return false;
}

bool isCandidateRejected(int code) {
    if (code == 16 || code == 2) {
        return false;
    }
    return true;
}

bool isInvalidVote(int number) {
    if (number >= 95 && number <= 98) {
        return true;
    }
    return false;
}

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
        int NR_PARTIDO = fields.get<int>("NR_PARTIDO");
        int NR_CANDIDATO = fields.get<int>("NR_CANDIDATO");
        int CD_CARGO = fields.get<int>("CD_CARGO");
        int CD_GENERO = fields.get<int>("CD_GENERO");
        int NR_FEDERACAO = fields.get<int>("NR_FEDERACAO");
        int CD_SIT_TOT_TURNO = fields.get<int>("CD_SIT_TOT_TURNO");
        int CD_SITUACAO_CANDIDATO_TOT =
            fields.get<int>("CD_SITUACAO_CANDIDATO_TOT");
        std::string SG_PARTIDO = fields.get<std::string>("SG_PARTIDO");
        std::string DT_NASCIMENTO = fields.get<std::string>("DT_NASCIMENTO");
        std::string NM_TIPO_DESTINACAO_VOTOS =
            fields.get<std::string>("NM_TIPO_DESTINACAO_VOTOS");
        std::string NM_URNA_CANDIDATO =
            fields.get<std::string>("NM_URNA_CANDIDATO");

        auto it = politicalParties.find(NR_PARTIDO);
        PoliticalParty *politicalParty = it->second;
        if (it == politicalParties.end()) {
            politicalParty = new PoliticalParty(NR_PARTIDO, SG_PARTIDO);
            politicalParties.insert({NR_PARTIDO, politicalParty});
        }

        if (isCandidatePositionInvalid(CD_CARGO)) {
            continue;
        }

        Gender gender = getCandidatGender(CD_GENERO);
        bool isElected = isCandidateElected(CD_SIT_TOT_TURNO);

        Candidate *candidate =
            new Candidate(NM_URNA_CANDIDATO, NR_CANDIDATO, politicalParty,
                          isElected, gender, Date(DT_NASCIMENTO), NR_FEDERACAO);

        if (destCaptionVote(NM_TIPO_DESTINACAO_VOTOS)) {
            captionCandidates.insert({NR_CANDIDATO, candidate});
            candidate->setCaptionCandidate(true);
        } else if (isCandidateRejected(CD_SITUACAO_CANDIDATO_TOT)) {
            rejectedCandidates.insert({NR_CANDIDATO, candidate});
            candidate->setRejected(true);
        } else {
            candidates.insert({NR_CANDIDATO, candidate});
        }
    }
}

void ElectionRepository::setupPoliticalParties() {
    CsvReader file(std::string(AppConfig::fileOfVoting));
    CsvField fields;

    while (file.hasNext()) {
        file >> fields;
        int CD_CARGO = fields.get<int>("CD_CARGO");
        int NR_VOTAVEL = fields.get<int>("NR_VOTAVEL");
        int QT_VOTOS = fields.get<int>("QT_VOTOS");
        if (isValidVote(CD_CARGO, NR_VOTAVEL)) {
            auto it1 = candidates.find(NR_VOTAVEL);
            auto it2 = captionCandidates.find(NR_VOTAVEL);
            auto it3 = politicalParties.find(NR_VOTAVEL);

            if (it1 != candidates.end()) {
                candidates[NR_VOTAVEL]->addVotes(QT_VOTOS);
            } else if (it2 != captionCandidates.end()) {
                captionCandidates[NR_VOTAVEL]
                    ->getPoliticalParty()
                    ->addCaptionVote(QT_VOTOS);
            } else if (it3 != politicalParties.end()) {
                it3->second->addCaptionVote(QT_VOTOS);
            }
        }
    }
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
