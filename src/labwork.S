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
.global hexasc, delay, time2string 

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

delay:
	li	$t0,0	#reset t0
	li	$a1,4200000	#for loop constant
	while:
		slt	$t4,$0,$a0
		beq	$t4,$0,whileDone	#while ms>0 
		nop
		addi	$a0,$a0,-1		#ms = ms - 1
		for:
			beq	$t0,$a1,forDone	#for (...)
			nop
			addi	$t0,$t0,1	#i++
			j	for
			nop

		forDone:
			j	while
			nop

	whileDone:
		jr 	$ra
		nop

time2string:
	PUSH    $s0            # save registers and return address    
    	PUSH    $s1
    	PUSH    $ra
    
    	move    $s1,$a1
    	move    $s0,$a0
    
    	andi    $a0,$s1,0x0000000f     # get first digit, 8
    	jal    hexasc
    	nop
    	sb    $v0,4($s0)        #save byte in memory at $s0 + 4 bytes    
    
    	andi     $a0,$s1,0x000000f0     #get second digit, 5
    	srl    $a0,$a0,4        #shift to least significant position
    	jal    hexasc
    	nop
    	sb    $v0,3($s0)        #save byte in memory at $s0 + 3 bytes        
    
    	li    $t2,0x3A
    	sb    $t2,2($s0)        #save byte in memory at $s0 + 2 bytes        
    
    	andi     $a0,$s1,0x00000f00    #9
    	srl    $a0,$a0,8
    	jal    hexasc    
    	nop
    	sb    $v0,1($s0)        #save byte in memory at $s0 + 1 bytes    
    
    	andi     $a0,$s1,0x0000f000    #5
    	srl    $a0,$a0,12
    	jal    hexasc
    	nop
    	sb    $v0,0($s0)        #save byte in memory at $s0    
    
    	addi    $t3,$t3,0x00        #add null byte
    	sb    $t3,5($s0)
    
    	addi    $t8,$0,0x00000000
    	andi    $t9,$s1, 0x0000ffff    
    	beq    $t9,$t8,setHour
    	nop
    	j done
    	nop
    	setHour:
        	li     $t2,0x52554f48
        	sw    $t2,0($s0)
        	sb    $0,4($s0)
    
    	done:
    
    	move    $a0,$s0            #move address back to a0
    
    	POP    $ra
    	POP    $s1
    	POP    $s0
    
    	jr    $ra
    	nop