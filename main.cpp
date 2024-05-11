#include "header.hpp"

/*-----------------------User functions starts -------------------------*/
user::user(string name, int id , string password) : name(name), id(id), password(password) {
}

void user::setName(string name)
{
    this->name=name;
}
void user::setPassword(string password)
{
    this->password=password;
}
void user::setId(int id)
{
    this->id=id;
}
string user::getName()
{
    return this->name;
}
string user::getPassword()
{
    return this->password;
}
int user::getId()
{
    return this->id;
}

void user::get_available_cars()
{
    vector<car> list=get_all_cars();
    if(list.size()==0)
    {
        cout<<"No cars available"<<endl;
        return;
    }
    for(auto&a : list)
    {
        if(a.getAvailable())
        {
            cout<<"Id of car : "<<a.getId()<<endl;
            cout<<"Model of car : "<<a.getModel()<<endl;
            cout<<"Condition of car : "<<a.getCondition()<<endl;
        }
        cout<<endl;
    }
}

/*-----------------------User functions ends -------------------------*/

customer get_customer_by_id(int id, string location)
{
    vector<customer> allCustomers=get_all_customers();
    for(auto&a : allCustomers)
    {
        if(a.getId()==id)
        {
            return a;
        }
    }
    customer notfound;
    return notfound;
}

vector<customer> get_all_customers()
{
    ifstream file("./databases/customer.txt");
    string currentLine;
    int lineNumber=1;
    customer currentUser;
    vector<car> rentedCars;
    car currentCar;
    vector<customer> customers;
    while(getline(file, currentLine))
    {
        if(currentLine.empty())
        {
            currentUser.setRentedCars(rentedCars);
            if(currentUser.getId()>0)
            {
                customers.push_back(currentUser);
            }
            currentUser=customer();
            rentedCars.clear();
            lineNumber=1;   
        }
        else
        {
            if(lineNumber==1)
            {
                currentUser.setId(stoi(currentLine));
            }
            else if(lineNumber==2)
            {
                currentUser.setName(currentLine);
            }
            else if(lineNumber==3)
            {
                currentUser.setPassword(currentLine);
            }
            else if(lineNumber==4)
            {
                currentUser.setCustomerScore(stoi(currentLine));
            }
            else if(lineNumber==5)
            {
                currentUser.setDue(stoi(currentLine));
            }
            else if(lineNumber==6)
            {
                currentUser.setFine(stoi(currentLine));
            }
            else if(lineNumber>7)
            {
                if(lineNumber%3==2)
                {
                    currentCar.setId(stoi(currentLine));
                }
                else if(lineNumber%3==0)
                {
                    currentCar.setModel(currentLine);
                }
                else
                {
                    currentCar.setDue_date(stringToDate(currentLine));
                    currentCar.setAvailable(0);
                    rentedCars.push_back(currentCar);
                    currentCar=car();
                }
            }
            lineNumber++;
        }
    }
    return customers;
}

void write_into_customers(vector<customer>& allCustomers)
{
    ofstream file("./databases/customer.txt");
    if(!file)
    {
        cerr<<"Cannot write into customer.txt"<<endl;
    }
    else
    {
        for(auto&a : allCustomers)
        {
            file<<a.getId()<<'\n';
            file<<a.getName()<<'\n';
            file<<a.getPassword()<<'\n';
            file<<a.getCustomerScore()<<'\n';
            file<<to_string(a.getDue())<<'\n';
            file<<to_string(a.getFine())<<'\n';
            file<<to_string((a.getRentedCars()).size())<<'\n';
            for(auto&c : a.getRentedCars())
            {
                file<<c.getId()<<'\n';
                file<<c.getModel()<<'\n';
                file<<dateToString(c.getDue_date())<<'\n';
            }
            file<<'\n';
        }
    }
    file.close();
}

employee get_employee_by_id(int id, string location)
{
    vector<employee> allEmployees=get_all_employees();
    for(auto&a : allEmployees)
    {
        if(a.getId()==id)
        {
            return a;
        }
    }
    employee notfound;
    return notfound;
}

