#include "../h/Settings.h"
// #include "../Includes/Helper.hpp"

using String = std::string;

Settings::Settings()
{
    // build();
}

Settings::~Settings()
{

}

bool Settings::read_from_file(const char* db, Sstream& ss)
{
    int success = true;
    std::fstream file;
    file.open(db, std::ios::in);

    if (!file.good())
        return false;

    // read file line by line
    String line;
    while (std::getline(file, line, '\n'))
    {
        // if line is empty
        if (line.empty())
            continue;

        // remove spaces
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // if comment
        if (line.at(0) == '#' || (line.at(0) == '/' && line.at(1) == '/'))
            continue;

        // if it doesn't contain an '=' or '#'
        if (line.find('=') == std::string::npos || line.find('#') == std::string::npos)
            ss << line << ',';
        else
            std::cout << "Settings error: Line \"" << line << "\" not valid\n";

    }
    String str = ss.str();

    // std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    ss = std::move(Sstream{str});

    if (ss.str().empty())
        success = false;

    file.close();

    return success;
}

Settings& Settings::construct_values(std::vector<std::vector<Vec_c>>& vvvc, const Sstream& ss)
{
    // split CSV to obtain vec<vec<char>>
    std::vector<Vec_c> components;
    split(components, ss.str().c_str(), ',');

    // for each
    for (const auto& i : components)
    {
        std::vector<Vec_c> c_no_eq;

        // split by '='
        split(c_no_eq, i.data(), '=');

        vvvc.push_back(c_no_eq);
    }

    return *this;
}

Settings& Settings::parse_values(const std::vector<std::vector<Vec_c>>& vvvc, bool is_default)
{
    for (const auto& pair : vvvc)
    {
        String key = pair[0].data();
        String val = pair[1].data();

        if (is_default)
            default_map[key].push_back(val);
        else
            user_map[key] = val;
    }

    return *this;
}

Settings& Settings::test_option_validity()
{
    std::vector<String> not_valid;
    for (auto& opt : user_map)
    {
        if (opt.first == "window_width" ||
                opt.first == "window_height" ||
                opt.first == "target_fps"
            )
            continue;

        if (std::find(
            default_map[opt.first].begin(),
            default_map[opt.first].end(),
            opt.second) == default_map[opt.first].end())
        {
            not_valid.push_back(opt.first);
            std::cout << "Settings: " << opt.first << " = " << opt.second << " not valid. Using default\n";
            opt.second = default_map[opt.first].at(0);
        }
    }

    for (const auto& inval : not_valid)
        user_map.erase(inval);

    return *this;
}

Settings& Settings::set_init_constants()
{
    return *this;
}

Settings& Settings::build()
{
    ////////////////////////////////
    // Construct Default Settings //
    ////////////////////////////////

    Sstream d_ss;
    if (!read_from_file(default_filename.c_str(), d_ss))
    {
        std::cout << "Settings: " << default_filename << " is empty\nExiting...\n";
        exit(1);
    }

    std::vector<std::vector<Vec_c>> d_vvvc;
    construct_values(d_vvvc, d_ss);

    parse_values(d_vvvc, true);

    /////////////////////////////
    // Construct User Settings //
    /////////////////////////////

    Sstream u_ss;
    if (!read_from_file(user_filename.c_str(), u_ss))
    {
        std::cout << "Settings: " << user_filename << " is empty. Using Defaults\n";
        for (const auto& opt : default_map)
            user_map[opt.first] = opt.second.at(0);
    }
    else
    {
        std::vector<std::vector<Vec_c>> u_vvvc;
        construct_values(u_vvvc, u_ss);

        parse_values(u_vvvc, false);

        test_option_validity();
        set_init_constants();
    }

    // for (const auto& i : user_map)
    // std::cout << i.first << " " << i.second << "\n";

    return *this;
}

const String& Settings::get(const String& key) const
{
    return user_map.at(key);
}

bool Settings::is_default(const String& key)
{
    // if (!default_map.count(key) && !user_map.count(key) &&
    //     default_map.at(key).at(0) == user_map.at(key))
    //     return true;

    return false;
}
