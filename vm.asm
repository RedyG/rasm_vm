	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"vm.c"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",one_only,main
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.Lfunc_begin0:
	.cv_func_id 0
	.cv_file	1 "C:\\Users\\minio\\source\\repos\\redylang_vm\\vm.c" "D616054F5BE213D700307D7AB33C879C" 1
	.cv_loc	0 1 18 0                        # vm.c:18:0
.seh_proc main
# %bb.0:
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
.Ltmp0:
	#DEBUG_VALUE: main:ip <- undef
	lea	rcx, [rip + program+1]
.Ltmp1:
	#DEBUG_VALUE: main:ip <- $rcx
	lea	rax, [rip + stack]
.Ltmp2:
	#DEBUG_VALUE: main:sp <- $rax
	movzx	r8d, byte ptr [rip + program]
	lea	r9, [rip + .L__const.main.opcodes]
.Ltmp3:
	#DEBUG_VALUE: main:ip <- undef
	#DEBUG_VALUE: main:sp <- undef
	jmp	qword ptr [r9 + 8*r8]
.Ltmp4:
	.p2align	4, 0x90
.Ltmp5:                                 # Block address taken
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	#DEBUG_LABEL: main:U64_CONST
	#DEBUG_VALUE: main:ip <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.cv_loc	0 1 30 0                        # vm.c:30:0
	mov	rdx, qword ptr [rcx]
	mov	qword ptr [rax], rdx
	add	rax, 8
.Ltmp6:
	#DEBUG_VALUE: main:sp <- $rax
	.cv_loc	0 1 31 0                        # vm.c:31:0
	add	rcx, 2
.Ltmp7:
	#DEBUG_VALUE: main:ip <- $rcx
	shr	rdx, 8
	movzx	edx, dl
.Ltmp8:
	#DEBUG_VALUE: main:ip <- undef
	#DEBUG_VALUE: main:sp <- undef
	jmp	qword ptr [r9 + 8*rdx]
.Ltmp9:
.Ltmp10:                                # Block address taken
.LBB0_2:
	#DEBUG_LABEL: main:U64_ADD
	.cv_loc	0 1 33 0                        # vm.c:33:0
	lea	rcx, [rax - 8]
.Ltmp11:
	#DEBUG_VALUE: main:sp <- $rcx
	mov	rdx, qword ptr [rax - 8]
.Ltmp12:
	#DEBUG_VALUE: main:l <- $rdx
	#DEBUG_VALUE: main:r <- undef
	.cv_loc	0 1 35 0                        # vm.c:35:0
	add	qword ptr [rax - 16], rdx
	jmp	.LBB0_4
.Ltmp13:
.Ltmp14:                                # Block address taken
.LBB0_3:
	mov	rcx, rax
.LBB0_4:
.Ltmp15:
	#DEBUG_LABEL: main:END
	#DEBUG_VALUE: main:sp <- $rcx
	.cv_loc	0 1 37 0                        # vm.c:37:0
	mov	rdx, qword ptr [rcx - 8]
	lea	rcx, [rip + "??_C@_07DOIONBAM@end?3?5?$CFd?$AA@"]
.Ltmp16:
	call	printf
	.cv_loc	0 1 38 0                        # vm.c:38:0
	xor	eax, eax
	add	rsp, 40
	ret
.Ltmp17:
.Lfunc_end0:
	.seh_endproc
                                        # -- End function
	.def	printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,printf
	.globl	printf                          # -- Begin function printf
	.p2align	4, 0x90
printf:                                 # @printf
.Lfunc_begin1:
	.cv_func_id 1
	.cv_file	2 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\stdio.h" "C1A1FBC43E7D45F0EA4AE539DDCFFB19" 1
	.cv_loc	1 2 956 0                       # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:956:0
.seh_proc printf
# %bb.0:
	#DEBUG_VALUE: printf:_Format <- $rcx
	push	rsi
	.seh_pushreg rsi
	push	rdi
	.seh_pushreg rdi
	push	rbx
	.seh_pushreg rbx
	sub	rsp, 64
	.seh_stackalloc 64
	.seh_endprologue
	mov	rsi, rcx
	mov	qword ptr [rsp + 104], rdx
	mov	qword ptr [rsp + 112], r8
	mov	qword ptr [rsp + 120], r9
.Ltmp18:
	#DEBUG_VALUE: _vfprintf_l:_Format <- $rsi
	mov	rax, qword ptr [rip + __security_cookie]
	xor	rax, rsp
	mov	qword ptr [rsp + 56], rax
	lea	rbx, [rsp + 104]
.Ltmp19:
	#DEBUG_VALUE: printf:_ArgList <- $rbx
	#DEBUG_VALUE: _vfprintf_l:_ArgList <- $rbx
	#DEBUG_VALUE: printf:_ArgList <- [DW_OP_plus_uconst 48, DW_OP_deref] $rsp
	.cv_loc	1 2 959 0                       # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:959:0
	mov	qword ptr [rsp + 48], rbx
	.cv_loc	1 2 960 0                       # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:960:0
	mov	ecx, 1
.Ltmp20:
	#DEBUG_VALUE: printf:_Format <- $rsi
	call	qword ptr [rip + __imp___acrt_iob_func]
	mov	rdi, rax
.Ltmp21:
	#DEBUG_VALUE: _vfprintf_l:_Stream <- $rdi
	#DEBUG_VALUE: _vfprintf_l:_Locale <- 0
	.cv_inline_site_id 2 within 1 inlined_at 2 960 0
	.cv_loc	2 2 645 0                       # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:645:0
	call	__local_stdio_printf_options
	mov	rcx, qword ptr [rax]
	mov	qword ptr [rsp + 32], rbx
	mov	rdx, rdi
	mov	r8, rsi
	xor	r9d, r9d
	call	qword ptr [rip + __imp___stdio_common_vfprintf]
	mov	esi, eax
