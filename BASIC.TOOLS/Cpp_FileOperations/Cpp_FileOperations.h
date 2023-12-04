
#ifndef CPP_FILEOPERATIONS_H
#define CPP_FILEOPERATIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <windows.h>
#include <tchar.h>
#include <sys/stat.h>



#define Rf   'r'     // Opens File for only reading

#define Wf   'w'     // Opens File for only writing

#define RWf  'x'     // Open the file for both reading and writing.
                     // The stream is positioned at the start of the file.

#define RWCf 'b'     // Open the file for both reading and writing. If the file exists,
                      //  it is truncated to zero length.
                      // If the file does not exist, it is created.

#define Af   'a'      // Open the file for writing in append mode.
                      // The file is created if it does not exist.
                      // The stream is positioned at the end of the file.
                      // All writes will append to the file.

#define BUFSIZE MAX_PATH


class Cpp_FileOperations
{
public:
 Cpp_FileOperations();
 Cpp_FileOperations(char opr_sis);
 virtual ~Cpp_FileOperations();
 void Receive_Operating_System(char opr_sis);
 void CpFile(char * path, char * target_path);
 void CpFile(std::string path, std::string target_path);
 void SetFilePath(std::string FilePATH);
 void SetFilePath(char * String);
 void MoveFile_Win(char * path, char * tr_path);  // Transfer file to another location in windows
 int  Delete_File(char * path);
 int  Delete_File(std::string path);
 int  Delete_File(const char * path);
 void FileOpen(char Open_Mode);
 void FileClose( );
 void WriteToFile(std::string string_list);
 void WriteToFile(const char * String);
 void WriteToFile(char * String);
 bool Control_Stop_Condition();
 std::string Read();
 std::string ReadLine();
 void Read_File(char * path);
 void Read_File(std::string path);
 void Record_File(char * path); // It reads whole of file in therms of cstring
 void Record_File(std::string target_path);
 bool Is_Path_Exist(std::string path);
 bool Is_Path_Exist(char * path);
 bool Is_This_File_Empty(char * path);
 bool Is_This_File_Empty(std::string path);
 bool TryOpen(char path);
 int  GetFileSize() const;
 std::string GetFilePath() const;
 std::string GetFileLine(int lnbr);
 void Printf();
 void Clear_Dynamic_Memory();
private:
 void Initialize_Members();
 char * Convert_Std_String_To_CString(std::string st);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_CString_Memory(char ** ptr);
 void Clear_Temporary_CString_Memory();
 void DetermineCurrentDirectory();
 void Place_String(char ** Pointer, char * String, int String_Size);
 bool Is_Current_Dir_Symbol_Exist_On_the_File_Path(char * path);
 void Find_Start_Point_When_Current_Dir_Symbol_Exist(char * path, int & start_point);
 void Determine_File_Path(char * path);
 std::fstream DataFile;
 std::string String_Line;
 std::string string_word;
 std::string FilePath;
 bool Memory_Delete_Condition;
 bool Is_File_Empty;
 std::vector<std::string> File_Content;
 char Open_Mode_Determiner;
 char opr_sis;
 char * CurrentDirectory;
 char * c_str;
 int  File_line_Number;
 int  Delete_Return_Status;
 int  FileDeleteCondition;
 bool isFilePathReceive;
 bool Read_Stop_Condition;
 bool is_path_exist;
 bool file_open_status;
};

#endif /* CPP_FILEOPERATIONS_H */
