
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


#include "CharOperator.h"

CharOperator::CharOperator(){

     this->Memory_Delete_Condition = false;

}

CharOperator::CharOperator(char opr_sis) : FileManager (opr_sis) {

    this->Memory_Delete_Condition = false;
}

CharOperator::~CharOperator(){

  if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
   }
}

void CharOperator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->FileManager.Clear_Dynamic_Memory();
     }
}

void CharOperator::SetFilePath(char * FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}


void CharOperator::SetFilePath(std::string FilePATH){

     this->FileManager.SetFilePath(FilePATH);
}

void CharOperator::ForwardFilePointer(Cpp_FileOperations * FileManager,int stepSize){

    for(int i=0;i<stepSize-1;i++){

        FileManager->ReadLine();
    }
}



int CharOperator::FindNextCharacterPositon(std::string targetList, int startPoint, char c){

     this->CharacterPosition = 0;

     int ListSize = targetList.length();

     int Position = startPoint;

     while(targetList[Position]!= c){

          Position++;

          if(Position == ListSize){

              this->CharacterPosition = Position;

              break;
          }
     };

     this->CharacterPosition = Position;

     return this->CharacterPosition;
}


int CharOperator::DetermineCharacterRepitation(std::string list, char c){

     this->CharacterRepitation = 0;

     size_t ListSize = list.length();

     for(size_t k=0;k<ListSize+1;k++){

          if(list[k]== c){

             this->CharacterRepitation++;
          }
     }

     return this->CharacterRepitation;
}

int CharOperator::FindTheSpecificWordLine(std::string word){

     this->FileManager.FileOpen(Rf);

     this->WordPosition = 0;

     std::string buffer = " ";

     while(true){

           buffer = this->FileManager.Read();

           if(buffer != word){

              break;
           }

           bool end_of_file = this->FileManager.Control_Stop_Condition();

           if(end_of_file){

              break;
           }

           this->WordPosition++;
      }

      this->FileManager.FileClose();

      return this->WordPosition;
}


bool CharOperator::CharacterCheck(std::string list,char character){

    int listLength;

    listLength = list.length();

    for(int i=0;i<listLength;i++){

         if(list[i]== character){

             return true;
         }
    }

    return false;
}


int CharOperator::FindFirstCharacterPosition(std::string list){

    this->FirstCharacterPosition = 0;

    while(list[this->FirstCharacterPosition]==' '){

          this->FirstCharacterPosition++;
    }

    return this->FirstCharacterPosition;
}


bool CharOperator::CompareString(std::string firstString, std::string secondString){

     int firstStringLength  = firstString.length();

     int secondStringLength = secondString.length();

     if(firstStringLength==secondStringLength){

        for(int i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

          this->isStringsEqual = false;

          return this->isStringsEqual;
     }
}
