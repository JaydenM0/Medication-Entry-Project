#include <iostream>
#include <string>

using namespace std;

// Abstract base class for a Pill
class Pill {
private:
    string name;
    int dosage;
    int size;
    bool isControlledSubstance;
    int scheduleNum;

protected:
    // Getter functions for private members
    string getName() const {
        return name;
    }

    int getDosage() const {
        return dosage;
    }

    int getSize() const {
        return size;
    }

    bool getIsControlledSubstance() const {
        return isControlledSubstance;
    }

    int getScheduleNum() const {
        return scheduleNum;
    }

public:
    // Constructor for Pill
    Pill(string name, int dosage, int size, bool isControlledSubstance, int scheduleNum)
        : name(name), dosage(dosage), size(size), isControlledSubstance(isControlledSubstance), scheduleNum(scheduleNum) {}

    // Setter function for the name property
    void setName(string newName) {
        name = newName;
    }

    // Setter function for the dosage property
    void setDosage(int newDosage) {
        dosage = newDosage;
    }

    // Setter function for the size property
    void setSize(int newSize) {
        size = newSize;
    }

    // Setter function for the controlled substance properties
    void setControlledSubstance(bool isControlled, int schedule = 0) {
        isControlledSubstance = isControlled;
        if (isControlled) {
            scheduleNum = schedule;
        }
    }

    // Virtual function to print details of the Pill (to be overridden by derived classes)
    virtual void printDetails() const = 0;
};

// Derived class representing a Tablet
class Tablet : public Pill {
private:
    string wording; // Additional property for Tablets

public:
    // Constructor for Tablet
    Tablet(string name, int dosage, int size, bool isControlledSubstance, int scheduleNum, string wording)
        : Pill(name, dosage, size, isControlledSubstance, scheduleNum), wording(wording) {}

    // Implementation of the virtual function to print details for Tablet
    void printDetails() const override {
        cout << "-----------------------------"<<endl;
        cout << "Tablet Details:" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Dosage: " << getDosage() << " mg" << endl;
        cout << "Size: " << getSize() << " mm" << endl;
        cout << "Controlled Substance: " << (getIsControlledSubstance() ? "Yes" : "No") << endl;
        if (getIsControlledSubstance()) {
            cout << "Schedule Number: " << getScheduleNum() << endl;
        }
        cout << "Wording: " << wording << endl;
        cout << "-----------------------------"<<endl;
    }
};

// Derived class representing a Capsule
class Capsule : public Pill {
public:
    // Constructor for Capsule
    Capsule(string name, int dosage, int size, bool isControlledSubstance, int scheduleNum)
        : Pill(name, dosage, size, isControlledSubstance, scheduleNum) {}

    // Implementation of the virtual function to print details for Capsule
    void printDetails() const override {
        cout << "-----------------------------"<<endl;
        cout << "Capsule Details:" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Dosage: " << getDosage() << " mg" << endl;
        cout << "Size: " << getSize() << " mm" << endl;
        cout << "Controlled Substance: " << (getIsControlledSubstance() ? "Yes" : "No") << endl;
        if (getIsControlledSubstance()) {
            cout << "Schedule Number: " << getScheduleNum() << endl;
        }
        cout << "-----------------------------"<<endl;
    }
};



int main() {
    string name, type, wording, yesNo, addAnother;
    int dosage, size, scheduleNum;

    do {
        // Get user input for the name of the drug
        cout << "Enter the name of the drug: ";
        cin >> name;

        // Get user input for the type of pill (Tablet or Capsule)
        cout << "Is this a Tablet or a Capsule? ";
        cin >> type;

        Pill* newPill = nullptr;

        bool isControlled = false;

        // Create a Tablet or Capsule object based on user input
        if (type == "tablet") {
            // If the pill is a Tablet, ask for additional input (wording)
            cout << "Is there wording on the tablet (Yes/No): ";
            cin >> yesNo;
            if (yesNo == "Yes" || yesNo == "yes") {
                cout << "Enter the wording that's on the pill: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, wording);
            }

            // Ask if it's a controlled substance
            cout << "Is this a controlled substance (Yes/No): ";
            cin >> yesNo;
            if (yesNo == "Yes" || yesNo == "yes") {
                cout << "Enter the schedule number: ";
                cin >> scheduleNum;
                isControlled = true;
            }

            // Create a new Tablet object
            newPill = new Tablet(name, 0, 0, isControlled, scheduleNum, wording);
        } else if (type == "capsule") {
            // Ask if it's a controlled substance
            cout << "Is this a controlled substance (Yes/No): ";
            cin >> yesNo;
            if (yesNo == "Yes" || yesNo == "yes") {
                cout << "Enter the schedule number: ";
                cin >> scheduleNum;
                isControlled = true;
            }

            // Create a new Capsule object
            newPill = new Capsule(name, 0, 0, isControlled, scheduleNum);
        } else {
            // Display an error message for an invalid pill type
            cout << "Invalid pill type. Is this a Tablet or a Capsule?" << endl;
            return 1; // Exit with an error code
        }

        // Get user input for dosage and perform validation
        cout << "Enter the dosage / strength in milligrams: ";
        cin >> dosage;
        if (dosage < 0) {
            cout << "Invalid strength. Enter the dosage / strength: ";
            cin >> dosage;
        }

        // Get user input for size and perform validation
        cout << "Enter the size in millimeters (>= 5): ";
        cin >> size;
        if (size < 5) {
            cout << "Invalid size. Enter the size in millimeters (>= 5): ";
            cin >> size;
        }

        // Set properties for the created pill
        newPill->setName(name);
        newPill->setDosage(dosage);
        newPill->setSize(size);

        // Display pill details
        newPill->printDetails();

        // Cleanup
        delete newPill;

        // Ask if the user wants to add another pill
        cout << "Do you want to add another pill? (Yes/No): ";
        cin >> addAnother;

    } while (addAnother == "Yes" || addAnother == "yes");

    return 0;
}
