#pragma once

#include <string>

class Date {
   private:
    int day;
    int month;
    int year;

   public:
   /**
     * @brief Date's simple constructor.
     */
    Date() {}

    /**
     * @brief Date's complete constructor.
     * 
     * @param date String to be transformed into a Date.
     */
    Date(const std::string& date);

    /**
     * @brief Transforms a Date in a string.
     * 
     * @returns String formatted.
     */
    std::string to_string() const;

    /**
     * @brief Calculates age using the date of the election 
     * and the candidate's birth date.
     * 
     * @param date Candidate's birth date.
     * @returns The candidate's age.
     */
    int until(const Date& date) const;

    /**
     * @brief Compares if date2 happened earlier (true) or later (false) than the other one.
     * 
     * @param date2 Date to be compared.
     * @returns A bool to the earliest date.
     */
    bool operator>(const Date& date2) const;

    /**
     * @brief Compares if date2 happened later (true) or earlier (false) than the other one.
     * 
     * @param date2 Date to be compared.
     * @returns A bool to the earliest date.
     */
    bool operator<(const Date& date2) const;

     /**
     * @brief Compares if two dates are the same.
     * 
     * @param date2 Date to be compared.
     * @returns A bool if they are the same date (true) or not (false).
     */
    bool operator==(const Date& date2) const;

     /**
     * @brief Formats date to be printed.
     * 
     * @param os String to be formatted.
     * @param date Date to be printed.
     * @returns String ready to be printed.
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

 /**
 * @brief Formats date to be printed.
 * 
 * @param os String to be formatted.
 * @param date Date to be printed.
 * @returns String ready to be printed.
 */
std::ostream& operator<<(std::ostream& os, const Date& date);