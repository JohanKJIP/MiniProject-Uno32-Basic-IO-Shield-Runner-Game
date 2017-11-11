  # assemblyUtil.S
  # Written by johvh & davidjo2.

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
.global hexasc, delay, time2string, enable_interrupt

enable_interrupt:
	ei
	jr	$ra
	nop

hexasc:
	slti	$t0,$a0,10	#check if a0 is less than 10
	beq	$t0,$0,else	#skip 30 char addition if previous condition not true
	nop
	addi	$v0,$a0,0x30	#add argument and shift to ASCII numbers (see ACSCII table)
	j skipElse
	nop
	else:
		addi	$v0,$a0,0x37	#add argument and shift to ASCII capital letters (see ACSCII table)
	skipElse:
		jr 	$ra
		nop