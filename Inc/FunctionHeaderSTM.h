/*
 * myHeader.h
 *
 *  Created on: 10 Jul 2018
 *      Author: ng_we
 */
#include <stdint.h>
#include <stdio.h>
#include "MasterFunc.h"
#include "main.h"


//global variable
// define variables
//private definition
//#define SEMIHOSTING


#ifndef SEMIHOSTING
#define log(...)
#else
#define log printf
#endif
