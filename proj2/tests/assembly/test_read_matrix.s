.import ../../src/read_matrix.s
.import ../../src/utils.s

.data
file_path: .asciiz "../inputs/test_read_matrix/test_input.bin"
row: .word 3
col: .word 3

.text
main:
    # Prologue
    addi sp, sp, -12
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)

    # Read matrix into memory
    la s0, file_path                    # load the address of file_path to s0
    la s1, row                          # load the address of row to s1
    la s2, col                          # load the address of col to s2
    mv a0, s0                           # set the pointer to string representing the filename
    mv a1, s1                           # set a pointer to an integer, we will set it to the number of rows
    mv a2, s2                           # set a pointer to an integer, we will set it to the number of columns
    jal read_matrix

    # Print out elements of matrix
    lw a1, 0(s1)                        # set the row to a1
    lw a2, 0(s2)                        # set the col to a2
    jal print_int_array                 # call the print_int_array func

    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    addi sp, sp, 12

    # Terminate the program
    jal exit