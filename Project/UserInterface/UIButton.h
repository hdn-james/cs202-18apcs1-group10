#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <string>

#include "UI.h"

class UIButton : public UI
{
private:
    std::string label;

public:
    UIButton(int x = 0, int y = 0, std::string label = "");

    void draw();
    bool onKeyPressed(unsigned short);
};

#endif // !UIBUTTON_H
