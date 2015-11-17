	.file	"1.ll"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	movl	$0, -4(%rsp)
	movl	$10, -8(%rsp)
	movl	$10, -4(%rsp)
	movl	$10, %eax
	ret
	.size	main, .-main


	.section	.note.GNU-stack,"",@progbits
