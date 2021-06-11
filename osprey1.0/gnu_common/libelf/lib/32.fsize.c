/*
32.fsize.c - implementation of the elf{32,64}_fsize(3) functions.
Copyright (C) 1995 - 1998 Michael Riepe <michael@stud.uni-hannover.de>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <private.h>
#include <ext_types.h>

#ifndef lint
static const char rcsid[] = "@(#) $Id: 32.fsize.c,v 1.1 2000/03/08 22:26:13 mpm Exp $";
#endif /* lint */

const size_t
_elf_fmsize[2][EV_CURRENT - EV_NONE][ELF_T_NUM][2] = {
    /* ELFCLASS32 */
    {
	/* version 1 */
	{
	    { sizeof(unsigned char),  sizeof(unsigned char)      },
	    { sizeof(Elf32_Addr),     sizeof(__ext_Elf32_Addr)   },
	    { sizeof(Elf32_Dyn),      sizeof(__ext_Elf32_Dyn)    },
	    { sizeof(Elf32_Ehdr),     sizeof(__ext_Elf32_Ehdr)   },
	    { sizeof(Elf32_Half),     sizeof(__ext_Elf32_Half)   },
	    { sizeof(Elf32_Off),      sizeof(__ext_Elf32_Off)    },
	    { sizeof(Elf32_Phdr),     sizeof(__ext_Elf32_Phdr)   },
	    { sizeof(Elf32_Rela),     sizeof(__ext_Elf32_Rela)   },
	    { sizeof(Elf32_Rel),      sizeof(__ext_Elf32_Rel)    },
	    { sizeof(Elf32_Shdr),     sizeof(__ext_Elf32_Shdr)   },
	    { sizeof(Elf32_Sword),    sizeof(__ext_Elf32_Sword)  },
	    { sizeof(Elf32_Sym),      sizeof(__ext_Elf32_Sym)    },
	    { sizeof(Elf32_Word),     sizeof(__ext_Elf32_Word)   },
	},
    },
#if __LIBELF64
    /* ELFCLASS64 */
    {
	/* version 1 */
	{
	    { sizeof(unsigned char),  sizeof(unsigned char)      },
	    { sizeof(Elf64_Addr),     sizeof(__ext_Elf64_Addr)   },
	    { sizeof(Elf64_Dyn),      sizeof(__ext_Elf64_Dyn)    },
	    { sizeof(Elf64_Ehdr),     sizeof(__ext_Elf64_Ehdr)   },
	    { sizeof(Elf64_Half),     sizeof(__ext_Elf64_Half)   },
	    { sizeof(Elf64_Off),      sizeof(__ext_Elf64_Off)    },
	    { sizeof(Elf64_Phdr),     sizeof(__ext_Elf64_Phdr)   },
	    { sizeof(Elf64_Rela),     sizeof(__ext_Elf64_Rela)   },
	    { sizeof(Elf64_Rel),      sizeof(__ext_Elf64_Rel)    },
	    { sizeof(Elf64_Shdr),     sizeof(__ext_Elf64_Shdr)   },
	    { sizeof(Elf64_Sword),    sizeof(__ext_Elf64_Sword)  },
	    { sizeof(Elf64_Sym),      sizeof(__ext_Elf64_Sym)    },
	    { sizeof(Elf64_Word),     sizeof(__ext_Elf64_Word)   },
	    { sizeof(Elf64_Sxword),   sizeof(__ext_Elf64_Sxword) },
	    { sizeof(Elf64_Xword),    sizeof(__ext_Elf64_Xword)  },
	},
    },
#endif /* __LIBELF64 */
};

static size_t
_elf_fsize(unsigned cls, Elf_Type type, unsigned ver) {
    size_t n = 0;

    if (!valid_version(ver)) {
	seterr(ERROR_UNKNOWN_VERSION);
    }
    else if (!valid_type(type)) {
	seterr(ERROR_UNKNOWN_TYPE);
    }
    else if (!(n = _fsize(cls, ver, type))) {
	seterr(ERROR_UNKNOWN_TYPE);
    }
    return n;
}

size_t
elf32_fsize(Elf_Type type, size_t count, unsigned ver) {
    return count * _elf_fsize(ELFCLASS32, type, ver);
}

#if __LIBELF64

size_t
elf64_fsize(Elf_Type type, size_t count, unsigned ver) {
    return count * _elf_fsize(ELFCLASS64, type, ver);
}

#endif /* __LIBELF64 */
