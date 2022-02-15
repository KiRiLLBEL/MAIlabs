	.file	"main.c"
	.text
	.globl	modul
	.type	modul, @function
modul:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	js	.L2
	movq	-8(%rbp), %rax
	jmp	.L3
.L2:
	movq	-8(%rbp), %rax
	negq	%rax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	modul, .-modul
	.section	.rodata
.LC1:
	.string	"%lld\n"
.LC2:
	.string	"-%lld\n"
.LC3:
	.string	"%lld"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	jmp	.L5
.L16:
	movq	$0, -96(%rbp)
	movq	-104(%rbp), %rax
	testq	%rax, %rax
	jns	.L6
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	modul
	movq	%rax, -104(%rbp)
	movq	$1, -96(%rbp)
.L6:
	movq	$0, -88(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, -80(%rbp)
	jmp	.L7
.L8:
	movq	-80(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -80(%rbp)
	addq	$1, -88(%rbp)
.L7:
	cmpq	$0, -80(%rbp)
	jg	.L8
	movq	-88(%rbp), %rax
	andl	$1, %eax
	testq	%rax, %rax
	jne	.L9
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	jmp	.L10
.L11:
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	%rax, -24(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	%rax, -16(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -104(%rbp)
	movq	-16(%rbp), %rax
	subq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	modul
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rcx
	movq	-16(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -144(%rbp)
	fildq	-144(%rbp)
	fstpt	-144(%rbp)
	fildq	-64(%rbp)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	fldt	.LC0(%rip)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	powl@PLT
	addq	$32, %rsp
	fldt	-144(%rbp)
	fmulp	%st, %st(1)
	fildq	-72(%rbp)
	faddp	%st, %st(1)
	fnstcw	-114(%rbp)
	movzwl	-114(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -116(%rbp)
	fldcw	-116(%rbp)
	fistpq	-72(%rbp)
	fldcw	-114(%rbp)
	addq	$1, -64(%rbp)
.L10:
	movq	-104(%rbp), %rax
	testq	%rax, %rax
	jg	.L11
	cmpq	$0, -96(%rbp)
	jne	.L12
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L5
.L12:
	movq	-72(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L5
.L9:
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	jmp	.L13
.L14:
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	%rax, -40(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	subq	%rax, %rcx
	movq	%rcx, %rax
	movq	%rax, -32(%rbp)
	movq	-104(%rbp), %rcx
	movabsq	$7378697629483820647, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -104(%rbp)
	movq	-32(%rbp), %rax
	subq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	modul
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rcx
	movq	-32(%rbp), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -144(%rbp)
	fildq	-144(%rbp)
	fstpt	-144(%rbp)
	fildq	-48(%rbp)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	fldt	.LC0(%rip)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	powl@PLT
	addq	$32, %rsp
	fldt	-144(%rbp)
	fmulp	%st, %st(1)
	fildq	-56(%rbp)
	faddp	%st, %st(1)
	fnstcw	-114(%rbp)
	movzwl	-114(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -116(%rbp)
	fldcw	-116(%rbp)
	fistpq	-56(%rbp)
	fldcw	-114(%rbp)
	addq	$1, -48(%rbp)
.L13:
	movq	-104(%rbp), %rax
	cmpq	$10, %rax
	jg	.L14
	movq	-104(%rbp), %rax
	movq	%rax, -144(%rbp)
	fildq	-144(%rbp)
	fstpt	-144(%rbp)
	fildq	-48(%rbp)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	fldt	.LC0(%rip)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	call	powl@PLT
	addq	$32, %rsp
	fldt	-144(%rbp)
	fmulp	%st, %st(1)
	fildq	-56(%rbp)
	faddp	%st, %st(1)
	fnstcw	-114(%rbp)
	movzwl	-114(%rbp), %eax
	orb	$12, %ah
	movw	%ax, -116(%rbp)
	fldcw	-116(%rbp)
	fistpq	-56(%rbp)
	fldcw	-114(%rbp)
	cmpq	$0, -96(%rbp)
	jne	.L15
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L5
.L15:
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	leaq	-104(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$-1, %eax
	jne	.L16
	movl	$0, %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L19
	call	__stack_chk_fail@PLT
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 16
.LC0:
	.long	0
	.long	4194304000
	.long	16392
	.long	0
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
