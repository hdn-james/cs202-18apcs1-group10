#include "Utilities.h"

#include <sstream>
#include <vector>
#include <Windows.h>

using namespace std;

static const Utilities::TableChar charDouble{char(187), char(201), char(188), char(200), char(205), char(203), char(202), char(186), char(204), char(185), char(206)};

static const Utilities::TableChar charSingle{char(191), char(218), char(217), char(192), char(196), char(194), char(193), char(179), char(195), char(180), char(197)};

static const Utilities::PixelTableChar charPixel{char(223), char(220), char(221), char(222), char(219), char(254)};

string Utilities::vk2Str(unsigned int key)
{
    switch (key)
    {
    case 0x26:
        return "arrow_up";
    case 0x28:
        return "arrow_down";
    case 0x25:
        return "arrow_left";
    case 0x27:
        return "arrow_right";
    case 0x20:
        return "space";
    case 0x1B:
        return "esc";
    case 0x0D:
        return "enter";
    case 0x13:
        return "pause";
    default:
        if ((0x41 <= key && key <= 0x5A) ||
            (0x30 <= key && key <= 0x39) ||
            (0x60 <= key && key <= 0x6F))
        {
            std::string res(1, char(MapVirtualKeyA(key, MAPVK_VK_TO_CHAR)));
            return res;
        }
        else
            return "none";
    }
}

string Utilities::whitespace(int count)
{
    if (count >= 0)
    {
        string res(count, ' ');
        return res;
    }
    else
        return "whitespace error";
}

Utilities::TableChar Utilities::getChars(StrokeType type)
{
    if (type == Utilities::DOUBLE)
        return charDouble;
    else
        return charSingle;
}

Utilities::PixelTableChar Utilities::getPixelChars() { return charPixel; }

int Utilities::cramp(int val, int start, int end)
{
    if (val < start)
        val = start;
    if (val >= end)
        val = end - 1;
    return val;
}

int Utilities::color(int forgC, int backC)
{
    return ((backC & 0x0F) << 4) + (forgC & 0x0F);
}

string Utilities::alignText(TextAlign align, string str, int width)
{
    bool hasLineBreak = false;
    if (str.length() > 0 && str[str.length() - 1] == '\n')
    {
        str = str.substr(0, str.length() - 1);
        hasLineBreak = true;
    }

    switch (align)
    {
    case TextAlign::left:
        str = str.substr(0, width);
        str += whitespace(width - str.length());
        break;

    case TextAlign::right:
        str = str.substr(str.length() - width);
        str = whitespace(width - str.length()) + str;
        break;

    case TextAlign::center:
        bool left = true;
        while (str.length() != width)
        {
            if (str.length() > width)
                str = left ? str.substr(1, str.length()) : str.substr(0, str.length() - 1);
            else
                str = left ? " " + str : str + " ";

            left = !left;
        }
        break;
    }
    if (hasLineBreak)
        return str + '\n';
    else
        return str;
}

string Utilities::textWithBorder(TextWithBorderOptions option, initializer_list<string> args)
{
    int i = 0;
    int maxWidth = option.minWidth;
    int maxHeight = option.minHeight;

    std::string s;
    std::vector<std::string> ss;
    for (std::string arg : args)
    {
        if (arg.length() > maxWidth)
            maxWidth = arg.length();

        ss.push_back(arg);
    }

    if (ss.size() > maxHeight)
        maxHeight = ss.size();

    PixelTableChar chars = getPixelChars();
    std::stringstream strstream;

    strstream << chars.full;
	for (i = 1; i < maxWidth + 1; i++)
		strstream << chars.top;
    strstream << chars.full << "\n";

    for (i = 0; i < maxHeight; i++)
    {
        strstream << chars.full;
        if (i < ss.size())
            strstream << alignText(option.align, ss[i], maxWidth);
        else
            strstream << whitespace(maxWidth);
        strstream << chars.full << "\n";
    }
    strstream << chars.full;
    for (i = 1; i < maxWidth + 1; i++)
        strstream << chars.bottom;
    strstream << chars.full;

    return strstream.str();
}

string stringReplace(string src, string replaceThis, string withThis)
{
    int pos, last = 0;
    string res = src;
    while ((pos = src.find(replaceThis, last)) != string::npos)
    {
        last = pos + 1;
        res.replace(pos, replaceThis.length(), withThis);
    }
    return res;
}