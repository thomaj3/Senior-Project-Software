# THIS FILE IS AUTOMATICALLY GENERATED
<<<<<<< HEAD
# Project: C:\Users\legoc\Documents\School\Senior Year\Senior Project\Senior Project Integrated\Senior Project Integrated\Design01.cydsn\Design01.cyprj
# Date: Mon, 06 May 2019 03:34:16 GMT
=======
# Project: C:\Users\Jacob-Laptop\Documents\PSoC Creator\Senior Project Stuff Backup - Copy\Senior Project Integrated\Design01.cydsn\Design01.cyprj
# Date: Fri, 26 Apr 2019 16:58:41 GMT
>>>>>>> 2d7ecf86914b76bbbaff7e814c9baff7add3da2a
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {emFile_1_Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {ADC_SAR_1_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 15 31} [list [get_pins {ClockBlock/aclk_glb_0}]]


<<<<<<< HEAD
# Component constraints for C:\Users\legoc\Documents\School\Senior Year\Senior Project\Senior Project Integrated\Senior Project Integrated\Design01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\legoc\Documents\School\Senior Year\Senior Project\Senior Project Integrated\Senior Project Integrated\Design01.cydsn\Design01.cyprj
# Date: Mon, 06 May 2019 03:34:08 GMT
=======
# Component constraints for C:\Users\Jacob-Laptop\Documents\PSoC Creator\Senior Project Stuff Backup - Copy\Senior Project Integrated\Design01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Jacob-Laptop\Documents\PSoC Creator\Senior Project Stuff Backup - Copy\Senior Project Integrated\Design01.cydsn\Design01.cyprj
# Date: Fri, 26 Apr 2019 16:58:27 GMT
>>>>>>> 2d7ecf86914b76bbbaff7e814c9baff7add3da2a
