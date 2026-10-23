#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <string>

class Member
{
private:
    unsigned id{};
    std::string name{};
    std::string surname{};
    std::string email{};
    double late_fees{0.0};

public:
    Member(unsigned id, std::string name, std::string surname, std::string email);
    unsigned getId() const;
    const std::string &getName() const;
    const std::string &getSurname() const;
    const std::string &getEmail() const;
    double getLateFees() const;
    void addLateFee(double fee);
    bool operator==(const Member &other) const;
};

#endif