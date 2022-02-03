
#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(){


  this->file_path = nullptr;
  this->standard = nullptr;
  this->debugging = false;
  this->Include_Directories = nullptr;
  this->Source_File_Directories = nullptr;
  this->Library_Directories = nullptr;
  this->Library_Names = nullptr;
  this->Memory_Delete_Condition = false;

}


Descriptor_File_Reader::Descriptor_File_Reader(const Descriptor_File_Reader & orig){


}

Descriptor_File_Reader::~Descriptor_File_Reader(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }


}

void Descriptor_File_Reader::Read_Descriptor_File_Path(char * path){


}

void Descriptor_File_Reader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }

}


void Descriptor_File_Reader::Read_Standard(){

}


void Descriptor_File_Reader::Read_Include_Directories(){

}


void Descriptor_File_Reader::Read_Source_File_Directories(){

}


void Descriptor_File_Reader::Read_Library_Directories(){


}


void Descriptor_File_Reader::Read_Library_Names(){


}


void Descriptor_File_Reader::Read_Debugging_Option(){


}


char ** Descriptor_File_Reader::Get_Library_Names(){


}


char ** Descriptor_File_Reader::Get_Library_Directories(){


}


char ** Descriptor_File_Reader::Get_Source_File_Directories(){


}


char ** Descriptor_File_Reader::Get_Include_Directories(){


}


char * Descriptor_File_Reader::Get_Standard(){


}


bool Descriptor_File_Reader::Get_Debugging_Option(){


}
