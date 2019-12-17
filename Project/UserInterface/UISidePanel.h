#ifndef UISIDEPANEL_H
#define UISIDEPANEL_H

#include "UI.h"

#define HISTORY_SIZE 5

class UISidePanel : public UI
{
private:
    std::string _info;
    static UISidePanel *_instance;
    UISidePanel();

public:
    static UISidePanel *getInstance();
    ~UISidePanel();

    void setInfo(std::string);
    void writeHeader(short, std::string, short attr = 15);
    void writeInfo(short, short, std::string, int);
    void clsInfo();
    void writeInstruct(short, short, std::string, int);
    void clsInstruct();

    bool onKeyPressed(unsigned short);
    void onButtonClick(int){};
    void onButtonHover(int){};

    void draw();
};

#endif // !UISIDEPANEL_H