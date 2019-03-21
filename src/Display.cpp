
#include "Display.h"

Display::Display(int width, int height)
    :screen(new Screen(width, height)), prevScreen(new Screen(width,height)) {
    showConsoleCursor(false);
}

Display::~Display() {
    delete screen;
    delete prevScreen;
}

void Display::display () {
    int color = 0;
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getWidth(); j++) {
            if (screen->get(j,i) != prevScreen->get(j,i)) {
                //move console cursor to the character to overwrite
                setCursorPosition(j,i);
                //set color
                int prevColor = color;
                color = getColor(screen->getFColor(j, i), screen->getBColor(j, i));
                if (prevColor != color)
                    setColor(color);
                //shenanigans
                if (glitch) {
                    std::cout << '\b' << color;///NEVER DELETE THIS ITS WONDERFUL
                }
                //if empty, print space instead
                if (screen->get(j, i) != 0)
                    std::cout << screen->get(j, i);
                else
                    std::cout << ' ';
            }
		}
	}
	swap(prevScreen,screen);
}

void Display::clear () {
	screen->clear();
}

void Display::setCursorPosition(int x, int y) {
    //std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(handle, coord);
}

void Display::showConsoleCursor(bool enabled) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = enabled;
    SetConsoleCursorInfo(handle, &cursorInfo);
}

void Display::flushInputBuffer() { //various attempts at clearing buffer
    //std::cin.clear();
	std::cin.ignore(255, '\n');
	//std::cin.sync();
	//std::cout << "a";
    //fflush(stdin);
    //FlushConsoleInputBuffer(handle);
    //std::cin.seekg (0, std::ios::end);
}

int Display::getColor(int fg, int bg) {
    if (bg < 0 || bg > 16)
        bg = defBColor;
    if (fg == -1)
        fg = defFColor;
    else if (fg < 0 || fg > 16)
        fg = bg;
    return bg*16 + fg;
}

void Display::setColor(int color) {
    SetConsoleTextAttribute(handle, color);
}

void Display::setColor(int fg, int bg) {
    setColor(getColor(fg,bg));
}

void Display::print(std::string str) {
    std::cout << str;
}

void Display::print(char c) {
    std::cout << c;
}

template <typename T>
void Display::swap (T& thing1, T& thing2) {
    T temp = thing1;
    thing1 = thing2;
    thing2 = temp;
}

Screen& Display::getScreen ()      { return *screen;             }
Screen** Display::getSafeScreen () { return &screen;             }
int Display::getWidth()            { return screen->getWidth();  }
int Display::getHeight()           { return screen->getHeight(); }
void Display::setDefFColor(int color) { defFColor = color; }
void Display::setDefBColor(int color) { defBColor = color; }
void Display::setGlitch (bool b)      { glitch = b;        }

void Display::draw (Screen &scr, int x, int y) {
	screen->draw(scr, x, y, true);
}

void Display::set (int x, int y, char c) {
	screen->set(x, y, c);
}
