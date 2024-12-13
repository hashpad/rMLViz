#pragma once
#include "State.h"
#include <memory>

class Context {
private:
    std::unique_ptr<State> state;

public:
    Context(std::unique_ptr<State> starting_state);
    State& get_state();
    void set_state(std::unique_ptr<State> new_state);
    void update();
    void draw();
};
