#include "header.hpp"

car::car(string model, int id , bool available , chrono::system_clock::time_point due_date, int price, int condition)
        : model(model), id(id), available(available), due_date(due_date), price(price), condition(condition) {}

void car::setModel(string model) {
    this->model = model;
}

void car::setId(int id) {
    this->id = id;
}

void car::setAvailable(bool available) {
    this->available = available;
}

void car::setDue_date(chrono::system_clock::time_point due_date) {
    this->due_date = due_date;
}

string car::getModel() {
    return model;
}

int car::getId() {
    return id;
}

bool car::getAvailable() {
    return available;
}

void car::setPrice(int price)
{
    this->price=price;
}

int car::getPrice()
{
    return this->price;
}

int car::getCondition()
{
    return this->condition;
}

void car::setCondition(int condition)
{
    this->condition=condition;
}

chrono::system_clock::time_point car::getDue_date() {
    return due_date;
}
