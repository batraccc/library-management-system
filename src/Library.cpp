#include "../include/Library.h"
#include <algorithm>
#include <stdexcept>

Library::Library() {}

void Library::addBook(Book book)
{
    if (books.size() == 0)
    {
        books.push_back(book);
    }
    else
    {
        auto it = std::find(books.begin(), books.end(), book);
        if (it == books.end())
            books.push_back(book);
        else
        {
            throw std::runtime_error("Book already in the library");
        }
    }
}

void Library::removeBook(unsigned id)
{
    if (books.size() == 0)
    {
        throw std::runtime_error("Library empty");
    }
    auto it = std::find_if(books.begin(), books.end(), [id](const Book &book)
                           { return book.getId() == id; });
    if (it != books.end())
    {
        books.erase(it);
    }
    else
    {
        throw std::runtime_error("No such book in library");
    }
}

const std::vector<Book> &Library::getAllBooks() const
{
    if (books.size() != 0)
    {
        return books;
    }
    throw std::runtime_error("No books in library");
}

std::vector<Book> Library::searchBooks(const std::string &title_author_isbn) const
{
    std::vector<Book> matching_books{};
    for (const Book &book : books)
    {
        if (book.getTitle() == title_author_isbn || book.getAuthor() == title_author_isbn || book.getISBN() == title_author_isbn)
        {
            matching_books.push_back(book);
        }
    }
    if (matching_books.size() != 0)
    {
        return matching_books;
    }
    throw std::runtime_error("No books found that match given criteria");
}

void Library::addMember(Member member)
{
    if (members.size() == 0)
    {
        members.push_back(member);
    }
    else
    {
        auto it = std::find(members.begin(), members.end(), member);
        if (it == members.end())
        {
            members.push_back(member);
        }
        else
        {
            throw std::runtime_error("Member already exists");
        }
    }
}

void Library::removeMember(unsigned id)
{
    if (members.size() == 0)
    {
        throw std::runtime_error("Member list empty");
    }
    auto it = std::find_if(members.begin(), members.end(), [id](const Member &member)
                           { return member.getId() == id; });
    if (it != members.end())
    {
        members.erase(it);
    }
    else
    {
        throw std::runtime_error("No such member exists");
    }
}

const std::vector<Member> &Library::getAllMembers() const
{
    if (members.size() == 0)
    {
        throw std::runtime_error("Member list empty");
    }
    return members;
}

void Library::borrowBook(unsigned book_id, unsigned member_id)
{
    auto book_it = std::find_if(books.begin(), books.end(), [book_id](const Book &book)
                                { return book.getId() == book_id; });
    auto member_it = std::find_if(members.begin(), members.end(), [member_id](const Member &member)
                                  { return member.getId() == member_id; });
    auto borrow_book_it = std::find_if(borrow_records.begin(), borrow_records.end(), [book_id](const BorrowRecord &borrow)
                                       { return borrow.getBookId() == book_id; });
    if (book_it == books.end())
    {
        throw std::runtime_error("Book doesn't exist");
    }
    else if (member_it == members.end())
    {
        throw std::runtime_error("Member doesn't exist");
    }
    else if (borrow_book_it != borrow_records.end())
    {
        throw std::runtime_error("Book already borrowed");
    }
    else
    {
        BorrowRecord record(book_id, member_id, Date());
        borrow_records.push_back(record);
    }
}

void Library::returnBook(unsigned book_id, unsigned member_id)
{
    auto book_it = std::find_if(books.begin(), books.end(), [book_id](const Book &book)
                                { return book.getId() == book_id; });
    auto member_it = std::find_if(members.begin(), members.end(), [member_id](const Member &member)
                                  { return member.getId() == member_id; });
    auto borrow_book_it = std::find_if(borrow_records.begin(), borrow_records.end(), [book_id](const BorrowRecord &borrow)
                                       { return borrow.getBookId() == book_id; });
    if (book_it == books.end())
    {
        throw std::runtime_error("Book doesn't exist");
    }
    else if (member_it == members.end())
    {
        throw std::runtime_error("Member doesn't exist");
    }
    else if (borrow_book_it != borrow_records.end())
    {
        if (borrow_book_it->getMemberId() != member_id)
        {
            throw std::runtime_error("That book is not borrowed by that member");
        }
        else if (borrow_book_it->isReturned())
        {
            throw std::runtime_error("Book is already returned");
        }
        else
        {
            borrow_book_it->setReturnDate(Date());
        }
    }
    else
    {
        throw std::runtime_error("Member has not borrowed that book!");
    }
}
std::vector<Book> Library::getMemberBorrowedBooks(unsigned member_id) const
{
    if (borrow_records.empty())
    {
        throw std::runtime_error("Borrow records do not exist");
    }
    std::vector<Book> member_borrowed_books{};
    for (const BorrowRecord &record : borrow_records)
    {
        if (record.getMemberId() == member_id && !record.isReturned())
        {
            unsigned book_id = record.getBookId();
            auto it = std::find_if(books.begin(), books.end(), [book_id](const Book &book)
                                   { return book.getId() == book_id; });
            if (it != books.end())
            {
                member_borrowed_books.push_back(*it);
            }
        }
    }
    if (member_borrowed_books.empty())
    {
        throw std::runtime_error("Member doesn't have any borrowed books");
    }
    return member_borrowed_books;
}
const std::vector<BorrowRecord> &Library::getBorrowingHistory() const
{
    if (borrow_records.empty())
    {
        throw std::runtime_error("No borrowing history");
    }
    return borrow_records;
}