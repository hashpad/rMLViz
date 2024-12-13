#include "Menu.h"
#include "raylib.h"
#include <algorithm>
#include <csignal>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>

ui::Option::Option(OPTION_TYPE option, const std::string& name)
    : m_type(option)
    , m_name(name)
    , highlighted(false) { };

bool ui::Option::operator==(const Option& other) const
{
    return this->get_type() == other.get_type();
}
const std::string& ui::Option::get_name() const
{
    return this->m_name;
};
const ui::OPTION_TYPE& ui::Option::get_type() const
{
    return this->m_type;
}

bool ui::Option::is_highlighted() const
{
    return this->highlighted;
}
void ui::Option::highlight()
{
    this->highlighted = true;
}

void ui::Option::unhighlight()
{
    this->highlighted = false;
}

ui::Menu::Menu(const std::string& name)
{
    this->m_name = name;
    this->m_options = std::vector<std::unique_ptr<Option>> {};
}
void ui::Menu::add_option(const std::string& name, ui::OPTION_TYPE type, bool highlighted)
{
    if (this->find_option_by_name(name)) {
        std::cerr << "Warning: Option '" << name << "' already exists in the menu!" << std::endl;
    }
    if (this->find_option_by_type(type)) {
        std::cerr << "Warning: Option '" << OPTION_TYPE_STR.at(type) << "' already exists in the menu!" << std::endl;
    }

    auto option = std::make_unique<Option>(type, name);
    if (highlighted)
        option->highlight();
    this->m_options.push_back(std::move(option));
};

std::vector<ui::Option*> ui::Menu::get_options()
{
    std::vector<Option*> options;
    for (auto& option : this->m_options) {
        options.push_back(option.get());
    }
    return options;
}
void ui::Menu::draw(int x, int y, int font_size) const
{
    DrawText(this->m_name.c_str(), x, y, font_size, BLACK);
    for (int i = 0; i < this->m_options.size(); ++i) {
        Option& opt = *this->m_options.at(i);
        Color c = opt.is_highlighted() ? RED : BLACK;
        DrawText(this->m_options.at(i)->get_name().c_str(), x + 10, y + (i + 1) * 40, font_size, c);
    }
}
ui::Option* ui::Menu::find_option_by_name(const std::string& name)
{
    for (auto& option : m_options) {
        if (option->get_name() == name) {
            return option.get();
        }
    }
    return nullptr;
}
ui::Option* ui::Menu::find_option_by_type(OPTION_TYPE type)
{
    for (auto& option : m_options) {
        if (option->get_type() == type) {
            return option.get();
        }
    }
    return nullptr;
}

const ui::Option& ui::Menu::get_current_option() const
{
    for (auto& option : this->m_options) {
        if (option->is_highlighted())
            return *option;
    }
    return *this->m_options[0];
}
const ui::Option& ui::Menu::get_prev_option() const
{
    int curr_idx = this->get_idx_of_option(this->get_current_option());
    int prev_idx = curr_idx == 0 ? this->m_options.size() - 1 : curr_idx - 1;
    return *this->m_options.at(prev_idx);
}
const ui::Option& ui::Menu::get_next_option() const
{
    int curr_idx = this->get_idx_of_option(this->get_current_option());
    int next_idx = curr_idx == this->m_options.size() - 1 ? 0 : curr_idx + 1;
    return *this->m_options.at(next_idx);
}
void ui::Menu::highlight_next_option()
{
    const Option& curr_option = this->get_current_option();
    this->highlight(this->get_next_option());
    this->unhighlight(curr_option);
}
void ui::Menu::highlight_prev_option()
{
    const Option& curr_option = this->get_current_option();
    this->highlight(this->get_prev_option());
    this->unhighlight(curr_option);
}
void ui::Menu::unhighlight(const ui::Option& option)
{
    int count_highlighted = std::count_if(this->m_options.begin(), this->m_options.end(), [](const std::unique_ptr<ui::Option>& option) {
        return option->is_highlighted();
    });
    if (count_highlighted == 1) {
        std::cerr << "Warning: unhighlighting last option, please select something else before unselecting, skipping..." << std::endl;
        return;
    }
    this->m_options.at(this->get_idx_of_option(option))->unhighlight();
}
void ui::Menu::highlight(const ui::Option& option)
{
    this->m_options.at(this->get_idx_of_option(option))->highlight();
}
const std::string& ui::Menu::get_name() const
{
    return this->m_name;
}
void ui::Menu::select()
{
}

ui::MenuBuilder::MenuBuilder(const std::string& name)
    : m_menu(std::make_unique<Menu>(name)) { };

ui::MenuBuilder ui::MenuBuilder::create_menu(const std::string& name)
{
    return MenuBuilder(name);
};
ui::MenuBuilder& ui::MenuBuilder::add_option(const std::string& name, OPTION_TYPE type, bool highlighted)
{
    this->m_menu->add_option(name, type, highlighted);
    return *this;
};
std::unique_ptr<ui::Menu> ui::MenuBuilder::get()
{
    return std::move(this->m_menu);
}

int ui::Menu::get_idx_of_option(const ui::Option& option) const
{
    auto it_for_curr = std::find_if(this->m_options.begin(), this->m_options.end(), [&option](const std::unique_ptr<Option>& _option) {
        return *_option == option;
    });
    return std::distance(this->m_options.begin(), it_for_curr);
}
