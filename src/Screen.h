
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <iostream>

class Screen{

    public:
        Screen(int w, int h, int priority = 0, char defChar = 0, int fgColor = -1, int bgColor = -2);

        //Draws from a screen on to the screen
        void draw (Screen &drawFrom, int x, int y, bool ignorePriority = false);
        void clear ();
        void display ();
        void fill (char c);
        void fillFColor (int fg);
        void fillBColor (int bg);

        int getHeight ();
        int getWidth ();
        char get(int x, int y);
        int getFColor(int x, int y);
        int getBColor(int x, int y);
        int getPriority(int x, int y);
        void set(int x, int y, char value);
        void set(int x, int y, char value, int fg);
        void set(int x, int y, char value, int fg, int bg);
        void setFColor(int x, int y, int value); //foreground
        void setBColor(int x, int y, int value); //background
        void setPriority(int p); //screen depth, bigger overwrites smaller and equal
        bool isFTransparent(int x, int y);
        bool isBTransparent(int x, int y);
        bool isTransparent(int x, int y);

    private:
        int width;
        int height;
        std::vector< std::vector<char> > screen;
        std::vector< std::vector<int> > fColor; //-1 = default; -2 = transparent
        std::vector< std::vector<int> > bColor;
        std::vector< std::vector<int> > priority;

};

#endif // SCREEN_H
