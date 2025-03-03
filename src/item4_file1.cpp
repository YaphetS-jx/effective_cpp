#include <iostream>
#include "item4_file1.h"
#include "item4_file2.h"



Directory::Directory() {
    // tfs is declared in item4_file1.h
    this->disks = tfs.numDisks();
    std::cout << "disks in Directory is " << disks << std::endl;
    // since tfs is not initialized yet, this will be 0
};

Directory::Directory(int s) {
    this->disks = tfsRef().numDisks();
    std::cout << "disks in Directory try is " << disks << std::endl;
    // here tfs is initialized, so this will be 100
}

// initialized before tfs in item4_file2.cpp
Directory tmpDir;
Directory tmpDir2(1);

int main () {
    FileSystem fs;

    // fs is initialized now, so this will be 100
    std::cout << "numDisks of fs is " << fs.numDisks() << std::endl;

    return 0;
}