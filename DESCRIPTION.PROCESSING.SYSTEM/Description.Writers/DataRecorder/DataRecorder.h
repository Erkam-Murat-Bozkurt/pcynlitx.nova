
#ifndef DATARECORDER_H
#define DATARECORDER_H

#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include <cstring>
#include <string>

class DataRecorder
{
public:
  DataRecorder(char * Path, char opr_sis);
  virtual ~DataRecorder();
  void Add_Data_Record(char * Data_Type, char * Data_Record);
  void Clear_Data_Record(char * Data_Type);
  void Replace_Data_Record(char * Data_Record);
  void Collect_Information_For_Data_Recording(char * Record_Type);
  void Collect_Information_For_Data_Clearing(char * Record_Type);
  void Determine_Data_Type_Record_Number(char * Data_Type);
  void Read_Data_Records(char * Data_Type);
  int  Determine_Record_Point(char * Record_Type);
  int  Determine_Data_Record_Start_Point(char * Data_Type);
  int  Determine_Data_Record_End_Point(char * Data_Type);
  void Read_Before_Record_Point(int read_start_point);
  void Read_After_Record_Point(int read_start_point);
  void Record_Data(char * Data);
  void Clear_Dynamic_Memory();
  char ** Get_Up_Record();
  char ** Get_Down_Record();
  char ** Get_Data_Type_Records();
  int Get_Up_Record_Number();
  int Get_Down_Record_Number();
  int Get_Data_Type_Record_Number();
  int Get_Record_Point();
  int Get_Data_Record_Start_Point();
private:
  bool Determine_Is_This_Line_A_Record_Line(std::string File_Line);
  bool Is_This_First_Brace(char * string);
  bool Is_This_Last_Brace(char * string);
  bool Is_This_Inside_of_Record_Area(char * string);
  StringOperator StringOperations;
  Cpp_FileOperations File_Manager;
  char ** Up_Record;
  char ** Down_Record;
  char ** Data_Records;
  bool Memory_Delete_Condition;
  bool is_this_a_record_line;
  bool is_this_a_brace_line;
  bool is_this_on_the_inside_of_record_area;
  bool Enter_Record_Area;
  int Data_Record_Start_Point;
  int Data_Record_End_Point;
  int Up_Record_Number;
  int Down_Record_Number;
  int Record_Point;
  int End_of_File;
  int Data_Type_Record_Number;
  int Data_Records_Number;
};

#endif /* DATARECORDER_H */
