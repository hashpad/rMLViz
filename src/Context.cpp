#include "Context.h"
#include <memory>

Context::Context(std::unique_ptr<State> starting_state)
    : state(std::move(starting_state))
{
}
State& Context::get_state()
{
    return *this->state;
}
void Context::set_state(std::unique_ptr<State> new_state)
{
    this->state = std::move(new_state);
}
void Context::update()
{
    auto new_state = this->state->update();
    if (new_state)
        this->state = std::move(new_state);
}
void Context::draw()
{
    this->state->draw();
}
