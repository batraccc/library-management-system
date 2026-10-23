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
        if (it != books.end())
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