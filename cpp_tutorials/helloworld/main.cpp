#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "header.h" //header file! -> Log()

// NOTES 
// '<<' = stream insertion operator (Data flows out)
// '>>' = stream extraction operator (data flows in)
// 'using namespace...' allows us to avoid calling the standard library every time, ex std::cout, std::string...

using namespace std;

// Hello World
int hello_world() 
{
    vector<string> msg{"Hello", "to", "C++", "from", "Hans", "!"};
    for (const string &word : msg)
    {
        cout << word << " ";
    }
    cout << endl;    

    return 0;
}

// Math
int math_operators()
{
    // basic
    double x = 10;
    int y = 3;
    double z = x + (x / y) * y;
    cout << "random math = " << z << endl;

    // reassignment
    int r = 5;
    int g = r + 5;
    cout << "g = r + 5 = " << g << ". r = " << r << endl;
    
    // increment
    int ten = 10;
    int ten_plus = ten++;   //ten_plus = 10, ten = 11
    int ten2 = --ten;       //ten2 = 11-1 = 10
    int plus_ten = ++ten2;  //plus_ten = 11, ten = 11

    cout << "ten = " << ten << " ten++ = " << ten_plus << endl
         << "ten = " << ten2 << " ++ten = " << plus_ten <<endl;

    return 0;
}

int math_expression()
{
    int x = 10;
    double y = 5;

    double z = (x + 10) / (3*y);
    cout << "z = (x + 10) / 3y --> " << z << endl;
    
    return 0;
}

int do_your_taxes()
{
    cout << "Doing taxes..." << endl;
    double sales = 95000;
    double state_rate = 0.04;
    double county_rate = 0.02;
    double state_tax = sales * state_rate;
    double county_tax = sales * county_rate;
    cout << "Total Sales: $" << sales << endl
         << "State Tax: $" << state_tax << " County Tax: $" << county_tax << endl
         << "Post-Tax Profit: $" << sales - state_tax - county_tax << endl;

    return 0;
}

int fun_cmath()
{
    double result = pow(2, floor(2.2));
    cout << "cmath result = " << result << endl;
    return 0;
}

int area_of_a_circle()
{
    cout << "Radius of circle: ";
    double radius;
    cin >> radius;
    double area = M_PI * pow(radius, 2);
    cout << "Area = " << area << endl;
    return 0;
}


// Console Input 
int read_from_console()
{
    cout << "Enter values for x and y: ";
    double x;
    double y;
    cin >> x >> y;
    cout << x + y << endl;

    return 0;
}

int farenheit_to_celsius()
{
    cout << "Enter the temperature in degrees Farenheit: ";
    int temp_f;
    cin >> temp_f;
    double temp_c = (temp_f - 32) * (5. / 9.);
    cout << temp_c << " degrees celsius" << endl;
    
    return 0;
}

/* Data Types
 * int: 4 bytes of mem, store #s from -2Billion to 2Billion
 * short: 2 bytes of mem, stores #s from -32,768 to 32,767 (can use to save mem)
 * long: 4 bytes, same as int
 * long long: 8 bytes, for very larg #s
 * double: 8 bytes of mem, #s from +-1.7E308
 * float: 4 bytes of mem, #s from +-3.4E38
 * long double: 8 bytes, -3.49E932 tp 1.7E4832
 * bool: 1 byte, true/false
 * char: 1 bytes
 * 
 * sizeof(type) or sizeof(variable_name) returns the memory size in bytes.
*/
int initialize_variables()
{
    double price = 99.99;
    float interestRate = 3.67F; //without F, compiler will treat var as a double and try to store the double as a float
    long fileSize = 90000L; //without L, compiler will treat as int
    char letter = 'a';
    bool isValid = true;
    auto autoVar = 'c'; //autoVar is a char
    /* brace initialization
     * Using the brace will prevent compilation when we provide a type error:
     * int number = 1.2 --> compiles to 1
     * int number {1.2} --> does not compile
     * int number {} ---> compiles to 0
     * int number ---> compiles to 'garbage'
     */
    int number {};
    cout << "int number {} = " << number << endl;
    return 0;
}

/* Number Systems
 * Decimal - base 10, digits 0-9, ex: 255
 * Binary - base 2, digits 0 or 1, ex: 11111
 * Hexadecimal - base 16, digits 0-9, A-F, ex: FF
*/
int hexadecimals()
{
    int binary_num = 0b11111111;             //255
    int hex_num = 0xff;                      //255
    cout << "binary_num " << binary_num
         << ". hex_num " << hex_num << endl; 

    return 0;
}

// Narrowing
// when you initialize a var of a smaller type using a larger type
int narrowing()
{
    int number = 1'000'000;
    short another = number; //converting an integer -> short will narrow the number
    // short another{number} would not compile - advantage of brace init
    cout << "number = " << number << ", narrowed = " << another << endl;

    return 0;
}

/* Random Numbers
 * srand(#) - set seed
 * time(nullptr) - produces elapsed seconds, so we can get a new random # every time 
 * 
*/
int rand_numbers()
{
    // time(nullptr) = number of seconds elapsed from jan 1 1970
    srand(time(nullptr));
    int number = rand() % 10; //%10 - limit to nums betwrrn 0 to 9
    cout << "radnom num = " << number << endl;

    return 0;
}


// For Loops
// for (variable; condition; code executed before next iter)
// Example: for (int i = 0; i < 5; i++)
//          {some code....}

// While Loops
// while (condition)
// Example: int i = 0; while (i < 5) {...; i++}

// Do While Loops (not as common)
// do {...} while {condition}
// do will be executed at least once and will repeat as long as condition is met

// Control Flow
// IF STATEMENTS: if (expression) {...} else if (expression) {...} else {...}
// SWITCH STATEMENTS: switch (variable) {..cases..}  //note: switches can only be integral types (like int)
//                   ex: case 17: code; break; case 18: code; break; default: code; break;
// switch is much more limited than ifelse

int roll_2_dice()
{   
    const short max = 6;
    const short min = 1;
    cout << "Rolling dice..." << endl;
    
    srand(time(nullptr));

    bool roll = true;
    int iters = 0;
    while (roll)
    {
        iters++;
        int d1 = (rand() % (max - min + 1)) + min;
        int d2 = (rand() % (max - min + 1)) + min;
        
        cout << "Your dice = " << d1 << " | Opponent's dice = " << d2 << endl;
        
        if (d1 > d2)
        {
            cout << "You win after " << iters << " turn(s)." << endl;
            roll = false;
        }
        else if (iters > 10)
        {
            cout << "You lose." << endl;
            roll = false;
        }
    }   
        return 0;
}

// Functions
int Multiply(int a, int b)
{
    return a * b;
}

void Multiply2(int a, int b) //void -> return nothing
{
    cout << a * b << endl;
}



int main()
{
    hello_world();
    math_operators();
    math_expression();
    do_your_taxes();
    farenheit_to_celsius();
    fun_cmath();
    area_of_a_circle();
    initialize_variables();
    hexadecimals();
    narrowing();
    rand_numbers();
    roll_2_dice();

    //function accessed from header file
    Log(99);

    cin.get();
    // main is a special function, and compiler automatically assumes 'return 0'
}