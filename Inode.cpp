//
// Created by tarnishedgroot on 7/27/23.
//

#include "Inode.hpp"

namespace TarnishedGroot {
    long int TarnishedGroot::Inode::ConvertToBytes(int _file_size, int unit_enum_rep) {
        const int rule = 1024;
        int exponent;
        switch (unit_enum_rep) {
            case 0:
                exponent = 1;
                break;
            case 1:
                exponent = 2;
                break;
            case 2:
                exponent = 3;
                break;
            case 3:
                exponent = 4;
                break;
            default:
                exponent = 1;
        }
        return (_file_size * (long) pow(rule, exponent));
    }

    int TarnishedGroot::Inode::CalculateNumBlocks(long _file_size, int _block_size) {
        //File size should be in BYTES
        if (_block_size <= 0 || _file_size <= 0)
            return 0;
        return (int) (_file_size / _block_size);
    }

    TarnishedGroot::Inode::Inode(int file_size, const std::string &_unit, int _ptr_size, int _block_size){
        this->size = file_size;
        this->_fileUnit = _unit;
        this->ptr_size = _ptr_size;
        this->block_size = _block_size;
        init();
    }

    void TarnishedGroot::Inode::init() {
        switch (toupper(_fileUnit[0])) {
            case 'K':
                fileUnits = unit::KB;
                break;
            case 'M':
                fileUnits = unit::MB;
                break;
            case 'G':
                fileUnits = unit::GB;
                break;
            case 'T':
                fileUnits = unit::TB;
                break;
            default:
                fileUnits = unit::KB;
                break;
        }
        this->numBytes = ConvertToBytes(this->size, (int) this->fileUnits);
        this->numBlocks = CalculateNumBlocks(this->numBytes, this->block_size);
        this->pointersPerBlock = this->block_size / this->ptr_size;
        //CalculateNumPointerBlocks(numDirectBlocks, numIndirectBlocks, numDoubleBlocks, totalBlocks);
        CalculateNumPointerBlocks();
    }

    void TarnishedGroot::Inode::CalculateNumPointerBlocks(){
        this->numDirectBlocks = ceil((double) (this->numBlocks - 12) / this->pointersPerBlock);
        this->numIndirectBlocks = ceil((double) (this->numDirectBlocks - 1) / this->pointersPerBlock);
        this->numDoubleBlocks = ceil((double) (this->numIndirectBlocks - 1) / this->pointersPerBlock);
        this->totalBlocks = this->numBlocks + this->numDirectBlocks + this->numIndirectBlocks + this->numDoubleBlocks;
    }
    void TarnishedGroot::Inode::Output() {
        printf("============================\n"
               "=========INODE INFO=========\n"
               "============================\n");
        printf("File size: %d %s ( %ld Bytes)\n", (int) this->size, _fileUnit.c_str(), numBytes);
        printf("Pointer Size : %d Bytes\nBlock Size : %d Bytes\n", this->ptr_size, this->block_size);
        printf("Number of Pointers per Block: %d\n", this->pointersPerBlock);
        printf("Number of Blocks Directly Pointed to by inode: %d\n", this->direct_pointers);
        printf("Number of Data Blocks (Pointed to by Direct Pointers): %d\n", numBlocks);
        printf("Number of Blocks of Direct Pointers (Blocks pointed to by Indirect pointers): %d\n",
               this->numDirectBlocks);
        printf("Number of Blocks of Indirect Pointers (Blocks pointed to by Double Indirect pointers): %d\n",
               this->numIndirectBlocks);
        printf("Number of Blocks of Double Indirect Pointers(Blocks pointed to by Triple Indirect Pointer): %d\n",
               this->numDoubleBlocks);
        printf("Total number of Blocks, not including the inode: %d\n", totalBlocks);
    }

}