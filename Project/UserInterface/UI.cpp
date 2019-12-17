#include "UI.h"
#include "../Console/Utilities.h"

void UI::cls() { Console::cls(UI::_x, UI::_y, UI::_width, UI::_height); }

void UI::show() { UI::_show = true; }

void UI::hide() { UI::_show = false; }

int UI::width() const { return UI::_width; }

int UI::height() const { return UI::_height; }

bool UI::isShowing() const { return UI::_show; }

bool UI::isHovered() const { return UI::_hover; }

void UI::highlight() { UI::_hover = true; }

void UI::unHighlight() { UI::_hover = false; }
