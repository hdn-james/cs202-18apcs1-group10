#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <ctime>

namespace Utilities
{
std::string vk2Str(unsigned int);
std::string whitespace(int);
int cramp(int, int, int);

struct TableChar
{
    char topRight, topLeft, bottomRight, bottomLeft,
        horizontal, topSeparation, bottomSeparation,
        vertical, leftSeparation, rightSeparation,
        centreSeparation;
};

struct PixelTableChar
{
    char top, bottom, left, right, full, center;
};

enum StrokeType
{
    SINGLE,
    DOUBLE,
};

TableChar getChars(StrokeType);

PixelTableChar getPixelChars();

enum Color
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
};
int color(int, int);

enum TextAlign
{
    left,
    right,
    center
};
std::string alignText(TextAlign, std::string, int);

struct TextWithBorderOptions
{
    int minWidth = 0, minHeight = 0;
    StrokeType type = StrokeType::DOUBLE;
    TextAlign align = TextAlign::center;
};
std::string textWithBorder(TextWithBorderOptions, std::initializer_list<std::string>);

template <typename... Arg>
std::string textWithBorder(TextWithBorderOptions option, Arg... ps)
{
    return textWithBorder(option, {ps...});
}

std::string stringReplace(std::string, std::string, std::string);
}; // namespace Utilities

#endif // !Utilities_H