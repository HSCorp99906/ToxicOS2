#ifndef FLOPPY_H
#define FLOPPY_H

#include "IO.h"
#include "VGA.h"

typedef struct {
    unsigned char steprate_headunload;
    unsigned char headload_ndma;
    unsigned char motor_delay_off; /*specified in clock ticks*/
    unsigned char bytes_per_sector;
    unsigned char sectors_per_track;
    unsigned char gap_length;
    unsigned char data_length; /*used only when bytes per sector == 0*/
    unsigned char format_gap_length;
    unsigned char filler;
    unsigned char head_settle_time; /*specified in milliseconds*/
    unsigned char motor_start_time; /*specified in 1/8 seconds*/
} __attribute__((packed)) floppy_param;


/*
 * All commands, parameter information, result codes, 
 * and disk data transfers go through the FIFO port. 
 */

typedef enum {
   FLOPPY_DOR  = 2,  // digital output register
   FLOPPY_MSR  = 4,  // master status register, read only
   FLOPPY_FIFO = 5,  // data FIFO, in DMA operation for commands
   FLOPPY_CCR  = 7   // configuration control register, write only
} floppy_reg_t;

typedef enum {
   CMD_SPECIFY = 3,            // SPECIFY
   CMD_WRITE_DATA = 5,         // WRITE DATA
   CMD_READ_DATA = 6,          // READ DATA
   CMD_RECALIBRATE = 7,        // RECALIBRATE
   CMD_SENSE_INTERRUPT = 8,    // SENSE INTERRUPT
   CMD_SEEK = 15,              // SEEK
} flppy_cmds_t;

static const char * drive_types[8] = {
    "none",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",

    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "unknown type",
    "unknown type"
};


void floppy_detect_drives();

#endif
