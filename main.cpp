#include <iostream>
#include <string>

using namespace std;

class Accomodation {

public:
    Accomodation() {}

    virtual int calculateCost() = 0;

    virtual void displayDetails() = 0;

    virtual ~Accomodation() {}
};

class Room : virtual public Accomodation{
    int number;
    string type;
    bool isFree;
    int nightsStayed;
    int pricePerNight;

public:
    Room(int number, const string &type, bool isFree, int nightsStayed)
        : number(number), type(type), isFree(isFree), nightsStayed(nightsStayed) {
        pricePerNight = 50;
    }

    int calculateCost() override {
        return pricePerNight *= nightsStayed;
    }

    void displayDetails() override {
        cout << "Room number: " << number << "\n";
        cout << "Type: " << type << "\n";
        cout << "Availability: ";
        if (isFree) cout << "Yes\n"; else cout << "N\n";
        cout << "Price per night: " << pricePerNight << "\n";
    }

    int getNightsStayed() {
        return nightsStayed;
    }

    ~Room() {}
};

class Service: virtual public Accomodation, public Room {
    int timesServed;
    float priceOfLaundry;
    float transportAmount;
    float amountPerServing = 10.0;

public:
    Service(int number, const string &type, bool isFree, int nightsStayed, int timesServed, float priceOfLaundry,
            float transportAmount) : Room(number, type, isFree, nightsStayed), timesServed(timesServed),
                                     priceOfLaundry(priceOfLaundry), transportAmount(transportAmount) {}

    int calculateCost() override {
        int nights = getNightsStayed();
        float foodAmount = (timesServed * amountPerServing);
        float cost = nights + foodAmount + transportAmount + priceOfLaundry;
        return cost;
    }

    void displayDetails() override {
        Room::displayDetails();
        cout << "Times served: " << timesServed << " with amount of " << amountPerServing << endl;
        cout << "Other expenses:\n";
        cout << "Laundry: " << priceOfLaundry << endl;
        cout << "Transport: " << transportAmount << endl;
    }

    ~Service() {}
};

int main() {

    // Create a Room object
    Room room1(101, "Single", true, 3);

    // Display details of the room
    cout << "Details of room1:\n";
    room1.displayDetails();

    // Calculate and display the cost of staying in the room
    cout << "Cost of staying in room1: $" << room1.calculateCost() << endl;

    // Create a Service object
    Service service1(102, "Laundry", false, 0, 2, 15.0, 20.0);

    // Display details of the service
    cout << "\nDetails of service1:\n";
    service1.displayDetails();

    // Calculate and display the cost of the service
    cout << "Cost of using service1: $" << service1.calculateCost() << endl;

    return 0;

}
