#include "../include/Member.h"

#include <stdexcept>

Member::Member(unsigned id, std::string name, std::string surname, std::string email) : id{id}, name{name}, surname{surname}, email{email} {}

unsigned Member::getId() const
{
    return id;
}

const std::string &Member::getName() const
{
    return name;
}

const std::string &Member::getSurname() const
{
    return surname;
}

const std::string &Member::getEmail() const
{
    return email;
}

double Member::getLateFees() const
{
    return late_fees;
}

void Member::addLateFee(double fee)
{
    if (fee > 0)
    {
        late_fees += fee;
    }
    else
    {
        throw std::runtime_error("Invalid fee");
    }
}
