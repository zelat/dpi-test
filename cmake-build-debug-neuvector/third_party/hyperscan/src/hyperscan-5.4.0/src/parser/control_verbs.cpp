
#line 1 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
/*
* Copyright (c) 2017, Intel Corporation
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  * Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*  * Neither the name of Intel Corporation nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

/**
* \file
* \brief Parser for control verbs that can occur at the beginning of a pattern.
*/

#include "parser/control_verbs.h"

#include "parser/Parser.h"
#include "parser/parse_error.h"

#include <cstring>
#include <sstream>

using namespace std;

namespace ue2 {
	
	const char *read_control_verbs(const char *ptr, const char *end, size_t start,
	ParseMode &mode) {
		const char *p = ptr;
		const char *pe = end;
		const char *eof = pe;
		const char *ts, *te;
		int cs;
		UNUSED int act;
		
		
		static const char _ControlVerbs_actions[] = {
			0, 1, 0, 1, 1, 1, 2, 1,
			3, 1, 4, 1, 5, 1, 6, 1,
			7, 1, 8, 1, 9, 0
		};
		
		static const short _ControlVerbs_key_offsets[] = {
			0, 7, 8, 10, 12, 14, 16, 18,
			20, 21, 23, 25, 27, 30, 32, 34,
			36, 38, 40, 42, 44, 46, 48, 50,
			52, 55, 57, 59, 61, 63, 66, 68,
			70, 72, 74, 76, 79, 82, 84, 86,
			88, 90, 92, 94, 96, 98, 100, 102,
			105, 107, 109, 111, 113, 115, 117, 119,
			121, 123, 125, 127, 129, 131, 133, 135,
			137, 139, 141, 143, 146, 148, 149, 151,
			155, 157, 159, 160, 161, 0
		};
		
		static const char _ControlVerbs_trans_keys[] = {
			41, 65, 66, 67, 76, 78, 85, 41,
			41, 78, 41, 89, 41, 67, 41, 82,
			41, 76, 41, 70, 41, 41, 83, 41,
			82, 41, 95, 41, 65, 85, 41, 78,
			41, 89, 41, 67, 41, 78, 41, 73,
			41, 67, 41, 79, 41, 68, 41, 69,
			41, 82, 41, 76, 41, 70, 73, 41,
			77, 41, 73, 41, 84, 41, 95, 41,
			77, 82, 41, 65, 41, 84, 41, 67,
			41, 72, 41, 61, 41, 48, 57, 41,
			48, 57, 41, 69, 41, 67, 41, 85,
			41, 82, 41, 83, 41, 73, 41, 79,
			41, 78, 41, 79, 41, 95, 41, 65,
			83, 41, 85, 41, 84, 41, 79, 41,
			95, 41, 80, 41, 79, 41, 83, 41,
			83, 41, 69, 41, 83, 41, 83, 41,
			84, 41, 65, 41, 82, 41, 84, 41,
			95, 41, 79, 41, 80, 41, 84, 41,
			67, 84, 41, 80, 41, 41, 70, 41,
			49, 51, 56, 41, 54, 41, 50, 41,
			40, 42, 0
		};
		
		static const char _ControlVerbs_single_lengths[] = {
			7, 1, 2, 2, 2, 2, 2, 2,
			1, 2, 2, 2, 3, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 2,
			3, 2, 2, 2, 2, 3, 2, 2,
			2, 2, 2, 1, 1, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 3,
			2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 3, 2, 1, 2, 4,
			2, 2, 1, 1, 1, 0
		};
		
		static const char _ControlVerbs_range_lengths[] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 1, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0
		};
		
		static const short _ControlVerbs_index_offsets[] = {
			0, 8, 10, 13, 16, 19, 22, 25,
			28, 30, 33, 36, 39, 43, 46, 49,
			52, 55, 58, 61, 64, 67, 70, 73,
			76, 80, 83, 86, 89, 92, 96, 99,
			102, 105, 108, 111, 114, 117, 120, 123,
			126, 129, 132, 135, 138, 141, 144, 147,
			151, 154, 157, 160, 163, 166, 169, 172,
			175, 178, 181, 184, 187, 190, 193, 196,
			199, 202, 205, 208, 212, 215, 217, 220,
			225, 228, 231, 233, 235, 0
		};
		
		static const char _ControlVerbs_trans_cond_spaces[] = {
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1,
			-1, 0
		};
		
