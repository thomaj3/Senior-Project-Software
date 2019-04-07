/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#include <FS.h>
#include <Global.h>
#include "string.h"
#include "stdio.h"
#include "sd.h"

//unsigned int move_file_with_same_name(char file_name[], unsigned int i)
//{
//    char file_name_ext[5];
//    char file_name_title[strlen(file_name)+1];
//    char new_file_name[strlen(file_name)+2];
//    
//    strcpy(file_name_ext,&file_name[strlen(file_name)-4]);
//    strncpy(file_name_title
//    //determine if file exists
//    strcat(new_file_name
//    FS_Rename(file_name,
//}

//used to create or overwrite a file
void create_file_with_text(char * file_name, char * text)
{
    FS_FILE * pFile;
    
    FS_Remove(file_name);
    pFile = FS_FOpen(file_name, "w");
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
}

//used to append a file
void append_file(char * file_name, char * text)
{
    FS_FILE * pFile;
    pFile = FS_FOpen(file_name, "a");
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
}

void write_header_info(char * file_name, unsigned char device_selection, unsigned char curve_num, double Vgs_double[])
{
    char y_label[2][3];
    strcpy(y_label[0], "Id");
    strcpy(y_label[1], "Ic");
    char x_label[2][4];
    strcpy(x_label[0],"Vds");
    strcpy(x_label[1],"Vce");
    char legend_label[2][4];
    strcpy(legend_label[0], "Vgs");
    strcpy(legend_label[1], "Ib");
    char temp_str[5];
    char beginning_message[] = "*Note all currents are in mA, all other units are SI*\n";
    if(!curve_num)
    {
        create_file_with_text(file_name, beginning_message);
    }
    //Vgs = x.xxx OR Ib = x.xxx
    append_file(file_name,legend_label[device_selection/2]);
    append_file(file_name,"=");
    sprintf(temp_str,"%.3f",Vgs_double[curve_num]);
    //Id;Vds OR Ic;Vce
    append_file(file_name,temp_str);
    append_file(file_name,"\n");
    append_file(file_name,y_label[device_selection/2]);
    append_file(file_name,",");
    append_file(file_name,x_label[device_selection/2]);
    append_file(file_name,"\n");
}

void write_data(char * file_name, double Id, unsigned char Vds_code, unsigned char device_selection)
{
    char temp_str[10];
    double Vds;
    if(device_selection < 2)
    {
        Vds = Vds_code/256.0*4.096*3;
    }
    else
    {
        Vds = Vds_code/256.0*4.096*4;
    }
    sprintf(temp_str,"%9f",Id);
    append_file(file_name,temp_str);//print Id Value
    append_file(file_name,",");
    sprintf(temp_str,"%5f",Vds);
    append_file(file_name,temp_str); //print Vds value
    append_file(file_name,"\n");
}