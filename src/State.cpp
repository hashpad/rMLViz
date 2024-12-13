#include "State.h"
#include "Menu.h"
#include "raylib.h"

MainMenuState::MainMenuState()
{
    this->menu = ui::MenuBuilder::create_menu("Main Menu")
                     .add_option("Linear Regression", ui::OPTION_TYPE::LINEAR_REGRESSION, true)
                     .add_option("Neural Network", ui::OPTION_TYPE::NEURAL_NETWORK, false)
                     .get();
};

std::unique_ptr<State> MainMenuState::update()
{
    if (IsKeyPressed(KEY_J) || IsKeyPressed(KEY_DOWN)) {
        this->menu->highlight_next_option();
    }
    if (IsKeyPressed(KEY_K) || IsKeyPressed(KEY_UP)) {
        this->menu->highlight_prev_option();
    }
    if (IsKeyPressed(KEY_ENTER)) {
        return std::make_unique<LinearRegressionState>();
    }
    return nullptr;
}
void MainMenuState::draw()
{

    this->menu->draw(200, 200, 40);
}

LinearRegressionState::LinearRegressionState() {
};

std::unique_ptr<State> LinearRegressionState::update()
{
    return nullptr;
}
void LinearRegressionState::draw()
{
    return;
}