vector<employee> get_all_employees()
{
    ifstream file("./databases/employee.txt");
    string currentLine;
    int lineNumber=1;
    employee currentUser;
    vector<car> rentedCars;
    car currentCar;
    vector<employee> employees;
    while(getline(file, currentLine))
    {
        if(currentLine.empty())
        {
            currentUser.setRentedCars(rentedCars);
            if(currentUser.getId()>0)
            {
                employees.push_back(currentUser);
            }
            currentUser=employee();
            rentedCars.clear();
            lineNumber=1;   
        }
        else
        {
            if(lineNumber==1)
            {
                currentUser.setId(stoi(currentLine));
            }
            else if(lineNumber==2)
            {
                currentUser.setName(currentLine);
            }
            else if(lineNumber==3)
            {
                currentUser.setPassword(currentLine);
            }
            else if(lineNumber==4)
            {
                currentUser.setEmployeeScore(stoi(currentLine));
            }
            else if(lineNumber==5)
            {
                currentUser.setDue(stoi(currentLine));
            }
            else if(lineNumber==6)
            {
                currentUser.setFine(stoi(currentLine));
            }
            else if(lineNumber>7)
            {
                if(lineNumber%3==2)
                {
                    currentCar.setId(stoi(currentLine));
                }
                else if(lineNumber%3==0)
                {
                    currentCar.setModel(currentLine);
                }
                else
                {
                    currentCar.setDue_date(stringToDate(currentLine));
                    currentCar.setAvailable(0);
                    rentedCars.push_back(currentCar);
                    currentCar=car();
                }
            }
            lineNumber++;
        }
    }
    return employees;
}

void write_into_employees(vector<employee>& allEmployees)
{
    ofstream file("./databases/employee.txt");
    if(!file)
    {
        cerr<<"Cannot write into employee.txt"<<endl;
    }
    else
    {
        for(auto&a : allEmployees)
        {
            file<<a.getId()<<'\n';
            file<<a.getName()<<'\n';
            file<<a.getPassword()<<'\n';
            file<<a.getEmployeeScore()<<'\n';
            file<<to_string(a.getDue())<<'\n';
            file<<to_string(a.getFine())<<'\n';
            file<<to_string((a.getRentedCars()).size())<<'\n';
            for(auto&c : a.getRentedCars())
            {
                file<<c.getId()<<'\n';
                file<<c.getModel()<<'\n';
                file<<dateToString(c.getDue_date())<<'\n';
            }
            file<<'\n';
        }
    }
    file.close();
}

chrono::system_clock::time_point stringToDate(const string& dateString) {
    tm tm = {};
    istringstream ss(dateString);
    ss >> get_time(&tm, "%Y-%m-%d");

    time_t t = mktime(&tm);

    return chrono::system_clock::from_time_t(t);
}

string dateToString(const chrono::system_clock::time_point& date) {
    time_t t = chrono::system_clock::to_time_t(date);

    tm tm = *localtime(&t);
    
    stringstream ss;
    ss << put_time(&tm, "%Y-%m-%d");
    return ss.str();
}

int daysBetween(chrono::system_clock::time_point dueDate, chrono::system_clock::time_point returnDate) {
    if (dueDate >= returnDate) {
        return 0;
    }
    std::string s1 = dateToString(dueDate);
    std::string s2 = dateToString(returnDate);
    int year1 = std::stoi(s1.substr(0, 4));
    int month1 = std::stoi(s1.substr(5, 2));
    int day1 = std::stoi(s1.substr(8, 2));
    int year2 = std::stoi(s2.substr(0, 4));
    int month2 = std::stoi(s2.substr(5, 2));
    int day2 = std::stoi(s2.substr(8, 2));
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto isLeapYear = [](int year) {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    };
    int days1 = day1;
    for (int i = 1; i < month1; ++i) {
        days1 += daysInMonth[i];
        if (i == 2 && isLeapYear(year1))
            ++days1;
    }
    days1 += year1 * 365 + (year1 - 1) / 4 - (year1 - 1) / 100 + (year1 - 1) / 400;

    int days2 = day2;
    for (int i = 1; i < month2; ++i) {
        days2 += daysInMonth[i];
        if (i == 2 && isLeapYear(year2))
            ++days2;
    }
    days2 += year2 * 365 + (year2 - 1) / 4 - (year2 - 1) / 100 + (year2 - 1) / 400;
    return (days2 - days1);
}

