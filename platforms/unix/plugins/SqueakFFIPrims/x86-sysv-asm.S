/* x86-sysv-asm.S -- 386 FFI trampoline for SVr4-like ABIs	-*- asm -*-
 *
 * Author: Ian.Piumarta@INRIA.Fr
 *
 * Last edited: Tue Jan 28 16:53:52 2003 by piumarta (Ian Piumarta) on xombul
 *
 * @copyright@
 */

	.text
	.globl	ffiCallAddressOf

ffiCallAddressOf:	/* 8=addr, 12=stack, 16=stackSize */
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %ecx
	testl	%ecx, %ecx
	je	2f
	subl	%ecx, %esp
	subl	$4, %ecx
	movl	12(%ebp), %edx
1:	movl	(%edx,%ecx,1), %eax
	movl	%eax, (%esp,%ecx,1)
	subl	$4, %ecx
	jnc	1b
2:	call	*8(%ebp)
	movl	%eax, ffiIntReturnValue
	movl	%edx, ffiLongReturnValue
	fstl	ffiFloatReturnValue
	movl	%ebp, %esp
	popl	%ebp
	ret
