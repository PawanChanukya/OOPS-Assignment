#include "header.hpp"

employeeDatabase::employeeDatabase(string name, int id, string password, int score, int due , int fine): employee(name, id, password, score, due, fine)
{
    allEmployees=get_all_employees();
}

void employeeDatabase::addEmployee()
{
    allEmployees.push_back(*this);
    write_into_employees(allEmployees);
}

void employeeDatabase::deleteEmployee()
{
    cout<<endl;
    bool found=false;
    for(int i=0 ; i<allEmployees.size() ; i++)
    {
        if(allEmployees[i].getId()==this->getId())
        {
            found=true;
            allEmployees.erase(allEmployees.begin()+i);
            break;
        }
    }
    if(found)
    {
        cout<<"Employee deleted from database"<<endl;
        write_into_employees(allEmployees);
    }
    else
    {
        cout<<"Employee not found"<<endl;
    }
    cout<<endl;
}

void employeeDatabase::updateEmployee()
{
    int i;
    bool found=false;
    for(i=0 ; i<allEmployees.size() ; i++)
    {
        if(this->getId()==allEmployees[i].getId())
        {
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"There is no employee with the given id"<<endl;
        return;
    }
    while(1)
    {
        cout<<"[1] : Update the chosen Employee"<<endl;
        cout<<"[2] : Terminate"<<endl;
        cout<<"Please choose an operation : ";
        int op;
        cin>>op;
        if(op==2)
        {
            break;
        }
        if(op>2 || op<1)
        {
            cout<<"Invalid Operation"<<endl;
            cout<<endl;
            continue;
        }
        cout<<endl;
    char p;
    cout<<"Do you want to change the id (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_id;
        cout<<"Please enter new id : ";
        cin>>new_id;
        allEmployees[i].setId(new_id);
    }
    cout<<"Do you want to change the name (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        string new_name;
        cin.ignore();
        cout<<"Please enter new name : ";
        getline(cin, new_name);
        allEmployees[i].setName(new_name);
    }
    cout<<"Do you want to change the password (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        string new_password;
        cin.ignore();
        cout<<"Please enter new name : ";
        getline(cin, new_password);
        allEmployees[i].setPassword(new_password);
    }
    cout<<"Do you want to change the score (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_score;
        cout<<"Please enter new score : ";
        cin>>new_score;
        allEmployees[i].setEmployeeScore(new_score);
    }
    cout<<"Do you want to change the due (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_due;
        cout<<"Please enter new due : ";
        cin>>new_due;
        allEmployees[i].setDue(new_due);
    }
    cout<<"Do you want to change the fine (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_fine;
        cout<<"Please enter new fine : ";
        cin>>new_fine;
        allEmployees[i].setFine(new_fine);
    }
    }
    write_into_employees(allEmployees);
}

void employeeDatabase::searchEmployee()
{
    bool found =false;
    cout<<endl;
    for(auto& a : allEmployees)
    {
        if(a.getId()==this->getId())
        {
            found=true;
            cout<<"Id of employee : "<<a.getId()<<endl;
            cout<<"Name of employee : "<<a.getName()<<endl;
            cout<<"Score : "<<a.getEmployeeScore()<<endl;
            cout<<"Dues : "<<a.getDue()<<endl;
            cout<<"Fine : "<<a.getFine()<<endl;
            cout<<"Number of cars currently renting : "<<a.getRentedCars().size()<<endl;
            cout<<endl;
            break;
        }
    }
    if(!found)
    {
        cout<<"Employee not found"<<endl;
        cout<<endl;
    }
}