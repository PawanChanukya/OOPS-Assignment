#include "header.hpp"

manager createManager()
{
    manager Manager;
    ifstream file("./databases/manager.txt");
    string current_line;
    int lineNumber=1;
    while(getline(file, current_line))
    {
        if(current_line.empty())
        {
            break;
        }
        else
        {
            if(lineNumber==1)
            {
                Manager.setId(stoi(current_line));
            }
            else if(lineNumber==2)
            {
                Manager.setName(current_line);
            }
            else if(lineNumber==3)
            {
                Manager.setPassword(current_line);
            }
            lineNumber++;
        }
    }
    return Manager;
}

manager::manager(string name, int id, string password) : user(name, id, password) {
}

void manager::addCar(car& C)
{
    carDatabase db(C.getModel(),C.getId(),C.getAvailable(), C.getDue_date(), C.getPrice());
    db.addCar();
}

void manager::deleteCar(int car_id)
{
    car C;
    C.setId(car_id);
    carDatabase db(C.getModel(),C.getId(),C.getAvailable(), C.getDue_date(), C.getPrice());
    db.deleteCar();
}

void manager::updateCar(int car_id)
{
    car C;
    C.setId(car_id);
    carDatabase db(C.getModel(),C.getId(),C.getAvailable(), C.getDue_date(), C.getPrice(), C.getCondition());
    db.updateCar();
}

void manager::addCustomer()
{
    int new_id,new_score,new_dues,new_fine;
    string new_password,new_name;
    new_id=get_new_id(1);
    cout<<"Please enter customer name : ";
    cin>>new_name;
    cout<<"Please enter customer password : ";
    cin>>new_password;
    cout<<"Please enter customer score : ";
    cin>>new_score;
    cout<<"Please enter customer dues : ";
    cin>>new_dues;
    cout<<"Please enter customer fine : ";
    cin>>new_fine;
    customerDatabase db(new_name,new_id, new_password, new_score , new_dues , new_fine);
    db.addCustomer();

}

void manager::deleteCustomer(int customer_id)
{
    customer C;
    C.setId(customer_id);
    customerDatabase db(C.getName(),C.getId(), C.getPassword(), C.getCustomerScore() , C.getDue() , C.getFine());
    db.deleteCustomer();
}

void manager::updateCustomer(int customer_id)
{
    customer C;
    C.setId(customer_id);
    customerDatabase db(C.getName(),C.getId(), C.getPassword(), C.getCustomerScore() , C.getDue() , C.getFine());
    db.updateCustomer();
}

void manager::addEmployee()
{
    int new_id,new_score,new_dues,new_fine;
    string new_password,new_name;
    new_id=get_new_id(2);
    cout<<"Please enter employee name : ";
    cin>>new_name;
    cout<<"Please enter employee password : ";
    cin>>new_password;
    cout<<"Please enter employee score : ";
    cin>>new_score;
    cout<<"Please enter employee dues : ";
    cin>>new_dues;
    cout<<"Please enter employee fine : ";
    cin>>new_fine;
    employeeDatabase db(new_name,new_id, new_password, new_score , new_dues , new_fine);
    db.addEmployee();

}

void manager::deleteEmployee(int employee_id)
{
    employee C;
    C.setId(employee_id);
    employeeDatabase db(C.getName(),C.getId(), C.getPassword(), C.getEmployeeScore() , C.getDue() , C.getFine());
    db.deleteEmployee();
}

void manager::updateEmployee(int employee_id)
{
    employee C;
    C.setId(employee_id);
    employeeDatabase db(C.getName(),C.getId(), C.getPassword(), C.getEmployeeScore() , C.getDue() , C.getFine());
    db.updateEmployee();
}

