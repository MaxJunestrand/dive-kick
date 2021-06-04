  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.data
.global hexasc
.global delay
.global time2string
.global enable_interrupt
.text
  # int hexasc(int n)
hexasc:
	PUSH $ra
	slti $t0, $a0, 10
	beq $t0, 1, numbers

	# Letters
	addi $v0, $a0, 55
	j return
	nop

	numbers:
		addi $v0, $a0, 0x30
	return:
		POP $ra
		jr $ra
		nop

#Delay function(int a0)
delay:
	PUSH $ra
	#constant
	addi $t3, $zero, 9000
	while:
		slt $t1,$zero, $a0 #while loop
		beq $t1, $zero, delayend

		addi $a0, $a0, -1

		addi $t5, $zero, 0 #i value
		for:
			slt $t4, $t5, $t3
			beq $t4, $zero, while
			addi $t5, $t5, 1 #i++
		j for
		nop

	delayend:
		addi $s0, $s0, 1
		POP $ra
		jr $ra
		nop

# void time2string(adress a0, int a1)
time2string:
	PUSH $ra

	# First number 10* minutes
	PUSH $a0
	andi $a0, $a1, 0x0000f000
	srl $a0, $a0, 12
	jal hexasc
	nop
	POP $a0
	sb $v0, 0($a0)

	PUSH $a0
	# Second number 1* minutes
	andi $a0, $a1, 0x00000f00
	srl $a0, $a0, 8
	jal hexasc
	nop
	POP $a0
	sb $v0, 1($a0)
	# Colon
	addi $t0, $0, 0x3A
	sb $t0, 2($a0)
	# Third number 10* seconds
	PUSH $a0
	andi $a0, $a1, 0x000000f0
	srl $a0, $a0, 4
	jal hexasc
	nop
	POP $a0
	sb $v0, 3($a0)
	# Fourth number 1* seconds
	PUSH $a0
	andi $a0, $a1, 0x0000000f
	jal hexasc
	nop
	POP $a0
	sb $v0, 4($a0)

	addi $t0, $0, 0x00
	sb $t0, 5($a0)


	POP $ra

	jr $ra
	nop
# void enable_interrupt()
enable_interrupt:
	ei
	jr $ra
	nop
