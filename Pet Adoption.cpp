#include <bits/stdc++.h>
#include <fstream>
#include <limits>

using namespace std;


class Pet {
private:
    string type;
    string breed;
    string name;
    int years;
    int months;
    double price;
    bool available; 

public:
    
    Pet(string t, string b, string n, int y, int m, double p, bool avail = true) 
        : type(t), breed(b), name(n), years(y), months(m), price(p), available(avail) {}

    // Getters
    string getType() const { return type; }
    string getBreed() const { return breed; }
    string getName() const { return name; }
    int getYears() const { return years; }
    int getMonths() const { return months; }
    double getPrice() const { return price; }
    bool isAvailable() const { return available; }
    void setAvailability(bool avail) { available = avail; }
};

// Function object to compare pets by name
struct CompareByName {
    bool operator()(const Pet& pet1, const Pet& pet2) {
        return pet1.getName() < pet2.getName();
    }
};

// Function object to compare pets by breed
struct CompareByBreed {
    bool operator()(const Pet& pet1, const Pet& pet2) {
        return pet1.getBreed() < pet2.getBreed();
    }
};

// Function object to compare pets by age
struct CompareByAge {
    bool operator()(const Pet& pet1, const Pet& pet2) {
        if (pet1.getYears() != pet2.getYears()) {
            return pet1.getYears() < pet2.getYears();
        } else {
            return pet1.getMonths() < pet2.getMonths();
        }
    }
};

// Class to represent a pet adoption platform
class PetAdoptionPlatform {
private:
    vector<Pet> pets; // Vector to store pets available for adoption
    map<string, vector<string>> breedMap; // to store breeds by type

public:
    // Function to add a pet to the platform
    void addPet() {
        string type, breed, name;
        int years, months;
        double price;

        cout << "Enter the type of pet : ";
        cin >> type;

        cout << "Enter breed of the pet: ";
        cin >> breed;

      
        if (breedMap.find(type) == breedMap.end()) {
            breedMap[type] = vector<string>{};
        }
        breedMap[type].push_back(breed);

        cout << "Enter name of the pet: ";
        cin >> name;
        
        cout << "Enter age of the pet in years: ";
        cin >> years;

        cout << "Enter additional months of the pet: ";
        cin >> months;

        cout << "Enter price of the pet: ";
        cin >> price;

        pets.push_back(Pet(type, breed, name, years, months, price));
        cout << "A pet named " << name << " of type " << type << ", breed " << breed << ", age ";
        if (years > 0) cout << years << " years ";
        if (months > 0) cout << "and " << months << " months ";
        cout << "and price $" << price << " added successfully to the Platform. Thank you." << endl;
    }

