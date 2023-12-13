#include "CsvReader.hpp"

#include <stdint.h>

#include <sstream>

std::string iso_8859_1_to_utf8(std::string &str) {
    std::string strOut;
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        uint8_t ch = *it;
        if (ch < 0x80) {
            strOut.push_back(ch);
        } else {
            strOut.push_back(0b11000000 | (ch >> 6));
            strOut.push_back(0b10000000 | (ch & 0b00111111));
        }
    }
    return strOut;
}

std::string CsvRemoveQuote(const std::string &plain) {
    std::string withoutQuote = plain;
    size_t firstQuote = withoutQuote.find_first_of("\"");
    size_t lastQuote = withoutQuote.find_last_of("\"");
    if (firstQuote != std::string::npos && lastQuote != std::string::npos) {
        withoutQuote.erase(firstQuote, 1);
        withoutQuote.erase(lastQuote - 1, 1);
    }
    return withoutQuote;
}

CsvField::CsvField(const std::string &line,
                   const std::vector<std::string> fields,
                   const char &delimiter) {
    std::istringstream fieldsStream(line);
    std::string value;
    for (const std::string &key : fields) {
        getline(fieldsStream, value, delimiter);
        this->field.insert(std::pair<std::string, std::string>(
            CsvRemoveQuote(key), CsvRemoveQuote(value)));
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
    fields = iso_8859_1_to_utf8(fields);
    std::istringstream fieldsStream(fields);
    std::string field;
    while (getline(fieldsStream, field, delimiter)) {
        this->fields.push_back(field);
    }
}

bool CsvReader::hasNext() {
    if (getline(fileStream, current)) {
        current = iso_8859_1_to_utf8(current);
        if (current == "") return false;
        return true;
    }
    return false;
}

void CsvReader::close() { fileStream.close(); }

CsvReader &operator>>(CsvReader &csv, CsvField &cf) {
    std::string line;
    cf = CsvField(csv.current, csv.fields, csv.delimiter);
    return csv;
}
