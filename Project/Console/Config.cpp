#include "Config.h"

#include <conio.h>
#include <fstream>
#include <algorithm>

using namespace std;

string const Config::string_config[] = {
    "null",
    "size",
    "key_up",
    "key_down",
    "key_left",
    "key_right",
    "key_enter",
    "key_pause",
    "key_ecs",
    "key_load",
    "key_save",
    "key_mute",
    "frame_length",
    "console_width",
    "console_height",
};

int const Config::config_count = (sizeof(Config::string_config) / sizeof(Config::string_config[0]));

WORD **Config::_configs;

void Config::defaultConfig() // Virtual key code
{
    set(size, 15);
    set(console_width, 1260);
    set(console_height, 900);
    set(frame_length, 20);
    set(key_up, 0x26, 1);    // up arrow
    set(key_down, 0x28, 1);  // down arrow
    set(key_left, 0x25, 1);  // left arrow
    set(key_right, 0x27, 1); // right arrow
    set(key_enter, 0x0D, 1); // ENTER
    set(key_pause, 0x50, 0); // P
    set(key_pause, 0x13, 1); // Pause
    set(key_esc, 0x1B);      // ESC
    set(key_load, 84);       // T
    set(key_save, 76);       // L
    set(key_mute, 77);       // M
}

void Config::parseConfig(string s)
{
    size_t eq = s.find(delimiter);
    if (eq == string::npos)
        return;

    string token = s.substr(0, eq);
    string rest = s.substr(eq + 1, s.length());

    int index = -1;
    for (int i = 0; i < config_count; i++)
        if (token == string_config[i])
        {
            index = i;
            break;
        }

    if (index <= 0)
        return;

    int count = 0;
    size_t pos;
    size_t last = 0;
    while (count < 2 && (pos = rest.find_first_of(Config::seperator, last)) != string::npos)
    {
        _configs[index][count++] = stoi(rest.substr(last, pos - last));
        last = pos + 1;
    }
}

void Config::init()
{
    _configs = new WORD *[config_count];
    for (int i = 0; i < config_count; i++)
    {
        _configs[i] = new WORD[2];
        _configs[i][0] = 0;
        _configs[i][1] = 0;
    }
}

void Config::destroy()
{
    for (int i = 0; i < config_count; i++)
    {
        delete[] _configs[i];
    }
    delete[] _configs;
}

void Config::load(const char *path)
{

    if (!_configs)
        init();

    defaultConfig();

    ifstream fin(path);
    if (fin.is_open())
    {
        string line;
        while (getline(fin, line))
            parseConfig(line);
    }

    fin.close();
}

WORD Config::get(int key, int index)
{
    if (index > 1)
        index = 1;
    if (key >= Key::size)
        index = 0;

    return _configs[key][index];
}

void Config::set(int key, WORD value, int index)
{
    if (index < 0 || index > 1)
        index = 0;
    _configs[key][index] = value;
}

void Config::save(const char* path)
{
	ofstream f(path);
	if (f.is_open())
	{
		for (int i = 0; i < config_count; i++)
		{
			f << string_config[i] << delimiter;
			for (size_t j = 0; j < 2; j++)
				if (_configs[i][j])
					f << _configs[i][j] << seperator;
			f << '\n';
		}
	}
	f.close();
}

WORD Config::parseKey(WORD k)
{
	/**
	 * The list of pressable key go from UP to MUTE
	 */
	for (int i = Key::key_up; i <= Key::key_mute; i++)
		for (int j = 0; j < 2; j++)
			if (_configs[i][j] == k)
				return i;

	return k;
}