    // Function to display all pets available for adoption
    void displayPets() const {
        cout << "Pets Available for Adoption:" << endl;
        cout << "-----------------------------" << endl;

    
        for (const auto& entry : breedMap) {
            cout << "Type: " << entry.first << endl;
            cout << "-----------------------------" << endl;

            set<string> displayedBreeds;

      
            for (const auto& breed : entry.second) {
         
                if (displayedBreeds.find(breed) == displayedBreeds.end()) {
                    cout << "Breed: " << breed << endl;
                    cout << "Available Pets:" << endl;

  
                    bool anyPetsDisplayed = false;
                    for (const auto& pet : pets) {
                        if (pet.getType() == entry.first && pet.getBreed() == breed && pet.isAvailable()) {
                            cout << "  - Name: " << pet.getName() << ", Age ";
                            if (pet.getYears() > 0) cout << pet.getYears() << " years ";
                            if (pet.getMonths() > 0) cout << " " << pet.getMonths() << " months ";
                            cout << ", Price: $" << pet.getPrice() << endl;
                            anyPetsDisplayed = true;
                        }
                    }

                    if (!anyPetsDisplayed) {
                        cout << "  No pets available for adoption." << endl;
                    }

                    displayedBreeds.insert(breed);

                    cout << endl;
                }
            }
            cout << endl; 
        }
    }

  
    void adoptPet() {
        cout << "Enter the type of pet you want to adopt : ";
        string type;
        cin >> type;

      
        if (breedMap.find(type) == breedMap.end()) {
            cout << "No breeds available for the selected type." << endl;
            return;
        }

        cout << "Available breeds for " << type << ":" << endl;
        set<string> displayedBreeds;
        for (const auto& breed : breedMap[type]) {
       
            if (displayedBreeds.find(breed) == displayedBreeds.end()) {
                cout << breed << endl;
                displayedBreeds.insert(breed);
            }
        }

        cout << "Enter the breed you want to adopt: ";
        string breed;
        cin >> breed;

        bool found = false;
        cout << "Pets of Breed " << breed << " available for adoption:" << endl;
        cout << "-----------------------------" << endl;
        for (const auto& pet : pets) {
            if (pet.isAvailable() && pet.getType() == type && pet.getBreed() == breed) {
                cout << "Name: " << pet.getName() << ", Age ";
                if (pet.getYears() > 0) cout << pet.getYears() << " years ";
                if (pet.getMonths() > 0) cout << " " << pet.getMonths() << " months ";
                cout << ", Price: $" << pet.getPrice() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No pets of type " << type << " and breed " << breed << " found for adoption." << endl;
            return;
        }

        cout << "Enter the name of the pet you want to adopt: ";
        string name;
        cin >> name;
        for (auto& pet : pets) {
            if (pet.getName() == name && pet.isAvailable()) {
                pet.setAvailability(false);

                
                cout << "Choose payment method:" << endl;
                cout << "1. Pay now using credit card" << endl;
                cout << "2. Pay online" << endl;
                int paymentChoice;
                cin >> paymentChoice;

                if (paymentChoice == 1 || paymentChoice == 2) {
                    double amount;
                    while (true) {
                        cout << "Enter the amount to pay: $";
                        cin >> amount;
                        if (amount == pet.getPrice()) {
                            cout << "Payment successful!" << endl;
                            cout << "Congratulations! You have adopted " << pet.getName() << "." << endl;
                            break;
                        } else {
                            cout << "Incorrect amount. Please repay the correct amount." << endl;
                        }
                    }
                } else {
                    cout << "Invalid payment choice." << endl;
                }
                return;
            }
        }
        cout << "Sorry, pet with name " << name << " is not available for adoption." << endl;
    }

  
    void savePetsToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error: Unable to open the file " << filename << " for writing." << endl;
            return;
        }

        for (const auto& pet : pets) {
            outFile << pet.getType() << " " << pet.getBreed() << " " << pet.getName() << " " << pet.getYears() << " " << pet.getMonths() << " " << pet.getPrice() << " " << pet.isAvailable() << endl;
        }

        outFile.close();
    }

    // Function to load pets' data from a file
    void loadPetsFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error: Unable to open the file " << filename << " for reading." << endl;
            return;
        }

        string type, breed, name;
        int years, months;
        double price;
        bool available;
        while (inFile >> type >> breed >> name >> years >> months >> price >> available) {
            pets.push_back(Pet(type, breed, name, years, months, price, available));

 
            if (breedMap.find(type) == breedMap.end()) {
                breedMap[type] = vector<string>{};
            }
            breedMap[type].push_back(breed);
        }

        inFile.close();
    }
};

int main() {
    PetAdoptionPlatform platform;
    platform.loadPetsFromFile("pets.txt");

    int choice;
    while (true) {
        cout << "\nChoose an option:" << endl;
        cout << "1. Add pets" << endl;
        cout << "2. Adopt a pet" << endl;
        cout << "3. See all available pets" << endl;
        cout << "4. Save and Exit" << endl;

        cin >> choice;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a valid option." << endl;
            continue;
        }

        if (choice == 1) {
            int numberofpets;
            cout << "Enter the number of pets you want to add: ";
            cin >> numberofpets;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid number of pets!" << endl;
                continue;
            }

            while (numberofpets--) {
                platform.addPet();
            }
        } else if (choice == 2) {
            platform.adoptPet();
        } else if (choice == 3) {
            platform.displayPets();
        } else if (choice == 4) {
            platform.savePetsToFile("pets.txt");
            cout << "Pets' data saved. Thank you for visiting us!!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please enter a valid choice." << endl;
        }
    }

    return 0;
}
