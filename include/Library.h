#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Book.h"
#include "Member.h"
#include "BorrowRecord.h"
#include <vector>

class Library
{
private:
    std::vector<Book> books{};
    std::vector<Member> members{};
    std::vector<BorrowRecord> borrow_records{};

public:
    Library();
    void addBook(Book book);
    void removeBook(unsigned id);
    std::vector<Book> searchBooks(const std::string &title_author_isbn) const;
    const std::vector<Book> &getAllBooks() const;
    void addMember(Member member);
    void removeMember(unsigned id);
    const std::vector<Member> &getAllMembers() const;
    void borrowBook(unsigned book_id, unsigned member_id);
    void returnBook(unsigned book_id, unsigned member_id);
    std::vector<Book> getMemberBorrowedBooks(unsigned member_id) const;
    const std::vector<BorrowRecord> &getBorrowingHistory() const;
};

#endif