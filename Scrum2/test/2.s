	.file	"2.ll"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	movl	$0, -4(%rsp)
	movl	-8(%rsp), %eax
	movl	%eax, -4(%rsp)
	ret
	.size	main, .-main

	.type	a,@object
	.comm	a,40,16                 # @a

	.section	.note.GNU-stack,"",@progbits
