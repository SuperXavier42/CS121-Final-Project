#include <iostream>
#include <math.h>

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
                cout<<"Select Option: \n1) Calculate\n2) Power Off\n";
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

                if(opp=='='){break;}
            }
            
            cout<<"Final value: "<<this->current_val<<"\n"<<endl;

            startUp();

            return this->current_val;
        };

};

int main(){
    Computer* Calc = new Calculator();
  
    int choice;
    cout<<"Select Function:\n1) Calculator\n";
    cin>>choice;

    if(choice==1){
        Calc->startUp();
    }

    return 0;
}