#include <iostream>
#include <iomanip>
using namespace std;

void Play (int letters, int rounds) {


}

void Menu () {
    int choice = 0;
    int rounds = 10, letters = 10;
    char subchoice = 0;
    while (choice != 4) {
        cout << endl << endl;
        cout << setw(13) << " Menu " << endl;
        cout << " -------------------- " << endl;
        cout << " 1. Start a new game " << endl;
        cout << " 2. Settings " << endl;
        cout << " 3. Enter a new word " << endl;
        cout << " 4. Exit " << endl;
        cout << " --------------------- " << endl << endl;
        cout << "Choose option from the menu" << endl << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                Play (letters, rounds);
                break;
            }
            case 2: {
                cout << endl;
                cout << " a. Change the number of submitted letters " << endl;
                cout << " b. Chane the number of rounds " << endl;
                cout << " ------------------------------------------- " << endl << endl;
                cout << "Choose option from the menu" << endl;
                cin >> subchoice;
                switch (subchoice) {
                    case 'a': {
                        cin >> letters;
                        break;
                    }
                    case 'b': {
                        cin >> rounds;
                        break;
                    }
                }
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            default: {
                cout << "Invalid choice";
            }
        }
    }
}

int main () {
    Menu ();
    return 0;
}
