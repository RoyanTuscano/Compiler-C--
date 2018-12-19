        .globl main
main:
        b _main
         .data
_tmp_3:    .asciiz "\n"
                                    #enter main
         .text
         .globl _main
_main:
         la $sp, -8($sp)
         sw $fp, 4($sp)
         sw $ra, 0($sp)
         la $fp, 0($sp)
         la $sp, -28($sp)
                                # k =0
        li $3, 0
        sw $3,-12($fp)
                                # i =0
        li $3, 0
        sw $3,-4($fp)
              #Goto _tdest2
         j _tdest2
                    #_tdest0:
     _tdest0 :
                                # tmp_1 =2
        li $3, 2
        sw $3,-20($fp)
                                # tmp_0 =2
        li $3, 2
        sw $3,-16($fp)
                                    #tmp_2 =  i /tmp_0
         lw $3, -4($fp)
         lw $4, -16($fp)
          div $5, $3, $4 
        sw $5,-24($fp)
                                    #tmp_0 =  tmp_1 *tmp_2
         lw $3, -20($fp)
         lw $4, -24($fp)
          mul $5, $3, $4 
        sw $5,-16($fp)
                                    #tmp_1 =  i -tmp_0
         lw $3, -4($fp)
         lw $4, -16($fp)
          sub $5, $3, $4 
        sw $5,-20($fp)
                                # tmp_2 =0
        li $3, 0
        sw $3,-24($fp)
                                #If tmp_1 != tmp_2 goto _tdest4 
         lw $3, -20($fp)
         lw $4, -24($fp)
        bne $3, $4, _tdest4
                                    #tmp_0 =  k +i
         lw $3, -12($fp)
         lw $4, -4($fp)
          add $5, $3, $4 
        sw $5,-16($fp)
                                # tmp_2 =1
        li $3, 1
        sw $3,-24($fp)
                                    #k =  tmp_0 +tmp_2
         lw $3, -16($fp)
         lw $4, -24($fp)
          add $5, $3, $4 
        sw $5,-12($fp)
              #Goto _tdest5
         j _tdest5
                    #_tdest4:
     _tdest4 :
                    #_tdest5:
     _tdest5 :
                                # tmp_0 =1
        li $3, 1
        sw $3,-16($fp)
                                    #i =  i +tmp_0
         lw $3, -4($fp)
         lw $4, -16($fp)
          add $5, $3, $4 
        sw $5,-4($fp)
                    #_tdest2:
     _tdest2 :
                                # tmp_0 =100
        li $3, 100
        sw $3,-16($fp)
                                #If i < tmp_0 goto _tdest0 
         lw $3, -4($fp)
         lw $4, -16($fp)
        blt $3, $4, _tdest0
                                # tmp_2 =0
        li $3, 0
        sw $3,-24($fp)
                                #If i <= tmp_2 goto _tdest7 
         lw $3, -4($fp)
         lw $4, -24($fp)
        ble $3, $4, _tdest7
                                    #param  k
         lw $3, -12($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-28($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #leave main
                                    #return 
         la $sp,0($fp)
         lw $ra,0($sp)
         lw $fp,4($sp)
         la $sp,8($sp)
         jr $ra
              #Goto _tdest8
         j _tdest8
                    #_tdest7:
     _tdest7 :
                                    #param  i
         lw $3, -4($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-28($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #leave main
                                    #return 
         la $sp,0($fp)
         lw $ra,0($sp)
         lw $fp,4($sp)
         la $sp,8($sp)
         jr $ra
                    #_tdest8:
     _tdest8 :
                                    #leave main
                                    #return 
         la $sp,0($fp)
         lw $ra,0($sp)
         lw $fp,4($sp)
         la $sp,8($sp)
         jr $ra
         .text
_print_int:
         li $v0, 1
         lw $a0, 0($sp)
         syscall
         jr $ra
         .text
_print_string:
         li $v0, 4
         lw $a0, 0($sp)
         syscall
         jr $ra
