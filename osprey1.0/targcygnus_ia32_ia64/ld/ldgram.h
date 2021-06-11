#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
  bfd_vma integer;
  char *name;
  const char *cname;
  struct wildcard_spec wildcard;
  struct name_list *name_list;
  int token;
  union etree_union *etree;
  struct phdr_info
    {
      boolean filehdr;
      boolean phdrs;
      union etree_union *at;
      union etree_union *flags;
    } phdr;
  struct lang_nocrossref *nocrossref;
  struct lang_output_section_phdr_list *section_phdr;
  struct bfd_elf_version_deps *deflist;
  struct bfd_elf_version_expr *versyms;
  struct bfd_elf_version_tree *versnode;
} yystype;
# define YYSTYPE yystype
#endif
# define	INT	257
# define	NAME	258
# define	LNAME	259
# define	PLUSEQ	260
# define	MINUSEQ	261
# define	MULTEQ	262
# define	DIVEQ	263
# define	LSHIFTEQ	264
# define	RSHIFTEQ	265
# define	ANDEQ	266
# define	OREQ	267
# define	OROR	268
# define	ANDAND	269
# define	EQ	270
# define	NE	271
# define	LE	272
# define	GE	273
# define	LSHIFT	274
# define	RSHIFT	275
# define	UNARY	276
# define	END	277
# define	ALIGN_K	278
# define	BLOCK	279
# define	BIND	280
# define	QUAD	281
# define	SQUAD	282
# define	LONG	283
# define	SHORT	284
# define	BYTE	285
# define	SECTIONS	286
# define	PHDRS	287
# define	SORT	288
# define	SIZEOF_HEADERS	289
# define	OUTPUT_FORMAT	290
# define	FORCE_COMMON_ALLOCATION	291
# define	OUTPUT_ARCH	292
# define	INCLUDE	293
# define	MEMORY	294
# define	DEFSYMEND	295
# define	NOLOAD	296
# define	DSECT	297
# define	COPY	298
# define	INFO	299
# define	OVERLAY	300
# define	DEFINED	301
# define	TARGET_K	302
# define	SEARCH_DIR	303
# define	MAP	304
# define	ENTRY	305
# define	NEXT	306
# define	SIZEOF	307
# define	ADDR	308
# define	LOADADDR	309
# define	MAX_K	310
# define	MIN_K	311
# define	STARTUP	312
# define	HLL	313
# define	SYSLIB	314
# define	FLOAT	315
# define	NOFLOAT	316
# define	NOCROSSREFS	317
# define	ORIGIN	318
# define	FILL	319
# define	LENGTH	320
# define	CREATE_OBJECT_SYMBOLS	321
# define	INPUT	322
# define	GROUP	323
# define	OUTPUT	324
# define	CONSTRUCTORS	325
# define	ALIGNMOD	326
# define	AT	327
# define	PROVIDE	328
# define	CHIP	329
# define	LIST	330
# define	SECT	331
# define	ABSOLUTE	332
# define	LOAD	333
# define	NEWLINE	334
# define	ENDWORD	335
# define	ORDER	336
# define	NAMEWORD	337
# define	ASSERT_K	338
# define	FORMAT	339
# define	PUBLIC	340
# define	BASE	341
# define	ALIAS	342
# define	TRUNCATE	343
# define	REL	344
# define	INPUT_SCRIPT	345
# define	INPUT_MRI_SCRIPT	346
# define	INPUT_DEFSYM	347
# define	CASE	348
# define	EXTERN	349
# define	START	350
# define	VERS_TAG	351
# define	VERS_IDENTIFIER	352
# define	GLOBAL	353
# define	LOCAL	354
# define	VERSIONK	355
# define	INPUT_VERSION_SCRIPT	356
# define	KEEP	357
# define	EXCLUDE_FILE	358


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
