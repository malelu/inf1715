.data
x: .int
p: .int
.text
.globl main, fun2
main:
	pushl %ebp
	movl %esp, %ebp
	subl $48, %esp
	pushl %ebx
	pushl %esi
	pushl %edi
	movl $0, %ebx 
	movl $0, %ecx 
	movl $0, %edx 
	movl $6, %edi 
	addl $5, %edi
	movl $8, %esi 
	imull $1, %esi
	movl %eax, %eax 
	movl $7, %edi 
	idivl %edi
	movl $5, %ebx 
	subl %ebx, %edi
	movl $6, %ecx 
	movl $4, %eax
	movl $1, %edx 
	idivl %edx
	cmpl $1, $4
	jl .L11
	jmp .L12
.L11:
	movl $1, %ebx
.L12:
	cmpl %ebx, $0
	jne .L0
	movl $0, %ebx 
.L2: 
	cmpl $5, $7
	jl .L13
	movl $0, %ebx 
	jmp .L14
.L13:
	movl $1, %ebx
.L14:
	cmpl %ebx, $0
	jne .L1
	movl $0, %ebx 
	jmp .L2
.L1: 
	jmp .L3
.L0: 
	cmpl %ebx, $0
	jne .L4
	movl $0, %ebx 
	jmp .L3
.L4: 
	movl $0, %ebx 
.L3: 
	popl %edi
	popl %esi
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret
fun2:
	pushl %ebp
	movl %esp, %ebp
	subl $20, %esp
	pushl %ebx
	pushl %esi
	pushl %edi
	movl $0, %ebx 
	cmpl %ebx, $0
	jne .L5
	movl $0, %ebx 
.L7: 
	cmpl %ebx, $0
	jne .L6
	movl $0, %ebx 
	jmp .L7
.L6: 
	jmp .L8
.L5: 
	cmpl %ebx, $0
	jne .L9
	movl $0, %ebx 
	jmp .L8
.L9: 
	movl $0, %ebx 
.L8: 
	popl %edi
	popl %esi
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret
	popl %edi
	popl %esi
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret
