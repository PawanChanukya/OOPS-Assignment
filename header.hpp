#ifndef HEADER_HPP
#define HEADER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class car{
    string model;
    bool available;
    int id;
    int price;
    int condition;
    chrono::system_clock::time_point due_date;
    public:
    car(string model="unknown", int id=-1 , bool available=true, chrono::system_clock::time_point due_date=chrono::system_clock::now(), int price=1000, int condition=3);
    void setModel(string model);
    void setId(int id);
    void setAvailable(bool available);
    void setPrice(int price);
    void setDue_date(chrono::system_clock::time_point due_date);
    string getModel();
    int getId();
    bool getAvailable();
    int getPrice();
    int getCondition();
    void setCondition(int condition);
    chrono::system_clock::time_point getDue_date();
};

class carDatabase : public car{
    vector<car> allCars;

    public:
    carDatabase(string model="unknown", int id=-1 , bool available=true, chrono::system_clock::time_point due_date=chrono::system_clock::now(), int price=1000, int condition=3);
    void addCar();
    void deleteCar();
    void updateCar();
    void searchCar();
};

class user {
protected:
    string name;
    int id;
    string password;
public:
    user(string name="unknown", int id=-1, string passwor="password" );
    void setName(string name);
    void setPassword(string password);
    void setId(int id);
    string getName();
    string getPassword();
    int getId();
    void get_available_cars();
};

class manager : public user {
public:
    manager(string name="unknown", int id=-1, string password="password");
    void addCar(car& C);
    void deleteCar(int id);
    void updateCar(int id);
    void addCustomer();
    void deleteCustomer(int id);
    void updateCustomer(int id);
    void addEmployee();
    void deleteEmployee(int id);
    void updateEmployee(int id);
    void getAllRecords();
    void modifyRecords();

    
};

class customer: public user{
    vector<car> rented_cars;
    int customer_score;
    int due;
    int fine;

    public:

    customer(string name="unknown", int id=-1, string password="password", int score=3, int due=0 , int fine=0);
    vector<car> getRentedCars();
    void setRentedCars(vector<car>& list);
    void setCustomerScore(int score);
    int getCustomerScore();
    void setDue(int due);
    int getDue();
    void setFine(int fine);
    int getFine();
    void rent_request();
    void return_request();
    int currentFines();
    void clearDues(int amount);
    void clearFine(int amount);
    void viewRecords(int n);
};

class customerDatabase : public customer{
    vector<customer> allCustomers;
    
    public:
    
    customerDatabase(string name="unknown", int id=-1, string password="password", int score=3, int due=0 , int fine=0);
    void addCustomer();
    void deleteCustomer();
    void updateCustomer();
    void searchCustomer();

};

class employee: public user{
    vector<car> rented_cars;
    int employee_score;
    int due;
    int fine;
    public:
    employee(string name="unknown", int id=-1, string password="password", int score=3, int due=0 , int fine=0);
    vector<car> getRentedCars();
    void setRentedCars(vector<car>& list);
    void setEmployeeScore(int score);
    int getEmployeeScore();
    void setDue(int due);
    int getDue();
    void setFine(int fine);
    int getFine();
    void rent_request();
    void return_request();
    int currentFines();
    void clearDues(int amount);
    void clearFine(int amount);
    void viewRecords(int n);
};

class employeeDatabase : public employee
{
    vector<employee> allEmployees;

    public:
    employeeDatabase(string name="unknown", int id=-1, string password="password", int score=3, int due=0 , int fine=0);
    void addEmployee();
    void deleteEmployee();
    void updateEmployee();
    void searchEmployee();
};

class record{
    int car_id;
    string car_model;
    int user_id;
    string user_name;
    int return_status;
    chrono::system_clock::time_point issue_date;
    chrono::system_clock::time_point due_date;
    chrono::system_clock::time_point return_date;
    public:
    record(int car_id=-1, string car_model="unknown", int user_id=-1, string user_name="unknown", int return_status=0, chrono::system_clock::time_point issue_date=chrono::system_clock::now(), chrono::system_clock::time_point due_date =chrono::system_clock::now(), chrono::system_clock::time_point return_date=chrono::system_clock::now());
    void setCarId(int id);
    void setUserId(int id);
    void setCarModel(string model);
    void setUserName(string name);
    void setReturnStatus(int status);
    void setDueDate(chrono::system_clock::time_point dueDate);
    void setReturnDate(chrono::system_clock::time_point returnDate);
    void setIssueDate(chrono::system_clock::time_point issue_date);
    int getCarId();
    int getUserId();
    string getCarModel();
    string getUserName();
    int getReturnStatus();
    chrono::system_clock::time_point getDueDate();
    chrono::system_clock::time_point getReturnDate();
    chrono::system_clock::time_point getIssueDate();

};


customer get_customer_by_id(int id, string location);

employee get_employee_by_id(int id, string location);

void customer_operation(customer &User);

void customer_process(customer& User);

void employee_operation(employee &User);

void employee_process(employee& User);

void manager_operation(manager& Manager);

void manager_process(manager& Manager);

vector<car> get_all_cars();

void write_into_cars(vector<car>& allCars);

vector<customer> get_all_customers();

void write_into_customers(vector<customer>& allCustomers);

void write_into_employees(vector<employee>& allEmployees);

vector<employee> get_all_employees();

employee get_employee_by_id(int id, string location);

void write_into_customer_records(vector<record>& allRecords);

vector<record> get_all_customer_records();

void write_into_employee_records(vector<record>& allRecords);

vector<record> get_all_employee_records();

chrono::system_clock::time_point stringToDate(const string& dateString);

string dateToString(const chrono::system_clock::time_point& date);

int daysBetween(chrono::system_clock::time_point dueDate, chrono::system_clock::time_point returnDate);

manager createManager();

int get_new_id(int i);

int get_record_by_id(vector<record>& allRecords, int car_id, int customer_id);

#endif
