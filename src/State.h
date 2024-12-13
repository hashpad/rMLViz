#pragma once
#include "Menu.h"
class Context;
class State {
public:
    virtual std::unique_ptr<State> update() = 0;
    virtual void draw() = 0;
    virtual ~State() = default;
};

class MainMenuState : public State {
private:
    std::unique_ptr<ui::Menu> menu;

public:
    MainMenuState();
    virtual std::unique_ptr<State> update() override;
    virtual void draw() override;
};
class LinearRegressionState : public State {
public:
    LinearRegressionState();
    virtual std::unique_ptr<State> update() override;
    virtual void draw() override;
};
