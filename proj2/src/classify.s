.globl classify

.text
classify:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0 (int)    argc
    #   a1 (char**) argv
    #   a2 (int)    print_classification, if this is zero, 
    #               you should print the classification. Otherwise,
    #               this function should not print ANYTHING.
    # Returns:
    #   a0 (int)    Classification
    # 
    # If there are an incorrect number of command line args,
    # this function returns with exit code 49.
    #
    # Usage:
    #   main.s -m -1 <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>

    # Prologue
    addi sp, sp, -64
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw s8, 32(sp)
    sw ra, 36(sp)

    # verify the number of command line arguments
    li t0, 5                            # 5 arguments
    bne a0, t0, exit_49                 # a0 (int)    argc

    # save arguments
    mv s0, a0                           # s0 = a0 (a0 (int)    argc)
    mv s1, a1                           # s1 = a1 (char**) argv      main.s m0.bin m1.bin input.bin output.bin
    mv s2, a2                           # s2 = a2 (print_classification, if this is zero)


	# =====================================
    # LOAD MATRICES
    # =====================================

    # Load pretrained m0
    lw a0, 4(s1)                        # a0 the pointer to string representing the filename (m0.bin)
    addi a1, sp, 40                     # a pointer to an integer, we will set it to the number of rows m0   40(sp) = the address of rows of m0
    addi a2, sp, 44                     # a pointer to an integer, we will set it to the number of columns m0  44(sp) = the address of columns of m0
    jal read_matrix
    mv s3, a0                           # return: a0 (int*)  is the pointer to the start of m0

    # Load pretrained m1
    lw a0, 8(s1)                        # a0 the pointer to string representing the filename (m1.bin)
    addi a1, sp, 48                     # a pointer to an integer, we will set it to the number of rows m1   48(sp) = the address of rows of m1
    addi a2, sp, 52                     # a pointer to an integer, we will set it to the number of columns m1  52(sp) = the address of columns of m1
    jal read_matrix
    mv s4, a0                           # return: a0 (int*)  is the pointer to the start of m1

    # Load input matrix
    lw a0, 12(s1)                       # a0 the pointer to string representing the filename (input.bin)
    addi a1, sp, 56                     # a pointer to an integer, we will set it to the number of rows input   56(sp) = the address of rows of input
    addi a2, sp, 60                     # a pointer to an integer, we will set it to the number of columns input  60(sp) = the address of columns of input
    jal read_matrix
    mv s5, a0                           # return: a0 (int*)  is the pointer to the start of input


    # =====================================
    # RUN LAYERS
    # =====================================
    # 1. LINEAR LAYER:    m0 * input
    # 2. NONLINEAR LAYER: ReLU(m0 * input)
    # 3. LINEAR LAYER:    m1 * ReLU(m0 * input)

    # 1. LINEAR LAYER
    ## malloc
    lw t0, 40(sp)                       # t0 = the rows of m0
    lw t1, 60(sp)                       # t1 = the columns of input
    li t2, 4                            # t2 = the size of a data
    mul t3, t0, t1                      # the number of data
    mul t3, t3, t2                      # t3 = the size of all data
    mv a0, t3                           # a0 is the # of bytes to allocate heap memory for
    jal malloc
    blt a0, x0, exit_48
    mv s6, a0                           # return: a0 is the pointer to the allocated heap memory

    ## m0 * input
    mv a0, s3                           # a0 = s3 = the pointer to the start of m0
    lw a1, 40(sp)                       # a1 (int)   is the # of rows (height) of m0
    lw a2, 44(sp)                       # a2 (int)   is the # of columns (width) of m0
    mv a3, s5                           # a3 = s5 = the pointer to the start of input
    lw a4, 56(sp)                       # a4 (int)   is the # of rows (height) of input
    lw a5, 60(sp)                       # a5 (int)   is the # of columns (width) of input
    mv a6, s6                           # a6 (int*)  is the pointer to the the start of d (s6 the malloced memory)
    jal matmul

    # 2. NONLINEAR LAYER: ReLU(m0 * input)
    mv a0, s6                           # a0 = s6   a0 (int*) is the pointer to the array
    lw t0, 40(sp)                       # t0 is the # of rows (height) of m0
    lw t1, 60(sp)                       # t1 is the # of columns (width) of input
    mul t2, t0, t1                      # t2 = the number of data in array
    mv a1, t2                           # a1 (int) = t2 is the # of elements in the array
    jal relu

    # 3. LINEAR LAYER:    m1 * ReLU(m0 * input)
    ## malloc
    lw t0, 48(sp)                       # t0 = the rows of m1
    lw t1, 60(sp)                       # t1 = the columns of input
    li t2, 4                            # t2 = the size of a data
    mul t3, t0, t1                      # the number of data
    mul t3, t3, t2                      # t3 = the size of all data
    mv a0, t3                           # a0 is the # of bytes to allocate heap memory for
    jal malloc
    blt a0, x0, exit_48
    mv s7, a0                           # return: a0 is the pointer to the allocated heap memory

    ## m1 * ReLU(m0 * input)
    mv a0, s4                           # a0 = s4 = the pointer to the start of m1
    lw a1, 48(sp)                       # a1 (int)   is the # of rows (height) of m1
    lw a2, 52(sp)                       # a2 (int)   is the # of columns (width) of m1
    mv a3, s6                           # a3 = s6 = the pointer to the start of (m0 * input)
    lw a4, 40(sp)                       # a4 (int)   is the # of rows (height) of (m0 * input)
    lw a5, 60(sp)                       # a5 (int)   is the # of columns (width) of (m0 * input)
    mv a6, s7                           # a6 (int*)  is the pointer to the the start of s7
    jal matmul


    # =====================================
    # WRITE OUTPUT
    # =====================================
    # Write output matrix
    lw a0, 16(s1)                       # a0 (char*) is the pointer to string representing the filename (output.bin)
    mv a1, s7                           # a1 (int*)  is the pointer to the start of the matrix in memory (s7)
    lw a2, 48(sp)                       # a2 (int)   is the # of rows (height) of m1
    lw a3, 60(sp)                       # a3 (int)   is the # of columns (width) of (m0 * input)
    jal write_matrix

    # =====================================
    # CALCULATE CLASSIFICATION/LABEL
    # =====================================
    # Call argmax
    mv a0, s7                           # a0 = s7 (int*) is the pointer to the start of the vector
    lw t0, 48(sp)                       # t0 (int)   is the # of rows (height) of m1
    lw t1, 60(sp)                       # t1 (int)   is the # of columns (width) of (m0 * input)
    mul a1, t0, t1                      # a1 (int)  is the # of elements in the vector  a1 = t0 * t1
    jal argmax
    mv s8, a0                           # return: s8 = a0 (int)  is the first index of the largest element

    # Print classification
    mv a1, s8                           # a1 = integer to print
    jal print_int

    # Print newline afterwards for clarity
    li a1, '\n'                         # a1 = character to print
    jal print_char

    # output
    mv a0, s8

    # Epilogue

    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw s8, 32(sp)
    lw ra, 36(sp)
    addi sp, sp, 64

    ret

exit_48:
    li a1, 48
    jal exit2

exit_49:
    li a1, 49
    jal exit2