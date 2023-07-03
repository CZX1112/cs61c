.import ../../src/write_matrix.s
.import ../../src/utils.s

.data
m0: .word 1, 2, 3, 4, 5, 6, 7, 8, 9 # MAKE CHANGES HERE TO TEST DIFFERENT MATRICES
file_path: .asciiz "../outputs/test_write_matrix/student_write_outputs.bin"

.text
main:
    # Write the matrix to a file
    la a0, file_path                    # a0 (char*) is the pointer to string representing the filename
    la a1, m0                           # a1 (int*)  is the pointer to the start of the matrix in memory
    li a2, 3                            # a2 (int)   is the number of rows in the matrix
    li a3, 3                            # a3 (int)   is the number of columns in the matrix
    jal write_matrix

    # Exit the program
    jal exit