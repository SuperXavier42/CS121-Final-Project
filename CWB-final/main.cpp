#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Computer{
    protected:
        bool on=false;

    public:
        void powerDevice() {
        on = !on;
        }
        
        virtual int Notepad(){return 0;};
        virtual void startUp(){exit;};


        void operation(){
            if(on==false){
                cout << "\n";
                string value;
                cout << "Power on device (y/n): ";
                cin >> value;
                cout << "\n";
                if(value=="y"){powerDevice();}
                else if(value=="n"){exit;}
            }
            if(on==true){
                int answer;
                cout << "Select Option: \n1) Notepad\n2) Power Off\n";
                cin >> answer;
                cout << "\n";
                if(answer==1){Notepad();}
                if(answer==2){powerDevice();}
            }
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

int main() {
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
    return 0;
}
