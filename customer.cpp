#include "header.hpp"

customer::customer(string name, int id, string password, int score, int due, int fine): user(name, id, password) , customer_score(score), due(due), fine(fine){ 
} 

vector<car> customer::getRentedCars()
{
    return this->rented_cars;
}

void customer::setRentedCars(vector<car>& list)
{
    this->rented_cars=list;
}
void customer::setCustomerScore(int score)
{
    this->customer_score=score;
}

int customer::getCustomerScore()
{
    return this->customer_score;
}

void customer::setDue(int due)
{
    this->due=due;
}

int customer::getDue()
{
    return this->due;
}

int customer::getFine()
{
    return this->fine;
}

void customer::setFine(int fine)
{
    this->fine=fine;
}

int customer::currentFines()
{
    chrono::system_clock::time_point pres=chrono::system_clock::now();
    vector<car> rented_cars=getRentedCars();
    int fine=0;
    for(auto&a : rented_cars)
    {
        if(a.getDue_date()<pres)
        {
            fine+=(daysBetween(a.getDue_date(),pres)*a.getPrice());
        }
    }
    return fine;
}

struct compareRecords{
    bool operator()(record a, record b)
    {
        return a.getIssueDate()>b.getIssueDate();
    }
};

void customer::viewRecords(int n)
{
    vector<record> allRecords=get_all_customer_records();
    vector<record> userRecords;
    for(auto&a : allRecords)
    {
        if(a.getUserId()==getId())
        {
            userRecords.push_back(a);
        }
    }
    if(n>userRecords.size())
    {
        n=userRecords.size();
    }
    if(n==0)
    {
        cout<<"No records to display"<<endl;
        return;
    }
    sort(userRecords.begin(), userRecords.end(), compareRecords());
    for(int i=0 ; i<n ; i++)
    {
        cout<<"ID of car rented : "<<userRecords[i].getCarId()<<endl;
        cout<<"Model of car rented : "<<userRecords[i].getCarModel()<<endl;
        cout<<"Issue date : "<<dateToString(userRecords[i].getIssueDate())<<endl;
        cout<<"Due date : "<<dateToString(userRecords[i].getDueDate())<<endl;
        if(userRecords[i].getReturnStatus())
        {
            cout<<"Return date : "<<dateToString(userRecords[i].getReturnDate())<<endl;
            cout<<"Car Status : Returned"<<endl;
        }
        else
        {
            cout<<"Car status : Rented"<<endl;
        }
        cout<<endl;
    }

}

void customer::clearDues(int amount)
{
    vector<customer> allCustomers=get_all_customers();
    for(auto&a : allCustomers)
    {
        if(a.getId()==getId())
        {
            a.setDue(a.getDue()-amount);
            setDue(getDue()-amount);
            break;
        }
    }
    write_into_customers(allCustomers);
}

void customer::clearFine(int amount)
{
    vector<customer> allCustomers=get_all_customers();
    for(auto&a : allCustomers)
    {
        if(a.getId()==getId())
        {
            a.setFine(a.getFine()-amount);
            setFine(getFine()-amount);
            break;
        }
    }
    write_into_customers(allCustomers);
}