.Ltmp22:
	#DEBUG_VALUE: printf:_Format <- [DW_OP_LLVM_entry_value 1] $rcx
	#DEBUG_VALUE: printf:_Result <- $esi
	#DEBUG_VALUE: printf:_ArgList <- [DW_OP_plus_uconst 48, DW_OP_deref] $rsp
	mov	rcx, qword ptr [rsp + 56]
	xor	rcx, rsp
	call	__security_check_cookie
.Ltmp23:
	.cv_loc	1 2 962 0                       # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:962:0
	mov	eax, esi
	add	rsp, 64
	pop	rbx
.Ltmp24:
	pop	rdi
.Ltmp25:
	pop	rsi
.Ltmp26:
	#DEBUG_VALUE: printf:_Result <- $eax
	ret
.Ltmp27:
.Lfunc_end1:
	.seh_endproc
                                        # -- End function
	.def	main2;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",one_only,main2
	.globl	main2                           # -- Begin function main2
	.p2align	4, 0x90
main2:                                  # @main2
.Lfunc_begin2:
	.cv_func_id 3
	.cv_loc	3 1 42 0                        # vm.c:42:0
.seh_proc main2
# %bb.0:
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
.Ltmp28:
	#DEBUG_VALUE: main2:ip <- undef
	lea	rcx, [rip + program+1]
.Ltmp29:
	#DEBUG_VALUE: main2:ip <- $rcx
	lea	rax, [rip + stack]
.Ltmp30:
	#DEBUG_VALUE: main2:sp <- $rax
	movzx	r8d, byte ptr [rip + program]
	lea	r9, [rip + .L__const.main2.opcodes]
.Ltmp31:
	#DEBUG_VALUE: main2:ip <- undef
	#DEBUG_VALUE: main2:sp <- undef
	jmp	qword ptr [r9 + 8*r8]
.Ltmp32:
	.p2align	4, 0x90
.Ltmp33:                                # Block address taken
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	#DEBUG_LABEL: main2:U64_CONST
	#DEBUG_VALUE: main2:ip <- [DW_OP_plus_uconst 1, DW_OP_stack_value] undef
	.cv_loc	3 1 54 0                        # vm.c:54:0
	mov	rdx, qword ptr [rcx]
	mov	qword ptr [rax + 8], rdx
	add	rax, 8
.Ltmp34:
	#DEBUG_VALUE: main2:sp <- $rax
	.cv_loc	3 1 55 0                        # vm.c:55:0
	add	rcx, 2
.Ltmp35:
	#DEBUG_VALUE: main2:ip <- $rcx
	shr	rdx, 8
	movzx	edx, dl
.Ltmp36:
	#DEBUG_VALUE: main2:ip <- undef
	#DEBUG_VALUE: main2:sp <- undef
	jmp	qword ptr [r9 + 8*rdx]
.Ltmp37:
.Ltmp38:                                # Block address taken
.LBB2_2:
	#DEBUG_LABEL: main2:U64_ADD
	.cv_loc	3 1 57 0                        # vm.c:57:0
	lea	rcx, [rax - 8]
.Ltmp39:
	#DEBUG_VALUE: main2:sp <- $rcx
	mov	rdx, qword ptr [rax - 8]
.Ltmp40:
	#DEBUG_VALUE: main2:l <- $rdx
	#DEBUG_VALUE: main2:r <- undef
	.cv_loc	3 1 59 0                        # vm.c:59:0
	add	qword ptr [rax - 16], rdx
	jmp	.LBB2_4
.Ltmp41:
.Ltmp42:                                # Block address taken
.LBB2_3:
	mov	rcx, rax
.LBB2_4:
.Ltmp43:
	#DEBUG_LABEL: main2:END
	#DEBUG_VALUE: main2:sp <- $rcx
	.cv_loc	3 1 61 0                        # vm.c:61:0
	mov	rdx, qword ptr [rcx - 8]
	lea	rcx, [rip + "??_C@_07DOIONBAM@end?3?5?$CFd?$AA@"]
.Ltmp44:
	call	printf
	.cv_loc	3 1 62 0                        # vm.c:62:0
	xor	eax, eax
	add	rsp, 40
	ret
.Ltmp45:
.Lfunc_end2:
	.seh_endproc
                                        # -- End function
	.def	__local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__local_stdio_printf_options
	.globl	__local_stdio_printf_options    # -- Begin function __local_stdio_printf_options
	.p2align	4, 0x90
__local_stdio_printf_options:           # @__local_stdio_printf_options
.Lfunc_begin3:
	.cv_func_id 4
# %bb.0:
	.cv_file	3 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_stdio_config.h" "DACF907BDA504AFB0B64F53A242BDAE6" 1
	.cv_loc	4 3 92 0                        # C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\corecrt_stdio_config.h:92:0
	lea	rax, [rip + __local_stdio_printf_options._OptionsStorage]
	ret
.Ltmp46:
.Lfunc_end3:
                                        # -- End function
	.data
	.globl	program                         # @program
	.p2align	4
program:
	.ascii	"\000\005\000\000\000\000\n\000\000\000\001\000\002\000\000\000\002\004"

	.section	.rdata,"dr"
	.p2align	4                               # @__const.main.opcodes
.L__const.main.opcodes:
	.quad	.Ltmp5
	.quad	.Ltmp10
	.quad	.Ltmp14

	.bss
	.globl	stack                           # @stack
	.p2align	4
stack:
	.zero	2048

	.section	.rdata,"dr",discard,"??_C@_07DOIONBAM@end?3?5?$CFd?$AA@"
	.globl	"??_C@_07DOIONBAM@end?3?5?$CFd?$AA@" # @"??_C@_07DOIONBAM@end?3?5?$CFd?$AA@"
"??_C@_07DOIONBAM@end?3?5?$CFd?$AA@":
	.asciz	"end: %d"

	.section	.rdata,"dr"
	.p2align	4                               # @__const.main2.opcodes
.L__const.main2.opcodes:
	.quad	.Ltmp33
	.quad	.Ltmp38
	.quad	.Ltmp42

	.lcomm	__local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:msvcrt.lib"
	.ascii	" /DEFAULTLIB:oldnames.lib"
	.section	.debug$S,"dr"
	.p2align	2
	.long	4                               # Debug section magic
	.long	241
	.long	.Ltmp48-.Ltmp47                 # Subsection size
