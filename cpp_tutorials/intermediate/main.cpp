#include <iostream>
#include <cstring>

using namespace std;

// Pointers (also stack vs heap), References, Classes & Structs, Enums, Constructors & Destructors, Inheritance [(Pure) Virtual ]
///////////////////////////////////////////////////////////////////////////////////////////////////

/* POINTERS - a number (integer) which stores a memory address, corresponding to some block of bytes
 * We can give pointers a type, which is to say that the data at that address is presumed to be of that type
 * but we do not need to provide a type (void*). (The type doesn't change the pointer, which is just an adress.)
 * 
*/
int basic_pointers()
{
    //Pointer with no type
    void* null_ptr = nullptr; // nullptr or 0 is not a valid memory address

    //Finding the memory address of an existing var
    int var = 8;
    void* ptr = &var;

    cout << "A memory address: " << ptr << endl;
    
    return 0;
}

int typed_pointers()
{
    int var = 8;
    int* ptr = &var;

    //Dereferencing - accessing or writing to the variable at the address of a pointer
    // (in this case, to assign int 10 to that address we needed the pointer to by of type int)
    *ptr = 10;
    return 0;
}

/* Stack vs Heap
 *  stack - Typically when we define a variable we allocate its memory on the stack, which is 'safer', 'faster',
 *            but has less storage space. Also, memory is allocated/de-allocated automatically as soon as the corresponding method completes.
 *  heap - This memory is allocated when the programmer explicitly allocates memory themselves. There is no automatic allocation/de-allocation
 *           and hence we need to delete the memory or use a garbage collector. 
*/

int heap_allocate()
{
    //Create a var on the Heap
    //(allocating a variable of exactly 8 bytes of memory... since char is exactly 1 bytes)
    char* buffer  = new char[8];
    // the above returns a pointer to the *beginning* of the allocated block of memory
    // we can fill the block using cstring's memset()
    memset(buffer, 0, 8); //takes pointer, a value, and the # of bytes to fill (in this case we fill with 0s)

    delete[] buffer; //we should delete memory we create on the heap.

    return 0;
}

int double_pointer()
{
    // We can have pointers which point to pointers
    char* buffer  = new char[8];
    memset(buffer, 0, 8);

    // At the address stored in 'ptr' is anotehr pointer which points to the buffer we allocated
    char** ptr = &buffer;
    delete[] buffer; //we should delete memory we create on the heap.

    return 0;
}


/* REFERENCES
 * Very similair to pointers, but semantically different. References are slightly easier to read
 * References are just references to an existing variable, but are not really variables themselves.
 * So when we compile the code, we do not get seperate variable for the references - they just become the variable reference
 *  
*/
int basic_references()
{
    //we put '&' next to the type and set the 'alias' equal to an existing variable
    int a = 5;
    int& ref = a;
    // we can change 'a' through a reference to it
    ref = 2;
    cout << a << endl; // returns 2
    
    return 0;
}

// example:
/* Increment a variable
 * If we just pass in the variable, it will get copied by the function, creating a new variable and thus our actual
 * variable will not get incremented.
*/

//We could pass the pointer of the variable to the function and then modify the data at that memory address...
void increment_viapointer(int* pointer)
{
    (*pointer)++; //deref the value first so we can write to it, and then increment ++
    // without (), it would increment pointer first instead of the value at the pointer
}

//Or with references, it's a bit easier
void increment_viareference(int& value)
{
    value++;
}

void Increment()
{
    int a = 5;
    increment_viapointer(&a); //provide the memory address to a
    cout << a << endl;

    increment_viareference(a); //all we have to do is pass in a, since we 'pass by reference'
    cout << a << endl;
}


/** CLASSES
 * Grouping data and methods together, essentially creating a new data 'type' (like python)
 * When we define a new class-type it is called an 'object' 
 *      and when we use it do define a variable, the var is an 'instance'. Functions inside classes = 'methods'
 *  Visibility - by default, classes make variable private such that only functions inside that class can access the variables.
 * However, we can make variable, functions public.
*/

