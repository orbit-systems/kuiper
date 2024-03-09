//header library for extracting instruction information from a u32
//functions prefaced with __ should not be used outside of this header file.

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef int64_t  i64;
typedef int32_t  i32;
typedef int16_t  i16;
typedef int8_t   i8;

typedef enum {
	FORMAT_E,
	FORMAT_R,
	FORMAT_M,
	FORMAT_F,
	FORMAT_B,
	INVALID_FORMAT
} instruction_format;

typedef union {
    u8 opcode;
    struct {
        u32 opcode : 8;
        u32 imm    : 8;
        u32 func   : 4;
        u32 rs2    : 4;
        u32 rs1    : 4;
        u32 rde    : 4;
    } E;
    struct {
        u32 opcode : 8;
        u32 imm    : 12;
        u32 rs2    : 4;
        u32 rs1    : 4;
        u32 rde    : 4;
    } R;
    struct {
        u32 opcode : 8;
        u32 imm    : 16;
        u32 rs1    : 4;
        u32 rde    : 4;
    } M;
    struct {
        u32 opcode : 8;
        u32 imm    : 16;
        u32 func   : 4;
        u32 rde    : 4;
    } F;
    struct {
        u32 opcode : 8;
        u32 imm    : 20;
        u32 func   : 4;
    } B;
    u32 instruction;
} raw_instruction;

typedef struct {
	raw_instruction ai;
	char* instruction_name;
	char* instruction_as_string;
	char* op_name;
} kepler_instruction;

char* __ki_get_raw_op(u8 opcode) {
	if (opcode > instruction_count) {
		return "invalid";
	} else {
		return opcode_names[opcode];
	}
}

char* __ki_get_variant_op(u32 inst) {

	switch (opcode) {
		case 0x1:
			return system_control_variants[func];
		case 0x10:
			return li_variants[func];
		case 0x0a:
			return branch_variants[func];
		default:
			return __ki_get_raw_op(opcode);
	}
}

//longest possible aphelion instruction is
//"lbs rz, rz, 15, rz, 15 " which is 23 bytes

kepler_instruction ki_as_struct(u32 inst) {
	kepler_instruction int_instruction;
	int_instruction.raw_instruction = (raw_instruction){.instruction = inst};
	int_instruction.instruction_as_string = ki_as_string(inst);
	int_instruction.op_name = __ki_get_raw_op(int_instruction.ai.opcode);
}

char* ki_as_string(u32 inst, char* buff, int buflen) {
	if (buff == NULL || buflen == 0) {
		return NULL;
	}
}

raw_instruction ki_as_raw(u32 inst) {
	return (raw_instruction){.instruction = inst};
}

int instruction_count = 0x4f;

char* system_control_variants[] = {
	"int",
	"iret",
	"ires",
	"usr",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID",
	"SC INVALID"
}

char* li_variants[] = {
	"lli",
	"llis",
	"lui",
	"luis",
	"lti",
	"ltis",
	"ltui",
	"ltuis",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID",
	"LI INVALID"
}

char* branch_variants[] = {
	"bra",
	"beq",
	"bez",
	"blt",
	"ble",
	"bltu",
	"bleu",
	"B(CC) INVALID",
	"B(CC) INVALID",
	"bne",
	"bnz",
	"bge",
	"bgt",
	"bgeu",
	"bgtu",
	"B(CC) INVALID"	
}

char* opcode_names[] = {
	//0x00
	"invalid",
	"int", //int, iret, ires, usr
	"outr",
	"outi",
	"inr",
	"ini",
	"jal",
	"jalr",
	"ret",
	"retr",
	"b(cc)",
	"push",
	"pop",
	"enter",
	"leave",
	"invalid",
	//0x10
	"lli", //li family
	"lw",
	"lh",
	"lhs",
	"lq",
	"lqs",
	"lb",
	"lbs",
	"sw",
	"sh",
	"sq",
	"sb",
	"invalid",
	"invalid",
	"cmpr",
	"cmpi",
	//0x20
	"addr",
	"addi",
	"subr",
	"subi",
	"imulr",
	"imuli",
	"idivr",
	"idivi",
	"umulr",
	"umuli",
	"udivr",
	"udivi",
	"remr",
	"remi",
	"modr",
	"modi",
	//0x30
	"andr",
	"andi",
	"orr",
	"ori",
	"norr",
	"nori",
	"xorr",
	"xori",
	"shlr",
	"shli",
	"asrr",
	"asri",
	"lsrr",
	"lsri",
	"bitr",
	"biti",
	//0x40
	"fcmp",
	"fto",
	"ffrom",
	"fneg",
	"fabs",
	"fadd",
	"fsub",
	"fmul",
	"fdiv",
	"fma",
	"fsqrt",
	"fmin",
	"fmax",
	"fsat",
	"fcnv",
	"fnan",
	//0x50 and beyond are invalid
}

instruction_format opcode_format[] = {
	INVALID_FORMAT,
	FORMAT_F,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_M,
	FORMAT_B,
	FORMAT_M,
	FORMAT_M,
	FORMAT_B,
	FORMAT_B,
	INVALID_FORMAT,
	//0x10
	FORMAT_F,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	INVALID_FORMAT,
	INVALID_FORMAT,
	FORMAT_M,
	FORMAT_F,
	//0x20
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	//0x30
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	FORMAT_R,
	FORMAT_M,
	//0x40
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E,
	FORMAT_E
	//0x50
}