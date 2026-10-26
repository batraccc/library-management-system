#include "../include/Library.h"
#include "../include/Utilities.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <sstream>

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
        if (standardizeString(book.getTitle()) == standardizeString(title_author_isbn) || standardizeString(book.getAuthor()) == standardizeString(title_author_isbn) || standardizeString(book.getISBN()) == standardizeString(title_author_isbn))
        {
            matching_books.push_back(book);
        }
        else if (standardizeString(book.getTitle()).find(standardizeString(title_author_isbn)) != std::string::npos)
        {
            matching_books.push_back(book);
        }
        else if (standardizeString(book.getAuthor()).find(standardizeString(title_author_isbn)) != std::string::npos)
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

bool Library::borrowBook(unsigned book_id, unsigned member_id)
{
    auto book_it = std::find_if(books.begin(), books.end(), [book_id](const Book &book)
                                { return book.getId() == book_id; });
    auto member_it = std::find_if(members.begin(), members.end(), [member_id](const Member &member)
                                  { return member.getId() == member_id; });
    auto borrow_book_it = std::find_if(borrow_records.begin(), borrow_records.end(), [book_id](const BorrowRecord &borrow)
                                       { return borrow.getBookId() == book_id && !borrow.isReturned(); });
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
        return true;
    }
}

void Library::returnBook(unsigned book_id, unsigned member_id)
{
    auto book_it = std::find_if(books.begin(), books.end(), [book_id](const Book &book)
                                { return book.getId() == book_id; });
    auto member_it = std::find_if(members.begin(), members.end(), [member_id](const Member &member)
                                  { return member.getId() == member_id; });
    auto borrow_book_it = std::find_if(borrow_records.begin(), borrow_records.end(), [book_id](const BorrowRecord &borrow)
                                       { return borrow.getBookId() == book_id && !borrow.isReturned(); });
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
            if ((*borrow_book_it->getReturnDate() - borrow_book_it->getBorrowDate()) > 30)
            {
                auto member_ptr = std::find_if(members.begin(), members.end(), [borrow_book_it](const Member &member)
                                               { return member.getId() == borrow_book_it->getMemberId(); });
                member_ptr->addLateFee(((*borrow_book_it->getReturnDate() - borrow_book_it->getBorrowDate()) - 30) * 1);
            }
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

bool Library::bookIdExists(unsigned id) const
{
    return std::any_of(books.begin(), books.end(), [id](const Book &book)
                       { return book.getId() == id; });
}

bool Library::memberIdExists(unsigned id) const
{
    return std::any_of(members.begin(), members.end(), [id](const Member &member)
                       { return member.getId() == id; });
}

bool Library::isBookBorrowed(unsigned id) const
{
    return std::any_of(borrow_records.begin(), borrow_records.end(), [id](const BorrowRecord &record)
                       { return record.getBookId() == id && !record.isReturned(); });
}

bool Library::isMemberBorrowing(unsigned id) const
{
    return std::any_of(borrow_records.begin(), borrow_records.end(), [id](const BorrowRecord &record)
                       { return record.getMemberId() == id && !record.isReturned(); });
}

void Library::saveToFile(const std::string &filename) const
{
    std::ofstream output_stream(filename);
    if (output_stream.is_open())
    {
        for (const Book &book : books)
        {
            output_stream << "book," << book.getId() << "," << book.getTitle() << "," << book.getAuthor() << "," << book.getPublishYear() << "," << book.getISBN() << std::endl;
        }
        for (const Member &member : members)
        {
            output_stream << "member," << member.getId() << "," << member.getName() << "," << member.getSurname() << "," << member.getEmail() << "," << member.getLateFees() << std::endl;
        }
        for (const BorrowRecord &record : borrow_records)
        {
            output_stream << "borrow," << record.getBookId() << "," << record.getMemberId() << ",";
            record.getBorrowDate().display(output_stream);
            output_stream << ",";
            if (record.getReturnDate().has_value())
            {
                record.getReturnDate()->display(output_stream);
            }
            else
            {
                output_stream << "no_date";
            }
            output_stream << std::endl;
        }
        output_stream.close();
        std::cout << "Saved successfully!" << std::endl;
    }
    else
    {
        throw std::runtime_error("File could not be opened!");
    }
}

void Library::loadFromFile(const std::string &filepath)
{
    std::ifstream input_stream(filepath);
    if (input_stream.is_open())
    {
        std::string line{};
        while (getline(input_stream, line))
        {
            if (line.empty())
                continue;
            std::stringstream ss(line);
            std::string type{};
            std::getline(ss, type, ',');
            if (type == "book")
            {
                std::string id_str, title, author, publish_year_str, isbn;
                std::getline(ss, id_str, ',');
                std::getline(ss, title, ',');
                std::getline(ss, author, ',');
                std::getline(ss, publish_year_str, ',');
                std::getline(ss, isbn, ',');

                unsigned id = std::stoi(id_str);
                unsigned short publish_year = std::stoi(publish_year_str);

                addBook(Book(id, title, author, publish_year, isbn));
            }
            else if (type == "member")
            {
                std::string id_str, name, surname, email, late_fees_str;
                std::getline(ss, id_str, ',');
                std::getline(ss, name, ',');
                std::getline(ss, surname, ',');
                std::getline(ss, email, ',');
                std::getline(ss, late_fees_str, ',');

                unsigned id = std::stoi(id_str);
                double late_fees = std::stod(late_fees_str);

                addMember(Member(id, name, surname, email, late_fees));
            }
            else if (type == "borrow")
            {
                std::string book_id_str, member_id_str, borrow_date_str, return_date_str;
                std::getline(ss, book_id_str, ',');
                std::getline(ss, member_id_str, ',');
                std::getline(ss, borrow_date_str, ',');
                std::getline(ss, return_date_str, ',');

                unsigned book_id = std::stoi(book_id_str);
                unsigned member_id = std::stoi(member_id_str);

                std::stringstream ss2(borrow_date_str);
                std::string day_str, month_str, year_str;
                std::getline(ss2, day_str, '/');
                std::getline(ss2, month_str, '/');
                std::getline(ss2, year_str, '/');

                int day_borrow = std::stoi(day_str);
                int month_borrow = std::stoi(month_str);
                int year_borrow = std::stoi(year_str);

                if (return_date_str != "no_date")
                {
                    std::stringstream ss2(return_date_str);
                    std::string day_str, month_str, year_str;
                    std::getline(ss2, day_str, '/');
                    std::getline(ss2, month_str, '/');
                    std::getline(ss2, year_str, '/');

                    int day_return = std::stoi(day_str);
                    int month_return = std::stoi(month_str);
                    int year_return = std::stoi(year_str);

                    if (borrowBook(book_id, member_id))
                    {
                        BorrowRecord &last_record = borrow_records.back();
                        last_record.setBorrowDate(Date(day_borrow, month_borrow, year_borrow));
                        last_record.setReturnDate(Date(day_return, month_return, year_return));
                    }
                }
                else
                {
                    if (borrowBook(book_id, member_id))
                    {
                        BorrowRecord &last_record = borrow_records.back();
                        last_record.setBorrowDate(Date(day_borrow, month_borrow, year_borrow));
                    }
                }
            }
        }
        input_stream.close();
    }
    else
    {
        throw std::runtime_error("File could not be opened!");
    }
}