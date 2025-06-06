#pragma bank 255

#include "hUGEDriver.h"
#include <stddef.h>

static const unsigned char order_cnt = 6;

static const unsigned char P0[] = {
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(G_5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P1[] = {
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(B_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(B_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P2[] = {
    DN(Ds5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(D_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P3[] = {
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P4[] = {
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(Fs5,1,0x000),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P5[] = {
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(A_5,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Gs5,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P6[] = {
    DN(F_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(As5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
};
static const unsigned char P7[] = {
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(Fs6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(Fs6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(F_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(As5,1,0x000),
    DN(___,0,0x000),
    DN(E_6,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P8[] = {
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Ds6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(D_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(C_6,1,0x000),
    DN(___,0,0x000),
    DN(___,0,0xE00),
    DN(___,0,0x000),
    DN(Cs6,1,0x000),
    DN(___,0,0x000),
};
static const unsigned char P9[] = {
    DN(A_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(Ds5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(E_5,1,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
    DN(___,0,0xF02),
    DN(___,0,0xF03),
    DN(___,0,0x000),
    DN(___,0,0x000),
};

static const unsigned char* const order1[] = {P0,P4,P7};
static const unsigned char* const order2[] = {P1,P5,P8};
static const unsigned char* const order3[] = {P2,P6,P9};
static const unsigned char* const order4[] = {P3,P3,P3};

static const hUGEDutyInstr_t duty_instruments[] = {
    {8,175,177,0,128},
};
static const hUGEWaveInstr_t wave_instruments[] = {
    {0,32,0,0,128},
};
static const hUGENoiseInstr_t noise_instruments[] = {
    {193,0,119,0,0},
    {193,0,0,0,0},
};
static const unsigned char waves[] = {
    1,35,69,103,137,171,205,239,254,220,186,152,118,84,50,16,
};

const void __at(255) __bank_music_castle;
const hUGESong_t music_castle = {2, &order_cnt, order1, order2, order3,order4, duty_instruments, wave_instruments, noise_instruments, NULL, waves};
