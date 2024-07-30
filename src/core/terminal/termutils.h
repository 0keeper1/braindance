#pragma once

#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

extern void termResizeSignal( int sig );