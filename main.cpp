/*
 ****************************************
 * Created by tarnishedgroot on 7/26/23.*
 ****************************************
 ****************************************
 * A small utility for calculating the  *
 * number of blocks and pointers in   ***
 * an inode  ****************************
 ****************************************
 */

#include "Inode.hpp"

int main(int argc, char* argv[]) {

    const std::string usage = "Not enough info!\nUsage: ./inodeCalc filesize units ptrSize blockSize";
    int blockSize, ptrSize, fileSize;
    std::string unit;

    if (argc < 2 || argc > 5) {
        //argc will always be at least 1 as argv[0] is the program name
        std::cout << usage << std::endl;
        return EXIT_FAILURE;
    }

    //A few default values just in case...
    std::string args[4] = {"", "KB", "4", "4096"};

    //Overwrite the args array with stdin (skipping the program name)
    for (int i = 1; i < argc; i++) {
        args[i - 1] = argv[i];
    }

    try {
        fileSize = stoi(args[0]);
        unit = args[1];
        ptrSize = stoi(args[2]);
        blockSize = stoi(args[3]);
    }
    catch (std::invalid_argument const &except) {
        std::cout << "Error: Invalid Argument" << std::endl;
        return EXIT_FAILURE;
    }

    TarnishedGroot::Inode inode = TarnishedGroot::Inode(fileSize, unit,ptrSize,blockSize);
    inode.Output();

    return EXIT_SUCCESS;
}