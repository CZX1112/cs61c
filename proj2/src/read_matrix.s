.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#   If any file operation fails or doesn't read the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
#
# If you receive an fopen error or eof, 
# this function exits with error code 50.
# If you receive an fread error or eof,
# this function exits with error code 51.
# If you receive an fclose error or eof,
# this function exits with error code 52.
# ==============================================================================
read_matrix:

    # Prologue
	addi sp, sp, -40
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

    # save arguments
    mv s0, a0                   # s0: the pointer to string representing the filename
    mv s1, a1                   # s1: the pointer to an integer, we will set it to the number of rows
    mv s2, a2                   # s2: the pointer to an integer, we will set it to the number of columns

    # fopen
    mv a1, s0                   # a1 = filepath
    li a2, 0                    # a2 = permissions (0, 1, 2, 3, 4, 5 = r, w, a, r+, w+, a+)
    jal fopen                   # return: a0 = file descriptor
    li t0, -1
    beq t0, a0, exit_50         # if return -1, jal exit_50
    mv s5, a0                   # save the file descriptor to register s5

    # read the number of rows and columns
    mv a1, s5                   # a1 = file descriptor
    mv a2, s1                   # a2 = pointer to the buffer you want to write the read bytes to.(the number of rows)
    li s6, 4                    # the number of bytes per word (the number of bytes to be read)
    mv a3, s6                   # a3 = Number of bytes to be read.(=4)
    jal fread                   # Reads a3 bytes of the file a1 into the buffer a2.
    bne a0, s6, exit_51         # return: a0 = Number of bytes actually read.
    mv a0, s5                   # a1 = file descriptor
    mv a2, s2                   # a2 = pointer to the buffer you want to write the read bytes to.(the number of columns)
    mv a3, s6                   # a3 = Number of bytes to be read.(=4)
    jal fread                   # Reads a3 bytes of the file a1 into the buffer a2.
    bne a0, s6, exit_51         # return: a0 = Number of bytes actually read.
    lw s3, 0(s1)                # s3 = the number of rows
    lw s4, 0(s2)                # s4 = the number of columns

    # allocate space
    mul s8, s3, s4              # s8 = s3 * s4, the number of all elements
    mul s8, s8, s6              # s6 = 4, the size of all elements, number of bytes to be read
    mv a0, s8                   # a0 is the # of bytes to allocate heap memory for
    jal malloc
    mv s7, a0                   # a0 is the pointer to the allocated heap memory, store it to s7

    # read matrix
    mv a1, s5                   # a1 = file descriptor
    mv a2, s7                   # a2 = pointer to the buffer you want to write the read bytes to.(the allocated memory)
    mv a3, s8                   # a3 = Number of bytes to be read.(=s3 * s4 * 4)
    jal fread                   # Reads a3 bytes of the file a1 into the buffer a2.
    bne a0, s8, exit_51         # return: a0 = Number of bytes actually read.

    # fclose
    mv a1, s5                   # a1 = file descriptor
    jal fclose
    bne a0, x0, exit_52         # return: a0 = 0 on success, and EOF (-1) otherwise.

    # return the result stored in a0
    mv a0, s7

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
    addi sp, sp, 40

    ret

exit_50:
    li a1, 50
    j exit2

exit_51:
    li a1, 51
    j exit2

exit_52:
    li a1, 52
    j exit2