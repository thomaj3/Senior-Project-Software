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
    
    #define DEVICE_SELECTION_SCREEN     0
    #define OPTIONS_SCREEN              1
    #define PLOT_SCREEN                 2
    #define OPTION_AVERAGES_SCREEN      3
    #define OPTION_SD_SCREEN            4
    #define OPTION_CURVES_SCREEN        5
    #define OPTION_GRID_SCREEN          6
    #define DEBUG_SCREEN                7
    #define DEBUG_WARNING_SCREEN        8
    #define NMOS                        0
    #define NPN                         1
    #define PMOS                        2
    #define PNP                         3

#endif /* (UIFUNCTIONS_H) */