#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//Class is made to securely manage passwords
class PasswordManager {
private:
    string masterPassword; //Stores master password
    vector<string> usernames; // Stores usernames
    vector<string> passwords; // Stores passwords
    const string FILENAME = "passwords.dat"; //File is made to store credentials

public:
    PasswordManager(); //Constructor to load the existing credentials
    bool setMasterPassword(const string& password); //Sets the master password
    bool authenticate(const string& password); //Verifies the master password
    void addCredential(const string& username); //Adds a new username and password
    string getCredential(const string& username); //Retrieves password for a username
    void deleteCredential(const string& username); //Deletes stored credential
    string generateRandomPassword(int length = 12); //Generates random password of 12 characters
    void saveToFile(); //Saves credentials to a file
    void loadFromFile(); //Loads credentials from a file
    void displayMenu(); //Displays the menu for the user
};
//Loads stored credentials from file
PasswordManager::PasswordManager() {
    loadFromFile();
}

//Sets master password if it is not already set
bool PasswordManager::setMasterPassword(const string& password) {
    if (masterPassword.empty()) {
        masterPassword = password;
        cout << "Master password set successfully.\n";
        return true;
    }
    cout << "Master password already set.\n";
    return false;
}

//Check if the entered password matches the master password
bool PasswordManager::authenticate(const string& password) {
    return password == masterPassword;
}

//Generates a random password with the length 12
string PasswordManager::generateRandomPassword(int length) {
    const string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*()-_=+[]{}|;:,.<>?";

    string password = "";
    srand(time(0));

    for (int i = 0; i < length; i++) {
        password += chars[rand() % chars.length()];
    }
    return password;
}

//Adds a new credential to the file
void PasswordManager::addCredential(const string& username) {
    string newPassword = generateRandomPassword(); //Generates random password
    usernames.push_back(username);
    passwords.push_back(newPassword);
    cout << "Generated Password: " << newPassword << endl;
    saveToFile(); //Save credentials after adding
}

//Retrieves a password for the entered username
string PasswordManager::getCredential(const string& username) {
    for (size_t i = 0; i < usernames.size(); i++) {
        if (usernames[i] == username) {
            return passwords[i]; // Return password if username is found
        }
    }
    return "Username not found!";
}

//Deletes a stored credential
void PasswordManager::deleteCredential(const string& username) {
    for (size_t i = 0; i < usernames.size(); i++) {
        if (usernames[i] == username) {
            usernames.erase(usernames.begin() + i);
            passwords.erase(passwords.begin() + i);
            cout << "Credentials for " << username << " deleted." << endl;
            saveToFile(); //Save changes to file
            return;
        }
    }
    cout << "Username not found." << endl;
}

//Save all credentials to a file
void PasswordManager::saveToFile() {
    ofstream file(FILENAME);
    if (!file) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    for (size_t i = 0; i < usernames.size(); i++) {
        file << usernames[i] << " " << passwords[i] << endl; //Saves username and password
    }

    file.close();
    cout << "Credentials saved successfully." << endl;
}

//Load credentials from a file
void PasswordManager::loadFromFile() {
    ifstream file(FILENAME);
    if (!file) {
        cout << "No existing credentials found." << endl;
        return;
    }

    usernames.clear();
    passwords.clear();

    string username, password;
    while (file >> username >> password) {
        usernames.push_back(username);
        passwords.push_back(password);
    }

    file.close();
    cout << "Credentials loaded successfully." << endl;
}

//Displays the menu for the user
void PasswordManager::displayMenu() {
    int choice;
    string username, password, temp;

    cout << "Password Manager" << endl;
    cout << "Set Master Password: ";
    cin.clear();
    getline(cin, temp);
    if (!setMasterPassword(temp) && !authenticate(temp)) {
        cout << "Incorrect master password!" << endl;
        return;
    }

    do {
        cout << "1. Add Credentials" << endl;
        cout << "2. Get Credentials" << endl;
        cout << "3. Delete Credentials" << endl;
        cout << "4. Save to File" << endl;
        cout << "5. Load from File" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

//Input validation for choice
cin >> temp;
        try {
            choice = stoi(temp);
        } catch (const std::invalid_argument& e) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter Username: ";
                cin >> username;
                cin.clear();
                getline(cin, username);
                addCredential(username);
                break;
            case 2:
                cout << "Enter Username: ";
                cin >> username;
                cin.clear();
                getline(cin, username);
                cout << "Retrieved Password: " << getCredential(username) << endl;
                break;
            case 3:
                cout << "Enter Username: ";
                cin >> username;
                cin.clear();
                getline(cin, username);
                deleteCredential(username);
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                loadFromFile();
                break;
            case 6:
                cout << "Exiting Password Manager" << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);
}

//Main function to start the password manager
int main() {
    PasswordManager manager;
    manager.displayMenu();
    return 0;
}
