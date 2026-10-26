#include "../include/BorrowRecord.h"

BorrowRecord::BorrowRecord(unsigned book_id, unsigned member_id, Date borrow_date) : book_id{book_id}, member_id{member_id}, borrow_date{borrow_date}, return_date{std::nullopt} {}

BorrowRecord::BorrowRecord(unsigned book_id, unsigned member_id, Date borrow_date, Date return_date) : book_id{book_id}, member_id{member_id}, borrow_date{borrow_date}, return_date{return_date} {}

void BorrowRecord::setBorrowDate(Date date)
{
    this->borrow_date = date;
}

void BorrowRecord::setReturnDate(Date return_date)
{
    this->return_date = return_date;
}

bool BorrowRecord::isReturned() const
{
    return (return_date.has_value());
}

unsigned BorrowRecord::getBookId() const
{
    return book_id;
}

unsigned BorrowRecord::getMemberId() const
{
    return member_id;
}

Date BorrowRecord::getBorrowDate() const
{
    return borrow_date;
}

std::optional<Date> BorrowRecord::getReturnDate() const
{
    return return_date;
}