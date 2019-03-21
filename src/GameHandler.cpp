
#include "GameHandler.h"
using namespace std;

//resolutions: laptop:120x30 school:80x24
GameHandler::GameHandler(GameHandler** existence_): display(80, 24), stage(78, 22), boss(stage), player(stage), p1(player), existence(existence_) {
    chooseSpell();
    load();

	boss.setGX(stage.getWidth()/2-boss.getWidth()/2+1);
	boss.setGY(stage.getHeight()/2-boss.getHeight()/2+1);
	stage.addObject(boss);

	player.setGX(stage.getWidth()/2-player.getWidth()/2+1);
	player.setGY(stage.getHeight()-player.getHeight()-2);
	stage.addObject(player);

	boss.petY(-5);
	player.petY(1);

	display.display();
}

void GameHandler::update() {
    frame++;
    if (frame > highScore)
        highScore = frame;
    p1.update();
    stage.update();
    updateSpell();
    collide();
}

void GameHandler::updateSpell() {
    switch(spell) {
        case 1:{ //flower
            double s = 1;
            double bossWait = 1;
            int check = bossWait/s;
            if (check == 0 || frame % check == 0) {
                boss.shoot(new Bullet(1,1,(s*frame)*52,0.2*s,'O',13));
                boss.shoot(new Bullet(1,1,180-(s*frame)*52,0.2*s,'O',13));
            }
        }break;
        case 2:{ //spiral
            int bossWait = 15;
            int check = bossWait-(frame/400);
            if (check == 0 || frame % check == 0) {
                double spd = 0.04+(0.002*(frame/200));
                int a = frame*1;
                int x = PhysicsMath::getAngledX(a, 5)+1;
                int y = PhysicsMath::getAngledY(a, 4)+1;
                boss.shoot(new Bullet(x,y,a+90,spd,'#',9));
                int a2 = frame*1+120;
                int x2 = PhysicsMath::getAngledX(a2, 5)+1;
                int y2 = PhysicsMath::getAngledY(a2, 4)+1;
                boss.shoot(new Bullet(x2,y2,a2+90,spd,'#',9));
                int a3 = frame*1+240;
                int x3 = PhysicsMath::getAngledX(a3, 5)+1;
                int y3 = PhysicsMath::getAngledY(a3, 4)+1;
                boss.shoot(new Bullet(x3,y3,a3+90,spd,'#',9));
            }
            if ((500-frame/10) == 0 || frame % (500-frame/10) == 0) {
                int a = PhysicsMath::getAngle(boss.getGX(),boss.getGY(),player.getGX(),player.getGY());
                boss.shoot(new Bullet(-1,-1,a,0.04,'o',3,3,3));
            }
        }break;
        case 3:{ //spiral
            boss.petX(PhysicsMath::getRotateX((frame*2+90)*(frame/500.0+1), 5*(frame/500.0+1), 1*(frame/500.0+1)));
            boss.petY(PhysicsMath::getRotateY((frame*2+90)*(frame/500.0+1), 5*(frame/500.0+1), 1*(frame/500.0+1)));
            int bossWait = 20;
            int check = bossWait/(frame/500.0+1);//-(frame/200);
            if (check == 0 || frame % check == 0) {
                int a = PhysicsMath::getAngle(boss.getGX(),boss.getGY(),player.getGX(),player.getGY());
                boss.shoot(new Bullet(1,1,a,0.04*(1.005*(frame/500.0+1)),'$',14));
            }
        }break;
    }
}
//check collisions between player and various bullets
void GameHandler::collide() {
    std::vector<Object*> objects = stage.getObjects();
    bool gotHit = false;
    for (Object* obj : objects) {
        if (&player != obj && isColliding(player, *obj)) {
            gotHit = true;
            break;
        }
    }
    if (gotHit) {
        if (playerHit == false) {
            playerHit = true;
            lives--;
            display.setDefBColor(12);
            if (lives == 4) {
                display.getScreen().fillBColor(12);
            }else if (lives == 2) {
                display.setGlitch(true);
            }else if (lives == 0) {
                gameover();
            }
        }
    }else{
        playerHit = false;
        display.setDefBColor(0);
    }
}
bool GameHandler::isColliding(Object& obj1, Object& obj2) {
    if ((int)obj1.getGHX() <= (int)(obj2.getGHX()+obj2.getHWidth()-1) && (int)obj2.getGHX() <= (int)(obj1.getGHX()+obj1.getHWidth()-1)
            && (int)obj1.getGHY() <= (int)(obj2.getGHY()+obj2.getHHeight()-1) && (int)obj2.getGHY() <= (int)(obj1.getGHY()+obj1.getHHeight()-1)) {
        return true;
    }
    return false;
}

