#ifndef __GAMELOOP_SETTINGS__
#define __GAMELOOP_SETTINGS__


#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

class Settings
{
    using String = std::string;
    using Sstream = std::stringstream;
    using Vec_c = std::vector<char>;

private:
    String user_filename = "conf/Settings.conf";
    String default_filename = "conf/Default_Settings.conf";

    std::unordered_map<String, String> user_map;

    std::unordered_map<String, std::vector<String>> default_map;

    bool read_from_file(const char* db, Sstream& ss);

    Settings& construct_values(std::vector<std::vector<Vec_c>>& vvvc, const Sstream& ss);

    Settings& parse_values(const std::vector<std::vector<Vec_c>>& vvvc, bool is_default);

    Settings& test_option_validity();

    Settings& set_init_constants();

    template<typename OUT_TYPE, typename IN_TYPE>
    void split(std::vector<std::vector<OUT_TYPE>>& output_vec, IN_TYPE to_split, char delim, bool add_null = true)
    {
        Sstream iss((char*) to_split);
        String temp_str;
        std::vector<OUT_TYPE> temp_vec;

        while (std::getline(iss, temp_str, delim))
        {
            str_to_vec(temp_str, temp_vec, true, add_null);
            output_vec.push_back(temp_vec);
        }
    }

    template<typename IN_TYPE>
    std::vector<Vec_c> split(IN_TYPE to_split, char delim)
    {
        std::vector<Vec_c> output_vec;
        split(output_vec, to_split, delim);

        return output_vec;
    }

    template<typename T>
    void str_to_vec(String& str, std::vector<T>& vec, bool zero_mem = true, bool add_null = true)
    {
        vec.resize(str.size() + 1);
        vec = std::move(
            std::vector<T>{
                str.begin(),
                str.end()
            }
        );
        if (add_null)
            vec.push_back('\0');

        if (zero_mem)
        {
            // sodium_memzero(
                // const_cast<void*>(reinterpret_cast<const void*>(str.c_str())), str.size()
            // );
        }
    }

public:
    Settings();

    ~Settings();

    Settings& build();

    const String& get(const String& key) const;

    bool is_default(const String& key);

};

#endif