.Ltmp47:
	.short	.Ltmp50-.Ltmp49                 # Record length
.Ltmp49:
	.short	4353                            # Record kind: S_OBJNAME
	.long	0                               # Signature
	.asciz	"C:\\Users\\minio\\source\\repos\\redylang_vm\\x64\\Release\\vm.obj" # Object name
	.p2align	2
.Ltmp50:
	.short	.Ltmp52-.Ltmp51                 # Record length
.Ltmp51:
	.short	4412                            # Record kind: S_COMPILE3
	.long	0                               # Flags and language
	.short	208                             # CPUType
	.short	15                              # Frontend version
	.short	0
	.short	1
	.short	0
	.short	15001                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 15.0.1"          # Null-terminated compiler version string
	.p2align	2
.Ltmp52:
.Ltmp48:
	.p2align	2
	.long	246                             # Inlinee lines subsection
	.long	.Ltmp54-.Ltmp53                 # Subsection size
.Ltmp53:
	.long	0                               # Inlinee lines signature

                                        # Inlined function _vfprintf_l starts at C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\stdio.h:635
	.long	4117                            # Type index of inlined function
	.cv_filechecksumoffset	2               # Offset into filechecksum table
	.long	635                             # Starting line number
.Ltmp54:
	.p2align	2
	.section	.debug$S,"dr",associative,main
	.p2align	2
	.long	4                               # Debug section magic
	.long	241                             # Symbol subsection for main
	.long	.Ltmp56-.Ltmp55                 # Subsection size
.Ltmp55:
	.short	.Ltmp58-.Ltmp57                 # Record length
.Ltmp57:
	.short	4423                            # Record kind: S_GPROC32_ID
	.long	0                               # PtrParent
	.long	0                               # PtrEnd
	.long	0                               # PtrNext
	.long	.Lfunc_end0-main                # Code size
	.long	0                               # Offset after prologue
	.long	0                               # Offset before epilogue
	.long	4120                            # Function type index
	.secrel32	main                    # Function section relative address
	.secidx	main                            # Function section index
	.byte	0                               # Flags
	.asciz	"main"                          # Function name
	.p2align	2
.Ltmp58:
	.short	.Ltmp60-.Ltmp59                 # Record length
.Ltmp59:
	.short	4114                            # Record kind: S_FRAMEPROC
	.long	40                              # FrameSize
	.long	0                               # Padding
	.long	0                               # Offset of padding
	.long	0                               # Bytes of callee saved registers
	.long	0                               # Exception handler offset
	.short	0                               # Exception handler section
	.long	1130496                         # Flags (defines frame register)
	.p2align	2
.Ltmp60:
	.short	.Ltmp62-.Ltmp61                 # Record length
.Ltmp61:
	.short	4414                            # Record kind: S_LOCAL
	.long	1568                            # TypeIndex
	.short	0                               # Flags
	.asciz	"ip"
	.p2align	2
.Ltmp62:
	.cv_def_range	 .Ltmp1 .Ltmp3 .Ltmp7 .Ltmp8, reg, 330
	.short	.Ltmp64-.Ltmp63                 # Record length
.Ltmp63:
	.short	4414                            # Record kind: S_LOCAL
	.long	1571                            # TypeIndex
	.short	0                               # Flags
	.asciz	"sp"
	.p2align	2
.Ltmp64:
	.cv_def_range	 .Ltmp2 .Ltmp3 .Ltmp6 .Ltmp8, reg, 328
	.cv_def_range	 .Ltmp11 .Ltmp13 .Ltmp15 .Ltmp16, reg, 330
	.short	.Ltmp66-.Ltmp65                 # Record length
.Ltmp65:
	.short	4414                            # Record kind: S_LOCAL
	.long	35                              # TypeIndex
	.short	0                               # Flags
	.asciz	"l"
	.p2align	2
.Ltmp66:
	.cv_def_range	 .Ltmp12 .Ltmp13, reg, 331
	.short	.Ltmp68-.Ltmp67                 # Record length
.Ltmp67:
	.short	4414                            # Record kind: S_LOCAL
	.long	35                              # TypeIndex
	.short	256                             # Flags
	.asciz	"r"
	.p2align	2
.Ltmp68:
	.short	2                               # Record length
	.short	4431                            # Record kind: S_PROC_ID_END
.Ltmp56:
	.p2align	2
	.cv_linetable	0, main, .Lfunc_end0
	.section	.debug$S,"dr",associative,printf
	.p2align	2
	.long	4                               # Debug section magic
	.long	241                             # Symbol subsection for printf
	.long	.Ltmp70-.Ltmp69                 # Subsection size
.Ltmp69:
	.short	.Ltmp72-.Ltmp71                 # Record length
.Ltmp71:
	.short	4423                            # Record kind: S_GPROC32_ID
	.long	0                               # PtrParent
	.long	0                               # PtrEnd
	.long	0                               # PtrNext
	.long	.Lfunc_end1-printf              # Code size
	.long	0                               # Offset after prologue
	.long	0                               # Offset before epilogue
	.long	4123                            # Function type index
	.secrel32	printf                  # Function section relative address
	.secidx	printf                          # Function section index
	.byte	0                               # Flags
	.asciz	"printf"                        # Function name
	.p2align	2
.Ltmp72:
	.short	.Ltmp74-.Ltmp73                 # Record length
.Ltmp73:
	.short	4114                            # Record kind: S_FRAMEPROC
	.long	64                              # FrameSize
	.long	0                               # Padding
	.long	0                               # Offset of padding
	.long	24                              # Bytes of callee saved registers
	.long	0                               # Exception handler offset
	.short	0                               # Exception handler section
	.long	1130784                         # Flags (defines frame register)
	.p2align	2
.Ltmp74:
	.short	.Ltmp76-.Ltmp75                 # Record length
.Ltmp75:
	.short	4414                            # Record kind: S_LOCAL
	.long	4099                            # TypeIndex
	.short	1                               # Flags
	.asciz	"_Format"
	.p2align	2
