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

#include "IntToCharTranslater.h"

IntToCharTranslater::IntToCharTranslater(){

    this->char_number = nullptr;

    this->int_number = 0;

    this->Memory_Empty_Status = true;
}

IntToCharTranslater::IntToCharTranslater(const IntToCharTranslater & oring){

}

IntToCharTranslater::~IntToCharTranslater(){

     if(!this->Memory_Empty_Status){

         this->Clear_Character_Memory();
     }
}

void IntToCharTranslater::Clear_Character_Memory()
{
     if(this->char_number != nullptr){

        delete [] this->char_number;

        this->char_number = nullptr;
     }

     this->Memory_Empty_Status = true;
}

void IntToCharTranslater::Fill_Character_Memory(std::string string_number)
{
     this->Memory_Empty_Status = false;

     int string_lenght = string_number.length();

     this->char_number = new char [5*string_lenght];

     int index_counter = 0;

     for(int i=0;i<string_lenght;i++){

         this->char_number[index_counter] = string_number[i];

         index_counter++;
     }

     this->char_number[index_counter] = '\0';
}


char * IntToCharTranslater::Translate(int integer){

       this->temp_str = std::to_string(integer);

       this->Clear_Character_Memory();

       this->Fill_Character_Memory(this->temp_str);

       return this->char_number;
}

int IntToCharTranslater::TranslateFromCharToInt(char * ch){

    this->int_number = atoi(ch);

    return this->int_number;
}
