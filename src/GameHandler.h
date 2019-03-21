
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "Display.h"
#include "Stage.h"
#include "Player.h"
#include "Boss.h"
#include "PlayerController.h"
#include "PhysicsMath.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

class GameHandler {

    public:
        GameHandler(GameHandler**);
        void update();
        void collide();
        void draw();
        void load();
        void save();
        void initSave();
        void kys();
        void chooseSpell();
        void updateSpell();

    private:
        Display display; //keep order for init list
        Stage stage;
        Player player;
        Boss boss;
        PlayerController p1;
        GameHandler** existence = nullptr;
        int lives = 7;
        int spell = 1;
        int frame = 0;
        int highScore = 0;
        std::string playerName = "";
        bool playerHit = false;

        bool isColliding(Object& obj1, Object& obj2);
        void gameover();
        std::string textField (int max = 20, std::string text = "");

};

#endif // GAMEHANDLER_H
