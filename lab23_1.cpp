#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>  

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int score1, score2, score3;
        
    
        getline(ss, name, ':');
        ss >> score1 >> score2 >> score3;

        while (!name.empty() && name.back() == ' ') {
            name.pop_back();
        }

        names.push_back(name);
        int totalScore = score1 + score2 + score3;
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }

    file.close();
}


void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command: "<< endl;
    getline(cin, input); 

    size_t spacePos = input.find(' '); 
    if (spacePos != string::npos) {
        command = input.substr(0, spacePos); 
        key = input.substr(spacePos + 1);  
    } else {
        command = input; 
        key = "";      
    }

   
    command = toUpperStr(command);
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    string searchKey = toUpperStr(key); 

    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == searchKey) { 
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    bool found = false;
    char searchKey = toupper(key[0]); 

    cout << "---------------------------------\n";
    for (size_t i = 0; i < names.size(); i++) {
        if (grades[i] == searchKey) { 
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}