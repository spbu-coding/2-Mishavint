	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	work_with_array
	.def	work_with_array;	.scl	2;	.type	32;	.endef
	.seh_proc	work_with_array
work_with_array:
	.seh_endprologue
	movl	(%rdx), %edx
	subl	$1, %edx
	testl	%edx, %edx
	jle	.L1
	leaq	8(%rcx), %r11
	.p2align 4,,10
.L3:
	subl	$1, %edx
	movq	%rcx, %rax
	leaq	(%r11,%rdx,8), %r9
	movq	%rdx, %r10
	.p2align 4,,10
.L5:
	movq	(%rax), %rdx
	movq	8(%rax), %r8
	cmpq	%r8, %rdx
	jbe	.L4
	movslq	%edx, %rdx
	movq	%r8, (%rax)
	movq	%rdx, 8(%rax)
.L4:
	addq	$8, %rax
	cmpq	%rax, %r9
	jne	.L5
	testl	%r10d, %r10d
	movl	%r10d, %edx
	jne	.L3
.L1:
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