void manager::getAllRecords()
{
    cout<<"[1] : Customer Records"<<endl;
    cout<<"[2] : Employee Records"<<endl;
    cout<<"Please choose an option : ";
    int role;
    cin>>role;
    if(role==1)
    {
        vector<record> customerRecords=get_all_customer_records();
        if(customerRecords.size()==0)
        {
            cout<<"No records found"<<endl;
            return;
        }
        for(auto&a : customerRecords)
        {
            cout<<"Car Id : "<<a.getCarId()<<endl;
            cout<<"car model : "<<a.getCarModel()<<endl;
            cout<<"Customer Id : "<<a.getUserId()<<endl;
            cout<<"Customer name : "<<a.getUserName()<<endl;
            if(a.getReturnStatus())
            {
                cout<<"Car status : Returned"<<endl;
            }
            else
            {
                cout<<"Car status : Not returned"<<endl;
            }
            cout<<"Issue date : "<<dateToString(a.getIssueDate())<<endl;
            cout<<"Due date : "<<dateToString(a.getDueDate())<<endl;
            if(a.getReturnStatus())
            {
                cout<<"Return date : "<<dateToString(a.getReturnDate())<<endl;
            }
            cout<<endl;
        }
    }
    else if(role==2)
    {
        vector<record> employeeRecords=get_all_employee_records();
        if(employeeRecords.size()==0)
        {
            cout<<"No records found"<<endl;
            return;
        }
        for(auto&a : employeeRecords)
        {
            cout<<"Car Id : "<<a.getCarId()<<endl;
            cout<<"car model : "<<a.getCarModel()<<endl;
            cout<<"Employee Id : "<<a.getUserId()<<endl;
            cout<<"Employee name : "<<a.getUserName()<<endl;
            if(a.getReturnStatus())
            {
                cout<<"Car status : Returned"<<endl;
            }
            else
            {
                cout<<"Car status : Not returned"<<endl;
            }
            cout<<"Issue date : "<<dateToString(a.getIssueDate())<<endl;
            cout<<"Due date : "<<dateToString(a.getDueDate())<<endl;
            if(a.getReturnStatus())
            {
                cout<<"Return date : "<<dateToString(a.getReturnDate())<<endl;
            }
        }
        cout<<endl;
    }
    else{
        cout<<"invalid role"<<endl;
    }
}

void manager::modifyRecords()
{
    int role,userId,carId;
    cout<<"[1] : Customer"<<endl;
    cout<<"[2] : Employee"<<endl;
    cout<<"Please enter the role of the user that you want the record of : ";
    cin>>role;
    cout<<"Please enter the Id of the car that you want the record of : ";
    cin>>carId;
    cout<<"Please enter the Id of the user that you want the record of : ";
    cin>>userId;
    if(role==1)
    {
        vector<record> customerRecords=get_all_customer_records();
        int index=get_record_by_id(customerRecords, carId, userId);
        if(index==-1)
        {
            cout<<"Record not found"<<endl;
        }
        else
        {
            while(1)
            {
                cout<<"[1] : Modify the record";
                cout<<"[2] : Terminate";
                int op;
                cin>>op;
                if(op==2)
                {
                    break;
                }
                else if(op>2 || op<1)
                {
                    cout<<"Invalid operation"<<endl;
                    continue;
                }
                cout<<"Please choose an operation : ";
                cout<<"[1] : Return Status"<<endl;
                cout<<"[2] : Due date"<<endl;
                cout<<"[3] : Issue date"<<endl;
                cout<<"[4] : Return Date"<<endl;
                cout<<"Please choose a field : ";
                int field;
                cin>>field;
                switch (field)
                {
                case 1:
                {
                    int status;
                    cout<<"New return status : ";
                    cin>>status;
                    customerRecords[index].setReturnStatus(status);
                    break;
                }
                case 2:
                {
                    string date;
                    cout<<"New due date(YYYY-MM-DD) : ";
                    cin>>date;
                    customerRecords[index].setDueDate(stringToDate(date));
                    break;
                }
                case 3:
                {
                    string date;
                    cout<<"New Issue date(YYYY-MM-DD) : ";
                    cin>>date;
                    customerRecords[index].setIssueDate(stringToDate(date));
                    break;
                }
                case 4:
                {
                    string date;
                    cout<<"New return date(YYYY-MM-DD) : ";
                    cin>>date;
                    customerRecords[index].setReturnDate(stringToDate(date));
                    break;
                }
                default:
                {
                    cout<<"Invalid field"<<endl;
                    break;
                }
                }
            }

        }

    }
    else if(role==2)
    {
        vector<record> employeeRecords=get_all_employee_records();
        int index=get_record_by_id(employeeRecords, carId, userId);
        if(index==-1)
        {
            cout<<"Record not found"<<endl;
        }
        else
        {
            while(1)
            {
                cout<<"[1] : Modify the record";
                cout<<"[2] : Terminate";
                int op;
                cin>>op;
                if(op==2)
                {
                    break;
                }
                else if(op>2 || op<1)
                {
                    cout<<"Invalid operation"<<endl;
                    continue;
                }
                cout<<"Please choose an operation : ";
                cout<<"[1] : Return Status"<<endl;
                cout<<"[2] : Due date"<<endl;
                cout<<"[3] : Issue date"<<endl;
                cout<<"[4] : Return Date"<<endl;
                cout<<"Please choose a field : ";
                int field;
                cin>>field;
                switch (field)
                {
                case 1:
                {
                    int status;
                    cout<<"New return status : ";
                    cin>>status;
                    employeeRecords[index].setReturnStatus(status);
                    break;
                }
                case 2:
                {
                    string date;
                    cout<<"New due date(YYYY-MM-DD) : ";
                    cin>>date;
                    employeeRecords[index].setDueDate(stringToDate(date));
                    break;
                }
                case 3:
                {
                    string date;
                    cout<<"New Issue date(YYYY-MM-DD) : ";
                    cin>>date;
                    employeeRecords[index].setIssueDate(stringToDate(date));
                    break;
                }
                case 4:
                {
                    string date;
                    cout<<"New return date(YYYY-MM-DD) : ";
                    cin>>date;
                    employeeRecords[index].setReturnDate(stringToDate(date));
                    break;
                }
                default:
                {
                    cout<<"Invalid field"<<endl;
                    break;
                }
                }
            }

        }
    }
    else
    {
        cout<<"Invalid role"<<endl;
    }
}


