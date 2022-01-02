#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Tesla {
    protected:
        string _model;
    public:
        Tesla() {
            _model = "Unknown model";
        }
        virtual string getDescription() {
            return _model;
        }
        virtual double getCost() = 0;
        virtual ~Tesla() {
            cout << "delete Tesla" << endl;
        }
};

class OptionsDecorator : public Tesla //Decorator Base class
{
    public:
        virtual string getDescription() = 0;
        virtual double getCost() = 0;
        virtual ~OptionsDecorator()
        {
            cout<<"~OptionsDecorator()\n";
        }
};

class ModelY : public Tesla {
    public:
        ModelY() {
            _model = "Model Y";
        }
        virtual double getCost() {
            return 58990.0;
        }
        virtual ~ModelY() {
            cout << "delete model Y" << endl;
        }
};

class Performance : public OptionsDecorator {
    public:
    unique_ptr<Tesla> _tesla;
    Performance(unique_ptr<Tesla> tesla) {
        this->_tesla = move(tesla);
    }
    string getDescription() {
        return _tesla->getDescription() + ", Performance";
    }
    double getCost() {
        return 5000.0 + _tesla->getCost();
    }
    virtual ~Performance() {
        cout << "remove performance" << endl;
    }
};

class FSD : public OptionsDecorator {
    public:
    unique_ptr<Tesla> _tesla;
    FSD(unique_ptr<Tesla> tesla) {
        this->_tesla = move(tesla);
    }
    string getDescription() {
        return _tesla->getDescription() + ", FSD";
    }
    double getCost() {
        return 10000.0 + _tesla->getCost();
    }
    virtual ~FSD() {
        cout << "remove performance" << endl;
    }
};

class TowHitch : public OptionsDecorator {
    public:
    unique_ptr<Tesla> _tesla;
    TowHitch(unique_ptr<Tesla> tesla) {
        this->_tesla = move(tesla);
    }
    string getDescription() {
        return _tesla->getDescription() + ", tow hinch";
    }
    double getCost() {
        return 1000.0 + _tesla->getCost();
    }
    virtual ~TowHitch() {
        cout << "delele two hitch" << endl;
    }
};

int main() {
    unique_ptr<Tesla> tesla = make_unique<ModelY>();

    cout << "Base model of " << tesla->getDescription() << " costs $" << tesla->getCost() << endl;
    unique_ptr<Tesla> tesla1 = make_unique<Performance>(make_unique<ModelY>());
    cout << tesla1->getDescription() << " costs $" << tesla1->getCost() << endl;
    unique_ptr<Tesla> tesla2 = make_unique<FSD>(make_unique<ModelY>());
    cout << tesla2->getDescription() << " costs $" << tesla2->getCost() << endl;
    unique_ptr<Tesla> tesla3 = make_unique<TowHitch>(make_unique<ModelY>());
    cout << tesla3->getDescription() << " costs $" << tesla3->getCost() << endl;

    return 0;
}
