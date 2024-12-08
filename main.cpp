#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

class Computer{
    protected:
        bool on=false;

    public:
        void powerDevice(){
            if(on==false){on=true;}
            else if(on==true){on=false;}
        }
        virtual int calculate(){return 0;};
        virtual void operation(){exit;};

};

class Calculator : public Computer{
    private:
        string name;
        double current_val=0;
    public:
        //sets name for calculator I guess
        void setName(string name){this->name=name;}

        void operation(){
            if(on==false){
                cout<<"\n";
                string value;
                cout<<"Power on device (y/n): ";
                cin>>value;

                cout<<"\n";
                if(value=="y"){powerDevice();}
                else if(value=="n"){exit;}
            }
            if(on==true){
                int answer;
                cout<<"Select Option: \n1) Calculate\n2) Contact Book\n 3)Power Off\n";
                cin>>answer;

                cout<<"\n";
                if(answer==1){calculate();}
                if(answer==2){powerDevice();}
            }

        }

        //allows user to calculate a number using basic opperations
        int calculate(){
            cout<<"Operations: + - * / % (= to exit)\n\n";
            cout<<"Enter number: ";
            //sets current val to the initial number
            cin>>this->current_val;

            char opp;
            cout<<"Enter operation: ";
            cin>>opp;

            //checks if the first value is a =
            if(opp=='='){cout<<"Final value: "<<this->current_val<<endl; return this->current_val;}

            //runs until user enters a =
            while(true){
                double temp;
                cout<<"Enter number: ";
                cin>>temp;

                //updates current val based on entered opperation
                switch (opp){
                    case '+':
                        this->current_val=this->current_val+temp;
                        break;
                    case '-':
                        this->current_val=this->current_val-temp;
                        break;
                    case '/':
                        this->current_val=this->current_val/temp;
                        break;
                    case '*':
                        this->current_val=this->current_val*temp;
                        break;
                    case '%':
                        this->current_val=fmod(this->current_val, temp);
                        break;
                    case '=':
                        break;
                    
                }
                cout<<"Current value: "<<this->current_val<<endl;

                cout<<"\nEnter operation: ";
                cin>>opp;

                if(opp=='=')break;
            }
            
            cout<<"Final value: "<<this->current_val<<endl;
            return this->current_val;
        };

};

class Contact{
private:
    std::string contactName;
    std::string phoneNumber;
    std::string contactEmail;

public:
    //constructor
    Contact(const std::string& contactName, const std::string& phoneNumber, const std::string& contactEmail): contactName(contactName), phoneNumber(phoneNumber), contactEmail(contactEmail){}
    //getter
    std::string getName() const{
        return contactName;}
    std::string getNumber() const{
        return phoneNumber;}
    std::string getEmail() const{
        return contactEmail;}
    //display
    void displayContact()const{
        std::cout << "Contact: "<<contactName 
                    << " \nPhone number: " << phoneNumber 
                    << "\nEmail: " << contactEmail << std::endl;
    }
};

class ContactBook{
private:
    std::vector<Contact> contacts;
    std::string match;

public:
    //view all
    void viewCBall(){
        for (const auto& contact: contacts){
            contact.displayContact();
            std::cout << "--------------------\n";
        }
    }
    //view searched contact by name
    void viewCBbyName(const std::string& name){
        for(const auto& contact: contacts){
            if (contact.getName() == name){
                contact.displayContact();
            }
        }
        std::cout <<"Contact not found.\n";
    }
    //Add contact to book
    void addCB(const std::string& name, const std::string& newNumber, const std::string& email){
        contacts.emplace_back(name, newNumber, email);
        std::cout << "Contact added\n";
    }
    //Change contact info
    void changeCB(const std::string name, const std::string newNumber, const std::string newEmail){
       for(auto& contact :contacts){
        if(contact.getName() == name){
            contact = Contact(name, newNumber, newEmail);
            std::cout << "Contact updated\n";
        }
       }
       std::cout << "Contact not found\n";
    }
};

//Contact book manager class
class ContactBookManager {
private:
    ContactBook book;

public:
    void run() {
        int choice;
        std::string name, number, email;

        while (true) {
            std::cout << "\nContact Book Menu:\n";
            std::cout << "1. View all contacts\n";
            std::cout << "2. View contact by name\n";
            std::cout << "3. Add a contact\n";
            std::cout << "4. Change contact info\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            std::cin.ignore(); // Clear the input buffer

            switch (choice) {
                case 1:
                    std::cout << "Viewing all contacts:\n";
                    book.viewCBall();
                    break;
                case 2:
                    std::cout << "Enter contact name: ";
                    std::getline(std::cin, name);
                    book.viewCBbyName(name);
                    break;
                case 3:
                    std::cout << "Enter contact name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter phone number: ";
                    std::getline(std::cin, number);
                    std::cout << "Enter email: ";
                    std::getline(std::cin, email);
                    book.addCB(name, number, email);
                    break;
                case 4:
                    std::cout << "Enter name of contact to change: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter new phone number: ";
                    std::getline(std::cin, number);
                    std::cout << "Enter new email: ";
                    std::getline(std::cin, email);
                    book.changeCB(name, number, email);
                    break;
                case 5:
                    std::cout << "Exiting.\n";
                    return;
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
};
int main(){
    Computer* User = new Calculator();
    
    User->operation();


    ContactBookManager manager;
    manager.run();


    return 0;
}