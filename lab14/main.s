	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"%d %d"
.LC1:
	.string	"%d"
.LC2:
	.string	"%d "
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$152, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	%rsp, %rax
	movq	%rax, -184(%rbp)
	leaq	-116(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-116(%rbp), %ecx
	movl	-116(%rbp), %esi
	movslq	%ecx, %rax
	subq	$1, %rax
	movq	%rax, -80(%rbp)
	movslq	%ecx, %rax
	movq	%rax, -176(%rbp)
	movq	$0, -168(%rbp)
	movslq	%ecx, %rax
	leaq	0(,%rax,4), %rbx
	movslq	%esi, %rax
	subq	$1, %rax
	movq	%rax, -72(%rbp)
	movslq	%ecx, %rax
	movq	%rax, -144(%rbp)
	movq	$0, -136(%rbp)
	movslq	%esi, %rax
	movq	%rax, -160(%rbp)
	movq	$0, -152(%rbp)
	movq	-144(%rbp), %r8
	movq	-136(%rbp), %r9
	movq	%r9, %rdx
	movq	-160(%rbp), %r10
	movq	-152(%rbp), %r11
	imulq	%r10, %rdx
	movq	%r11, %rax
	imulq	%r8, %rax
	leaq	(%rdx,%rax), %rdi
	movq	%r8, %rax
	mulq	%r10
	addq	%rdx, %rdi
	movq	%rdi, %rdx
	movslq	%ecx, %rax
	movq	%rax, %r14
	movl	$0, %r15d
	movslq	%esi, %rax
	movq	%rax, %r12
	movl	$0, %r13d
	movq	%r15, %rdx
	imulq	%r12, %rdx
	movq	%r13, %rax
	imulq	%r14, %rax
	leaq	(%rdx,%rax), %rdi
	movq	%r14, %rax
	mulq	%r12
	addq	%rdx, %rdi
	movq	%rdi, %rdx
	movslq	%ecx, %rdx
	movslq	%esi, %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	movq	%rax, %rdx
	andq	$-4096, %rdx
	movq	%rsp, %rcx
	subq	%rdx, %rcx
	movq	%rcx, %rdx
.L2:
	cmpq	%rdx, %rsp
	je	.L3
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	jmp	.L2
.L3:
	movq	%rax, %rdx
	andl	$4095, %edx
	subq	%rdx, %rsp
	movq	%rax, %rdx
	andl	$4095, %edx
	testq	%rdx, %rdx
	je	.L4
	andl	$4095, %eax
	subq	$8, %rax
	addq	%rsp, %rax
	orq	$0, (%rax)
.L4:
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -64(%rbp)
	movl	$0, -84(%rbp)
	jmp	.L5
.L18:
	leaq	-108(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	$1, -88(%rbp)
	movl	$0, -92(%rbp)
	jmp	.L6
.L9:
	movl	$0, -96(%rbp)
	jmp	.L7
.L8:
	movq	%rbx, %rcx
	shrq	$2, %rcx
	movl	-96(%rbp), %eax
	movslq	%eax, %rdx
	movl	-92(%rbp), %eax
	cltq
	imulq	%rcx, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	addl	$1, -96(%rbp)
.L7:
	movl	-108(%rbp), %eax
	cmpl	%eax, -96(%rbp)
	jl	.L8
	addl	$1, -92(%rbp)
.L6:
	movl	-108(%rbp), %eax
	cmpl	%eax, -92(%rbp)
	jl	.L9
	jmp	.L10
.L13:
	movl	-108(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -100(%rbp)
	jmp	.L11
.L12:
	movq	%rbx, %rsi
	shrq	$2, %rsi
	movl	-108(%rbp), %eax
	subl	$1, %eax
	addl	%eax, %eax
	subl	-88(%rbp), %eax
	addl	$1, %eax
	subl	-100(%rbp), %eax
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movslq	%edx, %rcx
	movl	-100(%rbp), %edx
	movslq	%edx, %rdx
	imulq	%rsi, %rdx
	addq	%rcx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	subl	$1, -100(%rbp)
.L11:
	movl	-108(%rbp), %eax
	subl	-88(%rbp), %eax
	cmpl	%eax, -100(%rbp)
	jge	.L12
	addl	$1, -88(%rbp)
.L10:
	movl	-108(%rbp), %eax
	cmpl	%eax, -88(%rbp)
	jle	.L13
	movl	$2, -88(%rbp)
	jmp	.L14
.L17:
	movl	-108(%rbp), %eax
	subl	-88(%rbp), %eax
	movl	%eax, -104(%rbp)
	jmp	.L15
.L16:
	movq	%rbx, %rsi
	shrq	$2, %rsi
	movl	-108(%rbp), %eax
	subl	-88(%rbp), %eax
	subl	-104(%rbp), %eax
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movslq	%edx, %rcx
	movl	-104(%rbp), %edx
	movslq	%edx, %rdx
	imulq	%rsi, %rdx
	addq	%rcx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	subl	$1, -104(%rbp)
.L15:
	cmpl	$0, -104(%rbp)
	jns	.L16
	addl	$1, -88(%rbp)
.L14:
	movl	-108(%rbp), %eax
	cmpl	%eax, -88(%rbp)
	jle	.L17
	movl	$10, %edi
	call	putchar@PLT
	addl	$1, -84(%rbp)
.L5:
	movl	-112(%rbp), %eax
	cmpl	%eax, -84(%rbp)
	jl	.L18
	movl	$0, %eax
	movq	-184(%rbp), %rsp
	movq	-56(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L20
	call	__stack_chk_fail@PLT
.L20:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
