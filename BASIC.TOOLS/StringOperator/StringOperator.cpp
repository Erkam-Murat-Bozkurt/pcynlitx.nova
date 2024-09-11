
/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "StringOperator.h"


StringOperator::StringOperator()
{
   this->Initialize_Members();
}


StringOperator::StringOperator(char opr_sis) :

   CharacterOperations(opr_sis), Cpp_File_Manager(opr_sis)
{
   this->Initialize_Members();
}

StringOperator::~StringOperator(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}


void StringOperator::Receive_Operating_System(char opr_sis){

     this->Cpp_File_Manager.Receive_Operating_System(opr_sis);

     this->opr_sis = opr_sis;
}

void StringOperator::SetFilePath(char * FilePATH){

     this->Cpp_File_Manager.SetFilePath(FilePATH);

     this->CharacterOperations.SetFilePath(FilePATH);
}


void StringOperator::SetFilePath(std::string FilePATH){

     this->Cpp_File_Manager.SetFilePath(FilePATH);

     this->CharacterOperations.SetFilePath(FilePATH);
}


void StringOperator::Initialize_Members(){

     this->StringBuffer = "";

     this->isBufferEmpty = false;

     this->Included_Word_Start_Position = 0;

     this->Included_Word_Start_Position_Set_Condition = false;

     this->Memory_Delete_Condition = false;

     this->Word_Count = 0;
}

void StringOperator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Cpp_File_Manager.Clear_Dynamic_Memory();

         if(!this->StringBuffer.empty()){

             this->StringBuffer.clear();

             this->StringBuffer.shrink_to_fit();
         }

         this->CharacterOperations.Clear_Dynamic_Memory();
     }
}

size_t StringOperator::GetBufferLength(){

    this->BufferLength = this->StringBuffer.length();

    return this->BufferLength;
}

bool StringOperator::CheckStringLine(char * readedline){

     this->isStringLine = false;

     bool isNewLine = false , isNull = false;

     if(readedline[0] == '\n'){

        isNewLine = true;
     }

     if(readedline[0] == '\0'){

        isNull = true;
     }

     if((!isNewLine) && (!isNull)){

          this->isStringLine = true;
     }

     return this->isStringLine;
}


bool StringOperator::CheckStringLine(std::string readedline){

     this->Delete_Spaces_on_String(&readedline);

     this->isStringLine = false;

     bool isNewLine = false , isNull = false;

     if(readedline[0] == '\n'){

        isNewLine = true;
     }

     if(readedline[0] == '\0'){

        isNull = true;
     }

     if((!isNewLine) && (!isNull)){

          this->isStringLine = true;
     }

     return this->isStringLine;
}


void StringOperator::Delete_Spaces_on_String(std::string * str)
{
     while((*str)[0] == ' '){

         str->erase(0,1);
     }
   
     bool search_cond = true;

     do{

        search_cond = false;

        for(size_t i=0;i<str->length();i++){

           if( ((*str)[i] == ' ') || ((*str)[i] == '\t') ){

              search_cond = true;

              str->erase(i,1);
           }
        }

     }while(search_cond);
}

void StringOperator::LoadStringBuffer(std::string ReadLine){

     if(!this->StringBuffer.empty()){

        this->StringBuffer.clear();

        this->StringBuffer.shrink_to_fit();
     }

     this->StringBuffer = ReadLine;
}

std::string StringOperator::GetStringBuffer(){

       return this->StringBuffer;
}

void StringOperator::ReceiveFileLine(std::string ReadLine){

     int spaceCounter=0;

     if(this->CheckStringLine(ReadLine)){

         while(ReadLine[spaceCounter]== ' ') {   // This loop corp the spaceses in the same line the readed word ..

               spaceCounter++;

               if(spaceCounter>500){

                  break;
               }
        };

        this->LoadStringBuffer(ReadLine);
    }
    else{

        std::string empty_string = "";

        this->LoadStringBuffer(empty_string);
    }
}

int StringOperator::FindNextWordLine(std::string search_word,int startPoint){

    this->Cpp_File_Manager.FileOpen(Rf);

    this->CharacterOperations.ForwardFilePointer(&this->Cpp_File_Manager,startPoint);

    int word_line = 0, search_line = 0;

    do{
            std::string string_line = this->Cpp_File_Manager.Read();

            if(this->Cpp_File_Manager.Control_Stop_Condition()){

               break;
            }

            if(this->CheckStringLine(string_line)){

               this->ReceiveFileLine(string_line);


               bool include_condition

                = this->CheckStringInclusion(this->GetStringBuffer(),search_word);


               if(include_condition){

                  word_line = search_line;

                  break;
               }
               else{
                     search_line++;
               }
            }
            else{

                search_line++;
            }

    }while(!this->Cpp_File_Manager.Control_Stop_Condition());

    this->Cpp_File_Manager.FileClose();

    return word_line;
}


bool StringOperator::Is_String_Exist_On_File(std::string search_word){

     bool is_exist = false;

     this->Cpp_File_Manager.FileOpen(Rf);

     int search_line = 0, start_point = 0;

     this->CharacterOperations.ForwardFilePointer(&this->Cpp_File_Manager,start_point);


    do{
            std::string string_line = this->Cpp_File_Manager.Read();

            if(this->Cpp_File_Manager.Control_Stop_Condition()){

               break;
            }

            if(this->CheckStringLine(string_line)){

               this->ReceiveFileLine(string_line);


               bool include_condition

                = this->CheckStringInclusion(string_line,search_word);


               if(include_condition){

                  is_exist = true;

                  break;
               }
            }


    }while(!this->Cpp_File_Manager.Control_Stop_Condition());

    this->Cpp_File_Manager.FileClose();

    return is_exist;
}

std::string StringOperator::ReadFileLine(int lineNumber){

       this->Cpp_File_Manager.FileOpen(Rf);

       this->CharacterOperations.ForwardFilePointer(&this->Cpp_File_Manager,lineNumber);

       std::string line = this->Cpp_File_Manager.ReadLine();

       this->ReceiveFileLine(line);

       this->Cpp_File_Manager.FileClose();

       return this->GetStringBuffer();
}


bool StringOperator::CheckStringInclusion(std::string StringLine, std::string search_word){

     this->includeCondition = false;

     int indexCounter = 0;

     int stringSize = StringLine.length();

     int wordSize = search_word.length();

     if(stringSize < wordSize){

        this->includeCondition = false;

        return this->includeCondition;
     }

     for(int i=0;i<stringSize;i++){

         indexCounter = 0;

         if(StringLine[i] == search_word[indexCounter]){

            this->Included_Word_Start_Position = i;

            while(StringLine[i] == search_word[indexCounter]){

                  if(indexCounter == wordSize -1){

                     this->includeCondition = true;

                     return this->includeCondition;
                  }

                  i++;

                  indexCounter++;
            }
         }
      }

      return this->includeCondition;
}

bool StringOperator::CompareString(std::string s1, std::string s2)
{
     return this->CharacterOperations.CompareString(s1,s2);
}


int StringOperator::Get_Start_Position_of_an_included_String(){

    return this->Included_Word_Start_Position;
}