void customer::rent_request()
{
    cout<<"Confirm Rent Request(y/n) : ";
    char a;
    cin>>a;
    if(this->getDue()>10000)
    {
        cout<<endl;
        cout<<"Please clear the existing dues to rent another car"<<endl;
        cout<<endl;
        return ;
    }
    if(a=='y')
    {
        cout<<"Rent Request Initiated"<<endl;
        cout<<"Number of cars you are currently renting : "<<(getRentedCars()).size()<<endl;
        cout<<"Customer Score : "<<getCustomerScore()<<endl;
        if((getRentedCars()).size()<getCustomerScore())
        {
            cout<<"Enter the car ID : ";
            int car_id;
            cin>>car_id;
            cout<<"Validating request..."<<endl;
            vector<car> cars=get_all_cars();
            bool success=false;
            car requested_car;
            for(int i=0 ; i<cars.size() ; i++)
            {
                if(cars[i].getId()==car_id && cars[i].getAvailable())
                {
                    success=true;
                    cars[i].setAvailable(0);
                    requested_car=cars[i];
                }
            }
            if(success)
            {
                cout<<"Number of days you want to rent the car : ";
                int days;
                cin>>days;
                requested_car.setDue_date(chrono::system_clock::now()+chrono::hours(24*days));
                write_into_cars(cars);
                vector<customer> customers=get_all_customers();
                for(int i=0 ; i< customers.size() ; i++)
                {
                    if(customers[i].getId()==getId())
                    {
                        vector<car> userCars=getRentedCars();
                        userCars.push_back(requested_car);
                        customers[i].setRentedCars(userCars);
                        setRentedCars(userCars);
                        cout<<"Number of rented cars by the user : "<<(getRentedCars()).size()<<endl;
                        customers[i].setDue(customers[i].getDue()+(requested_car.getPrice()*days));
                        setDue(getDue()+(requested_car.getPrice()*days));
                        break;
                    }
                }
                vector<record> allRecords=get_all_customer_records();
                record new_record;
                new_record.setCarId(requested_car.getId());
                new_record.setCarModel(requested_car.getModel());
                new_record.setUserId(this->getId());
                new_record.setUserName(this->getName());
                new_record.setReturnStatus(0);
                new_record.setIssueDate(chrono::system_clock::now());
                new_record.setDueDate(chrono::system_clock::now()+chrono::hours(24*days));
                new_record.setReturnDate(new_record.getDueDate());
                allRecords.push_back(new_record);
                write_into_customer_records(allRecords);
                write_into_customers(customers);
            }
            else
            {
                cout<<"Car requested is currently not available.. Please try again.."<<endl;
            }
        }
        else
        {
            cout<<"Rent capacity reached.. Please return the cars to rent more"<<endl;
        }
    }
}

void customer::return_request()
{
    cout<<"Confirm return request(y/n) : ";
    char y;
    cin>>y;
    if(y=='y')
    {
        cout<<"Enter the id of the car you want to return : ";
        int car_id;
        cin>>car_id;
        vector<car> allCars=get_all_cars();
        bool foundCar=false;
        int price=0;
        for(auto&a : allCars)
        {
            if(a.getId()==car_id)
            {
                a.setAvailable(1);
                foundCar=true;
                price=a.getPrice();
                break;
            }
        }
        if(!foundCar)
        {
            cout<<"Car not found.. please check the ID of the car.."<<endl;
            return;
        }
        write_into_cars(allCars);
        vector<customer> allCustomers=get_all_customers();
        bool foundCarInUser=false;
        for(auto&a : allCustomers)
        {
            if(a.getId()==getId())
            {
                vector<car> rented_cars=getRentedCars();
                for(int i=0 ; i<rented_cars.size() ; i++)
                {
                    if(rented_cars[i].getId()==car_id)
                    {
                        foundCarInUser=true;
                        auto return_date=chrono::system_clock::now();
                        auto due_date=rented_cars[i].getDue_date();
                        cout<<endl;
                        cout<<"[1] : Bad"<<endl;
                        cout<<"[2] : Average"<<endl;
                        cout<<"[3] : Good"<<endl;
                        cout<<"Please enter the condition in which the car is returned : ";
                        int return_condition;
                        cin>>return_condition;
                        if(return_condition==3)
                        {
                            setCustomerScore(getCustomerScore()+1);
                            a.setCustomerScore(a.getCustomerScore()+1);
                        }
                        //a fine of 20% the price of car imposed per day after the duedate
                        
                        int fine=((daysBetween(due_date,return_date)*price)/5);
                        setFine(getFine()+fine);
                        a.setFine(getFine()+fine);
                        int new_score;
                        if(fine>0)
                        {
                            new_score=(a.getCustomerScore()-1>1)?a.getCustomerScore()-1:1;
                            a.setCustomerScore(new_score);
                            setCustomerScore(new_score);
                        }
                        rented_cars.erase(rented_cars.begin()+i);
                        vector<record> allRecords=get_all_customer_records();
                        for(auto&r : allRecords)
                        {
                            if(r.getCarId()==car_id && r.getUserId()==a.getId() && !r.getReturnStatus())
                            {
                                r.setReturnDate(return_date);
                                r.setReturnStatus(1);
                                break;
                            }
                        }
                        write_into_customer_records(allRecords);
                        break;
                    }
                }
                setRentedCars(rented_cars);
                a.setRentedCars(rented_cars);
                break;
            }

        }
        if(!foundCarInUser)
        {
            cout<<"Requested car is not currently in your rented cars.. Please check the car ID again.."<<endl;
            return;
        }
        write_into_customers(allCustomers);
    }
}

