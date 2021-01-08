#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <fstream>
#include <ctime>
#include <stdlib.h>
using namespace std;

bool isFileOpen(string fileName) {
    fstream myFile;
    myFile.open (fileName);
    if (myFile.is_open() == false) {
        return false;
    }
    else {
        return true;
    }
    myFile.close();
}

bool isWord(string fileName, string candidate) {
    bool flag = 0;
    string buffer;

    fstream myFile;
    myFile.open (fileName, fstream::in);
    while (getline(myFile, buffer)) {
        if (buffer == candidate) {
            flag = 1;
        }
    }
    if (flag == 1) {
        return true;
    }
    else {
        return false;
    }
    myFile.close();
}

bool isSubset(string main, string sub) {
    int counter = 0;
    for (int i = 0; i < sub.size(); i++) {
        for (int j = 0; j < main.size(); j++) {
            if (sub[i] == main[j]) {
                main[j] = '0';    //avoid repeating elements
                counter++;
                break;
            }
        }
    }
    if (counter == sub.size()) {
        return true;
    }
    else {
        return false;
    }
}

string RandomLetters(int length) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string generator;
    int randIndex = 0;
    for (int i = 0; i < length; i++) {
        randIndex = rand() % alphabet.size(); //pick random index between 0 - 22
        generator += alphabet[randIndex];
    }
    return generator;
}

string RandomWord(string fileName, int fullSize) {
    int randIndex = 0;
    string buffer;
    vector <string> generator;
    string word;
    fstream myFile;
    myFile.open (fileName, fstream::in);
    while (getline(myFile, buffer)) {
        generator.push_back(buffer);
    }
    //generate only word which number of letters is lower or equal to generated letters
    do {
        randIndex = rand() % generator.size();
        word = generator[randIndex];
    } while (word.size() > fullSize);
    return word;
    myFile.close();
}

string Scramble(int fullSize, string word) {
    int size = word.size();
    int index_1 = 0, index_2 = 0;
    char tmp;
    string scramble;
    size = fullSize - size; //find how many random letters are needed to match full size of a string
    scramble = RandomLetters(size) + word; //concatenate the word from dictionary and random letters

    //scramble the string
    for (int i = 0; i < fullSize; i++) {
        index_1 = (rand() % fullSize);
        index_2 = (rand() % fullSize);
        tmp = scramble[index_1];
        scramble[index_1] = scramble[index_2];
        scramble[index_2] = tmp;
    }
    return scramble;
}

void Play(int letters, int rounds, string fileName) {
    int points = 0;
    bool flag = 0;
    string guess;
    string word;
    string available;

    for (int i = 1; i <= rounds; i++) {
        flag = false;
        word = RandomWord(fileName, letters);
        available = Scramble(letters, word);

        cout << "\n Round" << " " << i << ". Available letters: " << " ";
        for (int i = 0; i < available.size(); i++) {  //split string into letters
            cout << available[i] << " ";
        }
        cout << endl << " ";

        while (!flag) {
            cin >> guess;
            if (isSubset(available, guess) && isWord(fileName, guess)) {
                flag = true;
                points += guess.size();
                if (i != rounds){
                    cout << "\n Your points so far are: " << points << endl;
                }
            }
            else {
                cout << "\n Invalid word. Try again with: " << " ";
                for (int i = 0; i < available.size(); i++) {
                    cout << available[i] << " ";
                }
                cout << endl << " ";

            }
        }
    }
    cout << " Your total points are " << points << endl;
    cout << " Returning to menu. " << endl;
}

void Menu(string fileName) {
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
        cout << " Choose option from the menu " << endl << endl << " ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Play(letters, rounds, fileName);
                break;
            }
            case 2: {
                cout << endl;
                cout << " a. Change the number of submitted letters " << endl;
                cout << " b. Change the number of rounds " << endl;
                cout << " ------------------------------------------- " << endl << endl;
                cout << " Choose option from the menu " << endl << " ";
                cin >> subchoice;
                switch (subchoice){
                    case 'a': {
                        cout << " Choose the number of submitted letters: " << endl << " ";
                        cin >> letters;
                        break;
                    }
                    case 'b': {
                        cout << " Choose the number of rounds: " << endl << " ";
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
                cout << "\n Invalid choice " << endl;
            }
        }
    }
}

int main() {
    string file = "dictionary.txt";
    if (!isFileOpen(file)){
        cout << "Failed to open file";
        return 0;
    }
    srand(time(0));
    Menu(file);
    return 0;
}
