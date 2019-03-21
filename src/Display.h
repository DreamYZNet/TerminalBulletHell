
#ifndef DISPLAY_H
#define DISPLAY_H

#include "Screen.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>

class Display {

	public:
		Display(int width, int height);
		~Display();

        //print the display onto the console window
		void display ();
		//clear the buffered display
		void clear ();
        void setCursorPosition(int x, int y); //in console window
        void showConsoleCursor(bool enabled); //set visibility of console cursor
        void setColor(int color);
        void setColor(int fg, int bg);
        void flushInputBuffer();
        void print(std::string);
        void print(char);
        template <typename T>
        void swap(T&,T&);

		Screen& getScreen ();
		Screen** getSafeScreen ();
		int getWidth();
		int getHeight();
        void setDefFColor(int color);
        void setDefBColor(int color);
		void setGlitch (bool b);

	private:
	    Screen *screen;
	    Screen *prevScreen;
	    int defFColor = 10;
	    int defBColor = 0;
	    bool glitch = false;
	    const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //static gives errors

        int getColor(int fg, int bg);

		void draw (Screen &drawFrom, int x, int y);
        void set (int x, int y, char c);

};

#endif
