#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <string>
#include <cctype>
#include <string>

inline std::string standardizeString(const std::string &string)
{
    std::string new_string{};
    for (const char &character : string)
    {
        if (isalpha(character))
        {
            char new_character = tolower(character);
            new_string.push_back(new_character);
        }
        else if (!isspace(character))
        {
            new_string.push_back(character);
        }
    }
    return new_string;
}

inline bool isValidEmail(const std::string &email)
{
    size_t at_pos = email.find('@');

    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1)
    {
        return false;
    }

    if (email.find('@', at_pos + 1) != std::string::npos)
    {
        return false;
    }

    std::string first_part = email.substr(0, at_pos);
    std::string second_part = email.substr(at_pos + 1);

    size_t dot_pos = second_part.find('.');

    if (dot_pos == std::string::npos || dot_pos == 0 || dot_pos == second_part.length() - 1)
    {
        return false;
    }

    return true;
}

inline bool isValidISBN(const std::string &isbn)
{
    if (isbn.size() == 10 || isbn.size() == 13)
    {
        for (const char &digit : isbn)
        {
            if (!isdigit(digit))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

#endif