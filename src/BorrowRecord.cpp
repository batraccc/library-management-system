#include "../include/BorrowRecord.h"

BorrowRecord::BorrowRecord(unsigned book_id, unsigned member_id, Date borrow_date) : book_id{book_id}, member_id{member_id}, borrow_date{borrow_date}, return_date{std::nullopt} {}

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