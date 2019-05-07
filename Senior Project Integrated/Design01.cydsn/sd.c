//Jacob Thomas
//Senior Project TCNJ 2019

#include <FS.h>
#include <Global.h>
#include "string.h"
#include "stdio.h"
#include "sd.h"
#include "uifunctions.h"
#include "project.h"

//*************************************spi_device_select***************************************//
//                                                                                             //
//                                                                                             //
//              Sets the SD and SPIM pins so they do not interfere with each other             //
//                                                                                             //
//                                                                                             //
//*************************************spi_device_select***************************************//
void spi_device_select(int selection)
{
    if(selection == SCREEN_SELECT)
    {
        emFile_1_mosi0_SetDriveMode(emFile_1_mosi0_DM_DIG_HIZ);
        emFile_1_sclk0_SetDriveMode(emFile_1_sclk0_DM_DIG_HIZ);
        
        
        MOSI_SetDriveMode(MOSI_DM_STRONG);
        MISO_SetDriveMode(MISO_DM_STRONG);
        CLK_SetDriveMode(CLK_DM_STRONG);
        
    } else if (selection == SD_SELECT)
    {
        emFile_1_mosi0_SetDriveMode(emFile_1_mosi0_DM_STRONG);
        emFile_1_sclk0_SetDriveMode(emFile_1_sclk0_DM_STRONG);
        
        MOSI_SetDriveMode(MOSI_DM_DIG_HIZ);
        MISO_SetDriveMode(MISO_DM_DIG_HIZ);
        CLK_SetDriveMode(CLK_DM_DIG_HIZ);
    }
}
    

//****************************************create_file_with_text*********************************//
//                                                                                              //
//                                                                                              //
//              creates a fle or overwrites a text file with a beginning message                //
//                                                                                              //
//                                                                                              //
//****************************************create_file_with_text*********************************//
void create_file_with_text(char * file_name, char * text)
{
    //char * file_name name + extension of file to be overwritten
    //char * text text to be written to file
    FS_FILE * pFile;
    
    pFile = FS_FOpen(file_name, "w+");
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
}

//****************************************append_file*******************************************//
//                                                                                              //
//                                                                                              //
//                              appends a text file with text                                   //
//                                                                                              //
//                                                                                              //
//****************************************append_file*******************************************//
void append_file(char * file_name, char * text)
{
    //char * file_name name + extension of file to be appended 
    //char * text text to be written to file
    FS_FILE * pFile;
    pFile = FS_FOpen(file_name, "a");
    FS_Write(pFile,text,strlen(text));
    FS_FClose(pFile);
}

//*************************************write_header_info****************************************//
//                                                                                              //
//                      This function is exclusive to the Curve Tracer                          //
//                      This will write the unit note for currents and settings                 //
//                      It will also label Vgs/Ib, Ic/Id, and Vds/Vce                           //
//                                                                                              //
//*************************************write_header_info****************************************//
void write_header_info(char * file_name, unsigned char curve_num, double Vgs_double[])
{
    spi_device_select(SD_SELECT);
    //file_name is the char array of the file with extension to be overwritten
    //device_selection is the type of test (NMOS, NPN,PMOS,PNP) being run effects label
    //curve num is the current VGS iteration
    //Vgs_double is the Vgs/Ib (in reality) in double format 
    char y_label[2][3];
    strcpy(y_label[0], "Id"); //N Type Test
    strcpy(y_label[1], "Ic"); //P Type Test 
    char x_label[2][4];
    strcpy(x_label[0],"Vds"); //N Type Test
    strcpy(x_label[1],"Vce"); //P Type Test
    char legend_label[2][4];
    strcpy(legend_label[0], "Vgs"); //N Type Test
    strcpy(legend_label[1], "Ib");  //P Type Test
    char temp_str[5];
    char beginning_message[] = "*Note all currents are in mA, all other units are SI*\n";
    char options_str[35];
    if(curve_num != 0)
    {
        create_file_with_text(file_name, beginning_message);
        sprintf(options_str,"Averages Per Point: %d\n",num_avg);
        append_file(file_name,options_str);
        sprintf(options_str,"Cooldown milliseconds: %d\n",cooldown_time);
        append_file(file_name,options_str);
    }
    //Vgs = x.xxx OR Ib = x.xxx
    append_file(file_name,legend_label[device_selection%2]);
    append_file(file_name,"=");
    sprintf(temp_str,"%.3f",Vgs_double[curve_num]); //write Vgs/Ib double to string
    //Id;Vds OR Ic;Vce
    append_file(file_name,temp_str);//print Vgs/Ib value to CSV
    append_file(file_name,"\n");//create new lne
    append_file(file_name,y_label[device_selection%2]);
    append_file(file_name,",");//comma seperation
    append_file(file_name,x_label[device_selection%2]);
    append_file(file_name,"\n");//create new line
    spi_device_select(SCREEN_SELECT);
}

//****************************************write_data********************************************//
//                                                                                              //
//                                                                                              //
//                              writes the curve tracer data to SD                              //
//                                                                                              //
//                                                                                              //
//****************************************write_data********************************************//
void write_data(char * file_name, double Id, unsigned char Vds_code)
{
    spi_device_select(SD_SELECT);
    char temp_str[10];  //temp string to be used to move doubles to
    double Vds;         //Used to convert the VDAC code to real value
    if(device_selection < 2)
    {
        Vds = Vds_code/256.0*4.096*3; //Vds double in N Type tests
    }
    else
    {
        Vds = Vds_code/256.0*4.096*4;//Vds double in P Type Tests
    }
    sprintf(temp_str,"%9f",Id);
    append_file(file_name,temp_str);//print Id Value
    append_file(file_name,",");//comma sepeperation
    sprintf(temp_str,"%5f",Vds);
    append_file(file_name,temp_str); //print Vds value
    append_file(file_name,"\n");//create new line
    spi_device_select(SCREEN_SELECT);
}