void customer_process(customer& User)
{
    cout<<"[1]: View available cars"<<endl;
    cout<<"[2]: View rented cars"<<endl;
    cout<<"[3]: Rent Request"<<endl;
    cout<<"[4]: Return Request"<<endl;
    cout<<"[5]: Check Dues and Fine"<<endl;
    cout<<"[6]: Clear Dues"<<endl;
    cout<<"[7]: Clear Fine"<<endl;
    cout<<"[8]: View Records"<<endl;

    cout<<"Please choose an operation: ";
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
        User.get_available_cars();
        break;
    }
    case 2:
    {
        if(User.getRentedCars().size()==0)
        {
            cout<<endl;
            cout<<"No cars to display"<<endl;
            cout<<endl;
        }
        for(auto&a : User.getRentedCars())
        {
            cout<<"Id of rented Car : "<<a.getId()<<endl;
            cout<<"Model of rented Car : "<<a.getModel()<<endl;
            cout<<"Due date of rented Car : "<<dateToString(a.getDue_date())<<endl;
            cout<<endl;
        }
        break;
    }
    case 3:
    {
        User.rent_request();
        break;
    }
    case 4:
    {
        User.return_request();
        break;
    }
    case 5:
    {
        int fine=User.currentFines();
        cout<<endl;
        cout<<"Your current dues are : "<<User.getDue()<<endl;
        cout<<"A fine of "<<fine+User.getFine()<<" has been imposed on you"<<endl;
        cout<<endl;
        break;
    }
    case 6:
    {
        cout<<"Please enter the amount that you are paying : ";
        int amount;
        if(!(cin>>amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Invalid input. Please enter a valid option." << endl;
            break;
        }
        cout<<endl;
        if(User.getDue()<amount)
        {
            cout<<"The amount being paid is more than the due.. please check the due.."<<endl;
        }
        else
        {
            User.clearDues(amount);
            cout<<"Due of "<<amount<<" has been cleared"<<endl;
        }
        cout<<endl;
        break;
    }
    case 7:
    {
        cout<<"Please enter the amount that you are paying : ";
        int amount;
        if(!(cin>>amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Invalid input. Please enter a valid option." << endl;
            break;
        }
        cout<<endl;
        if(User.getFine()+User.currentFines()<amount)
        {
            cout<<"The amount being paid is more than the due.. please check the due.."<<endl;
        }
        else
        {
            User.clearFine(amount);
            cout<<"Fine of "<<amount<<" has been cleared"<<endl;
        }
        cout<<endl;
        break;
    }
    case 8:
    {
        int n;
        cout<<"Enter the number of records you want to view : ";
        if(!(cin>>n))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Invalid input. Please enter a valid input." << endl;
            break;
        }
        cout<<endl;
        User.viewRecords(n);
        cout<<endl;
        break;
    }

    default:
        break;
    }
}

void customer_operation(customer &User)
{
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
            customer_process(User);
        }
        else if(op==2)
        {
            break;
        }
        else
        {
            cout<<endl;
            cout<<"Invalid operation"<<endl;
            cout<<endl;
            continue;
        }
    }
}