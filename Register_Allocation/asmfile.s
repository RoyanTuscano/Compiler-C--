        .globl main
main:
        b _main
         .data
#char gc1;
            _gc1: .space 1
              .align 2
#char gc2;
            _gc2: .space 1
              .align 2
#char gc3;
            _gc3: .space 1
              .align 2
#int gi1;
            _gi1: .space 4
#int gi2;
            _gi2: .space 4
#int gi3;
            _gi3: .space 4
_tmp_3:    .asciiz "\n"
                                    #enter main
         .text
         .globl _main
_main:
         la $sp, -8($sp)
         sw $fp, 4($sp)
         sw $ra, 0($sp)
         la $fp, 0($sp)
         la $sp, -156($sp)
                                # tmp_0 =
        li $3, 97
        sb $3, -144($fp)
                                # a1 =tmp_0
         lb $3, -144($fp)
        sb $3, -8($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                # i1 =tmp_1
         lw $3, -148($fp)
        sw $3,-20($fp)
                                # tmp_1 =2
        li $3, 2
        sw $3,-148($fp)
                                # i2 =tmp_1
         lw $3, -148($fp)
        sw $3,-28($fp)
                                # tmp_1 =3
        li $3, 3
        sw $3,-148($fp)
                                # i3 =tmp_1
         lw $3, -148($fp)
        sw $3,-40($fp)
                                # tmp_1 =4
        li $3, 4
        sw $3,-148($fp)
                                # i4 =tmp_1
         lw $3, -148($fp)
        sw $3,-52($fp)
                                # tmp_1 =5
        li $3, 5
        sw $3,-148($fp)
                                # i5 =tmp_1
         lw $3, -148($fp)
        sw $3,-64($fp)
                                # tmp_1 =6
        li $3, 6
        sw $3,-148($fp)
                                # i6 =tmp_1
         lw $3, -148($fp)
        sw $3,-76($fp)
                                # tmp_1 =7
        li $3, 7
        sw $3,-148($fp)
                                # i7 =tmp_1
         lw $3, -148($fp)
        sw $3,-88($fp)
                                # tmp_1 =8
        li $3, 8
        sw $3,-148($fp)
                                # i8 =tmp_1
         lw $3, -148($fp)
        sw $3,-100($fp)
                                # tmp_1 =9
        li $3, 9
        sw $3,-148($fp)
                                # i9 =tmp_1
         lw $3, -148($fp)
        sw $3,-112($fp)
                                # tmp_1 =10
        li $3, 10
        sw $3,-148($fp)
                                # i10 =tmp_1
         lw $3, -148($fp)
        sw $3,-128($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                # j1 =tmp_1
         lw $3, -148($fp)
        sw $3,-24($fp)
                                # tmp_1 =2
        li $3, 2
        sw $3,-148($fp)
                                # j2 =tmp_1
         lw $3, -148($fp)
        sw $3,-36($fp)
                                # tmp_1 =3
        li $3, 3
        sw $3,-148($fp)
                                # j3 =tmp_1
         lw $3, -148($fp)
        sw $3,-48($fp)
                                # tmp_1 =4
        li $3, 4
        sw $3,-148($fp)
                                # j4 =tmp_1
         lw $3, -148($fp)
        sw $3,-60($fp)
                                # tmp_1 =5
        li $3, 5
        sw $3,-148($fp)
                                # j5 =tmp_1
         lw $3, -148($fp)
        sw $3,-72($fp)
                                # tmp_1 =6
        li $3, 6
        sw $3,-148($fp)
                                # j6 =tmp_1
         lw $3, -148($fp)
        sw $3,-84($fp)
                                # tmp_1 =7
        li $3, 7
        sw $3,-148($fp)
                                # j7 =tmp_1
         lw $3, -148($fp)
        sw $3,-96($fp)
                                # tmp_1 =8
        li $3, 8
        sw $3,-148($fp)
                                # j8 =tmp_1
         lw $3, -148($fp)
        sw $3,-108($fp)
                                # tmp_1 =9
        li $3, 9
        sw $3,-148($fp)
                                # j9 =tmp_1
         lw $3, -148($fp)
        sw $3,-120($fp)
                                # tmp_1 =10
        li $3, 10
        sw $3,-148($fp)
                                # j10 =tmp_1
         lw $3, -148($fp)
        sw $3,-132($fp)
                                # tmp_1 =15885
        li $3, 15885
        sw $3,-148($fp)
                                # k1 =tmp_1
         lw $3, -148($fp)
        sw $3,-32($fp)
                                # tmp_1 =2
        li $3, 2
        sw $3,-148($fp)
                                # k2 =tmp_1
         lw $3, -148($fp)
        sw $3,-44($fp)
                                # tmp_1 =3
        li $3, 3
        sw $3,-148($fp)
                                # k3 =tmp_1
         lw $3, -148($fp)
        sw $3,-56($fp)
                                # tmp_1 =4
        li $3, 4
        sw $3,-148($fp)
                                # k4 =tmp_1
         lw $3, -148($fp)
        sw $3,-68($fp)
                                # tmp_1 =5
        li $3, 5
        sw $3,-148($fp)
                                # k5 =tmp_1
         lw $3, -148($fp)
        sw $3,-80($fp)
                                # tmp_1 =6
        li $3, 6
        sw $3,-148($fp)
                                # k6 =tmp_1
         lw $3, -148($fp)
        sw $3,-92($fp)
                                # tmp_1 =7
        li $3, 7
        sw $3,-148($fp)
                                # k7 =tmp_1
         lw $3, -148($fp)
        sw $3,-104($fp)
                                # tmp_1 =8
        li $3, 8
        sw $3,-148($fp)
                                # k8 =tmp_1
         lw $3, -148($fp)
        sw $3,-116($fp)
                                # tmp_1 =9
        li $3, 9
        sw $3,-148($fp)
                                # k9 =tmp_1
         lw $3, -148($fp)
        sw $3,-124($fp)
                                # tmp_1 =10
        li $3, 10
        sw $3,-148($fp)
                                # k10 =tmp_1
         lw $3, -148($fp)
        sw $3,-136($fp)
                                # tmp_0 =
        li $3, 97
        sb $3, -144($fp)
                                # gc1 =tmp_0
         lb $3, -144($fp)
        sb $3, _gc1
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                # gi1 =tmp_1
         lw $3, -148($fp)
        sw $3,_gi1
              #Goto _tdest1
         j _tdest1
                    #_tdest0:
     _tdest0 :
                                # tmp_0 =
        li $3, 98
        sb $3, -144($fp)
                                # a2 =tmp_0
         lb $3, -144($fp)
        sb $3, -12($fp)
                                # tmp_1 =100
        li $3, 100
        sw $3,-148($fp)
                                # gc2 =tmp_1
         lw $3, -148($fp)
        sb $3, _gc2
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +gi1
         lw $3, -148($fp)
         lw $4, _gi1
          add $5, $3, $4 
        sw $5,-152($fp)
                                # gi2 =tmp_2
         lw $3, -152($fp)
        sw $3,_gi2
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +i1
         lw $3, -148($fp)
         lw $4, -20($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # j1 =tmp_2
         lw $3, -152($fp)
        sw $3,-24($fp)
                                # tmp_1 =2
        li $3, 2
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +i1
         lw $3, -148($fp)
         lw $4, -20($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # j2 =tmp_2
         lw $3, -152($fp)
        sw $3,-36($fp)
                                # tmp_1 =3
        li $3, 3
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +i
         lw $3, -148($fp)
         lw $4, -4($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # i3 =tmp_2
         lw $3, -152($fp)
        sw $3,-40($fp)
                                # tmp_1 =4
        li $3, 4
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +i
         lw $3, -148($fp)
         lw $4, -4($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # i4 =tmp_2
         lw $3, -152($fp)
        sw $3,-52($fp)
                                # tmp_1 =5
        li $3, 5
        sw $3,-148($fp)
                                    #tmp_2 =  tmp_1 +i
         lw $3, -148($fp)
         lw $4, -4($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # i5 =tmp_2
         lw $3, -152($fp)
        sw $3,-64($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  k3 +tmp_1
         lw $3, -56($fp)
         lw $4, -148($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # k3 =tmp_2
         lw $3, -152($fp)
        sw $3,-56($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  k4 +tmp_1
         lw $3, -68($fp)
         lw $4, -148($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # k4 =tmp_2
         lw $3, -152($fp)
        sw $3,-68($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  k5 +tmp_1
         lw $3, -80($fp)
         lw $4, -148($fp)
          add $5, $3, $4 
        sw $5,-152($fp)
                                # k5 =tmp_2
         lw $3, -152($fp)
        sw $3,-80($fp)
                                # tmp_1 =3
        li $3, 3
        sw $3,-148($fp)
                                # i =tmp_1
         lw $3, -148($fp)
        sw $3,-4($fp)
              #Goto _tdest5
         j _tdest5
                    #_tdest3:
     _tdest3 :
                                # a3 =k1
         lw $3, -32($fp)
        sb $3, -16($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  k1 *tmp_1
         lw $3, -32($fp)
         lw $4, -148($fp)
          mul $5, $3, $4 
        sw $5,-152($fp)
                                # k1 =tmp_2
         lw $3, -152($fp)
        sw $3,-32($fp)
                                # tmp_1 =1
        li $3, 1
        sw $3,-148($fp)
                                    #tmp_2 =  k1 *tmp_1
         lw $3, -32($fp)
         lw $4, -148($fp)
          mul $5, $3, $4 
        sw $5,-152($fp)
                                # k2 =tmp_2
         lw $3, -152($fp)
        sw $3,-44($fp)
                                # tmp_0 =
        li $3, 99
        sb $3, -144($fp)
                                # gc3 =tmp_0
         lb $3, -144($fp)
        sb $3, _gc3
                                # gi3 =k2
         lw $3, -44($fp)
        sw $3,_gi3
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  i -tmp_2
         lw $3, -4($fp)
         lw $4, -152($fp)
          sub $5, $3, $4 
        sw $5,-148($fp)
                                # i =tmp_1
         lw $3, -148($fp)
        sw $3,-4($fp)
                    #_tdest5:
     _tdest5 :
                                # tmp_2 =0
        li $3, 0
        sw $3,-152($fp)
                                #If i > tmp_2 goto _tdest3 
         lw $3, -4($fp)
         lw $4, -152($fp)
        bgt $3, $4, _tdest3
              #Goto _tdest4
         j _tdest4
                    #_tdest4:
     _tdest4 :
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  k6 +tmp_2
         lw $3, -92($fp)
         lw $4, -152($fp)
          add $5, $3, $4 
        sw $5,-148($fp)
                                # k6 =tmp_1
         lw $3, -148($fp)
        sw $3,-92($fp)
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  k7 +tmp_2
         lw $3, -104($fp)
         lw $4, -152($fp)
          add $5, $3, $4 
        sw $5,-148($fp)
                                # k7 =tmp_1
         lw $3, -148($fp)
        sw $3,-104($fp)
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  k8 +tmp_2
         lw $3, -116($fp)
         lw $4, -152($fp)
          add $5, $3, $4 
        sw $5,-148($fp)
                                # k8 =tmp_1
         lw $3, -148($fp)
        sw $3,-116($fp)
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  k9 +tmp_2
         lw $3, -124($fp)
         lw $4, -152($fp)
          add $5, $3, $4 
        sw $5,-148($fp)
                                # k9 =tmp_1
         lw $3, -148($fp)
        sw $3,-124($fp)
                                # tmp_2 =1
        li $3, 1
        sw $3,-152($fp)
                                    #tmp_1 =  k10 +tmp_2
         lw $3, -136($fp)
         lw $4, -152($fp)
          add $5, $3, $4 
        sw $5,-148($fp)
                                # k10 =tmp_1
         lw $3, -148($fp)
        sw $3,-136($fp)
                    #_tdest1:
     _tdest1 :
                                #If k8 < j10 goto _tdest0 
         lw $3, -116($fp)
         lw $4, -132($fp)
        blt $3, $4, _tdest0
              #Goto _tdest2
         j _tdest2
                    #_tdest2:
     _tdest2 :
                                # res =i1
         lw $3, -20($fp)
        sw $3,-140($fp)
                                    #param  res
         lw $3, -140($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  i1
         lw $3, -20($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i2
         lw $3, -28($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i3
         lw $3, -40($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i4
         lw $3, -52($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i5
         lw $3, -64($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i6
         lw $3, -76($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i7
         lw $3, -88($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i8
         lw $3, -100($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i9
         lw $3, -112($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  i10
         lw $3, -128($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  j1
         lw $3, -24($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j2
         lw $3, -36($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j3
         lw $3, -48($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j4
         lw $3, -60($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j5
         lw $3, -72($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j6
         lw $3, -84($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j7
         lw $3, -96($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j8
         lw $3, -108($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j9
         lw $3, -120($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  j10
         lw $3, -132($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  k1
         lw $3, -32($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k2
         lw $3, -44($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k3
         lw $3, -56($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k4
         lw $3, -68($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k5
         lw $3, -80($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k6
         lw $3, -92($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k7
         lw $3, -104($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k8
         lw $3, -116($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k9
         lw $3, -124($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  k10
         lw $3, -136($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  a1
         lb $3, -8($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  a2
         lb $3, -12($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  a3
         lb $3, -16($fp)
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  gc1
         lb $3, _gc1
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  gc2
         lb $3, _gc2
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  gc3
         lb $3, _gc3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                # tmp_3 =\n
          la $3, _tmp_3
        sw $3,-156($fp)
                                    #param  tmp_3
        la $3, _tmp_3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_string 1
         jal _print_string
         la $sp, 4($sp)
                                    #param  gi1
         lw $3, _gi1
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  gi2
         lw $3, _gi2
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
                                    #param  gi3
         lw $3, _gi3
         la $sp, -4($sp)
         sw $3, 0($sp)
                                    #call  print_int 1
         jal _print_int
         la $sp, 4($sp)
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
