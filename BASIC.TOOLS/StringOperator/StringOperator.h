
#ifndef STRINGOPERATOR_H
#define STRINGOPERATOR_H

#include <cstring>
#include "Cpp_FileOperations.h"
#include "CharOperator.h"


class StringOperator
{
public:
 StringOperator();
 StringOperator(char * FilePATH);
 StringOperator(std::string FilePATH);
 virtual ~StringOperator();
 void ReceiveFileLine(std::string ReadLine);
 void LoadStringBuffer(std::string ReadLine);
 int  FindNextWordLine(std::string search_word, int startPoint);
 bool CheckStringLine(std::string readline);
 bool CheckStringLine(char * readline);
 bool CheckStringInclusion(std::string StringLine, std::string search_word);
 bool CompareString(std::string firstString, std::string secondString);  // Compares two string
 int  Get_Start_Position_of_an_included_String();
 void Clear_Dynamic_Memory();
 std::string ReadFileLine(int lineNumber);
 std::string GetStringBuffer();
 size_t GetBufferLength();
private:
 void Initialize_Members();
 CharOperator CharacterOperations;
 Cpp_FileOperations Cpp_File_Manager;
 int Word_Count;
 int wordPosition;
 int Included_Word_Start_Position;
 int BufferLength;
 bool isStringLine;
 bool includeCondition;
 bool isBufferEmpty;
 bool Included_Word_Start_Position_Set_Condition;
 bool Memory_Delete_Condition;
 std::string StringBuffer;
};

#endif /* STRINGOPERATOR_H */


/* FindNextWordLine : This member function search a word from the start point to the end of file

                      It stops the searching when it find a word maches the search word

                      However, it returns true if the readed line includes only the search word   */

/* CheckStringLine : This member function determines that this line information includes a string

                     It returns false if the readed line only includes a null character or a new line character */
