#ifndef USTAR_H
#define USTAR_H

#include "../util/strings.h"
#include "../util/converters.h"
#include "../memory/memcmp.h"

int tar_lookup(unsigned char* archive, char* filename, char** out);


#endif
