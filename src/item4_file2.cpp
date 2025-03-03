#include "item4_file2.h"

// static tfs in globe space
// it's not gaurenteed to be initialized before static variables in main files
FileSystem tfs;

int FileSystem::numDisks() const {
    return this->ndisks;
};

// return a static reference of FileSystem forcing the initialization of fs that is returned
FileSystem& tfsRef() {
    // fs is only difined and initialized once when tfsRef is called
    // but the lifetime extends for entire program
    static FileSystem fs;
    return fs;
}