//
// Created by Ð¡ºÚ on 2020/8/15.
// ÖØÐ´µÄ io.h
//
#pragma once

#ifndef MCDREFORGED_BY_CPP_REWRITEIO_H
#define MCDREFORGED_BY_CPP_REWRITEIO_H
#include <string>
using namespace std;

#ifdef __MACH__
#include <sys/uio.h>
#define OK
#define MACOS
#endif

#ifdef _WIN32
#include <io.h>
#define OK
#define WINDOWS
#endif

#ifndef OK
#include <sys/io.h>
#define UNIX
#endif


#endif //MCDREFORGED_BY_CPP_REWRITEIO_H
