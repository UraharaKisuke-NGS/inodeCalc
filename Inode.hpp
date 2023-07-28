//
// Created by tarnishedgroot on 7/27/23.
//

#ifndef INODECALC_INODE_HPP
#define INODECALC_INODE_HPP
#include <iostream>
#include <string>
#include <cmath>

namespace TarnishedGroot {
    class Inode {
    private:
        const std::string usage = "\nUsage: inodeCalc filesize units ptrSize blockSize\n";
        enum class unit {
            KB = 0,
            MB,
            GB,
            TB
        };
        unit fileUnits{unit::KB};
        const int direct_pointers = 12;
        int size;
        int ptr_size{4};
        int block_size{4096};
        int pointersPerBlock{};
        long int numBytes{};
        int numBlocks{}, numDirectBlocks{}, numIndirectBlocks{}, numDoubleBlocks{}, totalBlocks{};

        static long int ConvertToBytes(int _file_size, int unit_enum_rep);

        static int CalculateNumBlocks(long int _file_size, int _block_size);
        void CalculateNumPointerBlocks();
        std::string _fileUnit;

        void init();

    public:

        Inode(int file_size, const std::string &_unit, int _ptr_size, int _block_size);

        void Output();

        ~Inode() = default;

    };
}
 // TarnishedGroot

#endif //INODECALC_INODE_HPP
