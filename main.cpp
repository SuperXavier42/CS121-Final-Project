#include <iostream>

using namespace std;

class Computer{
    private:
        bool on=false;

    public:
        void powerDevice(){
            if(this->on==false)this->on=true;
            if(this->on==true)this->on=false;
        }

};

class Calculator : public Computer{
    private:
        string name;
        double current_val=0;
    public:
        //sets name for calculator I guess
        void setName(string name){this->name=name;}

        //allows user to calculate a number using basic opperations
        int calculate(){
            cout<<"Enter = for opperation to see result\n";
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

int main(){
    Calculator* User = new Calculator();

    User->calculate();

    return 0;
}