class Player
{
public:
    int x, y;
    int speed;
    void Move(int xa, int ya)
    {
        x += xa * speed;
        y += ya * speed; 
    }
};


void player_example()
{
    //creating an instance and setting variables
    Player player1; 
    player1.x = 5;
    player1.y = 5;
    player1.speed = 1;
    player1.Move(2, 2);
}

/** STRUCTS vs CLASSES
 * ONE DIFFERENCE: A class is private by default (we have to specify public), but a STRUCT IS PUBLIC BY DEFAULT.
 * C has structs (but not classes) so including structs in C++ allows backward compatibility.
 * Basically, can use structs if we expect everything in the struct to be public, and use classes if we expect some private components.
 * Use structs for simpler objects with less functionality.
*/
// example: a simple 'structure' to represent 2 floats as a vector 
struct Vec2
{
    float x, y;
    void Add(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }
};

// LOG EXAMPLE //
// Basic - simple but not a good code
class SimpleLog
{
public:
    const int LogLevelError = 0;
    const int LogLevelWarning = 1;
    const int LogLevelInfo = 2;

private:
    int m_LogLevel = LogLevelInfo;


public:
    void SetLevel(int level)
    {
        m_LogLevel = level;
    }

    void Error(const char* message)
    {
        if (m_LogLevel >= LogLevelError)
            cout << "[ERROR]: " << message << endl;
    }

    void Warn(const char* message)
    {
        if (m_LogLevel >= LogLevelWarning)
            cout << "[WARNING]: " << message << endl;
 
    }
    
    void Info(const char* message)
    {
        if (m_LogLevel >= LogLevelInfo)
            cout << "[INFO]: " << message << endl;
    }

};

/**STATIC
 * Static outside of a class - the linkage of the symbol declared to be static is internal, not shared outside of this 'translation unit' (.cpp file)
 * Static inside of a class/struct - that variable will share memory with ALL instances of that class 
 * Good idea to keep variables, functions as static unless we know for sure we want to link them across translation units
*/
static void s_StaticVariables()
{
    static int s_Variable = 5;
}

/**Static for classes/structs
 * Inside a class, a static variable will only exist once no matter how many instances of the class.
 * Changing the static variable in one instance will change it for all instances.
 * Static methods - can be called 
*/
struct Entity
{
    int x, y;
    static int z;

    void Print()
    {
        cout << x << " " << y << " " << z << endl;
    }
};

int Entity::z; //since z is static, it is not technically a class member and we have to define it

void entity_example()
{

    Entity e;
    e.x = 3;
    e.y = 2;
    e.z = 7;
    
    Entity e1 = {5, 8};
    e1.z = 10;    //this will also change e.z to 10 since z is static! 

    e.Print();   //3 2 10
    e1.Print();  //5 8 10
}

/**ENUMS
 * Short for enumeration. Enum is a set of integer values (kinda like python dict).
 * Can set which type of int to use for the enum. By default, they are 32-bit integers
 * 
*/
void enum_example()
{
   enum Example : char  //can use an 8bit integer for this case to use less mem
   {
    A = 0, B = 2, C = 4
   };
    // A=0, B=1, C=2, ... by default, but can specify values

    //a lambda function to demonstrate
    auto some_lambda_fn = []()   
    {
        Example value = B;
        if (value == A)
        {
            //do something
        }
        
    };
}


/// LOG EXAMPLE // 
class EnumLog
{
public:
    enum Level
    {
        LevelError = 0, LevelWarning, LevelInfo
    };
private:
    Level m_LogLevel = LevelInfo;


public:
    void SetLevel(Level level)
    {
        m_LogLevel = level;
    }

    void Error(const char* message)
    {
        if (m_LogLevel >= LevelError)
            cout << "[ERROR]: " << message << endl;
    }

    void Warn(const char* message)
    {
        if (m_LogLevel >= LevelWarning)
            cout << "[WARNING]: " << message << endl;
 
    }
    
    void Info(const char* message)
    {
        if (m_LogLevel >= LevelInfo)
            cout << "[INFO]: " << message << endl;
    }

};

