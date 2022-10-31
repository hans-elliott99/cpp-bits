#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>

// Main functions
void run();
void changeDirection(char key);
void initMap();
void update();
void clearScreen();
void printMap();
void generateFood();
char getMapValue(int value);
void move(int dx, int dy);
int changeSpeed();


/* Helpers */
// Determines whether to show blinking console cursor 
void showCursor(bool show)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Calculates time elapsed from initialization
class ElapsedTime
{
private:
    std::chrono::steady_clock::time_point m_begin = std::chrono::steady_clock::now();
public:
    int elapsed()
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        int et = std::chrono::duration_cast<std::chrono::seconds>(now - m_begin).count();
        return et;
    }
};

void printTitle()
{
    std::cout << "    __                          ___   " << std::endl;
    std::cout << "   /     |\\   |    /\\    |   / |    " << std::endl;
    std::cout << "   \\__   | \\  |   /__\\   |__/  |___" << std::endl;
    std::cout << "      \\  |  \\ |  /    \\  |  \\  |  " << std::endl;
    std::cout << "   ___/  |   \\| /      \\ |   \\ |___" << std::endl;
}


// Map dims
const int mapwidth = 20;
const int mapheight = 20;
const int size = mapwidth * mapheight;

// Map tiles
int map[size];

// Snake position
int headxpos;
int headypos;
int direction;

// Snake's food quantity (how long is its body)
int food = 4;

// Speed of the game
enum Speed {a = 350, b = 250, c = 100, d = 0};
int gamespeed = 1;

// Game status
bool running;


// Execute Game
int main()
{   
    run();
    return 0;
}

// Run Game
void run()
{
    //color console text
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);

    // Hide console cursor and initialize elapsed time tracker
    showCursor(false);
    ElapsedTime time;

    // Initialize map & game
    initMap();
    running = true;
    while (running)
    {
        // If a key is pressed, change direction to that key character
        if (kbhit()) changeDirection(getch());

        // Update Map
        update();
        // Clear screen
        clearScreen();
        // Print updated map
        printTitle();
        printMap();
        std::cout << "Score: " << food << " | Time: " << time.elapsed()
        << "s | Difficulty: " << gamespeed << "/4" << std::endl;
        // delay 0.x seconds
        Sleep(changeSpeed());
    }
    // End game
    std::cout << "Game Over. " << std::endl;

    SetConsoleTextAttribute(hConsole, 15); //set back to black background and white text
    // stop console from closing
    std::cin.get();
}



// Change direction of snake
void changeDirection(char key)
{
    switch(key)
    {
    case 'w':
        if (direction != 2) direction = 0; //if(direction !=2 )... so the snake cannot track back overitself
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

// Update map
void update()
{
    // Move in direction indicated
    switch(direction)
    {
    case 0: move(-1, 0); // key = w
        break;
    case 1: move(0, 1);  // key = d
        break;
    case 2: move(1, 0);  // key = s
        break;
    case 3: move(0, -1); // key = a
        break;
    }

    // Reduce snake values on map by 1
    for (int i=0; i < size; i++)
    {
        //where we have snake values, decrement.
        if (map[i] > 0) map[i]--;
    }
}

// Move snake
void move(int dx, int dy)
{
    //determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // check for food at new position
    if (map[newx + newy*mapwidth] == -2)
    {  
        // Increase body length, since more food.
        food++;
        // Generate next food
        generateFood();
    }
    // check if the location is free, otherwise it is a wall or the snake
    else if (map[newx + newy*mapwidth] != 0)
    {
        running = false; //end game
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos*mapwidth] = food + 1;
}

int changeSpeed()
{
    
    if (food <= 10) 
    {
        return Speed::a;
    }
    else if (food > 10 & food <= 30) 
    {   
        gamespeed = 2;
        return Speed::b;
    }
    else if (food > 30 & food <= 50) 
    {
        gamespeed = 3;
        return Speed::c;
    }
    else 
    {
        gamespeed = 4;
        return Speed::d;
    }
}

// print map to console
void printMap()
{
    for (int x=0; x < mapwidth; ++x) {
        for (int y=0; y<mapheight; ++y) {
            //Print value at current x,y location
            std::cout << getMapValue(map[x + y * mapwidth]) << ' ';
        }
        //start new line
        std::cout << std::endl;
    }
}

void initMap()
{
    // Initialize snake-head in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    // Place walls at top and bottom
    for (int x = 0; x < mapwidth; x++)
    {
        map[x] = -1;
        map[x + (mapheight -1) * mapwidth] = -1; 
    }

    // Place left and right walls
    for (int y = 0; y < mapheight; y++)
    {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generate food
    generateFood();
}

void generateFood()
{
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y coords within map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        // If location is not free, try again 
        // (If there is any value other than 0 at the (x,y) we re-generate)
    } while (map[x + y*mapwidth] != 0);

    // Place food
    map[x + y*mapwidth] = -2;
}

// Maps from map-value to the character to display on screen. 
char getMapValue(int value)
{
    // Return snake-bodypart
    if (value > 0) return 'o';

    switch (value)
    {
    case -1: 
        return 'X'; //wall
    case -2: 
        return '$'; //food
    }
    return ' ';
}


void clearScreen()
{
    system("cls");
}