void manager_process(manager& Manager)
{
    cout<<endl;
    cout<<"Operations : "<<endl;
    cout<<"[1] : Add car"<<endl;
    cout<<"[2] : Delete car"<<endl;
    cout<<"[3] : Update car"<<endl;
    cout<<"[4] : Add customer"<<endl;
    cout<<"[5] : Delete customer"<<endl;
    cout<<"[6] : Update customer"<<endl;
    cout<<"[7] : Add Employee"<<endl;
    cout<<"[8] : Delete Employee"<<endl;
    cout<<"[9] : Update Employee"<<endl;
    cout<<"[10] : View Records"<<endl;
    cout<<"[11] : Modify Records"<<endl;
    cout<<"[12] : View all customers"<<endl;
    cout<<"[13] : View all employees"<<endl;
    cout<<"[14] : View all cars"<<endl;
    cout<<"[15] : Search car details"<<endl;
    cout<<"[16] : Search customer details"<<endl;
    cout<<"[17] : Search employee details"<<endl;
    cout<<"[18] : Search record"<<endl;
    cout<<"Please select an operation : ";
    int op;
    if(!(cin>>op))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        cout << "Invalid input. Please enter a valid option." << endl;
        return;
    }
    switch (op)
    {
    case 1:
    {
        while (1)
        {
            cout<<"[1] : Add new car"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Please choose an option : ";
            int opn;
            if(!(cin>>opn))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            cin.ignore();
            if(opn==2)
            {
                break;
            }
            else if(opn>2 || opn<1)
            {
                cout<<"Invalid option"<<endl;
                cout<<endl;
                continue;
            }
            int new_id=get_new_id(3);
            string new_model;
            int price, condition;
            cout<<"Enter the model of car : ";
            getline(cin, new_model);
            cout<<"Enter the price of car : ";
            cin>>price;
            cout<<"Enter the condition of car : ";
            cin>>condition;
            cout<<endl;
            car Car(new_model, new_id, 1 , chrono::system_clock::now(), price, condition);
            Manager.addCar(Car);   
        }
        break;
    }
    case 2:
    {
        while(1)
        {
            cout<<"Options :"<<endl;
            cout<<"[1] : Delete a car"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Please choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                cout<<endl;
                continue;
            }
            cout<<"Enter the Id of car that you want to delete : ";
            int id;
            cin>>id;
            cout<<endl;
            Manager.deleteCar(id);
        }
        break;
    }
    case 3:
    {
        while(1)
        {
            cout<<"Options :"<<endl;
            cout<<"[1] : Update a car"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Please choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                cout<<endl;
                continue;
            }
            cout<<"Enter the Id of the car that you want to update : ";
            int id;
            cin>>id;
            cout<<endl;
            Manager.updateCar(id);
        }
        break;
    }
    case 4:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Add new customer"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<endl;
            Manager.addCustomer();
        }
        break;
    }
    case 5:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : delete customer"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Enter the id of the customer that you want to delete : ";
            int id;
            cin>>id;
            Manager.deleteCustomer(id);
            cout<<endl;
        }
        break;
    }
    case 6:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Update customer"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Enter the id of the customer that you want to update : ";
            int id;
            cin>>id;
            Manager.updateCustomer(id);
            cout<<endl;
        }
        break;
    }
    case 7:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Add new employee"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            Manager.addEmployee();
            cout<<endl;
        }
        break;
    }
    case 8:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Delete employee"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Enter the id of the employee that you want to delete : ";
            int id;
            cin>>id;
            Manager.deleteEmployee(id);
            cout<<endl;
        }
        break;
    }
    case 9:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Update employee"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Enter the id of the employee that you want to update : ";
            int id;
            cin>>id;
            Manager.updateEmployee(id);
            cout<<endl;
        }
        break;
    }
    case 10:
    {
        Manager.getAllRecords();
        break;
    }
    case 11:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Modify Record"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            Manager.modifyRecords();
            cout<<endl;
        }
        break;
    }
    case 12:
    {
        vector<customer> allCustomers=get_all_customers();
        cout<<endl;
        if(allCustomers.size()==0)
        {
            cout<<"No Customers to display"<<endl;
            cout<<endl;
        }
        for(auto&a : allCustomers)
        {
            cout<<"Id of customer : "<<a.getId()<<endl;
            cout<<"Name of customer : "<<a.getName()<<endl;
            cout<<"Score : "<<a.getCustomerScore()<<endl;
            cout<<"Dues : "<<a.getDue()<<endl;
            cout<<"Fine : "<<a.getFine()<<endl;
            cout<<"Number of cars currently renting : "<<a.getRentedCars().size()<<endl;
            cout<<endl;
        }
        break;
    }
    case 13:
    {
        vector<employee> allEmployees=get_all_employees();
        cout<<endl;
        if(allEmployees.size()==0)
        {
            cout<<"No Employees to display"<<endl;
            cout<<endl;
        }
        for(auto&a : allEmployees)
        {
            cout<<"Id of employee : "<<a.getId()<<endl;
            cout<<"Name of employee : "<<a.getName()<<endl;
            cout<<"Score : "<<a.getEmployeeScore()<<endl;
            cout<<"Dues : "<<a.getDue()<<endl;
            cout<<"Fine : "<<a.getFine()<<endl;
            cout<<"Number of cars currently renting : "<<a.getRentedCars().size()<<endl;
            cout<<endl;
        }
        break;
    }
    case 14:
    {
        vector<car> allCars=get_all_cars();
        cout<<endl;
        if(allCars.size()==0)
        {
            cout<<"No Cars to display"<<endl;
            cout<<endl;
        }
        for(auto& a : allCars)
        {
            cout<<"Id of car : "<<a.getId()<<endl;
            cout<<"Model of car : "<<a.getModel()<<endl;
            cout<<"Availability of car : "<<a.getAvailable()<<endl;
            cout<<"Condition of car : "<<a.getCondition()<<endl;
            cout<<"Price of car : "<<a.getPrice()<<endl;
            cout<<endl;
        }
        break;
    }
    case 15:
    {
        while(1)
        {
            cout<<endl;
            cout<<"Options"<<endl;
            cout<<"[1] : Search car"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<endl;
                cout<<"Invalid option"<<endl;
                cout<<endl;
                continue;
            }
            cout<<"Please enter the id of the car : ";
            int car_id;
            cin>>car_id;
            carDatabase db;
            db.setId(car_id);
            db.searchCar();
        }
        break;
    }
    case 16:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Search Customer"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Please enter the id of the customer : ";
            int customer_id;
            cin>>customer_id;
            customerDatabase db;
            db.setId(customer_id);
            db.searchCustomer();
        }
        break;
    }
    case 17:
    {
        while(1)
        {
            cout<<"Options"<<endl;
            cout<<"[1] : Search Employee"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            cout<<endl;
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                continue;
            }
            cout<<"Please enter the id of the employee : ";
            int employee_id;
            cin>>employee_id;
            employeeDatabase db;
            db.setId(employee_id);
            db.searchEmployee();
        }
        break;
    }
    case 18:
    {
        while(1)
        {
            cout<<endl;
            cout<<"Options"<<endl;
            cout<<"[1] : Search Record"<<endl;
            cout<<"[2] : Terminate"<<endl;
            cout<<"Choose an option : ";
            int op;
            if(!(cin>>op))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            if(op==2)
            {
                break;
            }
            else if(op>2 || op<1)
            {
                cout<<"Invalid option"<<endl;
                cout<<endl;
                continue;
            }
            cout<<endl;
            int car_id,user_id,role;
            cout<<"Please enter the id of car : ";
            cin>>car_id;
            cout<<"Please enter the id of user : ";
            cin>>user_id;
            cout<<"[1] : Customer"<<endl;
            cout<<"[2] : Employee"<<endl;
            cout<<"Please enter the role of user : ";
            if(!(cin>>role))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl;
                cout << "Invalid input. Please enter a valid option." << endl;
                continue;
            }
            if(role>2 || role<1)
            {
                cout<<endl;
                cout<<"Invalid role"<<endl;
                cout<<endl;
            }
            else if(role == 1)
            {
                vector<record> allRecords=get_all_customer_records();
                int index=get_record_by_id(allRecords , car_id, user_id);
                cout<<endl;
                if(index<0)
                {
                    cout<<"Record not found"<<endl;   
                }
                else
                {
                    cout<<"Car id : "<<allRecords[index].getCarId()<<endl;
                    cout<<"Car model : "<<allRecords[index].getCarModel()<<endl;
                    cout<<"Customer id : "<<allRecords[index].getUserId()<<endl;
                    cout<<"Customer Name : "<<allRecords[index].getUserName()<<endl;
                    if(allRecords[index].getReturnStatus())
                    {
                        cout<<"Return Status : Returned"<<endl;
                    }
                    else
                    {
                        cout<<"Return Status : Not returned"<<endl;
                    }
                    cout<<"Issue date : "<<dateToString(allRecords[index].getIssueDate())<<endl;
                    cout<<"Due date : "<<dateToString(allRecords[index].getDueDate())<<endl;
                    if(allRecords[index].getReturnStatus())
                    {
                        cout<<"Return date : "<<dateToString(allRecords[index].getReturnDate())<<endl;
                    }
                }
                cout<<endl;
            }
            else if(role == 2)
            {
                vector<record> allRecords=get_all_employee_records();
                int index=get_record_by_id(allRecords , car_id, user_id);
                cout<<endl;
                if(index<0)
                {
                    cout<<"Record not found"<<endl;
                }
                else
                {
                    cout<<"Car id : "<<allRecords[index].getCarId()<<endl;
                    cout<<"Car model : "<<allRecords[index].getCarModel()<<endl;
                    cout<<"Employee id : "<<allRecords[index].getUserId()<<endl;
                    cout<<"Employee Name : "<<allRecords[index].getUserName()<<endl;
                    if(allRecords[index].getReturnStatus())
                    {
                        cout<<"Return Status : Returned"<<endl;
                    }
                    else
                    {
                        cout<<"Return Status : Not returned"<<endl;
                    }
                    cout<<"Issue date : "<<dateToString(allRecords[index].getIssueDate())<<endl;
                    cout<<"Due date : "<<dateToString(allRecords[index].getDueDate())<<endl;
                    if(allRecords[index].getReturnStatus())
                    {
                        cout<<"Return date : "<<dateToString(allRecords[index].getReturnDate())<<endl;
                    }
                }
                cout<<endl;
            }
        }
        break;
    }
    default:
    {
        cout<<"Invalid operation"<<endl;
        break;
    }
    }

}

void manager_operation(manager& Manager)
{
    cout<<"Welcome to our Car Rental System"<<endl;
    cout<<endl;
    while (1)
    {
        cout<<"[1]: Proceed"<<endl;
        cout<<"[2]: Terminate"<<endl;
        cout<<"Please choose an option: ";
        int op;
        if(!(cin>>op))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Invalid input. Please enter a valid option." << endl;
            continue;
        }
        cout<<endl;
        if(op==1)
        {
            manager_process(Manager);
        }
        else if(op==2)
        {
            break;
        }
        else
        {
            cout<<endl;
            cout<<"Invalid Operation"<<endl;
            cout<<endl;
            continue;
        }
    }
}