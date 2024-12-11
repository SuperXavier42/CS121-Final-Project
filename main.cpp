#include <iostream>
#include <math.h>
#include <vector>

#include "libraries/graphing.h"
#include "libraries/config.h"
#include "libraries/SFML-2.6.2/include/SFML/Graphics.hpp"
#include <functional>
// #include <typeinfo>
// #include <cxxabi.h>

using namespace std;

class Computer{
    protected:
        bool on=false;

    public:
        void powerDevice(){
            on = !on;
        }
        virtual int calculate(){return 0;};
        virtual void startUp(){exit;};
        virtual void graph(){return;};

};

class Calculator : public Computer{
    private:
        string name;
        double current_val=0;
    public:
        //sets name for calculator I guess
        void setName(string name){this->name=name;}

        void startUp(){
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
                cout<<"Select Option: \n1) Calculate\n2) Graph a Function \n3) Power Off\n";
                cin>>answer;

                cout<<"\n";
                if(answer==1){calculate();}
                if (answer == 2) {
                    graph();
                }
                if(answer==3){powerDevice();}
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

                if(opp=='='){break;}
            }
            
            cout<<"Final value: "<<this->current_val<<"\n"<<endl;

            startUp();

            return this->current_val;
        };

        void graph(){
            while (true) {
                cout << "Select a function to graph: \n1) Linear\n2) Quadratic\n3) Cubic\n4) nth-root\nEnter 5 to exit" << endl;
                int selection;
                cin >> selection;
                std::function<double(double, double, double, double, double)> f;
                // the above line initializes the function according to the argument list for each function in graphing.h
                // the only function which actually utilizes five doubles is the cubic function
                // however, the other functions accept dummy variables for extra doubles in order to match argument number
                // without matching argument number, the compiler errors "too few arguments" (or too many)
                // this was the quick and dirty way of fixing it; just making all function types resemble the cubic one by number of parameters
                double arg1, arg2, arg3, arg4; // the first double sent to each function is the x value, the remaining are the constants (coefficients, nth root)
                //therefore we only initialize four, not five arguments
                // any unused arguments remain as 0
                if (selection == 1) {
                    f = linear_func;
                    cout << "\nSelected function: y = mx + b" << endl;
                    cout << "Enter a number value for 'm': ";
                    cin >> arg1;
                    
                    // int status;
                    // char* typeName = abi::__cxa_demangle(typeid(arg1).name(), nullptr, nullptr, &status);
                    // std::cout << arg1 << " " << typeName << std::endl;
                    // break;

                    cout << "\nEnter a number value for 'b': ";
                    cin >> arg2;
                } else if (selection == 2) {
                    f = quadratic_func;
                    cout << "\nSelected function: y = ax^2 + bx + c" << endl;
                    cout << "Enter a number value for coefficient 'a': ";
                    cin >> arg1;
                    cout << "\nEnter a number value for coefficient 'b': ";
                    cin >> arg2;
                    cout << "\nEnter a number value for coefficient 'c': ";
                    cin >> arg3;
                } else if (selection == 3) {
                    f = cubic_func;
                    cout << "\nSelected function: y = ax^3 + bx^2 + cx + d" << endl;
                    cout << "Enter a number value for coefficient 'a': ";
                    cin >> arg1;
                    cout << "\nEnter a number value for coefficient 'b': ";
                    cin >> arg2;
                    cout << "\nEnter a number value for coefficient 'c': ";
                    cin >> arg3;
                    cout << "\nEnter a number value for coefficient 'd': ";
                    cin >> arg4;
                } else if (selection == 4) {
                    cout << "\nSelected function: y = a * root(x, n) + b" << endl;
                    f = n_root_func;
                    cout << "Enter a number value for the 'n' root of x: ";
                    cin >> arg1;
                    cout << "\nEnter a number value for coefficient 'a': ";
                    cin >> arg2;
                    cout << "\nEnter a number value for coefficient 'b': ";
                    cin >> arg3;
                } else if (selection == 5) {
                    break;
                }

                if (f) {
                    cout << "The graphing window will now open.\nWhen you are finished, just close the window." << endl;
                    sf::RenderWindow window(sf::VideoMode(cfg.res_x, cfg.res_y), "Graph Drawer");
                    window.setFramerateLimit(10);

                    while (window.isOpen()) {
                        sf::Event event;
                        bool eventProcessed = false;

                        while (window.pollEvent(event)) {
                            eventProcessed = true;
                            if (event.type == sf::Event::Closed)
                                window.close();
                        }

                        if (!eventProcessed) {
                            sf::sleep(sf::milliseconds(100)); // this prevents the application from lagging
                        }

                        window.clear(sf::Color::White);

                        draw_axes(window);
                        draw_graph(window, f, arg1, arg2, arg3, arg4);
                        window.display();
                    }
                    cout << "\nGraphing window closed.\n";
                } else {
                    cout << "Invalid function selected.\n";
                }
            }
            cout << "Graphing application terminated.\n";
            startUp();
        }
};

class Notepad{
    private:
        string title;
        string content;
    public:
        Notepad(string t, string c) {
            title = t;
            content = c;
        }
    string getHead() {
        return title;
    }

    string  getContent() {
        return content;
    }
    void setHead(string t) {
        title = t;
    }

    void setContent(string c) {
        content = c;
    }
    void displayNotepad() {
        cout << "Title: " << title << endl;
        cout << "Content: " << content << endl;
    }
    void editContent(string newContent) {
        content = newContent;
        cout << "Note content updated." << endl;
    }
};

Notepad createNewNote() {
    string title, content;

    cout << "Enter the title: ";
    getline(cin, title);
    cout << "Enter the content: ";
    getline(cin, content);

    return Notepad(title, content);
}


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
    Computer* Calc = new Calculator();
    ContactBookManager manager;
  
    int choice;
    cout<<"Select Function:\n1) Calculator\n2) Notepad\n3) Contact Book\n";
    cin>>choice;

    if(choice==1){Calc->startUp();}
    if(choice==2){
        vector<Notepad> notes;
        int choice;

        do {
            cout << "\nNotepad Application Menu:\n";
            cout << "1) Create new note\n";
            cout << "2) Display all notes\n";
            cout << "3) Edit a note\n";
            cout << "4) Exit\n";
            cout << "Enter Command: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    Notepad newNote = createNewNote();
                    notes.push_back(newNote);
                    cout << "New note created successfully!" << endl;
                    break;
                }

                case 2: {
                    if (notes.empty()) {
                        cout << "No notes available.\n";
                    } else {
                        cout << "\nAll Notes:\n";
                        for (size_t i = 0; i < notes.size(); ++i) {
                            cout << "\nNote #" << i + 1 << endl;
                            notes[i].displayNotepad();
                        }
                    }
                    break;
                }
                case 3: {
                    if (notes.empty()) {
                        cout << "No notes to edit.\n";
                    } else {
                        int noteIndex;
                        cout << "Enter the note number to edit (1 to " << notes.size() << "): ";
                        cin >> noteIndex;
                        cin.ignore();

                        if (noteIndex > 0 && noteIndex <= notes.size()) {
                            string newContent;
                            cout << "Enter the new content for the note: ";
                            getline(cin, newContent);
                            notes[noteIndex - 1].editContent(newContent);
                        } else {
                            cout << "Invalid note number.\n";
                        }
                    }
                    break;
                }

                case 4:
                    cout << "Exiting the application.\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
    if(choice==3){
        manager.run();
    }

    return 0;
}