#include "header.hpp"

customerDatabase::customerDatabase(string name, int id, string password, int score, int due , int fine): customer(name, id, password, score, due, fine)
{
    allCustomers=get_all_customers();
}

void customerDatabase::addCustomer()
{
    allCustomers.push_back(*this);
    write_into_customers(allCustomers);
}

void customerDatabase::deleteCustomer()
{
    cout<<endl;
    bool found=false;
    for(int i=0 ; i<allCustomers.size() ; i++)
    {
        if(allCustomers[i].getId()==this->getId())
        {
            found=true;
            allCustomers.erase(allCustomers.begin()+i);
            break;
        }
    }
    if(found)
    {
        cout<<"Customer deleted from database"<<endl;
        write_into_customers(allCustomers);
    }
    else
    {
        cout<<"Customer not found"<<endl;
    }
    cout<<endl;
}

void customerDatabase::updateCustomer()
{
    int i;
    bool found=false;
    for(i=0 ; i<allCustomers.size() ; i++)
    {
        if(this->getId()==allCustomers[i].getId())
        {
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"There is no customer with the given id"<<endl;
        return;
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
        allCustomers[i].setId(new_id);
    }
    cout<<"Do you want to change the name (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        string new_name;
        cin.ignore();
        cout<<"Please enter new name : ";
        getline(cin, new_name);
        allCustomers[i].setName(new_name);
    }
    cout<<"Do you want to change the password (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        string new_password;
        cin.ignore();
        cout<<"Please enter new name : ";
        getline(cin, new_password);
        allCustomers[i].setPassword(new_password);
    }
    cout<<"Do you want to change the score (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_score;
        cout<<"Please enter new score : ";
        cin>>new_score;
        allCustomers[i].setCustomerScore(new_score);
    }
    cout<<"Do you want to change the due (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_due;
        cout<<"Please enter new due : ";
        cin>>new_due;
        allCustomers[i].setDue(new_due);
    }
    cout<<"Do you want to change the fine (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        int new_fine;
        cout<<"Please enter new fine : ";
        cin>>new_fine;
        allCustomers[i].setFine(new_fine);
    }
    write_into_customers(allCustomers);
}

void customerDatabase::searchCustomer()
{
    bool found=false;
    cout<<endl;
    for(auto& a : allCustomers)
    {
        if(a.getId()==this->getId())
        {
            found=true;
            cout<<"Id of customer : "<<a.getId()<<endl;
            cout<<"Name of customer : "<<a.getName()<<endl;
            cout<<"Score : "<<a.getCustomerScore()<<endl;
            cout<<"Dues : "<<a.getDue()<<endl;
            cout<<"Fine : "<<a.getFine()<<endl;
            cout<<"Number of cars currently renting : "<<a.getRentedCars().size()<<endl;
            cout<<endl;
            break;
        }
    }
    if(!found)
    {
        cout<<"Customer not found"<<endl;
        cout<<endl;
    }
}