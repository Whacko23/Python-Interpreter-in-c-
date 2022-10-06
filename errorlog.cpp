#ifndef LOGGER_CPP
#define LOGGER_CPP

//#define DEBUG

#include "logger.h"
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

void
log(int32 code){

  #ifdef DEBUG
  printf("error code %i\n", code);
  #endif

  if(code==0){
    printf("%s","Exiting the program...");
    printf("%s","The log is saved on logfile.log");
    logger("Exiting the program...");
    exit(0);
  }
  if(code==1){
    printf("%s","Required arguments not passed to the console");
    logger("Required arguments not passed to the console");
    log(0);
  }
  if(code==2){
    logger("Invalid arguments");
    log(0);
  }
   if(code==3){
    logger("Encountered an empty line");
  }
}

void
logger(string message){
  FILE *fs;
  string logfile = "error.log";

  time_t current_time = time(0); 
  char *time = ctime(&current_time);

  #ifdef DEBUG
  printf("[ %.24s ] %s\n", time, message.c_str());
  #endif
  
  fs = fopen(logfile.c_str(), "a");
  fprintf(fs,"[ %.24s ] %s\n", time, message.c_str());
  fclose(fs);
}

#endif