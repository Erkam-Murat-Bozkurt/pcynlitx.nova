
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



#include "CMAKE_System_Constructor.hpp"

CMAKE_System_Constructor::CMAKE_System_Constructor(char * DesPath, char opr_sis, char build_type) :

     Meta_Data_Collector(DesPath,opr_sis,build_type), CMK_MF_Builder(opr_sis)
{
     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;

     this->Des_Path = DesPath;
     
     this->build_type = build_type;
}


CMAKE_System_Constructor::~CMAKE_System_Constructor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_System_Constructor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(this->repo_obj_dir);

         this->Clear_String_Memory(this->Warehouse_Path);

         this->Clear_String_Memory(this->Repo_Dir);
     }
}


void CMAKE_System_Constructor::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;

     this->Meta_Data_Collector.Receive_System_Interface(sysInt);

}


void CMAKE_System_Constructor::Build_Make_Files(std::string project_name, std::string version_num)
{
     this->Meta_Data_Collector.Collect_Meta_Data();

     this->Compiler_Data_Pointer = this->Meta_Data_Collector.Get_Compiler_Data();

     this->Write_Main_CMakeLists_File(project_name,version_num);

     this->Perform_MakeFile_Construction();
}





void CMAKE_System_Constructor::Write_Main_CMakeLists_File(std::string project_name,
    
     std::string version_num){

     const Descriptor_File_Reader * Des_Reader = 
     
          this->Meta_Data_Collector.Get_Descriptor_File_Reader();
  
     const Source_File_Dependency_Determiner * Dep_Determiner = 
     
          this->Meta_Data_Collector.Get_Source_File_Dependency_Determiner();


     this->CMK_MF_Builder.Receive_Project_Titles(project_name,version_num);

     this->CMK_MF_Builder.Receive_Descriptor_File_Reader(Des_Reader);

     this->CMK_MF_Builder.Receive_Source_File_Dependency_Determiner(Dep_Determiner);
    
     this->CMK_MF_Builder.Build_Main_CMAKE_File();

     std::cout << "CMAKE main file writed..";
}



void CMAKE_System_Constructor::Construct_For_Large_Data_Set(size_t data_size){

     size_t str=0, end=0;

     size_t thread_num = data_size/50;

     if(thread_num > 64){

        thread_num = 64;
     }

     size_t remaining_job = 0;

     size_t range = this->Split_Range(data_size,thread_num,remaining_job);


     for(int i=0;i<thread_num;i++){

         if(i==0){

            str = 0;

            end = range;
         }
         else{

            str  = end;

            end  = end + range;

            if(remaining_job > 0){

               end = end+1;

               remaining_job--;
            }
         }

         if(i==(thread_num-1)){
            
               end = data_size;
         }

         this->threadPool.push_back(std::thread(&CMAKE_System_Constructor::Write_MakeFiles,this,str,end));
     }
    
     for(size_t i=0;i<thread_num;i++){
            
         this->threadPool[i].join();
     }
}



void CMAKE_System_Constructor::Construct_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(&CMAKE_System_Constructor::Write_MakeFiles,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }
}



void CMAKE_System_Constructor::Construct_For_Small_Data_Set(size_t data_size){

     this->Write_MakeFiles(0,data_size);    
}



void CMAKE_System_Constructor::Perform_MakeFile_Construction(){

    

     size_t data_size = this->Compiler_Data_Pointer->size();

     if(data_size > 50){

        this->Construct_For_Large_Data_Set(data_size);        
     }
     else{

         if(data_size>16){

             this->Construct_For_Middle_Data_Set(data_size);
         }
         else{

             this->Construct_For_Small_Data_Set(data_size);
         }
     }

     char construction_result [] = "\nThe new makefiles have been constructed..\n";

     std::cout << "\n";
     std::cout << construction_result;
     std::cout << "\n";
     std::cout << "\n";

     if(this->build_type == 'g'){

       this->SysInt->WriteTo_NamedPipe_FromChild(construction_result);
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}



size_t CMAKE_System_Constructor::Split_Range(size_t range_size, size_t partition, size_t & remaining_job){

    if(range_size ==0){

        range_size = 1;
    }

    if(partition == 0){

       partition = 1;
    }

    int range  = range_size/partition; 

    if(range<1){

        range = 1;
    }

    remaining_job = range_size - range*partition;

    return range;    
}

void CMAKE_System_Constructor::Write_MakeFiles(int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();


     const Descriptor_File_Reader * Des_Reader = this->Meta_Data_Collector.Get_Descriptor_File_Reader();
 
     Git_Data_Processor * Data_Processor = this->Meta_Data_Collector.Get_Git_Data_Processor();
 
     CMAKE_Target_Library_Builder Target_Builder;

     Target_Builder.Receive_Operating_System(this->opr_sis);

     Target_Builder.Receive_Descriptor_File_Reader(Des_Reader);

     Source_File_Dependency_Determiner Dp_Determiner(this->Des_Path,this->opr_sis);

     Dp_Determiner.Receive_Descriptor_File_Reader(Des_Reader);

     Dp_Determiner.Receive_Git_Data_Processor(Data_Processor);

    
     for(size_t i=start;i<end;i++){

         std::string source_file_path = this->Compiler_Data_Pointer->at(i).source_file_path;

         Dp_Determiner.Simple_Dependency_Determination_For_Single_Source_File(source_file_path);

         const Simple_Source_File_Dependency * data_ptr = Dp_Determiner.Get_Simple_File_Dependencies();

         Target_Builder.Receive_Simple_Dependency_Data(data_ptr);

         Target_Builder.Build_MakeFile(source_file_path);

         
         mt.lock();

         Target_Builder.Add_Target_Path_To_Directory_List();

         Target_Builder.Construct_SubDirectory_List_File();

         mt.unlock();


         Target_Builder.Clear_Dynamic_Memory();

         Dp_Determiner.Clear_Dynamic_Memory();
     }
}


void CMAKE_System_Constructor::Construct_Path(std::string * pointer, std::string string, 

     std::string warehouse_path){

     int index = 0;

     size_t warehouse_path_size = warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         pointer->push_back(warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){
      
        if(pointer->back() != '\\'){
         
           pointer->push_back('\\');         
        }      
     }
     else{
      
          if(this->opr_sis == 'l'){
           
            if(pointer->back() != '/'){
         
               pointer->push_back('/');         
            }      
         }      
     }

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         pointer->push_back(string[i]);
     }
}





void CMAKE_System_Constructor::Clear_Vector_Memory(std::vector<std::string> & vec){

    vec.shrink_to_fit();

    for(size_t i=0;i<vec.size();i++){

        this->Clear_String_Memory(vec.at(i));
    }

    vec.shrink_to_fit();

    vec.clear();
}




void CMAKE_System_Constructor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}