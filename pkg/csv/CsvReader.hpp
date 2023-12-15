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
    /**
     * @brief CsvField's constructor.
     */
    CsvField(){};

    /**
     * @brief CsvField's alternate constructor.
     */
    CsvField(const std::string &line, const std::string &fields,
             const char &delimiter);

    template <typename T>
    T get(const std::string &key);
    template <typename T>
    T getColumn(const int &column);
};

class CsvReader {
    std::string filename;
    std::ifstream fileStream;
    char delimiter;
    std::string fields;
    std::string current;

   public:
    
    /**
     * @brief CsvReader's constructor.
     */
    CsvReader(const std::string &filename);

    /**
     * @brief Evaluates if there's a next line on the file.
     */
    bool hasNext();

    /**
     * @brief Closes file.
     */
    void close();

    /**
     * @brief Sets the CSV Field for the CSV Reader.
     * @param csv CSV Reader without CSV Field.
     * @param cf CSV Field.
     * @returns CSV Reader with CSV Field.
     */
    friend CsvReader &operator>>(CsvReader &csv, CsvField &cf);
};

/**
 * @brief Sets the CSV Field for the CSV Reader.
 * @param csv CSV Reader without CSV Field.
 * @param cf CSV Field.
 * @returns CSV Reader with CSV Field.
 */
CsvReader &operator>>(CsvReader &csv, CsvField &cf);