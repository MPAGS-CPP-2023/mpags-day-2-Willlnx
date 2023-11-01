#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//function declarations
std::string transformChar(const char in);
bool processCommandLine(const std::vector<std::string>&args,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFile, std::string& outputFile);


int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    //Process cmd line args
    const bool cmdLineStatus{processCommandLine(
        cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};

    if (!cmdLineStatus)
    {
        return 1;
    }
    
    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    //Transliteration code from before
    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!inputFile.empty()) 
        {
        //Open the file to check it is readable
        std::ifstream inputStream{inputFile};
        if (!inputStream.good())
         {
            std::cerr << "[error] failed to create istream on file'"
                      << inputFile << "'" << std::endl;
            return 1;
         }
        
        // Loop over each char from file
        while (inputStream >> inputChar)
        {
            inputText += transformChar(inputChar);
        }
    }

    else 
    {
        // loop over each character from user input until ctrl-d pressed
        while (std::cin >> inputChar) 
        {
            inputText += transformChar(inputChar);
        }
    }



    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) 
    // Open file to check its writable
    {
        std::ofstream outputStream{outputFile};
        if (outputStream.good())
        {
            std::cerr << "[error] failed to create ostream on file'"
                      << outputFile << "'" << std::endl;
            return 1;
        }
    
    //Print transl text to file
    outputStream << inputText << std::endl;
    }

    //Print transl text to screen
    else
    {
        std::cout << inputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

std::string transformChar(const char inputChar)
{
    std::string inputText;

    //Uppercase alphabetic chars
    if (std::isalpha(inputChar))
        {
            inputText += std::toupper(inputChar);
            return inputText;
        }

     // Transliterate digits to English words
        switch (inputChar) {
            case '0':
                inputText += "ZERO";
                break;
            case '1':
                inputText += "ONE";
                break;
            case '2':
                inputText += "TWO";
                break;
            case '3':
                inputText += "THREE";
                break;
            case '4':
                inputText += "FOUR";
                break;
            case '5':
                inputText += "FIVE";
                break;
            case '6':
                inputText += "SIX";
                break;
            case '7':
                inputText += "SEVEN";
                break;
            case '8':
                inputText += "EIGHT";
                break;
            case '9':
                inputText += "NINE";
                break;
        }

        // If the character isn't alphabetic or numeric, DONT add it

        return inputText;
    }

    bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                            bool& helpRequested, bool& versionRequested,
                            std::string& inputFile, std::string& outputFile)
    {
        //Status flag indicating if the parsing was successful
        bool processStatus{true};

        //Processing the arguments

        const std::size_t nCmdLineArgs{cmdLineArgs.size()};
        for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") 
            {
                helpRequested = true;
                break; 
            } 

        else if (cmdLineArgs[i] == "--version") 
            {
                versionRequested = true;
                break;
            } 
            
        else if (cmdLineArgs[i] == "-i") 
        {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                //Set error flag to terminate loop
                processStatus = false;
                break;
            } 
            
            else 
            {
                // Got filename, so assign value and advance past it
                inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } 

        else if (cmdLineArgs[i] == "-o") 
        {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) 
            {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                //Set error flag to terminate loop
                processStatus = false;
                break;
            } 

            else 
            {
                // Got filename, so assign value and advance past it
                outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        } 
        
        else 
        {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
        }
    }

    return processStatus;

}