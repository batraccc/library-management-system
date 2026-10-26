#ifndef _BORROW_RECORD_H_
#define _BORROW_RECORD_H_
#include "Date.h"
#include <optional>

class BorrowRecord
{
private:
    unsigned book_id;
    unsigned member_id;
    Date borrow_date;
    std::optional<Date> return_date;

public:
    BorrowRecord(unsigned book_id, unsigned member_id, Date borrow_date);
    BorrowRecord(unsigned book_id, unsigned member_id, Date borrow_date, Date return_date);
    void setReturnDate(Date date);
    void setBorrowDate(Date date);
    bool isReturned() const;
    unsigned getBookId() const;
    unsigned getMemberId() const;
    Date getBorrowDate() const;
    std::optional<Date> getReturnDate() const;
};

#endif