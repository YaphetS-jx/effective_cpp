#pragma once

class Directory {
public:
    int disks;
    Directory();
    // can not write Directory() : disks(0) {};
    // even it's empty, it's still a definition
    
    Directory(int s);
};
