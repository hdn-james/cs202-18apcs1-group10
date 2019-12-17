#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <Windows.h>

class Config
{
private:
    static WORD **_configs;

public:
    static int const config_count;
    static std::string const string_config[];
    static const char delimiter = '=';
    static const char seperator = ',';
    enum Key
    {
        undefine,
        size,
        key_up,
        key_down,
        key_left,
        key_right,
        key_enter,
        key_pause,
        key_esc,
        key_load,
        key_save,
        key_mute,
        frame_length,
        console_width,
        console_height
    };

public:
    static WORD get(int key, int index = 0);
    static void set(int key, WORD value, int index = 0);

private:
    static void defaultConfig();
    static void parseConfig(std::string);

public:
    static void init();
    static void destroy();
    static void load(const char *);
    static void save(const char *);
    static WORD parseKey(WORD);
};

#endif // !CONFIG_H