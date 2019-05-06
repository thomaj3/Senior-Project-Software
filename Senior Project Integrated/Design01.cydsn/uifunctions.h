// Steven Andresen
//Senior Project Spring 2019

#if !defined(UIFUNCTIONS_H)
#define UIFUNCTIONS_H

    extern int screen_state;
    extern int device_selection;
    extern int curve_nums;
    extern int write_sd;
    extern int num_avg;
    extern int draw_grid;
    extern int rand_num_1;
    extern int rand_num_2;
    extern int cooldown_time;
    extern int vds_high;
    extern int vds_high_vdac_code;
    
    #define DEVICE_SELECTION_SCREEN     0
    #define OPTIONS_SCREEN              1
    #define PLOT_SCREEN                 2
    #define OPTION_AVERAGES_SCREEN      3
    #define OPTION_SD_SCREEN            4
    #define OPTION_CURVES_SCREEN        5
    #define OPTION_GRID_SCREEN          6
    #define DEBUG_SCREEN                7
    #define OPTIONS_SCREEN_2            8
    #define OPTION_COOLDOWN_SCREEN      9
    #define OPTION_VDS_SCREEN           10
    #define WARNING_SCREEN              11
    #define NMOS                        0
    #define NPN                         1
    #define PMOS                        2
    #define PNP                         3

#endif /* (UIFUNCTIONS_H) */