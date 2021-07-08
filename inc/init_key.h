#ifndef __INIT_KEY_H__
#define __INIT_KEY_H__

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

static struct termios initial_settings, new_settings;
static int peek_character = -1;
void init_keyboard(void);
void close_keyboard(void);
int kbhit(void);
int readch(void);
void init_keyboard();
void close_keyboard();
int readch();

#endif