		static const short _ControlVerbs_trans_offsets[] = {
			0, 1, 2, 3, 4, 5, 6, 7,
			8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29, 30, 31,
			32, 33, 34, 35, 36, 37, 38, 39,
			40, 41, 42, 43, 44, 45, 46, 47,
			48, 49, 50, 51, 52, 53, 54, 55,
			56, 57, 58, 59, 60, 61, 62, 63,
			64, 65, 66, 67, 68, 69, 70, 71,
			72, 73, 74, 75, 76, 77, 78, 79,
			80, 81, 82, 83, 84, 85, 86, 87,
			88, 89, 90, 91, 92, 93, 94, 95,
			96, 97, 98, 99, 100, 101, 102, 103,
			104, 105, 106, 107, 108, 109, 110, 111,
			112, 113, 114, 115, 116, 117, 118, 119,
			120, 121, 122, 123, 124, 125, 126, 127,
			128, 129, 130, 131, 132, 133, 134, 135,
			136, 137, 138, 139, 140, 141, 142, 143,
			144, 145, 146, 147, 148, 149, 150, 151,
			152, 153, 154, 155, 156, 157, 158, 159,
			160, 161, 162, 163, 164, 165, 166, 167,
			168, 169, 170, 171, 172, 173, 174, 175,
			176, 177, 178, 179, 180, 181, 182, 183,
			184, 185, 186, 187, 188, 189, 190, 191,
			192, 193, 194, 195, 196, 197, 198, 199,
			200, 201, 202, 203, 204, 205, 206, 207,
			208, 209, 210, 211, 212, 213, 214, 215,
			216, 217, 218, 219, 220, 221, 222, 223,
			224, 225, 226, 227, 228, 229, 230, 231,
			232, 233, 234, 235, 236, 237, 238, 239,
			240, 241, 242, 243, 244, 245, 246, 247,
			248, 249, 250, 251, 252, 253, 254, 255,
			256, 257, 258, 259, 260, 261, 262, 263,
			264, 265, 266, 267, 268, 269, 270, 271,
			272, 273, 274, 275, 276, 277, 278, 279,
			280, 281, 282, 283, 284, 285, 286, 287,
			288, 289, 290, 291, 292, 293, 294, 295,
			296, 297, 298, 299, 300, 301, 302, 303,
			304, 305, 306, 307, 308, 309, 310, 311,
			312, 0
		};
		
		static const char _ControlVerbs_trans_lengths[] = {
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 0
		};
		