vector<car> get_all_cars()
{
    ifstream cars_file("./databases/cars.txt");
    string current_line;
    int line_number=1;
    car current;
    vector<car> allCars;
    while(getline(cars_file,current_line))
    {
        if(current_line.empty())
        {
            allCars.push_back(current);
            line_number=1;
            current=car();
        }
        else
        {
            if(line_number==1)
            {
                current.setId(stoi(current_line));
            }
            else if(line_number==2)
            {
                current.setModel(current_line);
            }
            else if(line_number==3)
            {
                current.setAvailable(stoi(current_line));
            }
            else if(line_number==4)
            {
                current.setPrice(stoi(current_line));
            }
            else if(line_number==5)
            {
                current.setCondition(stoi(current_line));
            }
            line_number++;
        }
    }
    return allCars;
}

void write_into_cars(vector<car>& allCars)
{
    ofstream file("./databases/cars.txt");
    if(!file)
    {
        cerr<<"customer.txt cannot be opened"<<endl;
    }
    else
    {
        for(auto& a : allCars)
        {
            file<<a.getId()<<'\n';
            file<<a.getModel()<<'\n';
            file<<a.getAvailable()<<'\n';
            file<<a.getPrice()<<'\n';
            file<<a.getCondition()<<'\n';
            file<<'\n';
        }
    }
    file.close();
}

vector<record> get_all_customer_records()
{
    ifstream file("./databases/customer_records.txt");
    string current_line;
    int line_number=1;
    record current;
    vector<record> allRecords;
    while(getline(file, current_line))
    {
        if(current_line.empty())
        {
            if(current.getCarId()>0)
            {
                allRecords.push_back(current);
            }
            current=record();
            line_number=1;
        }
        else
        {
            switch (line_number)
            {
                case 1:
                {
                    current.setCarId(stoi(current_line));
                    break;
                }
                case 2:
                {
                    current.setCarModel(current_line);
                    break;
                }
                case 3:
                {
                    current.setUserId(stoi(current_line));
                    break;
                }
                case 4:
                {
                    current.setUserName(current_line);
                    break;
                }
                case 5:
                {
                    current.setReturnStatus(stoi(current_line));
                }
                case 6:
                {
                    current.setIssueDate(stringToDate(current_line));
                    break;
                }
                case 7:
                {
                    current.setDueDate(stringToDate(current_line));
                    break;
                }
                case 8:
                {
                    current.setReturnDate(stringToDate(current_line));
                    break;
                }
                default:
                    break;
            }
            line_number++;
        }
    }
    file.close();
    return allRecords;
}

void write_into_customer_records(vector<record>& allRecords)
{
    ofstream file("./databases/customer_records.txt");
    if(!file)
    {
        cerr<<"customer_records.txt cannot be opened.."<<endl;
    }
    else
    {
        for(auto&a : allRecords)
        {
            file<<a.getCarId()<<'\n';
            file<<a.getCarModel()<<'\n';
            file<<a.getUserId()<<'\n';
            file<<a.getUserName()<<'\n';
            file<<a.getReturnStatus()<<'\n';
            file<<dateToString(a.getIssueDate())<<'\n';
            file<<dateToString(a.getDueDate())<<'\n';
            file<<dateToString(a.getReturnDate())<<'\n';
            file<<'\n';
        }
        file.close();
    }
}

vector<record> get_all_employee_records()
{
    ifstream file("./databases/employee_records.txt");
    string current_line;
    int line_number=1;
    record current;
    vector<record> allRecords;
    while(getline(file, current_line))
    {
        if(current_line.empty())
        {
            allRecords.push_back(current);
            current=record();
            line_number=1;
        }
        else
        {
            switch (line_number)
            {
                case 1:
                {
                    current.setCarId(stoi(current_line));
                    break;
                }
                case 2:
                {
                    current.setCarModel(current_line);
                    break;
                }
                case 3:
                {
                    current.setUserId(stoi(current_line));
                    break;
                }
                case 4:
                {
                    current.setUserName(current_line);
                    break;
                }
                case 5:
                {
                    current.setReturnStatus(stoi(current_line));
                }
                case 6:
                {
                    current.setIssueDate(stringToDate(current_line));
                    break;
                }
                case 7:
                {
                    current.setDueDate(stringToDate(current_line));
                    break;
                }
                case 8:
                {
                    current.setReturnDate(stringToDate(current_line));
                    break;
                }
                default:
                    break;
            }
            line_number++;
        }
    }
    file.close();
    return allRecords;
}

