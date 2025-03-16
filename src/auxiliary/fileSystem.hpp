#pragma once

class FileSystem {
public:
  int ndisks;
  FileSystem() : ndisks(100) {};
  ~FileSystem() {};
  
  int numDisks() const;
};

// declaration, definition is in item4_file2.cpp
extern FileSystem tfs;

// using a function to return static FileSystem
FileSystem& tfsRef();