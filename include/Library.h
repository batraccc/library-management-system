#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Book.h"
#include "Member.h"
#include <vector>

class Library
{
private:
    std::vector<Book> books{};
    std::vector<Member> members{};

public:
    Library();
    void addBook(Book book);
    void removeBook(unsigned id);
    std::vector<Book> searchBooks(const std::string &title_author_isbn) const;
    const std::vector<Book> &getAllBooks() const;
};

#endif