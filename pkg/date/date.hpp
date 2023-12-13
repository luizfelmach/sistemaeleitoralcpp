#pragma once

#include <string>

class Date {
   private:
    int day;
    int month;
    int year;

   public:
    Date() {}
    Date(const std::string& date);
    std::string to_string() const;
    int until(const Date& date) const;
    bool operator>(const Date& date2) const;
    bool operator<(const Date& date2) const;
    bool operator==(const Date& date2) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

std::ostream& operator<<(std::ostream& os, const Date& date);