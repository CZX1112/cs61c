.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
#   If any file operation fails or doesn't write the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
#
# If you receive an fopen error or eof, 
# this function exits with error code 53.
# If you receive an fwrite error or eof,
# this function exits with error code 54.
# If you receive an fclose error or eof,
# this function exits with error code 55.
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -28
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw ra, 24(sp)

    # save arguments(a0123)
    mv s0, a0                   # s0 (char*) is the pointer to string representing the filename
    mv s1, a1                   # s1 (int*)  is the pointer to the start of the matrix in memory
    mv s2, a2                   # s2 (int)   is the number of rows in the matrix
    mv s3, a3                   # s3 (int)   is the number of columns in the matrix
    
    # fopen
    mv a1, s0                   # a1 = filepath
    li a2, 1                    # a2 = permissions (0, 1, 2, 3, 4, 5 = r, w, a, r+, w+, a+)
    jal fopen                   # return: a0 = file descriptor
    li t0, -1
    beq t0, a0, exit_53         # if return -1, jal exit_53
    mv s4, a0                   # save the file descriptor to register s4

    # fwrite
    mv a1, s4                   # a1 = file descriptor
    mv a2, s1                   # a2 = Buffer to read from
    mul s5, s2, s3              # s5 = s2 * s3, s5 is the number of items
    mv a3, s5                   # a3 = Number of items to read from the buffer.
    li a4, 4                    # a4 = Size of each item in the buffer.(4)
    jal fwrite                  # a0 = Number of elements writen. If this is less than a3, return false
    blt a0, a3, exit_54

    # fclose
    mv a1, s4                   # a1 = file descriptor
    jal fclose
    bne a0, x0, exit_55         # return: a0 = 0 on success, and EOF (-1) otherwise.

    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw ra, 24(sp)
    addi sp, sp, 28

    ret

exit_53:
    li a1, 53
    j exit2

exit_54:
    li a1, 54
    j exit2

exit_55:
    li a1, 55
    j exit2