
#ifndef CPP_FILEOPERATIONS_H
#define CPP_FILEOPERATIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <tchar.h>
#include <sys/stat.h>



#define Rf   'r'     // Opens File for only reading

#define Wf   'w'     // Opens File for only writing

#define RWf  'x'     // Open the file for both reading and writing.
                     // The stream is positioned at the start of the file.

#define RWCf   'b'    // Open the file for both reading and writing. If the file exists,
                      //  it is truncated to zero length.
                      // If the file does not exist, it is created.

#define Af   'a'      // Open the file for writing in append mode.
                      // The file is created if it does not exist.
                      // The stream is positioned at the end of the file.
                      // All writes will append to the file.

class Cpp_FileOperations
{
public:
 Cpp_FileOperations();
 Cpp_FileOperations(const Cpp_FileOperations & orig);
 virtual ~Cpp_FileOperations();
 void SetFilePath(std::string FilePATH);
 void SetFilePath(char * String);
 void SetFilePath(const char * String);
 void CpFile(char * path, char * target_path);
 void MoveFile_Win(char * path, char * target_path);  // Transfer file to another location in windows
 int  Delete_File(char * path);
 void FileOpen(char Open_Mode);
 void FileClose( );
 void WriteToFile(std::string string_list);
 void WriteToFile(const char * String);
 void WriteToFile(char * String);
 bool Control_End_of_File();
 std::string Read();
 std::string ReadLine();
 std::string Receive_File_As_std_string(char * path);
 int GetFileSize() const;
 char * GetFilePath();
 char * GetFileLine(int line_number); // in therms of cstring
 char * ReadLine_as_Cstring();
 void Determine_Base_File_Size(char * path);
 void Receive_File(char * path);
 void Record_File(char * path); // It reads whole of file in therms of cstring
 void Read_File_as_CString(char * path);
 char * Convert_Std_String_To_Char(std::string string_line);
 bool Is_Path_Exist(char * path);
 bool Is_This_File_Empty(char * path);
 bool TryOpen(char path);
 void Clear_Dynamic_Memory();
private:
 std::fstream DataFile;
 std::string String_Line;
 std::string string_word;
 std::string FilePath;
 std::string File_Content;
 bool Memory_Delete_Condition;
 bool Is_File_Empty;
 char * CString;
 char * CString_FilePATH;
 char ** File_Index;
 int  File_line_Number;
 int  Delete_Return_Status;
 char Open_Mode_Determiner;
 int  FileDeleteCondition;
 bool isFilePathReceive;
 bool End_Of_File_Condition;
 bool is_path_exist;
 bool file_open_status;
};

#endif /* CPP_FILEOPERATIONS_H */
