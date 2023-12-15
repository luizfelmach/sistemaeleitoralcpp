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

CsvField::CsvField(const std::string &line, const std::string &fields,
                   const char &delimiter) {
    this->line = line;
    this->fields = fields;
    this->delimiter = delimiter;
}

template <>
int CsvField::get(const std::string &keyToFind) {
    std::istringstream fieldsStream(fields);
    std::istringstream lineStream(line);

    std::string key;
    std::string value;

    while (getline(fieldsStream, key, delimiter)) {
        getline(lineStream, value, delimiter);
        if (key == keyToFind) {
            char *value_c = (char *)value.c_str();
            value_c++;
            value_c[value.size() - 2] = '\0';
            std::string valueStr = std::string(value_c);
            // std::cout << iso_8859_1_to_utf8(valueStr) << "\n";
            return stoi(valueStr);
        }
    }
    return 0;
}

template <>
std::string CsvField::get(const std::string &keyToFind) {
    std::istringstream fieldsStream(fields);
    std::istringstream lineStream(line);

    std::string key;
    std::string value;

    while (getline(fieldsStream, key, delimiter)) {
        getline(lineStream, value, delimiter);
        if (key == keyToFind) {
            char *value_c = (char *)value.c_str();
            value_c++;
            value_c[value.size() - 2] = '\0';
            std::string valueStr = std::string(value_c);
            // std::cout << iso_8859_1_to_utf8(valueStr) << "\n";
            return iso_8859_1_to_utf8(valueStr);
        }
    }
    return std::string();
}

CsvReader::CsvReader(const std::string &filename) {
    this->filename = filename;
    this->fileStream = std::ifstream(filename);
    this->delimiter = ';';
    getline(fileStream, fields);
}

bool CsvReader::hasNext() {
    if (getline(fileStream, current)) {
        if (current == "") return false;
        return true;
    }
    return false;
}

void CsvReader::close() { fileStream.close(); }

CsvReader &operator>>(CsvReader &csv, CsvField &cf) {
    cf = CsvField(csv.current, csv.fields, csv.delimiter);
    return csv;
}
