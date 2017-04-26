//
//  main.c
//  packet dump
//
//  Created by Denis on 26/03/2017.
//  Copyright © 2017 Denis. All rights reserved.
//


#include <stdio.h>
#include "watcher.h"


int main(int argc, const char * argv[]) {
    return listen_bpf ();
}
