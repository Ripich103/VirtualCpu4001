#include <iostream>
// Made by Ripich103 feel free to copy or use it
#include "Memory.h"
#include "CPU.h"
#include "Assembly.h"

using namespace std;
using namespace Asm;
using namespace CPU_4001;

void DefaultProgram(Memory*);

void ReportMemory(Memory*);

void ClearMemory(Memory*);

void ShowMenu();
const bool ChooseFromMenu(const char&, Memory*);
const bool IsExitOption(const char& selection);

bool ReadFile(CPU*);
bool WriteFile(CPU*);
void ProgramEntry(Memory*);


bool write = false;
bool read = false;


int main()
{
    cout << "Init Memory...";
    Memory* theMemory = new Memory();
    cout << "Ready" << endl;

    // Changes here: We have the CPU ONLY active
    // for the cycle from the menu through, however
    // we don't want to loose the memory, so that is
    // created outside the loop
    bool quitAll = false;
    char selectedOption = ' ';
    
    do
    {
        // Show the menu & read in a
        // character (plus enter) for
        // the next option to perform
        ShowMenu();
        cin >> selectedOption;

        // Check if we're exiting
        if (!IsExitOption(selectedOption))
        {
            // Check if we're running
            if (ChooseFromMenu(selectedOption, theMemory))
            {
                cout << "\n************************************" << endl;
                // Create the CPU    
                CPU* theCPU = new CPU(theMemory);

                //check the flags
                if (read == true)
                {
                    char filename[255];
                    std::cout << "\nEnter filename: ";
                    std::cin >> filename;
                    if (theCPU->ReadFromFile(filename))
                    {
                        std::cout << "\nFile was writen to memory succesfully\n";
                        read = false;
                    }
                }
                if (write == true)
                {
                    char filename[255];
                    std::cout << "\nEnter filename: ";
                    std::cin >> filename;
                    if (theCPU->WriteToFile(filename))
                    {
                        std::cout << "\nmemory was written to file succesfully\n";
                        write = false;
                    }
                }

                // Run the program in memory    
                theCPU->Run();

                // The CPU is done
                delete theCPU;
                cout << "************************************" << endl;
            }
        }
        else
        {
            quitAll = true;
        }
    } while (!quitAll);

    delete theMemory;
}

void ShowMenu()
{
    cout << endl << "===== Menu =====" << endl;
    cout << "1. Load Default Program" << endl;
    cout << "2. Clear the Memory" << endl;
    cout << "3. Report Memory" << endl;
    cout << "4. Save to file" << endl;
    cout << "5. Import from file" << endl;
    cout << "R. Run the current memory state through the CPU" << endl;
    cout << "E. Enter programe editor" << endl;
    cout << endl;
    cout << "X. Exit Interpter" << endl;
    cout << endl;
    cout << "Selection: ";
}



const bool IsExitOption(const char& selection)
{
    return (selection == 'x' || selection == 'X');
}

const bool ChooseFromMenu(const char& selection,
    Memory* theMemory)
{
    bool l_RunThroughCPU = false;

    switch (selection)
    {
    case '1':
        DefaultProgram(theMemory);
        break;

    case '2':
        ClearMemory(theMemory);
        break;

    case '3':
        ReportMemory(theMemory);
        break;
    
    case '4':
        write = true;
        break;

    case '5':
        read = true;
        break;

    case 'e':
    case 'E':
        ProgramEntry(theMemory);
        break;

    case 'r':
    case 'R':
        l_RunThroughCPU = true;
        break;
    }

    return l_RunThroughCPU;
}

void ProgramEntry(Memory* theMemory)
{
    if (theMemory == nullptr)
        return;
    
    std::cout << "Entering Program Entry, by memory address: " << std::endl;
    std::cout << "N - incriment current address, B - decrement current address, X - exit the editor" << std::endl;

    bool exitEditor = false;
    byte value = 0;
    string option;
    option.reserve(255);
    byte currentAddress = 2; // we reserve 2 addresses in out cpu for jump address and extra halt.
    do
    {
        std::cout << "Memory editor: [" << (int)currentAddress << "] (" << (int)theMemory->Read(currentAddress) << ") > ";
        std::cin >> option;
        std::cout << '\n';
        if (option == "x" || option == "X")
        {
            exitEditor = true;
        }
        else if (option == "b" || option == "B")
        {
            --currentAddress;
        }
        else if (option == "n" || option == "N")
        {
            ++currentAddress;
        }
        else
        {
            DC::Decode(value, option);


            theMemory->Write(currentAddress, value);
            ++currentAddress;
        }

    } while (!exitEditor);
    
}

void ClearMemory(Memory* theMemory)
{
    if (theMemory != nullptr)
    {
        cout << "\nClearing the memory...";
        theMemory->Clear();
        cout << "Complete" << endl;
    }
}

void DefaultProgram(Memory* theMemory)
{
    if (theMemory != nullptr)
    {
        ClearMemory(theMemory);
        
        // Add the program
        cout << "\n\nAdding our default machine code program..." << endl;
        // Load0 value 1
        theMemory->Write(2, MOV_R0);
        theMemory->Write(3, 1);

        // Load1 Value 2
        theMemory->Write(4, MOV_R1);
        theMemory->Write(5, 2);

        // Add
        theMemory->Write(6, ADD);

        // Store to 12
        theMemory->Write(7, STORE);
        theMemory->Write(8, 13);

        // Print from 12
        theMemory->Write(9, PRINT);
        theMemory->Write(10, 13);

        // Beep
        theMemory->Write(11, BEEP);

        // HALT
        theMemory->Write(12, HALT);
    }
}

void ReportMemory(Memory* theMemory)
{
    // Now, we only need to add "(int)" here, because the cout
    // stream does not know to use our "byte" as a number, the
    // C++ language would just assume that our memory spot is
    // an "unsigned char"... or character, so we'd output garbage.
    // (int) in front simply means "Treat this as a number"...
    cout << "\nMemory Size: " << (int)theMemory->c_MaxAddress << endl;

    cout << "\nDo you want to list the memory?";
    char yesNo;
    cin >> yesNo;
    if (yesNo == 'Y' || yesNo == 'y')
    {
        for (byte currentAddress = 0; currentAddress < theMemory->c_MaxAddress; ++currentAddress)
        {
            // Again, add "(int)" to force usage as a number
            cout << "Address [" << (int)currentAddress << "] = " << (int)theMemory->Read(currentAddress) << "\n";
        }
    }
}

bool ReadFile(CPU* cpu)
{
    return true;
}

bool WriteFile(CPU* cpu)
{
    
    return true;
}