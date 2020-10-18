	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	work_with_array
	.type	work_with_array, @function
work_with_array:
.LFB0:
	.cfi_startproc
	movl	(%rsi), %edx
	subl	$1, %edx
	testl	%edx, %edx
	jle	.L1
	leaq	8(%rdi), %r9
	.p2align 4,,10
	.p2align 3
.L3:
	subl	$1, %edx
	movq	%rdi, %rax
	leaq	(%r9,%rdx,8), %r8
	movq	%rdx, %rsi
	.p2align 4,,10
	.p2align 3
.L5:
	movq	(%rax), %rcx
	movq	8(%rax), %rdx
	cmpq	%rdx, %rcx
	jbe	.L4
	movq	(%rcx), %rcx
	movq	%rdx, (%rax)
	movq	%rcx, (%rdx)
.L4:
	addq	$8, %rax
	cmpq	%r8, %rax
	jne	.L5
	testl	%esi, %esi
	movl	%esi, %edx
	jne	.L3
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	work_with_array, .-work_with_array
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
