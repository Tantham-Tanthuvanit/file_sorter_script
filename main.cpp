#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main() {

    // read file
    std::fstream file("types.txt");
    // get current directory
    fs::path dir = ".";

    std::vector<std::string> types;

    // check for errors, if there are any then print out the error
    if (!file.is_open()) {
        std::cerr << "Failed to open file";
        return 1;
    }

    // read each type that we want to sort and then put them into a vector
    std::string type;
    while (std::getline(file, type))
        if (!type.empty()) types.push_back(type);


    // loop through the entire directory
    for (const auto& entry : fs::directory_iterator(dir)) {
        
        // check if the entry is a regular file, if not then skip it
        if (!entry.is_regular_file())
            continue;
    
        fs::path file_path = entry.path();
        std::string ext = file_path.extension().string(); // get the files extension as a string

        // loop throgh each type
        for (const auto& t : types) {
            // check if the extension is equal to the type
            if (ext == t) {
                // make a path fo the target directory
                fs::path target_dir = t;

                // check if directory exists, if it does than create it
                if (!fs::exists(target_dir))
                    fs::create_directory(target_dir);

                // construct new path
                fs::path new_path = target_dir / file_path.filename();
                // move the file to the directory
                fs::rename(file_path, new_path);
                break;
            }
        }
    
    }
    
    return 0;

}