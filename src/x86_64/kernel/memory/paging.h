#ifndef PAGING_H
#define PAGING_H

#include <stddef.h>

#define INDEX_FROM_BIT(a)	(a/(8*4))
#define OFFSET_FROM_BIT(a)	(a%(8*4))


typedef struct {
    uint32_t present : 1;	    // Page present in memory
	uint32_t rw	: 1;	        // Read-only if clear, readwrite if set
	uint32_t user : 1;	        // Suprevisor level only if clear
	uint32_t accessed : 1;	    // Has the page been accessed since last refresh?
	uint32_t dirty : 1;	        // Has the page been written to since last refresh?
	uint32_t unused	: 7;	    // Amalgamation of unused and reserved bits
	uint32_t frame : 20;	
} __attribute__((packed)) page_t;


typedef struct {
    page_t pages[1024]; 
} __attribute__((packed)) page_tbl_t;


typedef struct {
    page_tbl_t* tables[1024];
    uint32_t tablesPhys[1024];
    uint32_t physAddr;
} page_dir_t;

void load_page_dir(page_dir_t* dir);
page_t* get_page(uint32_t addr, int make, page_dir_t* dir);
void page_fault();


#endif
