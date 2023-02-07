
/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "CharOperator.h"

CharOperator::CharOperator(){

     this->Memory_Delete_Condition = false;

}

CharOperator::CharOperator(char * FilePath) : FileManager (FilePath) {

    this->Memory_Delete_Condition = false;
}

CharOperator::CharOperator(std::string FilePath): FileManager (FilePath){


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


void CharOperator::ForwardFilePointer(Cpp_FileOperations * FileManager,int stepSize){

    for(int i=0;i<stepSize-1;i++){

        FileManager->Read();
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

     for(int k=0;k<ListSize+1;k++){

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
