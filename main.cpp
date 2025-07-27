#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base Ride class
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double calculateFare() const = 0;
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID
             << ", From: " << pickupLocation
             << ", To: " << dropoffLocation
             << ", Distance: " << distance << " miles\n";
    }

    virtual ~Ride() = default;
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double calculateFare() const override {
        return distance * 1.5;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Standard, Fare: $" << calculateFare() << "\n";
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double calculateFare() const override {
        return distance * 2.5;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Premium, Fare: $" << calculateFare() << "\n";
    }
};

// Driver class
class Driver {
private:
    int driverID;
    string name;
    float rating;
    vector<shared_ptr<Ride>> assignedRides;

public:
    Driver(int id, string name, float rating)
        : driverID(id), name(name), rating(rating) {}

    void addRide(shared_ptr<Ride> ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\nDriver: " << name << " (ID: " << driverID << ", Rating: " << rating << ")\n";
        cout << "Assigned Rides:\n";
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<shared_ptr<Ride>> requestedRides;

public:
    Rider(int id, string name) : riderID(id), name(name) {}

    void requestRide(shared_ptr<Ride> ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "\nRider: " << name << " (ID: " << riderID << ")\n";
        cout << "Requested Rides:\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

int main() {
    shared_ptr<Ride> ride1 = make_shared<StandardRide>(1, "Downtown", "Airport", 10.5);
    shared_ptr<Ride> ride2 = make_shared<PremiumRide>(2, "Mall", "University", 8.0);

    Driver driver(101, "Alice", 4.8);
    Rider rider(201, "Bob");

    driver.addRide(ride1);
    driver.addRide(ride2);

    rider.requestRide(ride1);
    rider.requestRide(ride2);

    cout << "\nAll Ride Details (Polymorphic Calls):\n";
    vector<shared_ptr<Ride>> rides = {ride1, ride2};
    for (const auto& r : rides) {
        r->rideDetails();
    }

    driver.getDriverInfo();
    rider.viewRides();

    return 0;
}