#ifndef UIPOPUP_H
#define UIPOPUP_H

#define popup_width 48
#define popup_height 12

#include <string>

#include "UIButton.h"

class UIPopUp : public UI
{
private:
    enum PopUpType
    {
        alert,
        question,
        confirm,
        prompt
    };

    bool _done;
    bool _donePrompt = false;
    void *_result;
    PopUpType _type;
    std::string _msg;
    std::vector<UIButton> _buttons;
    int _hoveredButton = 0;

    UIPopUp(short x, short y, std::string msg, PopUpType type);
    ~UIPopUp();

    void drawBorder(int, int, int, int, int);

public:
    static void Alert(short, short, std::string);
    static bool Question(short, short, std::string);
    static bool Confirm(short, short, std::string);
    static std::string Prompt(short, short, std::string);

    void draw();
    bool onKeyPressed(unsigned short);
    void onButtonPressed(int);
};

#endif // !POPUP_H
