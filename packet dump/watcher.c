//
//  watcher.c
//  packet dump
//
//  Created by Denis on 26/03/2017.
//  Copyright © 2017 Denis. All rights reserved.
//


#include "watcher.h"

#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <net/bpf.h>
#include <fcntl.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"


int listen_bpf () {
  
  char buf[11] = {0};
  int bpf = 0;
  
  for (int i = 0; i < 99; i++) {
    sprintf (buf, "/dev/bpf%d", i);
    bpf = open (buf, O_RDWR);
    if (bpf != -1) { break; }
    perror (buf);
  }
  
  printf ("found bpf device: %s\n", buf);
  
  const char* interface = "en0";
  struct ifreq bound_if;
  
  strcpy (bound_if.ifr_name, interface);
  if (ioctl (bpf, BIOCSETIF, &bound_if) > 0) { return -1; }
  printf ("set bpf interface: %d. %s\n", bpf, interface);

  int buf_len = 1;
  if (ioctl (bpf, BIOCIMMEDIATE, &buf_len) == -1) { return -1; }
  if (ioctl (bpf, BIOCGBLEN, &buf_len) == -1) { return -1; }
  
  printf ("buffer length is set to %d\n", buf_len);
  
  size_t read_bytes = 0;
  int errors = 0;
  
  struct bpf_hdr* bpf_buf = malloc (sizeof (struct bpf_hdr));
  
  while (1) {
    
    memset (bpf_buf, 0, buf_len);
    read_bytes = read (bpf, bpf_buf, buf_len);
    printf ("%ld bytes read:", read_bytes);

    if ((int)read_bytes > 0) {
      errors = 0;
      btoa (bpf_buf, read_bytes);
      printf("\n\n");
    
    } else if (errors < 10) {
      errors++;
    
    } else {
      perror ("unable to read from bpf\n");
      break;
    }
  }
  
  close (bpf);
  return 0;
}

void btoa (const void *data, size_t size) {
  const unsigned char *byte = data;
  while (size-- > 0) {
    printf("%c", *byte);
    byte++;
  }
}
