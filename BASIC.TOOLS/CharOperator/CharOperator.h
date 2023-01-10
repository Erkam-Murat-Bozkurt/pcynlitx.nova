
/* This class is a character processor for a file or documents */

#ifndef CHAROPERATOR_H
#define CHAROPERATOR_H

#include "Cpp_FileOperations.h"
#include <string>
#include <iostream>
#include <cstring>

class CharOperator
{
public:
  CharOperator();
  CharOperator(char * FilePATH);
  CharOperator(std::string FilePATH);
  virtual ~CharOperator();
  int  DetermineCharacterRepitation(std::string list, char c);             // The function determines that how many character is there in a list
  int  FindNextCharacterPositon(std::string list, int start ,char c);      // Search a character in a list starting from a given point..
  int  FindTheSpecificWordLine(std::string line);                          // The return value is the line number includes a specific word..
  void ForwardFilePointer(Cpp_FileOperations * pointer, int start);        // Move File Pointer
  int  FindFirstCharacterPosition(std::string list);                       // Finds first character position in a list
  bool CharacterCheck(std::string list, char c);                           // Does exist character which selected in the list
  bool CompareString(std::string firstString, std::string secondString);   // Compares two string
  void Clear_Dynamic_Memory();
private:
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  int  CharacterPosition;
  int  CharacterRepitation;
  int  WordPosition;
  int  FirstCharacterPosition;
  bool isStringsEqual;
};

#endif /* CHAROPERATOR_H */
