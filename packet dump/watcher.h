//
//  watcher.h
//  packet dump
//
//  Created by Denis on 26/03/2017.
//  Copyright © 2017 Denis. All rights reserved.
//


#ifndef watcher_h
#define watcher_h


#include <stdio.h>


int watch ();
int listen_bpf ();
void btoa (const void *data, size_t size);

#endif /* watcher_h */
