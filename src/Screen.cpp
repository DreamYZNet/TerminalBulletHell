
#include "Screen.h"

Screen::Screen(const int w, const int h, int p, char defChar, int fg, int bg)
    :width(w), height(h), screen(h, std::vector<char>(w, defChar))
    ,fColor(h, std::vector<int>(w, fg)), bColor(h, std::vector<int>(w, bg)), priority(h, std::vector<int>(w, p)){}

void Screen::draw (Screen &from, int x, int y, bool ignorePriority) {
	for (int i = 0; i < from.getHeight(); i++) {
		for (int j = 0; j < from.getWidth(); j++) {
            if (j+x < width && j+x >= 0 && i+y < height && i+y >= 0) {
                //if TO is transparent, or FROM is visible but also priority is higher, then draw over (transp to transp ok)
                if (isFTransparent(j,i) || !from.isFTransparent(j,i) && (ignorePriority || from.getPriority(j, i) >= getPriority(j, i))) {
                    if (from.get(j, i) != 0){
                        screen[i+y][j+x] = from.get(j, i);
                    }
                    if (from.getFColor(j, i) != -2)
                        fColor[i+y][j+x] = from.getFColor(j, i);
                    priority[i+y][j+x] = from.getPriority(j, i);
                }
                if (!from.isBTransparent(j,i) && (isBTransparent(j,i) || ignorePriority || from.getPriority(j, i) >= getPriority(j, i))) {
                    bColor[i+y][j+x] = from.getBColor(j, i);
                    priority[i+y][j+x] = from.getPriority(j, i);
                }
            }
		}
	}
}

void Screen::clear (){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			screen[i][j] = ' ';
			fColor[i][j] = -1;
			bColor[i][j] = -2;
			priority[i][j] = -1;
		}
	}
}

void Screen::display (){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << screen[i][j];
		}
		std::cout << std::endl;
	}
}

void Screen::fill (char c){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			screen[i][j] = c;
		}
	}
}
void Screen::fillFColor (int fg){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fColor[i][j] = fg;
		}
	}
}
void Screen::fillBColor (int bg){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			bColor[i][j] = bg;
		}
	}
}

int Screen::getHeight ()              { return height;         }
int Screen::getWidth ()               { return width;          }
char Screen::get(int x, int y)        { return screen[y][x];   }
int Screen::getFColor(int x, int y)   { return fColor[y][x];   }
int Screen::getBColor(int x, int y)   { return bColor[y][x];   }
int Screen::getPriority(int x, int y) { return priority[y][x]; }

void Screen::setPriority(int p) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			priority[i][j] = p;
		}
	}
}
bool Screen::isFTransparent(int x, int y) {
    if (screen[y][x] == 0 || fColor[y][x] == -2)
        return true;
    return false;
}
bool Screen::isBTransparent(int x, int y) {
    if (bColor[y][x] == -2)
        return true;
    return false;
}
bool Screen::isTransparent(int x, int y) {
    if (isBTransparent(x,y) && isFTransparent(x,y))
        return true;
    return false;
}
void Screen::set(int x, int y, char value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (screen[y][x] != value) {
            screen[y][x] = value;
        }
    }
}
void Screen::set(int x, int y, char value, int fg) { //inneficient, x y boundaries checked multiple times
    set(x, y, value);
    setFColor(x, y, fg);
}
void Screen::set(int x, int y, char value, int fg, int bg) {
    set(x, y, value, fg);
    setBColor(x, y, bg);
}
void Screen::setFColor(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (fColor[y][x] != value) {
            fColor[y][x] = value;
        }
    }
}
void Screen::setBColor(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (bColor[y][x] != value) {
            bColor[y][x] = value;
        }
    }
}
