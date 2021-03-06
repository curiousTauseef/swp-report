/*
 * Copyright (C) 2012, [Your Company Here] All Rights Reserved.
 * IT IS EXPECTED THAT THIS TEXT BE REPLACED WITH THE BOARD SOFTWARE
 * PROVIDER'S COPYRIGHT INFORMATION. THIS TEXT WILL BE DISPLAYED AT 
 * THE TOP OF ALL SOURCE FILES GENERATED FOR THIS BOARD DESIGN.
*/

// File: pwm2_iomux_config.c

/* ------------------------------------------------------------------------------
 * <auto-generated>
 *     This code was generated by a tool.
 *     Runtime Version:3.4.0.3
 *
 *     Changes to this file may cause incorrect behavior and will be lost if
 *     the code is regenerated.
 * </auto-generated>
 * ------------------------------------------------------------------------------
*/

#include "iomux_config.h"
#include "registers/regsiomuxc.h"

// Function to configure IOMUXC for pwm2 module.
void pwm2_iomux_config(void)
{
    // Config pwm2.PWM2_OUT to pad DISP0_DATA09(T25)
    // HW_IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09_WR(0x00000002);
    // HW_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_WR(0x0001B0B0);
    // Mux Register:
    // IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09(0x020E010C)
    //   SION [4] - Software Input On Field Reset: DISABLED
    //              Force the selected mux mode Input path no matter of MUX_MODE functionality.
    //     DISABLED (0) - Input Path is determined by functionality of the selected mux mode (regular).
    //     ENABLED (1) - Force input path of pad.
    //   MUX_MODE [2:0] - MUX Mode Select Field Reset: ALT5
    //                    Select iomux modes to be used for pad.
    //     ALT0 (0) - Select instance: ipu1 signal: IPU1_DISP0_DATA09
    //     ALT1 (1) - Select instance: lcd signal: LCD_DATA09
    //     ALT2 (2) - Select instance: pwm2 signal: PWM2_OUT
    //     ALT3 (3) - Select instance: wdog2 signal: WDOG2_B
    //     ALT5 (5) - Select instance: gpio4 signal: GPIO4_IO30
    HW_IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09_SION_V(DISABLED) | 
            BF_IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09_MUX_MODE_V(ALT2));
    // Pad Control Register:
    // IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09(0x020E0420)
    //   HYS [16] - Hysteresis Enable Field Reset: ENABLED
    //     DISABLED (0) - CMOS input
    //     ENABLED (1) - Schmitt trigger input
    //   PUS [15:14] - Pull Up / Down Config. Field Reset: 100K_OHM_PU
    //     100K_OHM_PD (0) - 100K Ohm Pull Down
    //     47K_OHM_PU (1) - 47K Ohm Pull Up
    //     100K_OHM_PU (2) - 100K Ohm Pull Up
    //     22K_OHM_PU (3) - 22K Ohm Pull Up
    //   PUE [13] - Pull / Keep Select Field Reset: PULL
    //     KEEP (0) - Keeper Enabled
    //     PULL (1) - Pull Enabled
    //   PKE [12] - Pull / Keep Enable Field Reset: ENABLED
    //     DISABLED (0) - Pull/Keeper Disabled
    //     ENABLED (1) - Pull/Keeper Enabled
    //   ODE [11] - Open Drain Enable Field Reset: DISABLED
    //              Enables open drain of the pin.
    //     DISABLED (0) - Output is CMOS.
    //     ENABLED (1) - Output is Open Drain.
    //   SPEED [7:6] - Speed Field Reset: 100MHZ
    //     RESERVED0 (0) - Reserved
    //     50MHZ (1) - Low (50 MHz)
    //     100MHZ (2) - Medium (100 MHz)
    //     200MHZ (3) - Maximum (200 MHz)
    //   DSE [5:3] - Drive Strength Field Reset: 40_OHM
    //     HIZ (0) - HI-Z
    //     240_OHM (1) - 240 Ohm
    //     120_OHM (2) - 120 Ohm
    //     80_OHM (3) - 80 Ohm
    //     60_OHM (4) - 60 Ohm
    //     48_OHM (5) - 48 Ohm
    //     40_OHM (6) - 40 Ohm
    //     34_OHM (7) - 34 Ohm
    //   SRE [0] - Slew Rate Field Reset: SLOW
    //             Slew rate control.
    //     SLOW (0) - Slow Slew Rate
    //     FAST (1) - Fast Slew Rate
    HW_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_HYS_V(ENABLED) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_PUS_V(100K_OHM_PU) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_PUE_V(PULL) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_PKE_V(ENABLED) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_ODE_V(DISABLED) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_SPEED_V(100MHZ) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_DSE_V(40_OHM) | 
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09_SRE_V(SLOW));
}
