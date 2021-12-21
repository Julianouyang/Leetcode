//
//  main.cpp
//
//  Created by Julian Ouyang on 8/25/21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <unordered_map>
using namespace std;

enum Seat {Economy, Premium, Business};
enum AirlineName {United, Delta, Southwest, LuigiAir};

unordered_map<string, Seat> seats {
    {"Economy", Economy},
    {"Premium", Premium},
    {"Business", Business}
};

unordered_map<string, AirlineName> airlines {
    {"United", United},
    {"Delta", Delta},
    {"Southwest", Southwest},
    {"LuigiAir", LuigiAir}
};

class Airline_Ticket {
public:
    virtual ~Airline_Ticket() {};
    virtual void setDistance(float distance) {
        _distance = distance;
    }
    virtual void setSeat(Seat seat) {
        _seat = seat;
    }
    virtual float getTotalCost() = 0;
private:
protected:
    float _distance = 0;
    Seat _seat;
    virtual float getOperatingCost(Seat type) {
        float cost = 0.0;
        switch (type) {
            case (Economy):
                cost = 0.0;
                break;
            case (Premium):
                cost = 25.0;
                break;
            case (Business):
                cost = 50.0 + _distance * 0.25;
                break;
        }
        return cost;
    }
};

class United_Ticket : public Airline_Ticket {
public:
    virtual ~United_Ticket() {};
    virtual float getTotalCost() {
        float extra = _seat == Premium ? 0.1 : 0;
        float opCost = getOperatingCost(_seat);
        return opCost + (0.75 + extra) * _distance;
    }
private:
};

class Delta_Ticket : public Airline_Ticket {
public:
    virtual ~Delta_Ticket() {};
    virtual float getTotalCost() {
        float opCost = getOperatingCost(_seat);
        return opCost + 0.5 * _distance;
    }
private:
};

class Southwest_Ticket : public Airline_Ticket {
public:
    virtual ~Southwest_Ticket() {};
    virtual float getTotalCost() {
        return 1.0 * _distance;
    }
private:
};

class LuigiAir_Ticket : public Airline_Ticket {
public:
    virtual ~LuigiAir_Ticket() {};
    virtual float getTotalCost() {
        float opCost = getOperatingCost(_seat);
        return 100.0 > 2 * opCost ? 100 : 2 * opCost;
    }
private:
};

class TicketProcessor {
public:
    static unique_ptr<Airline_Ticket> createTicket(AirlineName airlineType) {
        switch (airlineType) {
            case United:
                return make_unique<United_Ticket>();
            case Delta:
                return make_unique<Delta_Ticket>();
            case Southwest:
                return make_unique<Southwest_Ticket>();
            case LuigiAir:
                return make_unique<LuigiAir_Ticket>();
            default:
                return nullptr;
        }
    }
};

vector<float> parseInput(vector<string>& input) {
    vector<float> res;
    for (auto s : input) {
        vector<string> info;
        stringstream ss (s);
        string token;
        while (getline(ss, token, ' ')) {
            info.push_back(token);
        }
        assert (info.size() == 3);
//        assert (seats.count(info[2]) > 0);

        unique_ptr<Airline_Ticket> ticket = TicketProcessor::createTicket(airlines[info[0]]);
        ticket->setDistance(stof(info[1]));
        ticket->setSeat(seats[info[2]]);
        res.push_back(ticket->getTotalCost());
    }
    return res;
}

int main(int argc, const char * argv[]) {
//    ofstream myfile;
//    myfile.open();
    vector<string> input{
        "United 150.0 Premium",
        "Delta 60.0 Business",
        "Southwest 1000.0 Economy",
        "LuigiAir 50.0 Business"
    };
    vector<float> costs = parseInput(input);
    for (int i = 0; i < costs.size(); i++) {
        cout << costs[i] << endl;
    }
    return 0;
}

