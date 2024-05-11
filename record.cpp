#include "header.hpp"

record::record(int car_id, string car_model, int user_id, string user_name, int return_status, chrono::system_clock::time_point issue_date, chrono::system_clock::time_point due_date, chrono::system_clock::time_point return_date): car_id(car_id), user_id(user_id), car_model(car_model), user_name(user_name), return_status(return_status), due_date(due_date), issue_date(issue_date), return_date(return_date){}

void record::setCarId(int id)
{
    this->car_id=id;
}

void record::setUserId(int id)
{
    this->user_id=id;
}

void record::setCarModel(string model)
{
    this->car_model=model;
}

void record::setUserName(string name)
{
    this->user_name=name;
}

void record::setReturnStatus(int status)
{
    this->return_status=status;
}

void record::setIssueDate(chrono::system_clock::time_point issue_date)
{
    this->issue_date=issue_date;
}

void record::setDueDate(chrono::system_clock::time_point due_date)
{
    this->due_date=due_date;
}

void record::setReturnDate(chrono::system_clock::time_point return_date)
{
    this->return_date=return_date;
}

int record::getCarId()
{
    return this->car_id;
}

int record::getUserId()
{
    return this->user_id;
}

string record::getCarModel()
{
    return this->car_model;
}

string record::getUserName()
{
    return this->user_name;
}

int record::getReturnStatus()
{
    return this->return_status;
}

chrono::system_clock::time_point record::getIssueDate()
{
    return this->issue_date;
}

chrono::system_clock::time_point record::getDueDate()
{
    return this->due_date;
}

chrono::system_clock::time_point record::getReturnDate()
{
    return this->return_date;
}

