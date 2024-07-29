
#include "Empty_Descriptor_File_Builder.hpp"


Empty_Descriptor_File_Builder::Empty_Descriptor_File_Builder(char opr_sis){

      this->file_path = nullptr;

      this->Memory_Delete_Condition = true;

      this->opr_sis = opr_sis;
}

Empty_Descriptor_File_Builder::Empty_Descriptor_File_Builder(const Empty_Descriptor_File_Builder & orig){


}


Empty_Descriptor_File_Builder::~Empty_Descriptor_File_Builder(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}

void Empty_Descriptor_File_Builder::Clear_Dynamic_Memory(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        delete [] this->file_path;

        this->FileManager.Clear_Dynamic_Memory();
    }

}

void Empty_Descriptor_File_Builder::Receive_File_Path(char * path){

     char Descriptor_File_Name [] = "Pcb_Descriptor.txt";

     size_t path_size = strlen(path);

     size_t name_size = strlen(Descriptor_File_Name);

     this->Memory_Delete_Condition = false;

     this->file_path = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<path_size;i++){

        this->file_path[index] = path[i];

        index++;
     }

     if(this->opr_sis == 'w'){

        this->file_path[index] = '\\';
     }

     if(this->opr_sis == 'l'){

        this->file_path[index] = '/';
     }

     index++;

     for(size_t i=0;i<name_size;i++){

        this->file_path[index] = Descriptor_File_Name[i];

        index++;
     }

     this->file_path[index] = '\0';
}

void Empty_Descriptor_File_Builder::Build_Empty_File(char * path){

     this->Receive_File_Path(path);

     int new_lines = 3;

     this->FileManager.SetFilePath(this->file_path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("DESCRIPTOR FILE FOR PCYNLITX BUILD SYSTEM");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("[PROJECT-ROOT-DIR]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[PROJECT-WAREHOUSE-LOCATION]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[C++-STANDARD]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("[BUILD-SYSTEM]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[PROJECT-NAME]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[VERSION-NUMBER]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);

     

     this->FileManager.WriteToFile("[INCLUDE-DIRECTORIES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[SOURCE-FILE-DIRECTORIES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[LIBRARY-DIRECTORIES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);



     this->FileManager.WriteToFile("[LIBRARY-FILES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[COMPILER-OPTIONS]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("[LINKER-OPTIONS]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[MAIN-FILE-NAMES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[EXECUTABLE-FILE-NAMES]{");

     this->WriteNewLines(new_lines);

     this->FileManager.WriteToFile("}");

     this->WriteNewLines(new_lines);


     this->FileManager.WriteToFile("[END]:");

     this->WriteNewLines(new_lines);

     this->FileManager.FileClose();
}

void Empty_Descriptor_File_Builder::WriteNewLines(int line_number){

     for(int i=0;i<line_number;i++){

        this->FileManager.WriteToFile("\n");
     }
}
