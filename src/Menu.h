#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace ui {

enum OPTION_TYPE {
    RESUME,
    LINEAR_REGRESSION,
    NEURAL_NETWORK,
    QUIT,
};

inline std::map<OPTION_TYPE, std::string> OPTION_TYPE_STR {
    { RESUME, "RESUME" },
    { LINEAR_REGRESSION, "LINEAR_REGRESSION" },
    { NEURAL_NETWORK, "NEURAL_NETWORK" },
    { QUIT, "QUIT" },
};

class Option {
private:
    const OPTION_TYPE m_type;
    const std::string m_name;
    bool highlighted;

public:
    Option(OPTION_TYPE option, const std::string& name);
    bool operator==(const Option& other) const;

    const std::string& get_name() const;
    const OPTION_TYPE& get_type() const;
    bool is_highlighted() const;
    void highlight();
    void unhighlight();
};

class Menu {
private:
    std::vector<std::unique_ptr<Option>> m_options;
    std::string m_name;

    int get_idx_of_option(const Option& option) const;

public:
    Menu(const std::string& name);

    void add_option(const std::string& name, OPTION_TYPE type, bool highlighted);
    std::vector<Option*> get_options();
    Option* find_option_by_name(const std::string& name);
    Option* find_option_by_type(const OPTION_TYPE type);
    const Option& get_current_option() const;
    const Option& get_next_option() const;
    const Option& get_prev_option() const;
    void highlight_next_option();
    void highlight_prev_option();
    void unhighlight(const Option& option);
    void highlight(const Option& option);

    void select();

    const std::string&
    get_name() const;
    void draw(int x, int y, int font_size) const;
};

class MenuBuilder {
private:
    std::unique_ptr<Menu> m_menu;
    MenuBuilder(const std::string& name);

public:
    static MenuBuilder create_menu(const std::string& name);
    MenuBuilder& add_option(const std::string& name, OPTION_TYPE type, bool highlighted);
    std::unique_ptr<Menu> get();
};

// end namespace ui
};
