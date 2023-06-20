.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
#   The order of error codes (checked from top to bottom):
#   If the dimensions of m0 do not make sense, 
#   this function exits with exit code 2.
#   If the dimensions of m1 do not make sense, 
#   this function exits with exit code 3.
#   If the dimensions don't match, 
#   this function exits with exit code 4.
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# =======================================================
matmul:

    # Error checks
    li t0, 1
    blt a1, t0, exit_2
    blt a2, t0, exit_2
    blt a4, t0, exit_3
    blt a5, t0, exit_3
    bne a2, a4, exit_4

    # Prologue
    addi sp, sp, -48
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)
    sw s6, 28(sp)
    sw s7, 32(sp)
    sw s8, 36(sp)
    sw s9, 40(sp)
    sw s10, 44(sp)

    # initialize the loop
    mv s0, a0                                   # s0 is the pointer to the start of m0 
    mv s1, a1                                   # s1 is the # of rows (height) of m0（行）
    mv s2, a2                                   # s2 is the # of columns (width) of m0（列）
    mv s3, a3                                   # s3 is the pointer to the start of m1
    mv s4, a4                                   # s4 is the # of rows (height) of m1（行）
    mv s5, a5                                   # s5 is the # of columns (width) of m1（列）
    mv s6, a6                                   # s6 is the pointer to the the start of d
    li s7, 0                                         # s7 is the ith row of m0
    li s8, 0                                         # s8 is the jth column of m1
    li t0, 4
    mul s9, a5, t0                           # s9 is the strides of m1
    li s10, 0                                       # s10 is the index of d

outer_loop_start:
    # 这是外层循环的开始点，它检查当前行（s7）是否大于等于m0的行数（s1）。如果是，跳转到外层循环的结束点。
    bge s7, s1, outer_loop_end

inner_loop_start:



inner_loop_end:



outer_loop_end:

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    lw s7, 32(sp)
    lw s8, 36(sp)
    lw s9, 40(sp)
    lw s10, 44(sp)

    addi sp, sp, 48
    
    ret

exit_2:
    li a0, 17
    li a1, 2
    ecall

exit_3:
    li a0, 17
    li a1, 3
    ecall

exit_4:
    li a0, 17
    li a1, 4
    ecall