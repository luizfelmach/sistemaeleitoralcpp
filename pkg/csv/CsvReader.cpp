#include "CsvReader.hpp"
#include <sstream>

CsvField::CsvField(const std::string &line,
                   const std::vector<std::string> fields,
                   const char &delimiter) {
    std::istringstream fieldsStream(line);
    std::string value;
    for (const std::string &key : fields) {
        getline(fieldsStream, value, delimiter);
        this->field.insert(std::pair<std::string, std::string>(key, value));
    }
}

template <>
int CsvField::get(const std::string &key) {
    return stoi(field[key]);
}

template <>
std::string CsvField::get(const std::string &key) {
    return field[key];
}

CsvReader::CsvReader(const std::string &filename) {
    this->filename = filename;
    this->fileStream = std::ifstream(filename);
    this->delimiter = ';';
    this->getFields();
}

void CsvReader::getFields() {
    std::string fields;
    getline(this->fileStream, fields);
    std::istringstream fieldsStream(fields);
    std::string field;
    while (getline(fieldsStream, field, delimiter)) {
        this->fields.push_back(field);
    }
}

bool CsvReader::hasNext() { return !fileStream.eof(); }

void CsvReader::close() { fileStream.close(); }

CsvReader &operator>>(CsvReader &csv, CsvField &cf) {
    std::string line;
    getline(csv.fileStream, line);
    cf = CsvField(line, csv.fields, csv.delimiter);
    return csv;
}