void write_into_employee_records(vector<record>& allRecords)
{
    ofstream file("./databases/employee_records.txt");
    if(!file)
    {
        cerr<<"employee_records.txt cannot be opened.."<<endl;
    }
    else
    {
        for(auto&a : allRecords)
        {
            file<<a.getCarId()<<'\n';
            file<<a.getCarModel()<<'\n';
            file<<a.getUserId()<<'\n';
            file<<a.getUserName()<<'\n';
            file<<a.getReturnStatus()<<'\n';
            file<<dateToString(a.getIssueDate())<<'\n';
            file<<dateToString(a.getDueDate())<<'\n';
            file<<dateToString(a.getReturnDate())<<'\n';
            file<<'\n';
        }
        file.close();
    }
}

int get_new_id(int i)
{
    ifstream file("./databases/nextId.txt");
    if(!file)
    {
        cout<<"File nextId.txt can't be opened"<<endl;
        return -1;
    }
    string currentLine;
    int customer_id;
    int employee_id;
    int car_id;
    int lineNumber=1;
    while(getline(file, currentLine))
    {
        if(lineNumber==1)
        {
            customer_id = stoi(currentLine);
        }
        else if(lineNumber==2)
        {
            employee_id=stoi(currentLine);
        }
        else if(lineNumber==3)
        {
            car_id=stoi(currentLine);
            break;
        }
        lineNumber++;
    }
    file.close();
    ofstream outfile("./databases/nextId.txt");
    int res=-1;
    if(i==1)
    {
        res=customer_id;
        customer_id++;
    }
    else if(i==2)
    {
        res=employee_id;
        employee_id++;
    }
    else if(i==3)
    {
        res=car_id;
        car_id++;
    }
    outfile<<(customer_id)<<'\n';
    outfile<<(employee_id)<<'\n';
    outfile<<(car_id)<<'\n';
    outfile<<'\n';
    outfile.close();
    return res;
}

int get_record_by_id(vector<record>& allRecords, int car_id, int user_id)
{
    for(int i=0 ; i<allRecords.size() ; i++)
    {
        if(allRecords[i].getCarId()==car_id && allRecords[i].getUserId()==user_id)
        {
            return i;
        }
    }
    return -1;
}

void startSystem()
{
    cout<<"Roles : "<<endl;
    cout<<"[1]: Manager"<<endl;
    cout<<"[2]: Employee"<<endl;
    cout<<"[3]: Customer"<<endl;
    cout<<"Please enter your role: ";
    int role;
    cin>>role;
    cout<<endl;
    int id;
    cout<<"Please enter your id : ";
    if(!(cin>>id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cout << "Invalid input. Please enter a valid option." << endl;
        return;
    }
    string password;
    cout<<"Please enter your password : ";
    if(!(cin>>password))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cout << "Invalid input. Please enter a valid option." << endl;
        return;
    }
    cout<<endl;
    if(role==1)
    {
        manager Manager=createManager();
        if(Manager.getPassword()==password)
        {
            cout<<"Welcome manager : "<<endl;
            cout<<endl;
            manager_operation(Manager);
        }
        else
        {
            cout<<"Invalid Password"<<endl;
            cout<<endl;
        }
    }
    else if(role==2)
    {
        employee User=get_employee_by_id(id,"./databases/employee.txt");
        if(User.getPassword()!=password)
        {
            cout<<"Invalid Password"<<endl;
            cout<<endl;
            return;
        }
        cout<<"Welcome "<<User.getName()<<endl;
        cout<<endl;
        employee_operation(User);
    }
    else if(role==3)
    {
        customer User=get_customer_by_id(id,"./databases/customer.txt");
        if(User.getPassword()!=password)
        {
            cout<<"Invalid Password"<<endl;
            return;
        }
        cout<<"Welcome "<<User.getName()<<endl;
        cout<<endl;
        customer_operation(User);
    }
    else
    {
        cout<<"Please enter a valid role"<<endl;
        cout<<endl;
    }
    
}

int main()
{
    cout<<"SYSTEM STARTED"<<endl;
    while (1)
    {
        cout<<endl;
        cout<<"[1]: Login"<<endl;
        cout<<"[2]: Terminate"<<endl;
        int process;
        cout<<"Please choose an option:";
        if(!(cin>>process))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }
        cout<<endl;
        if(process!=1 && process!=2)
        {
            cout<<endl;
            cout<<"Invalid process"<<endl;
            cout<<endl;
            continue;
        }
        if(process==1)
        {
            startSystem();
        }
        else
        {
            break;
        }
    }
    
}