		static const char _ControlVerbs_cond_keys[] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0
		};
		
		static const char _ControlVerbs_cond_targs[] = {
			75, 2, 9, 22, 24, 45, 67, 1,
			75, 1, 75, 3, 1, 75, 4, 1,
			75, 5, 1, 75, 6, 1, 75, 7,
			1, 75, 8, 1, 75, 1, 75, 10,
			1, 75, 11, 1, 75, 12, 1, 75,
			13, 16, 1, 75, 14, 1, 75, 15,
			1, 75, 5, 1, 75, 17, 1, 75,
			18, 1, 75, 19, 1, 75, 20, 1,
			75, 21, 1, 75, 8, 1, 75, 23,
			1, 75, 7, 1, 75, 8, 25, 1,
			75, 26, 1, 75, 27, 1, 75, 28,
			1, 75, 29, 1, 75, 30, 37, 1,
			75, 31, 1, 75, 32, 1, 75, 33,
			1, 75, 34, 1, 75, 35, 1, 75,
			36, 1, 75, 36, 1, 75, 38, 1,
			75, 39, 1, 75, 40, 1, 75, 41,
			1, 75, 42, 1, 75, 43, 1, 75,
			44, 1, 75, 34, 1, 75, 46, 1,
			75, 47, 1, 75, 48, 59, 1, 75,
			49, 1, 75, 50, 1, 75, 51, 1,
			75, 52, 1, 75, 53, 1, 75, 54,
			1, 75, 55, 1, 75, 56, 1, 75,
			57, 1, 75, 58, 1, 75, 8, 1,
			75, 60, 1, 75, 61, 1, 75, 62,
			1, 75, 63, 1, 75, 64, 1, 75,
			65, 1, 75, 66, 1, 75, 8, 1,
			75, 68, 70, 1, 75, 69, 1, 75,
			1, 75, 71, 1, 75, 72, 73, 74,
			1, 75, 8, 1, 75, 8, 1, 75,
			1, 76, 75, 0, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 75, 75, 75, 75, 75, 75, 75,
			75, 0
		};
		
		static const char _ControlVerbs_cond_actions[] = {
			19, 0, 0, 0, 0, 0, 0, 0,
			13, 0, 13, 0, 0, 13, 0, 0,
			11, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 11, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 13, 0, 0, 13, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 11, 0, 0, 13, 0, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 11, 0, 0, 13, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 13, 0, 0, 13, 0, 0,
			13, 0, 0, 13, 0, 0, 0, 13,
			0, 0, 13, 0, 0, 13, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 13, 0, 0, 13, 0, 0,
			13, 0, 0, 13, 0, 0, 13, 0,
			0, 13, 0, 0, 13, 0, 0, 13,
			0, 0, 13, 0, 0, 13, 0, 0,
			13, 0, 0, 0, 13, 0, 0, 9,
			0, 13, 0, 0, 7, 0, 0, 0,
			0, 13, 0, 0, 13, 0, 0, 7,
			0, 5, 15, 0, 17, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			19, 19, 19, 19, 19, 19, 19, 19,
			17, 0
		};
		
		static const char _ControlVerbs_to_state_actions[] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 0, 0
		};
		
		static const char _ControlVerbs_from_state_actions[] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 3, 0, 0
		};
		
		static const char _ControlVerbs_eof_trans_indexed[] = {
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 76, 76, 76, 76, 76,
			76, 76, 76, 0, 82, 0
		};
		
		static const short _ControlVerbs_eof_trans_direct[] = {
			238, 239, 240, 241, 242, 243, 244, 245,
			246, 247, 248, 249, 250, 251, 252, 253,
			254, 255, 256, 257, 258, 259, 260, 261,
			262, 263, 264, 265, 266, 267, 268, 269,
			270, 271, 272, 273, 274, 275, 276, 277,
			278, 279, 280, 281, 282, 283, 284, 285,
			286, 287, 288, 289, 290, 291, 292, 293,
			294, 295, 296, 297, 298, 299, 300, 301,
			302, 303, 304, 305, 306, 307, 308, 309,
			310, 311, 312, 0, 313, 0
		};
		
		static const char _ControlVerbs_nfa_targs[] = {
			0, 0
		};
		
		static const char _ControlVerbs_nfa_offsets[] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0
		};
		
		static const char _ControlVerbs_nfa_push_actions[] = {
			0, 0
		};
		
		static const char _ControlVerbs_nfa_pop_trans[] = {
			0, 0
		};
		
		static const int ControlVerbs_start = 75;
		static const int ControlVerbs_first_final = 75;
		static const int ControlVerbs_error = -1;
		
		static const int ControlVerbs_en_main = 75;
		
		
		{
			cs = (int)ControlVerbs_start;
			ts = 0;
			te = 0;
		}
		
		#line 105 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
		
		
		try {
			
			{
				int _klen;
				unsigned int _trans = 0;
				unsigned int _cond = 0;
				const char *_acts;
				unsigned int _nacts;
				const char *_keys;
				const char *_ckeys;
				int _cpc;
				{
					
					if ( p == pe )
					goto _test_eof;
					_resume:  {
						_acts = ( _ControlVerbs_actions + (_ControlVerbs_from_state_actions[cs]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 ) {
							switch ( (*( _acts)) ) {
								case 1:  {
									{
										#line 1 "NONE"
										{ts = p;}}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						_keys = ( _ControlVerbs_trans_keys + (_ControlVerbs_key_offsets[cs]));
						_trans = (unsigned int)_ControlVerbs_index_offsets[cs];
						
						_klen = (int)_ControlVerbs_single_lengths[cs];
						if ( _klen > 0 ) {
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _keys;
							_upper = _keys + _klen - 1;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + ((_upper-_lower) >> 1);
								if ( ( (*( p))) < (*( _mid)) )
								_upper = _mid - 1;
								else if ( ( (*( p))) > (*( _mid)) )
								_lower = _mid + 1;
								else {
									_trans += (unsigned int)(_mid - _keys);
									goto _match;
								}
							}
							_keys += _klen;
							_trans += (unsigned int)_klen;
						}
						
						_klen = (int)_ControlVerbs_range_lengths[cs];
						if ( _klen > 0 ) {
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _keys;
							_upper = _keys + (_klen<<1) - 2;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + (((_upper-_lower) >> 1) & ~1);
								if ( ( (*( p))) < (*( _mid)) )
								_upper = _mid - 2;
								else if ( ( (*( p))) > (*( _mid + 1)) )
								_lower = _mid + 2;
								else {
									_trans += (unsigned int)((_mid - _keys)>>1);
									goto _match;
								}
							}
							_trans += (unsigned int)_klen;
						}
						
					}
					_match:  {
						_ckeys = ( _ControlVerbs_cond_keys + (_ControlVerbs_trans_offsets[_trans]));
						_klen = (int)_ControlVerbs_trans_lengths[_trans];
						_cond = (unsigned int)_ControlVerbs_trans_offsets[_trans];
						
						_cpc = 0;
						{
							const char *_lower;
							const char *_mid;
							const char *_upper;
							_lower = _ckeys;
							_upper = _ckeys + _klen - 1;
							while ( 1 ) {
								if ( _upper < _lower )
								break;
								
								_mid = _lower + ((_upper-_lower) >> 1);
								if ( _cpc < (int)(*( _mid)) )
								_upper = _mid - 1;
								else if ( _cpc > (int)(*( _mid)) )
								_lower = _mid + 1;
								else {
									_cond += (unsigned int)(_mid - _ckeys);
									goto _match_cond;
								}
							}
							cs = -1;
							goto _again;
						}
					}
					_match_cond:  {
						cs = (int)_ControlVerbs_cond_targs[_cond];
						
						if ( _ControlVerbs_cond_actions[_cond] == 0 )
						goto _again;
						
						_acts = ( _ControlVerbs_actions + (_ControlVerbs_cond_actions[_cond]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 )
						{
							switch ( (*( _acts)) )
							{
								case 2:  {
									{
										#line 1 "NONE"
										{te = p+1;}}
									break; }
								case 3:  {
									{
										#line 76 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p+1;{
												#line 76 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												mode.utf8 = true;
											}}}
									break; }
								case 4:  {
									{
										#line 80 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p+1;{
												#line 80 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												mode.ucp = true;
											}}}
									break; }
								case 5:  {
									{
										#line 84 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p+1;{
												#line 84 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												ostringstream str;
												str << "Unsupported control verb " << string(ts, te - ts);
												throw LocatedParseError(str.str());
											}}}
									break; }
								case 6:  {
									{
										#line 90 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p+1;{
												#line 90 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												ostringstream str;
												str << "Unknown control verb " << string(ts, te - ts);
												throw LocatedParseError(str.str());
											}}}
									break; }
								case 7:  {
									{
										#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p+1;{
												#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												{p = p - 1; }
												{p+= 1; goto _out; }
											}}}
									break; }
								case 8:  {
									{
										#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{te = p;p = p - 1;{
												#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												{p = p - 1; }
												{p+= 1; goto _out; }
											}}}
									break; }
								case 9:  {
									{
										#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
										{p = ((te))-1;
											{
												#line 97 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
												
												{p = p - 1; }
												{p+= 1; goto _out; }
											}}}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						
					}
					_again:  {
						_acts = ( _ControlVerbs_actions + (_ControlVerbs_to_state_actions[cs]));
						_nacts = (unsigned int)(*( _acts));
						_acts += 1;
						while ( _nacts > 0 ) {
							switch ( (*( _acts)) ) {
								case 0:  {
									{
										#line 1 "NONE"
										{ts = 0;}}
									break; }
							}
							_nacts -= 1;
							_acts += 1;
						}
						
						p += 1;
						if ( p != pe )
						goto _resume;
					}
					_test_eof:  { {}
						if ( p == eof )
						{
							if ( _ControlVerbs_eof_trans_direct[cs] > 0 ) {
								_trans = (unsigned int)_ControlVerbs_eof_trans_direct[cs] - 1;
								_cond = (unsigned int)_ControlVerbs_trans_offsets[_trans];
								goto _match_cond;
							}
						}
						
					}
					_out:  { {}
					}
				}
			}
			
			#line 109 "/root/dpi-test/cmake-build-debug-neuvector/third_party/hyperscan/src/hyperscan-5.4.0/src/parser/control_verbs.rl"
			
		} catch (LocatedParseError &error) {
			if (ts >= ptr && ts <= pe) {
				error.locate(ts - ptr + start);
			} else {
				error.locate(0);
			}
			throw;
		}
		
		return p;
	}
	
} // namespace ue2
