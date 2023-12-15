#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

#define CSVFIELD(str) "\"" str "\""

class CsvField {
    char delimiter;
    std::string fields;
    std::string line;

   public:
    CsvField(){};
    CsvField(const std::string &line, const std::string &fields,
             const char &delimiter);
    template <typename T>
    T get(const std::string &key);
};

class CsvReader {
    std::string filename;
    std::ifstream fileStream;
    char delimiter;
    std::string fields;
    std::string current;

   public:
    CsvReader(const std::string &filename);
    bool hasNext();
    void close();
    friend CsvReader &operator>>(CsvReader &csv, CsvField &cf);
};

CsvReader &operator>>(CsvReader &csv, CsvField &cf);