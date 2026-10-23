#include "../include/Book.h"

Book::Book(unsigned id, std::string title, std::string author, unsigned short publish_year, std::string isbn) : id{id}, title{title}, author{author}, publish_year{publish_year}, ISBN{isbn} {}

unsigned Book::getId() const
{
    return id;
}

const std::string &Book::getTitle() const
{
    return title;
}

const std::string &Book::getAuthor() const
{
    return author;
}

unsigned short Book::getPublishYear() const
{
    return publish_year;
}

const std::string &Book::getISBN() const
{
    return ISBN;
}

bool Book::operator==(const Book &other) const
{
    return this->author == other.author && this->title == other.title && this->publish_year == other.publish_year && this->ISBN == other.ISBN;
}