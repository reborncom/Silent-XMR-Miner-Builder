#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>



#define CONSOLE_MODE




std::string get_curr_dir() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH); 
    std::string full_path = path;
    size_t last_slash = full_path.find_last_of("\\/");
    if (last_slash != std::string::npos) {
        return full_path.substr(0, last_slash);
    }
    return full_path; 
}



int main() {
	//Setuping paths
    std::string currpath = get_curr_dir();
    std::string gccpath = "temp\\gcc\\bin\\g++.exe";
    std::string srcpath = "temp\\src";

    std::cout << "G++ path: " << gccpath << std::endl;
    std::cout << "Src path: " << srcpath << std::endl;

    std::vector<std::string> cpp_files;
    for (const auto& entry : std::filesystem::directory_iterator(srcpath)) {
        if (entry.path().extension() == ".cpp" or entry.path().extension() == ".o") {
            std::string name = entry.path().string();
            cpp_files.push_back(name);
            std::cout << "Adding '" << name << "' into project" << std::endl;
        }
    }

    if (cpp_files.empty()) {
        std::cout << "Cant find .cpp files in '\\temp\\src'." << std::endl;
        return 1;
    }

    std::string compile_command = gccpath + " -o out -static";
    for (const auto& file : cpp_files) {
        compile_command += " " + file;
    }
    std::cout << "Command line: " << compile_command << std::endl;

    int compile_result = system(compile_command.c_str());
    if (compile_result == 0) {
        std::cout << "Project 'out.exe' sucessfully compiled" << std::endl;
    }
    else {
        std::cout << "Error while compiling." << std::endl;
        std::cin.get();
        return 1;
    }


    std::cin.get();
	return 0;
}