	.file	"qsort.ll"
	.text
	.globl	printa
	.align	16, 0x90
	.type	printa,@function
printa:                                 # @printa
# BB#0:                                 # %entry
	subq	$24, %rsp
	movq	%rdi, 16(%rsp)
	movl	%esi, 12(%rsp)
	movl	$0, 8(%rsp)
	jmp	.LBB1_1
	.align	16, 0x90
.LBB1_2:                                #   in Loop: Header=BB1_1 Depth=1
	movslq	8(%rsp), %rax
	movq	16(%rsp), %rcx
	movl	(%rcx,%rax,4), %esi
	xorb	%al, %al
	movl	$_printa, %edi
	callq	printf
	incl	8(%rsp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	12(%rsp), %eax
	cmpl	%eax, 8(%rsp)
	jl	.LBB1_2
# BB#3:
	addq	$24, %rsp
	ret
	.size	printa, .-printa

	.globl	_quicksort
	.align	16, 0x90
	.type	_quicksort,@function
_quicksort:                             # @_quicksort
.Leh_func_begin1:
# BB#0:
	subq	$40, %rsp
.Llabel1:
	movq	%rdi, 32(%rsp)
	movl	%esi, 28(%rsp)
	movl	%edx, 24(%rsp)
	movl	28(%rsp), %eax
	movl	%eax, 20(%rsp)
	movl	24(%rsp), %eax
	movl	%eax, 16(%rsp)
	addl	20(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movslq	%ecx, %rax
	movq	32(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 12(%rsp)
	jmp	.LBB2_1
	.align	16, 0x90
.LBB2_5:                                #   in Loop: Header=BB2_4 Depth=2
	decl	16(%rsp)
.LBB2_4:                                #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	12(%rsp), %eax
	movslq	16(%rsp), %rcx
	movq	32(%rsp), %rdx
	cmpl	%eax, (%rdx,%rcx,4)
	jg	.LBB2_5
# BB#6:                                 #   in Loop: Header=BB2_1 Depth=1
	movl	16(%rsp), %eax
	cmpl	%eax, 20(%rsp)
	jg	.LBB2_1
# BB#7:                                 #   in Loop: Header=BB2_1 Depth=1
	movslq	20(%rsp), %rax
	movq	32(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 8(%rsp)
	movslq	16(%rsp), %rax
	movq	32(%rsp), %rcx
	movl	(%rcx,%rax,4), %eax
	movslq	20(%rsp), %rdx
	movl	%eax, (%rcx,%rdx,4)
	movq	32(%rsp), %rax
	movslq	16(%rsp), %rcx
	movl	8(%rsp), %edx
	movl	%edx, (%rax,%rcx,4)
	incl	20(%rsp)
	decl	16(%rsp)
.LBB2_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_4 Depth 2
                                        #     Child Loop BB2_2 Depth 2
	movl	16(%rsp), %eax
	cmpl	%eax, 20(%rsp)
	jge	.LBB2_8
	.align	16, 0x90
.LBB2_2:                                #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	12(%rsp), %eax
	movslq	20(%rsp), %rcx
	movq	32(%rsp), %rdx
	cmpl	%eax, (%rdx,%rcx,4)
	jge	.LBB2_4
# BB#3:                                 #   in Loop: Header=BB2_2 Depth=2
	incl	20(%rsp)
	jmp	.LBB2_2
.LBB2_8:
	movl	28(%rsp), %eax
	cmpl	%eax, 16(%rsp)
	jle	.LBB2_10
# BB#9:
	movl	16(%rsp), %edx
	movl	28(%rsp), %esi
	movq	32(%rsp), %rdi
	callq	_quicksort
.LBB2_10:
	movl	24(%rsp), %eax
	cmpl	%eax, 20(%rsp)
	jge	.LBB2_12
# BB#11:
	movl	24(%rsp), %edx
	movl	20(%rsp), %esi
	movq	32(%rsp), %rdi
	callq	_quicksort
.LBB2_12:
	addq	$40, %rsp
	ret
	.size	_quicksort, .-_quicksort
.Leh_func_end1:

	.globl	quicksort
	.align	16, 0x90
	.type	quicksort,@function
quicksort:                              # @quicksort
.Leh_func_begin2:
# BB#0:
	subq	$24, %rsp
.Llabel2:
	movq	%rdi, 16(%rsp)
	movl	%esi, 12(%rsp)
	movq	16(%rsp), %rdi
	movl	%esi, %edx
	decl	%edx
	xorl	%esi, %esi
	callq	_quicksort
	addq	$24, %rsp
	ret
	.size	quicksort, .-quicksort
.Leh_func_end2:

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
.Leh_func_begin3:
# BB#0:
	pushq	%rbx
.Llabel3:
	subq	$48, %rsp
.Llabel4:
	movl	$0, 44(%rsp)
	movl	$10, (%rsp)
	movl	$1, 4(%rsp)
	movl	$2, 8(%rsp)
	movl	$0, 12(%rsp)
	movl	$10, 16(%rsp)
	movl	$22, 20(%rsp)
	movl	$1, 24(%rsp)
	movl	$3, 28(%rsp)
	movl	$12, 32(%rsp)
	movl	$4, 36(%rsp)
	movl	$3, 40(%rsp)
	movl	(%rsp), %esi
	leaq	4(%rsp), %rbx
	movq	%rbx, %rdi
	callq	quicksort
	movl	(%rsp), %esi
	movq	%rbx, %rdi
	callq	printa
	movl	$0, 44(%rsp)
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbx
	ret
	.size	main, .-main
.Leh_func_end3:

	.type	_printa,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
_printa:                                # @_printa
	.asciz	 "%d  "
	.size	_printa, 5

	.section	.eh_frame,"aw",@progbits
.LEH_frame0:
.Lsection_eh_frame:
.Leh_frame_common:
	.set	.Lset1eh,.Leh_frame_common_end-.Leh_frame_common_begin
	.long	.Lset1eh                # Length of Common Information Entry
.Leh_frame_common_begin:
	.long	0                       # CIE Identifier Tag
	.byte	1                       # DW_CIE_VERSION
	.asciz	 "zR"
                                        # CIE Augmentation
	.uleb128	1               # CIE Code Alignment Factor
	.sleb128	-8              # CIE Data Alignment Factor
	.byte	16
                                        # CIE Return Address Column
	.uleb128	1               # Augmentation Size
	.byte	3                       # FDE Encoding = udata4
	.byte	12                      # CFA_def_cfa
	.uleb128	7               # Register
	.uleb128	8               # Offset
	.byte	144                     # DW_CFA_offset + Reg (16)
	.uleb128	1               # Offset
	.align	8
.Leh_frame_common_end:

.L_quicksort.eh:
	.set	.Lset2eh,.Leh_frame_end1-.Leh_frame_begin1
	.long	.Lset2eh                # Length of Frame Information Entry
.Leh_frame_begin1:
	.long	.Leh_frame_begin1-.Leh_frame_common # FDE CIE offset
	.long	.Leh_func_begin1        # FDE initial location
	.set	.Lset3eh,.Leh_func_end1-.Leh_func_begin1
	.long	.Lset3eh                # FDE address range
	.uleb128	0               # Augmentation size
	.byte	4                       # CFA_advance_loc4
	.set	.Lset4eh,.Llabel1-.Leh_func_begin1
	.long	.Lset4eh
	.byte	14                      # CFA_def_cfa_offset
	.uleb128	48              # Offset
	.align	8
.Leh_frame_end1:

.Lquicksort.eh:
	.set	.Lset5eh,.Leh_frame_end2-.Leh_frame_begin2
	.long	.Lset5eh                # Length of Frame Information Entry
.Leh_frame_begin2:
	.long	.Leh_frame_begin2-.Leh_frame_common # FDE CIE offset
	.long	.Leh_func_begin2        # FDE initial location
	.set	.Lset6eh,.Leh_func_end2-.Leh_func_begin2
	.long	.Lset6eh                # FDE address range
	.uleb128	0               # Augmentation size
	.byte	4                       # CFA_advance_loc4
	.set	.Lset7eh,.Llabel2-.Leh_func_begin2
	.long	.Lset7eh
	.byte	14                      # CFA_def_cfa_offset
	.uleb128	32              # Offset
	.align	8
.Leh_frame_end2:

.Lmain.eh:
	.set	.Lset8eh,.Leh_frame_end3-.Leh_frame_begin3
	.long	.Lset8eh                # Length of Frame Information Entry
.Leh_frame_begin3:
	.long	.Leh_frame_begin3-.Leh_frame_common # FDE CIE offset
	.long	.Leh_func_begin3        # FDE initial location
	.set	.Lset9eh,.Leh_func_end3-.Leh_func_begin3
	.long	.Lset9eh                # FDE address range
	.uleb128	0               # Augmentation size
	.byte	4                       # CFA_advance_loc4
	.set	.Lset10eh,.Llabel3-.Leh_func_begin3
	.long	.Lset10eh
	.byte	14                      # CFA_def_cfa_offset
	.uleb128	16              # Offset
	.byte	4                       # CFA_advance_loc4
	.set	.Lset11eh,.Llabel4-.Llabel3
	.long	.Lset11eh
	.byte	14                      # CFA_def_cfa_offset
	.uleb128	64              # Offset
	.byte	131                     # DW_CFA_offset + Reg (3)
	.uleb128	2               # Offset
	.align	8
.Leh_frame_end3:


	.section	.note.GNU-stack,"",@progbits
