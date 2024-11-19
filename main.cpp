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
        void setName(string name){this->name=name;}
        int calculate(){
            cout<<"Enter = for opperation to see result\n";
            cout<<"Enter number: ";
            cin>>this->current_val;

            char opp;
            cout<<"Enter operation: ";
            cin>>opp;

            if(opp=='='){cout<<"Final value: "<<this->current_val<<endl; return this->current_val;}

            while(true){
                double temp;
                cout<<"Enter number: ";
                cin>>temp;

                switch (opp){
                    case '+':
                        //cout<<"+\n";
                        this->current_val=this->current_val+temp;
                        break;
                    case '-':
                        //cout<<"-\n";
                        this->current_val=this->current_val-temp;
                        break;
                    case '/':
                        //cout<<"/\n";
                        this->current_val=this->current_val/temp;
                        break;
                    case '*':
                        //cout<<"*\n";
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