.Ltmp76:
	.cv_def_range	 .Lfunc_begin1 .Ltmp20, reg, 330
	.cv_def_range	 .Ltmp20 .Ltmp22, reg, 332
	.short	.Ltmp78-.Ltmp77                 # Record length
.Ltmp77:
	.short	4414                            # Record kind: S_LOCAL
	.long	1648                            # TypeIndex
	.short	0                               # Flags
	.asciz	"_ArgList"
	.p2align	2
.Ltmp78:
	.cv_def_range	 .Ltmp19 .Ltmp19, reg, 329
	.cv_def_range	 .Ltmp19 .Lfunc_end1, frame_ptr_rel, 48
	.short	.Ltmp80-.Ltmp79                 # Record length
.Ltmp79:
	.short	4414                            # Record kind: S_LOCAL
	.long	116                             # TypeIndex
	.short	0                               # Flags
	.asciz	"_Result"
	.p2align	2
.Ltmp80:
	.cv_def_range	 .Ltmp22 .Ltmp26, reg, 23
	.cv_def_range	 .Ltmp26 .Lfunc_end1, reg, 17
	.short	.Ltmp82-.Ltmp81                 # Record length
.Ltmp81:
	.short	4429                            # Record kind: S_INLINESITE
	.long	0                               # PtrParent
	.long	0                               # PtrEnd
	.long	4117                            # Inlinee type index
	.cv_inline_linetable	2 2 635 .Lfunc_begin1 .Lfunc_end1
	.p2align	2
.Ltmp82:
	.short	.Ltmp84-.Ltmp83                 # Record length
.Ltmp83:
	.short	4414                            # Record kind: S_LOCAL
	.long	4097                            # TypeIndex
	.short	1                               # Flags
	.asciz	"_Stream"
	.p2align	2
.Ltmp84:
	.cv_def_range	 .Ltmp21 .Ltmp25, reg, 333
	.short	.Ltmp86-.Ltmp85                 # Record length
.Ltmp85:
	.short	4414                            # Record kind: S_LOCAL
	.long	4099                            # TypeIndex
	.short	1                               # Flags
	.asciz	"_Format"
	.p2align	2
.Ltmp86:
	.cv_def_range	 .Ltmp18 .Ltmp22, reg, 332
	.short	.Ltmp88-.Ltmp87                 # Record length
.Ltmp87:
	.short	4414                            # Record kind: S_LOCAL
	.long	4102                            # TypeIndex
	.short	257                             # Flags
	.asciz	"_Locale"
	.p2align	2
.Ltmp88:
	.short	.Ltmp90-.Ltmp89                 # Record length
.Ltmp89:
	.short	4414                            # Record kind: S_LOCAL
	.long	1648                            # TypeIndex
	.short	1                               # Flags
	.asciz	"_ArgList"
	.p2align	2
.Ltmp90:
	.cv_def_range	 .Ltmp19 .Ltmp24, reg, 329
	.short	2                               # Record length
	.short	4430                            # Record kind: S_INLINESITE_END
	.short	2                               # Record length
	.short	4431                            # Record kind: S_PROC_ID_END
.Ltmp70:
	.p2align	2
	.cv_linetable	1, printf, .Lfunc_end1
	.section	.debug$S,"dr",associative,main2
	.p2align	2
	.long	4                               # Debug section magic
	.long	241                             # Symbol subsection for main2
	.long	.Ltmp92-.Ltmp91                 # Subsection size
.Ltmp91:
	.short	.Ltmp94-.Ltmp93                 # Record length
.Ltmp93:
	.short	4423                            # Record kind: S_GPROC32_ID
	.long	0                               # PtrParent
	.long	0                               # PtrEnd
	.long	0                               # PtrNext
	.long	.Lfunc_end2-main2               # Code size
	.long	0                               # Offset after prologue
	.long	0                               # Offset before epilogue
	.long	4124                            # Function type index
	.secrel32	main2                   # Function section relative address
	.secidx	main2                           # Function section index
	.byte	0                               # Flags
	.asciz	"main2"                         # Function name
	.p2align	2
.Ltmp94:
	.short	.Ltmp96-.Ltmp95                 # Record length
.Ltmp95:
	.short	4114                            # Record kind: S_FRAMEPROC
	.long	40                              # FrameSize
	.long	0                               # Padding
	.long	0                               # Offset of padding
	.long	0                               # Bytes of callee saved registers
	.long	0                               # Exception handler offset
	.short	0                               # Exception handler section
	.long	1130496                         # Flags (defines frame register)
	.p2align	2
.Ltmp96:
	.short	.Ltmp98-.Ltmp97                 # Record length
.Ltmp97:
	.short	4414                            # Record kind: S_LOCAL
	.long	1568                            # TypeIndex
	.short	0                               # Flags
	.asciz	"ip"
	.p2align	2
.Ltmp98:
	.cv_def_range	 .Ltmp29 .Ltmp31 .Ltmp35 .Ltmp36, reg, 330
	.short	.Ltmp100-.Ltmp99                # Record length
.Ltmp99:
	.short	4414                            # Record kind: S_LOCAL
	.long	1571                            # TypeIndex
	.short	0                               # Flags
	.asciz	"sp"
	.p2align	2
.Ltmp100:
	.cv_def_range	 .Ltmp30 .Ltmp31 .Ltmp34 .Ltmp36, reg, 328
	.cv_def_range	 .Ltmp39 .Ltmp41 .Ltmp43 .Ltmp44, reg, 330
	.short	.Ltmp102-.Ltmp101               # Record length
.Ltmp101:
	.short	4414                            # Record kind: S_LOCAL
	.long	35                              # TypeIndex
	.short	0                               # Flags
	.asciz	"l"
	.p2align	2
.Ltmp102:
	.cv_def_range	 .Ltmp40 .Ltmp41, reg, 331
	.short	.Ltmp104-.Ltmp103               # Record length
.Ltmp103:
	.short	4414                            # Record kind: S_LOCAL
	.long	35                              # TypeIndex
	.short	256                             # Flags
	.asciz	"r"
	.p2align	2
