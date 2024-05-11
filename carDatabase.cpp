#include "header.hpp"

carDatabase::carDatabase(string model, int id , bool available, chrono::system_clock::time_point due_date, int price, int condition): car(model,id, available, due_date, price, condition)
{
    allCars=get_all_cars();
}

void carDatabase::addCar()
{
    allCars.push_back(*this);
    write_into_cars(allCars);
}

void carDatabase::deleteCar()
{
    cout<<endl;
    bool found=false;
    for(int i=0 ; i<allCars.size() ; i++)
    {
        if(allCars[i].getId()==this->getId())
        {
            found=true;
            allCars.erase(allCars.begin()+i);
            break;
        }
    }
    if(found)
    {
        cout<<"Car deleted from database"<<endl;
        write_into_cars(allCars);
    }
    else
    {
        cout<<"Car not found"<<endl;
    }
    cout<<endl;
}

void carDatabase::updateCar()
{
    bool found=false;
    int i;
    for(i=0 ; i<allCars.size() ; i++)
    {
        if(allCars[i].getId()==this->getId())
        {
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"Car not found"<<endl;
        return;
    }
    cout<<endl;
    char p;
    cout<<"Do you want to change the model (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        cout<<"Enter the new model : ";
        string model;
        cin.ignore();
        getline(cin, model);
        allCars[i].setModel(model);
    }
    cout<<"Do you want to change the Price (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        cout<<"Enter the new price : ";
        int price;
        cin>>price;
        allCars[i].setPrice(price);
    }
    cout<<"Do you want to change the Availability status (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        cout<<"Enter the new status : ";
        int status;
        cin>>status;
        allCars[i].setAvailable(status);
    }
    cout<<"Do you want to change the car condition (y/n) : ";
    cin>>p;
    if(p=='y' || p=='Y')
    {
        cout<<"Enter the new condition : ";
        int status;
        cin>>status;
        allCars[i].setCondition(status);
    }
    write_into_cars(allCars);
}

void carDatabase::searchCar()
{
    bool found=false;
    cout<<endl;
    for(auto&a : allCars)
    {
        if(a.getId()==this->getId())
        {
            found=true;
            cout<<"Id of car : "<<a.getId()<<endl;
            cout<<"Model of car : "<<a.getModel()<<endl;
            cout<<"Availability of car : "<<a.getAvailable()<<endl;
            cout<<"Condition of car : "<<a.getCondition()<<endl;
            cout<<"Price of car : "<<a.getPrice()<<endl;
            cout<<endl;
            break;
        }
    }
    if(!found)
    {
        cout<<"Car not found"<<endl;
        cout<<endl;
    }
}