void GameHandler::draw() {
    Screen &screen = display.getScreen();
    screen.setPriority(-1);

    //draw borders and bg
    int width = stage.getWidth();
    int height = stage.getHeight();
	screen.set(0, 0, '+', 10);
	for (int i = 0; i < width; i++){
		screen.set(i+1, 0, '-', 10);
	}
	screen.set(width+1, 0, '+', 10);
	for (int i = 0; i < height; i++) {
		screen.set(0, i+1, '|', 10);
		for (int j = 0; j < width; j++) {
            screen.set(j+1, i+1, ' ', 8);
		}
		screen.set(width+1, i+1, '|', 10);
	}
	screen.set(0, height+1, '+', 10);
	for (int i = 0; i < width; i++){
		screen.set(i+1, height+1, '-', 10);
	}
	screen.set(width+1, height+1, '+', 10);

    //draw objects
	std::vector<Object*> &objects = stage.getObjects();
	for (Object *obj: objects) {
        screen.draw(obj->getGraphic(), 1+obj->getGX(), 1+obj->getGY());
	}

	//display
    display.display();

    display.setCursorPosition(0,display.getHeight());
    display.setColor(-1,-1);
    cout << "Lives: " << left << setw(2) << lives;
    cout << " Score: " << left << setw(5) << frame;
    cout << "  HighScore: " << left << setw(5) << highScore;
    cout << "  Name: " << left << setw(10) << playerName;
}

void GameHandler::load() {
    std::fstream fin;
    try{
        fin.open("score.dat", std::ios::in | std::ios::binary);
    }catch(...){
        return;
    }
    fin.read(reinterpret_cast<char *>(&highScore), sizeof(highScore));
    int length;
    fin.read(reinterpret_cast<char *>(&length), sizeof(length));
    char temp[length+1];
    fin.read(temp, length);
    temp[length] = 0;
    playerName = temp;
    fin.close();
}
void GameHandler::save() {
    std::fstream fin;
    try{
        fin.open("score.dat", std::ios::out | std::ios::binary);
    }catch(...){
        return;
    }
    fin.write(reinterpret_cast<char *>(&highScore), sizeof(highScore));
    int length = playerName.length();
    fin.write(reinterpret_cast<char *>(&length), sizeof(length));
    const char* temp = playerName.c_str();
    fin.write(temp, length);
    fin.close();
}
void GameHandler::initSave() {
    std::fstream fin;
    try{
        fin.open("score.dat", std::ios::out | std::ios::binary);
    }catch(...){
        return;
    }
    int score = 1000;
    string name = "HelloThere";
    fin.write(reinterpret_cast<char *>(&score), sizeof(score));
    int length = name.length();
    fin.write(reinterpret_cast<char *>(&length), sizeof(length));
    const char* temp = name.c_str();
    fin.write(temp, length);
    fin.close();
}

void GameHandler::gameover() {
    system("cls");
    display.setCursorPosition(0,0);
    cout << "GameOver...\n";
    display.flushInputBuffer();
    if (frame == highScore) {
        cout << "You reached a high score!\n\nEnter your name: ";
        display.showConsoleCursor(true);
        playerName = textField(10, playerName);
        display.showConsoleCursor(false);
        save();
    }else{
        system("pause");
    }
    kys();
}
//prompt for text
string GameHandler::textField (int max, string text) {//bugs abound
    cout << text;
    int length = text.length();
    char c = 0;
	while(c != 13) {
		c = getch();
		if (c == 8 && length > 0) { //backspace
            //text = text.substr(0, length-1);
            text.pop_back();
            cout << "\b \b";
            length--;
		}else if (c != 13 && length < max && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) { //not enter
			text += c;
			display.print(c);
			length++;
		}
	}
	return text;
}

void GameHandler::kys() {
    *existence = new GameHandler(existence);
    delete this;
    throw "GameHandler terminated. ";
}

void GameHandler::chooseSpell() {
    system("cls");
    display.setCursorPosition(0,0);
    cout << "Welcome to Danmaku Project!\n\nChoose spell: \n"
         << "1. Flower\n"
         << "2. Spiral\n"
         << "3. Spin";
    char c = 0;
    while(!(c >= '1' && c <= '3')) {
        c = getch();
    }
    spell = c - '0';
}


