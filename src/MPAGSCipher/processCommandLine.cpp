#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
    
#include "processCommandLine.hpp"

bool processCommandLine(const std::vector<std::string>&args,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFile, std::string& outputFile);