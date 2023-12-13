#include <date.hpp>
#include <sstream>
#include <vector>

Date::Date(std::string date) {
    std::vector<std::string> parsedDate;
    std::stringstream stream(date);
    std::string data;
    while (std::getline(stream, data, '/')) {
        parsedDate.push_back(data);
    }
    this->day = stoi(parsedDate[0]);
    this->month = stoi(parsedDate[1]);
    this->year = stoi(parsedDate[2]);
}

bool Date::operator>(const Date& date2) const {
    if (year > date2.year) {
        return true;
    } else if (year == date2.year && month > date2.month) {
        return true;
    } else if (year == date2.year && month == date2.month && day > date2.day) {
        return true;
    }
    return false;
}

bool Date::operator<(const Date& date2) const {
    if (year < date2.year) {
        return true;
    } else if (year == date2.year && month < date2.month) {
        return true;
    } else if (year == date2.year && month == date2.month && day < date2.day) {
        return true;
    }
    return false;
}

bool Date::operator==(const Date& date2) const {
    return this->day == date2.day and this->month == date2.month and
           this->year == date2.year;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.to_string();
    return os;
}

int Date::until(const Date& date) const {
    int age = date.year - this->year;

    if (date.month < this->month) {
        age--;
    } else if (date.month == this->month) {
        if (date.day < this->day) {
            age--;
        }
    }
    return age;
}

std::string Date::to_string() const {
    std::string a = std::to_string(this->day) + '/' +
                    std::to_string(this->month) + '/' +
                    std::to_string(this->year);
    return a;
}