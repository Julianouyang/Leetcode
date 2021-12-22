#include <iostream>
#include <memory>

using namespace std;

class Pizza {
public:
    void setDough(const string& dough) {
        _dough = dough;
    }
    void setSauce(const string& sauce) {
        _sauce = sauce;
    }
    void setTopping(const string& topping) {
        _topping = topping;
    }
    void open() const {
        cout << "The pizza have " <<
        _dough << " dough, " <<
        _sauce << " sauce, " <<
        _topping << " topping" << endl;
    }
private:
    string _dough;
    string _sauce;
    string _topping;
};

class PizzaBuilder {
public:
    virtual ~PizzaBuilder() = default;
    void createNewPizza() {
        _pizza = make_unique<Pizza>();
    }
    Pizza* getPizza() {
        return _pizza.release();
    }
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
protected:
    unique_ptr<Pizza> _pizza;
};

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    ~HawaiianPizzaBuilder() override = default;
    void buildDough() override {
        _pizza->setDough("cross");
    }
    void buildSauce() override {
        _pizza->setSauce("mild");
    }
    void buildTopping() override {
        _pizza->setTopping("ham+pineapple");
    }
};

class SpicyPizzaBuilder : public PizzaBuilder {
public:
    ~SpicyPizzaBuilder() override = default;
    void buildDough() override {
        _pizza->setDough("pan baked");
    }
    void buildSauce() override {
        _pizza->setSauce("hot");
    }
    void buildTopping() override {
        _pizza->setTopping("pepperoni+salami");
    }
};

class Cook {
public:
    void openPizza() const {
        _pizzaBuilder->getPizza()->open();
    }
    void createPizza(PizzaBuilder* pizzaBuilder) {
        _pizzaBuilder = pizzaBuilder;
        _pizzaBuilder->createNewPizza();
        _pizzaBuilder->buildDough();
        _pizzaBuilder->buildSauce();
        _pizzaBuilder->buildTopping();
    }
private:
    PizzaBuilder* _pizzaBuilder;
};

int main(){
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    cook.createPizza(&hawaiianPizzaBuilder);
    cook.openPizza();
}