.Ltmp104:
	.short	2                               # Record length
	.short	4431                            # Record kind: S_PROC_ID_END
.Ltmp92:
	.p2align	2
	.cv_linetable	3, main2, .Lfunc_end2
	.section	.debug$S,"dr",associative,__local_stdio_printf_options
	.p2align	2
	.long	4                               # Debug section magic
	.long	241                             # Symbol subsection for __local_stdio_printf_options
	.long	.Ltmp106-.Ltmp105               # Subsection size
.Ltmp105:
	.short	.Ltmp108-.Ltmp107               # Record length
.Ltmp107:
	.short	4423                            # Record kind: S_GPROC32_ID
	.long	0                               # PtrParent
	.long	0                               # PtrEnd
	.long	0                               # PtrNext
	.long	.Lfunc_end3-__local_stdio_printf_options # Code size
	.long	0                               # Offset after prologue
	.long	0                               # Offset before epilogue
	.long	4126                            # Function type index
	.secrel32	__local_stdio_printf_options # Function section relative address
	.secidx	__local_stdio_printf_options    # Function section index
	.byte	0                               # Flags
	.asciz	"__local_stdio_printf_options"  # Function name
	.p2align	2
.Ltmp108:
	.short	.Ltmp110-.Ltmp109               # Record length
.Ltmp109:
	.short	4114                            # Record kind: S_FRAMEPROC
	.long	0                               # FrameSize
	.long	0                               # Padding
	.long	0                               # Offset of padding
	.long	0                               # Bytes of callee saved registers
	.long	0                               # Exception handler offset
	.short	0                               # Exception handler section
	.long	1048576                         # Flags (defines frame register)
	.p2align	2
.Ltmp110:
	.short	.Ltmp112-.Ltmp111               # Record length
.Ltmp111:
	.short	4364                            # Record kind: S_LDATA32
	.long	35                              # Type
	.secrel32	__local_stdio_printf_options._OptionsStorage # DataOffset
	.secidx	__local_stdio_printf_options._OptionsStorage # Segment
	.asciz	"__local_stdio_printf_options::_OptionsStorage" # Name
	.p2align	2
.Ltmp112:
	.short	2                               # Record length
	.short	4431                            # Record kind: S_PROC_ID_END
.Ltmp106:
	.p2align	2
	.cv_linetable	4, __local_stdio_printf_options, .Lfunc_end3
	.section	.debug$S,"dr"
	.long	241                             # Symbol subsection for globals
	.long	.Ltmp114-.Ltmp113               # Subsection size
.Ltmp113:
	.short	.Ltmp116-.Ltmp115               # Record length
.Ltmp115:
	.short	4365                            # Record kind: S_GDATA32
	.long	4127                            # Type
	.secrel32	program                 # DataOffset
	.secidx	program                         # Segment
	.asciz	"program"                       # Name
	.p2align	2
.Ltmp116:
	.short	.Ltmp118-.Ltmp117               # Record length
.Ltmp117:
	.short	4365                            # Record kind: S_GDATA32
	.long	4128                            # Type
	.secrel32	stack                   # DataOffset
	.secidx	stack                           # Segment
	.asciz	"stack"                         # Name
	.p2align	2
.Ltmp118:
.Ltmp114:
	.p2align	2
	.long	241
	.long	.Ltmp120-.Ltmp119               # Subsection size
.Ltmp119:
	.short	.Ltmp122-.Ltmp121               # Record length
.Ltmp121:
	.short	4360                            # Record kind: S_UDT
	.long	4106                            # Type
	.asciz	"FILE"
	.p2align	2
.Ltmp122:
	.short	.Ltmp124-.Ltmp123               # Record length
.Ltmp123:
	.short	4360                            # Record kind: S_UDT
	.long	4114                            # Type
	.asciz	"__crt_locale_pointers"
	.p2align	2
.Ltmp124:
	.short	.Ltmp126-.Ltmp125               # Record length
.Ltmp125:
	.short	4360                            # Record kind: S_UDT
	.long	4101                            # Type
	.asciz	"_locale_t"
	.p2align	2
.Ltmp126:
	.short	.Ltmp128-.Ltmp127               # Record length
.Ltmp127:
	.short	4360                            # Record kind: S_UDT
	.long	1648                            # Type
	.asciz	"va_list"
	.p2align	2
.Ltmp128:
	.short	.Ltmp130-.Ltmp129               # Record length
.Ltmp129:
	.short	4360                            # Record kind: S_UDT
	.long	4106                            # Type
	.asciz	"_iobuf"
	.p2align	2
.Ltmp130:
	.short	.Ltmp132-.Ltmp131               # Record length
.Ltmp131:
	.short	4360                            # Record kind: S_UDT
	.long	4114                            # Type
	.asciz	"__crt_locale_pointers"
	.p2align	2
.Ltmp132:
	.short	.Ltmp134-.Ltmp133               # Record length
.Ltmp133:
	.short	4360                            # Record kind: S_UDT
	.long	32                              # Type
	.asciz	"uint8_t"
	.p2align	2
.Ltmp134:
	.short	.Ltmp136-.Ltmp135               # Record length
.Ltmp135:
	.short	4360                            # Record kind: S_UDT
	.long	35                              # Type
	.asciz	"uint64_t"
	.p2align	2
.Ltmp136:
	.short	.Ltmp138-.Ltmp137               # Record length
.Ltmp137:
	.short	4360                            # Record kind: S_UDT
	.long	35                              # Type
	.asciz	"size_t"
	.p2align	2
.Ltmp138:
.Ltmp120:
	.p2align	2
	.cv_filechecksums                       # File index to string table offset subsection
	.cv_stringtable                         # String table
	.long	241
	.long	.Ltmp140-.Ltmp139               # Subsection size
.Ltmp139:
	.short	.Ltmp142-.Ltmp141               # Record length
.Ltmp141:
	.short	4428                            # Record kind: S_BUILDINFO
	.long	4134                            # LF_BUILDINFO index
	.p2align	2
