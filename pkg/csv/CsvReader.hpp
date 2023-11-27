#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

class CsvField {
    std::map<std::string, std::string> field;

   public:
    CsvField(){};
    CsvField(const std::string &line, const std::vector<std::string> fields,
             const char &delimiter);
    template <typename T>
    T get(const std::string &key);
};

class CsvReader {
    std::string filename;
    std::ifstream fileStream;
    char delimiter;
    std::vector<std::string> fields;
    void getFields();

   public:
    CsvReader(const std::string &filename);
    bool hasNext();
    void close();
    friend CsvReader &operator>>(CsvReader &csv, CsvField &cf);
};

CsvReader &operator>>(CsvReader &csv, CsvField &cf);