/** CONSTRUCTORS & DESTRUCTORS
 * Constructor - A method which runs whenever we instantiate an object.
 * Desctructor - A method which runs whenever we destory an object 
*/
class Entity2
{
public:
    float X, Y;

    // Constructor
    Entity2(float x, float y)
    {
        cout << "Constructed Entity" << endl;
        X = x;
        Y = y;
    }

    void Print()
    {
        cout << X <<", "<< Y << endl;
    }

    // Destructor
    ~Entity2()
    {
        cout << "Destroyed Entity!" << endl;
    }

};

void entity2_example()
{
    Entity2 e(10.0f, 10.0f);
    e.Print();

}

/** INHERITANCE
 * Allows us to have a related hierarchy of classes... a base class with common functionality + sub-classes 
*/
/** VIRTUAL FUNCTIONS
 * Virtual functions allow us to override methods in sub-classes.
 * Say B is a subclass of A, if we create a virtual method in A we have the option to override it in B.
 * Virtual functions arent free - they require additional memory to store a V-table which maps from overriddent function to base function
*/
/** PURE VIRTUAL FUNCTIONS
 * Same as an 'abstract method' or 'interface'
 * Define a function in a base class that does not have an implementation, and force subclasses to fill out the implementation .
 * An "interface" is a class that exists of only unimplemented methods, acting as a sort of template.
*/
/**VISIBILITY
 * No effect on performance or compilation, just exists to help write better code.
 * Private - only the object containing the private method/variable can access it (a 'friend' can also access private members tho)
 * Protected - the current class and any subclass can access the method/variable.
 * Public - anyone - the class, subclass, or anyone can access the method/variable.
*/

class Printable
{
public:
    virtual string GetClassName() = 0; //pure virtual
};

class BaseEntity : public Printable
{
// Every sub-entity will have these attributes (inheritance)
public:
    float X, Y;
    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
    // Virtual Function... we can override the implementation in any subclass
    virtual string GetName() {return "Entity"; }

    // Pure Virtual Function... we have to implement it in any subclass
    virtual string LastName() = 0; //seting = 0 makes it 'pure'

    // Implementing the pure virtual fn inherited from Printable
    string GetClassName() override {return "BaseEntity"; }
};


// SubClass - this class is technically *both* types
class NewPlayer : public BaseEntity
{
private:
    string m_Name;
public:
    NewPlayer(const string& name) //constructor to declare a name
    {
        m_Name = name;
    }
    void PrintName() {cout << m_Name << endl; }

    // ovverride the virtual function (override keyword is optional)
    string GetName() override {return m_Name; }

    // implement the *pure* virtual function
    string LastName() override {return "Elliott"; }

    // override getclassname
    string GetClassName() override {return "NewPlayer"; }

};

// Example - a function that can print a class's name by extracting the GetClassName method
void Print(Printable* obj)
{
    cout << obj->GetClassName() << endl;
}

void inheritance_example()
{
    NewPlayer player("Hans");
    player.X = 2.0f; //player inherits X
    player.PrintName(); //Prints Hans using the new method added to player virtual function
    cout << player.GetName() << endl; //Prints Hans using the overrident virtual fn
    cout << player.LastName() << endl; //Prints Elliott using the implemented pure virtual fn


    NewPlayer player2("Bob");
    Print(&player2);  //prints NewPlayer
}



/////////////////////////////////////////////////////////////////
void log_test()
{
    // Simple Log class
    SimpleLog slog;
    slog.SetLevel(slog.LogLevelError);
    slog.Warn("Simple Hello");
    slog.Info("Simple Hello");
    slog.Error("Simple Hello");

    // More advanced, w/ Enums.
    EnumLog log;
    log.SetLevel(EnumLog::LevelError);
    log.Warn("enum hello"); log.Info("enum hello"); log.Error("enum hello");
}


int main()
{
    basic_pointers();
    typed_pointers();
    basic_references();
    Increment();
    entity_example();
    entity2_example();
    inheritance_example();

    log_test();
    // cin.get();
}