.Ltmp142:
.Ltmp140:
	.p2align	2
	.section	.debug$T,"dr"
	.p2align	2
	.long	4                               # Debug section magic
	# Struct (0x1000)
	.short	0x1e                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x0                             # MemberCount
	.short	0x80                            # Properties ( ForwardReference (0x80) )
	.long	0x0                             # FieldList
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x0                             # SizeOf
	.asciz	"_iobuf"                        # Name
	.byte	243
	.byte	242
	.byte	241
	# Pointer (0x1001)
	.short	0xa                             # Record length
	.short	0x1002                          # Record kind: LF_POINTER
	.long	0x1000                          # PointeeType: _iobuf
	.long	0x1040c                         # Attrs: [ Type: Near64, Mode: Pointer, SizeOf: 8, isConst ]
	# Modifier (0x1002)
	.short	0xa                             # Record length
	.short	0x1001                          # Record kind: LF_MODIFIER
	.long	0x70                            # ModifiedType: char
	.short	0x1                             # Modifiers ( Const (0x1) )
	.byte	242
	.byte	241
	# Pointer (0x1003)
	.short	0xa                             # Record length
	.short	0x1002                          # Record kind: LF_POINTER
	.long	0x1002                          # PointeeType: const char
	.long	0x1040c                         # Attrs: [ Type: Near64, Mode: Pointer, SizeOf: 8, isConst ]
	# Struct (0x1004)
	.short	0x2a                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x0                             # MemberCount
	.short	0x80                            # Properties ( ForwardReference (0x80) )
	.long	0x0                             # FieldList
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x0                             # SizeOf
	.asciz	"__crt_locale_pointers"         # Name
	# Pointer (0x1005)
	.short	0xa                             # Record length
	.short	0x1002                          # Record kind: LF_POINTER
	.long	0x1004                          # PointeeType: __crt_locale_pointers
	.long	0x1000c                         # Attrs: [ Type: Near64, Mode: Pointer, SizeOf: 8 ]
	# Modifier (0x1006)
	.short	0xa                             # Record length
	.short	0x1001                          # Record kind: LF_MODIFIER
	.long	0x1005                          # ModifiedType: __crt_locale_pointers*
	.short	0x1                             # Modifiers ( Const (0x1) )
	.byte	242
	.byte	241
	# ArgList (0x1007)
	.short	0x16                            # Record length
	.short	0x1201                          # Record kind: LF_ARGLIST
	.long	0x4                             # NumArgs
	.long	0x1001                          # Argument: _iobuf* const
	.long	0x1003                          # Argument: const char* const
	.long	0x1006                          # Argument: const __crt_locale_pointers*
	.long	0x670                           # Argument: char*
	# Procedure (0x1008)
	.short	0xe                             # Record length
	.short	0x1008                          # Record kind: LF_PROCEDURE
	.long	0x74                            # ReturnType: int
	.byte	0x0                             # CallingConvention: NearC
	.byte	0x0                             # FunctionOptions
	.short	0x4                             # NumParameters
	.long	0x1007                          # ArgListType: (_iobuf* const, const char* const, const __crt_locale_pointers*, char*)
	# FieldList (0x1009)
	.short	0x1a                            # Record length
	.short	0x1203                          # Record kind: LF_FIELDLIST
	.short	0x150d                          # Member kind: DataMember ( LF_MEMBER )
	.short	0x3                             # Attrs: Public
	.long	0x603                           # Type: void*
	.short	0x0                             # FieldOffset
	.asciz	"_Placeholder"                  # Name
	.byte	241
	# Struct (0x100A)
	.short	0x1e                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x1                             # MemberCount
	.short	0x0                             # Properties
	.long	0x1009                          # FieldList: <field list>
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x8                             # SizeOf
	.asciz	"_iobuf"                        # Name
	.byte	243
	.byte	242
	.byte	241
	# StringId (0x100B)
	.short	0x5a                            # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt_wstdio.h" # StringData
	.byte	242
	.byte	241
	# UdtSourceLine (0x100C)
	.short	0xe                             # Record length
	.short	0x1606                          # Record kind: LF_UDT_SRC_LINE
	.long	0x100a                          # UDT: _iobuf
	.long	0x100b                          # SourceFile: C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\corecrt_wstdio.h
	.long	0x1c                            # LineNumber
	# Struct (0x100D)
	.short	0x26                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x0                             # MemberCount
	.short	0x80                            # Properties ( ForwardReference (0x80) )
	.long	0x0                             # FieldList
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x0                             # SizeOf
	.asciz	"__crt_locale_data"             # Name
	# Pointer (0x100E)
	.short	0xa                             # Record length
	.short	0x1002                          # Record kind: LF_POINTER
	.long	0x100d                          # PointeeType: __crt_locale_data
	.long	0x1000c                         # Attrs: [ Type: Near64, Mode: Pointer, SizeOf: 8 ]
	# Struct (0x100F)
	.short	0x2a                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x0                             # MemberCount
	.short	0x80                            # Properties ( ForwardReference (0x80) )
	.long	0x0                             # FieldList
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x0                             # SizeOf
	.asciz	"__crt_multibyte_data"          # Name
	.byte	241
	# Pointer (0x1010)
	.short	0xa                             # Record length
	.short	0x1002                          # Record kind: LF_POINTER
	.long	0x100f                          # PointeeType: __crt_multibyte_data
	.long	0x1000c                         # Attrs: [ Type: Near64, Mode: Pointer, SizeOf: 8 ]
	# FieldList (0x1011)
	.short	0x2a                            # Record length
	.short	0x1203                          # Record kind: LF_FIELDLIST
	.short	0x150d                          # Member kind: DataMember ( LF_MEMBER )
	.short	0x3                             # Attrs: Public
	.long	0x100e                          # Type: __crt_locale_data*
	.short	0x0                             # FieldOffset
	.asciz	"locinfo"                       # Name
	.byte	242
	.byte	241
	.short	0x150d                          # Member kind: DataMember ( LF_MEMBER )
	.short	0x3                             # Attrs: Public
	.long	0x1010                          # Type: __crt_multibyte_data*
	.short	0x8                             # FieldOffset
	.asciz	"mbcinfo"                       # Name
	.byte	242
	.byte	241
	# Struct (0x1012)
	.short	0x2a                            # Record length
	.short	0x1505                          # Record kind: LF_STRUCTURE
	.short	0x2                             # MemberCount
	.short	0x0                             # Properties
	.long	0x1011                          # FieldList: <field list>
	.long	0x0                             # DerivedFrom
	.long	0x0                             # VShape
	.short	0x10                            # SizeOf
	.asciz	"__crt_locale_pointers"         # Name
	# StringId (0x1013)
	.short	0x52                            # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt\\corecrt.h" # StringData
	.byte	241
	# UdtSourceLine (0x1014)
	.short	0xe                             # Record length
	.short	0x1606                          # Record kind: LF_UDT_SRC_LINE
	.long	0x1012                          # UDT: __crt_locale_pointers
	.long	0x1013                          # SourceFile: C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\ucrt\corecrt.h
	.long	0x269                           # LineNumber
	# FuncId (0x1015)
	.short	0x16                            # Record length
	.short	0x1601                          # Record kind: LF_FUNC_ID
	.long	0x0                             # ParentScope
	.long	0x1008                          # FunctionType: int (_iobuf* const, const char* const, const __crt_locale_pointers*, char*)
	.asciz	"_vfprintf_l"                   # Name
	# ArgList (0x1016)
	.short	0x6                             # Record length
	.short	0x1201                          # Record kind: LF_ARGLIST
	.long	0x0                             # NumArgs
	# Procedure (0x1017)
	.short	0xe                             # Record length
	.short	0x1008                          # Record kind: LF_PROCEDURE
	.long	0x74                            # ReturnType: int
	.byte	0x0                             # CallingConvention: NearC
	.byte	0x0                             # FunctionOptions
	.short	0x0                             # NumParameters
	.long	0x1016                          # ArgListType: ()
	# FuncId (0x1018)
	.short	0x12                            # Record length
	.short	0x1601                          # Record kind: LF_FUNC_ID
	.long	0x0                             # ParentScope
	.long	0x1017                          # FunctionType: int ()
	.asciz	"main"                          # Name
	.byte	243
	.byte	242
	.byte	241
	# ArgList (0x1019)
	.short	0xe                             # Record length
	.short	0x1201                          # Record kind: LF_ARGLIST
	.long	0x2                             # NumArgs
	.long	0x1003                          # Argument: const char* const
	.long	0x0                             # Argument
	# Procedure (0x101A)
	.short	0xe                             # Record length
	.short	0x1008                          # Record kind: LF_PROCEDURE
	.long	0x74                            # ReturnType: int
	.byte	0x0                             # CallingConvention: NearC
	.byte	0x0                             # FunctionOptions
	.short	0x2                             # NumParameters
	.long	0x1019                          # ArgListType: (const char* const, <no type>)
	# FuncId (0x101B)
	.short	0x12                            # Record length
	.short	0x1601                          # Record kind: LF_FUNC_ID
	.long	0x0                             # ParentScope
	.long	0x101a                          # FunctionType: int (const char* const, <no type>)
	.asciz	"printf"                        # Name
	.byte	241
	# FuncId (0x101C)
	.short	0x12                            # Record length
	.short	0x1601                          # Record kind: LF_FUNC_ID
	.long	0x0                             # ParentScope
	.long	0x1017                          # FunctionType: int ()
	.asciz	"main2"                         # Name
	.byte	242
	.byte	241
	# Procedure (0x101D)
	.short	0xe                             # Record length
	.short	0x1008                          # Record kind: LF_PROCEDURE
	.long	0x623                           # ReturnType: unsigned __int64*
	.byte	0x0                             # CallingConvention: NearC
	.byte	0x0                             # FunctionOptions
	.short	0x0                             # NumParameters
	.long	0x1016                          # ArgListType: ()
	# FuncId (0x101E)
	.short	0x2a                            # Record length
	.short	0x1601                          # Record kind: LF_FUNC_ID
	.long	0x0                             # ParentScope
	.long	0x101d                          # FunctionType: unsigned __int64* ()
	.asciz	"__local_stdio_printf_options"  # Name
	.byte	243
	.byte	242
	.byte	241
	# Array (0x101F)
	.short	0xe                             # Record length
	.short	0x1503                          # Record kind: LF_ARRAY
	.long	0x20                            # ElementType: unsigned char
	.long	0x23                            # IndexType: unsigned __int64
	.short	0x12                            # SizeOf
	.byte	0                               # Name
	.byte	241
	# Array (0x1020)
	.short	0xe                             # Record length
	.short	0x1503                          # Record kind: LF_ARRAY
	.long	0x23                            # ElementType: unsigned __int64
	.long	0x23                            # IndexType: unsigned __int64
	.short	0x800                           # SizeOf
	.byte	0                               # Name
	.byte	241
	# StringId (0x1021)
	.short	0x2e                            # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"C:\\Users\\minio\\source\\repos\\redylang_vm" # StringData
	# StringId (0x1022)
	.short	0xe                             # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"vm.c"                          # StringData
	.byte	243
	.byte	242
	.byte	241
	# StringId (0x1023)
	.short	0xa                             # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.byte	0                               # StringData
	.byte	243
	.byte	242
	.byte	241
	# StringId (0x1024)
	.short	0x62                            # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\clang-cl.exe" # StringData
	.byte	241
	# StringId (0x1025)
	.short	0xe1a                           # Record length
	.short	0x1605                          # Record kind: LF_STRING_ID
	.long	0x0                             # Id
	.asciz	"\"-cc1\" \"-triple\" \"x86_64-pc-windows-msvc19.36.32537\" \"-S\" \"-disable-free\" \"-clear-ast-before-backend\" \"-disable-llvm-verifier\" \"-discard-value-names\" \"-mrelocation-model\" \"pic\" \"-pic-level\" \"2\" \"-mframe-pointer=none\" \"-relaxed-aliasing\" \"-fmath-errno\" \"-ffp-contract=on\" \"-fno-rounding-math\" \"-mconstructor-aliases\" \"-funwind-tables=2\" \"-target-cpu\" \"x86-64\" \"-mllvm\" \"-x86-asm-syntax=intel\" \"-tune-cpu\" \"generic\" \"-mllvm\" \"-treat-scalable-fixed-error-as-warning\" \"-D_MT\" \"-D_DLL\" \"--dependent-lib=msvcrt\" \"--dependent-lib=oldnames\" \"-stack-protector\" \"2\" \"-fexceptions\" \"-fms-volatile\" \"-fdefault-calling-conv=cdecl\" \"-fdiagnostics-format\" \"msvc\" \"-gno-column-info\" \"-gcodeview\" \"-debug-info-kind=constructor\" \"-ffunction-sections\" \"-fcoverage-compilation-dir=C:\\\\Users\\\\minio\\\\source\\\\repos\\\\redylang_vm\" \"-resource-dir\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\Llvm\\\\x64\\\\lib\\\\clang\\\\15.0.1\" \"-I\" \"Z:\\\\vcpkg\\\\installed\\\\x64-windows\\\\include\" \"-D\" \"NDEBUG\" \"-D\" \"_CONSOLE\" \"-D\" \"_UNICODE\" \"-D\" \"UNICODE\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\Llvm\\\\x64\\\\lib\\\\clang\\\\15.0.1\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\Llvm\\\\x64\\\\lib\\\\clang\\\\15.0.1\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\MSVC\\\\14.36.32532\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\MSVC\\\\14.36.32532\\\\atlmfc\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Auxiliary\\\\VS\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\ucrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\um\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\shared\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\winrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\cppwinrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\NETFXSDK\\\\4.8\\\\Include\\\\um\" \"-internal-isystem\" \"Z:\\\\vcpkg\\\\installed\\\\x64-windows\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\MSVC\\\\14.36.32532\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Tools\\\\MSVC\\\\14.36.32532\\\\atlmfc\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\VC\\\\Auxiliary\\\\VS\\\\include\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\ucrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\um\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\shared\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\winrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\10\\\\Include\\\\10.0.22000.0\\\\cppwinrt\" \"-internal-isystem\" \"C:\\\\Program Files (x86)\\\\Windows Kits\\\\NETFXSDK\\\\4.8\\\\Include\\\\um\" \"-internal-isystem\" \"Z:\\\\vcpkg\\\\installed\\\\x64-windows\\\\include\" \"-O2\" \"-Wall\" \"-Wno-error\" \"-fdebug-compilation-dir=C:\\\\Users\\\\minio\\\\source\\\\repos\\\\redylang_vm\" \"-ferror-limit\" \"19\" \"-fno-use-cxa-atexit\" \"-fms-extensions\" \"-fms-compatibility\" \"-fms-compatibility-version=19.36.32537\" \"-fdelayed-template-parsing\" \"-fno-caret-diagnostics\" \"-vectorize-loops\" \"-vectorize-slp\" \"-faddrsig\" \"-x\" \"c\"" # StringData
	.byte	242
	.byte	241
	# BuildInfo (0x1026)
	.short	0x1a                            # Record length
	.short	0x1603                          # Record kind: LF_BUILDINFO
	.short	0x5                             # NumArgs
	.long	0x1021                          # Argument: C:\Users\minio\source\repos\redylang_vm
	.long	0x1024                          # Argument: C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\clang-cl.exe
	.long	0x1022                          # Argument: vm.c
	.long	0x1023                          # Argument
	.long	0x1025                          # Argument: "-cc1" "-triple" "x86_64-pc-windows-msvc19.36.32537" "-S" "-disable-free" "-clear-ast-before-backend" "-disable-llvm-verifier" "-discard-value-names" "-mrelocation-model" "pic" "-pic-level" "2" "-mframe-pointer=none" "-relaxed-aliasing" "-fmath-errno" "-ffp-contract=on" "-fno-rounding-math" "-mconstructor-aliases" "-funwind-tables=2" "-target-cpu" "x86-64" "-mllvm" "-x86-asm-syntax=intel" "-tune-cpu" "generic" "-mllvm" "-treat-scalable-fixed-error-as-warning" "-D_MT" "-D_DLL" "--dependent-lib=msvcrt" "--dependent-lib=oldnames" "-stack-protector" "2" "-fexceptions" "-fms-volatile" "-fdefault-calling-conv=cdecl" "-fdiagnostics-format" "msvc" "-gno-column-info" "-gcodeview" "-debug-info-kind=constructor" "-ffunction-sections" "-fcoverage-compilation-dir=C:\\Users\\minio\\source\\repos\\redylang_vm" "-resource-dir" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1" "-I" "Z:\\vcpkg\\installed\\x64-windows\\include" "-D" "NDEBUG" "-D" "_CONSOLE" "-D" "_UNICODE" "-D" "UNICODE" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.36.32532\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.36.32532\\atlmfc\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\VS\\include" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\um" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\shared" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\winrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\cppwinrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\NETFXSDK\\4.8\\Include\\um" "-internal-isystem" "Z:\\vcpkg\\installed\\x64-windows\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.36.32532\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.36.32532\\atlmfc\\include" "-internal-isystem" "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\VS\\include" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\ucrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\um" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\shared" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\winrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\cppwinrt" "-internal-isystem" "C:\\Program Files (x86)\\Windows Kits\\NETFXSDK\\4.8\\Include\\um" "-internal-isystem" "Z:\\vcpkg\\installed\\x64-windows\\include" "-O2" "-Wall" "-Wno-error" "-fdebug-compilation-dir=C:\\Users\\minio\\source\\repos\\redylang_vm" "-ferror-limit" "19" "-fno-use-cxa-atexit" "-fms-extensions" "-fms-compatibility" "-fms-compatibility-version=19.36.32537" "-fdelayed-template-parsing" "-fno-caret-diagnostics" "-vectorize-loops" "-vectorize-slp" "-faddrsig" "-x" "c"
	.byte	242
	.byte	241
	.addrsig
	.addrsig_sym main
	.addrsig_sym main2
	.addrsig_sym __local_stdio_printf_options._OptionsStorage
