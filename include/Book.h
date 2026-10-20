#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>

class Book
{
private:
    unsigned id{};
    std::string title{};
    std::string author{};
    unsigned short publish_year{};
    std::string ISBN{};

public:
    Book(unsigned id, std::string title, std::string author, unsigned short publish_year, std::string ISBN);
    unsigned getId() const;
    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    unsigned short getPublishYear() const;
    const std::string &getISBN() const;
};

#endif