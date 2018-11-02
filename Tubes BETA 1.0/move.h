// Header untuk move.c

#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <string.h>
#include "boolean.h"
#include "matriks.c"
#include "input.c"

boolean pathFilled(MATRIKS M, int x , int Y);
// Menghasilkan true jika "kotak" sudah terisi

void newCoordinate(MATRIKS M , int *X, int *Y, Kata command);
// I.S : Sembarang
// F.S : Menghasilkan koordinat baru untuk move player

void move(MATRIKS *M, int *X , int *Y, Kata command);
// I.S : Sembarang
// F.S : Memindahkan player menuju koordinat baru sesuai perintah

#endif