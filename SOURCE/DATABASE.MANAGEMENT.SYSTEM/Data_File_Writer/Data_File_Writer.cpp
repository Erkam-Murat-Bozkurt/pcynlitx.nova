/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */




#include "Data_File_Writer.hpp"


Data_File_Writer::Data_File_Writer(){

      this->file_path = nullptr;

      this->Memory_Delete_Condition = true;
}

Data_File_Writer::Data_File_Writer(const Data_File_Writer & orig){


}


Data_File_Writer::~Data_File_Writer(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}

void Data_File_Writer::Clear_Dynamic_Memory(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        delete [] this->file_path;
    }

}

void Data_File_Writer::Receive_Source_File_Data(Script_Data * data){

     this->Data_Ptr = data;
}

void Data_File_Writer::Build_Data_File(char * path){

     this->Receive_File_Path(path);

     int new_lines = 3;

     this->FileManager.SetFilePath(this->file_path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("DATA FILE FOR SOURCE FILE: ");

     this->FileManager.WriteToFile(this->Data_Ptr->source_file_name);

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("// HEADER FILES DATA RECORDS //");

     for(int i=0;i<50;i++){

         this->FileManager.WriteToFile("-");
     }

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("[INCLUDED-HEADER-NUMBER]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[INCLUDED-HEADER-FILE-NAMES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[HEADER-FILES-GIT-RECORD-DIRECTORIES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("// SOURCE FILE RECORDS //");

     for(int i=0;i<50;i++){

         this->FileManager.WriteToFile("-");
     }

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[SOURCE-FILE-NAME]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[SOURCE-FILE-DIRECTORY]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);



     this->FileManager.WriteToFile("[SOURCE-FILE-GIT-RECORD-DIRECTORY]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);



     this->FileManager.WriteToFile("// DEPENDENCY DATA //");

     for(int i=0;i<50;i++){

         this->FileManager.WriteToFile("-");
     }


     this->FileManager.WriteToFile("[DEPENDENCIES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);



     this->FileManager.WriteToFile("[DEPENDENCY-NUMBER]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("// MAKE FILE DATA //");

     for(int i=0;i<50;i++){

         this->FileManager.WriteToFile("-");
     }


     this->FileManager.WriteToFile("[MAKE-FILE-NAME]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[OBJECT-FILE-NAME]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[BUILD-REPOSITORY-PATH]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[END]:");

     this->WriteNewLines(new_lines);

     this->FileManager.FileClose();
}

void Data_File_Writer::Receive_File_Path(char * path){

     this->Memory_Delete_Condition = false;

     this->file_path = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<path_size;i++){

        this->file_path[index] = path[i];

        index++;
     }

     this->file_path[index] = '\\';

     index++;

     for(size_t i=0;i<name_size;i++){

        this->file_path[index] = Descriptor_File_Name[i];

        index++;
     }

     this->file_path[index] = '\0';
}


void Data_File_Writer::WriteNewLines(int line_number){

     for(int i=0;i<line_number;i++){

        this->FileManager.WriteToFile("\n");
     }
}
