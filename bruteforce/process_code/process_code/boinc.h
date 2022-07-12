#ifndef BOINC_H
#define BOINC_H

#ifdef BOINCAPP

#ifdef _WIN32
#include "boinc_win.h"
#else
#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include "config.h"
#endif

#include "boinc_api.h"
#include "filesys.h"
#include "mfile.h"
#include "str_util.h"
#include "util.h"

#define OUTPUT_FILENAME "out"

extern char buf[256], output_path[512];
extern MFILE output_file;

#endif // BOINCAPP

void initialize_boinc();

void finish_boinc();

#ifdef BOINCAPP
#define boinc_log(...) output_file.printf(__VA_ARGS__)
#else
#define boinc_log(...) printf(__VA_ARGS__)
#endif

void fraction_done(double percentage);

#endif // BOINC_H