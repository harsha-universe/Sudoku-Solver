from datetime import datetime
start_time = datetime.now()
num_rows = 9
num_cols = 9

board = [
    [7, 8, 0, 4, 0, 0, 1, 2, 0],
    [6, 0, 0, 0, 7, 5, 0, 0, 9],
    [0, 0, 0, 6, 0, 1, 0, 7, 8],
    [0, 0, 7, 0, 4, 0, 2, 6, 0],
    [0, 0, 1, 0, 5, 0, 9, 3, 0],
    [9, 0, 4, 0, 6, 0, 0, 0, 5],
    [0, 7, 0, 3, 0, 0, 0, 1, 2],
    [1, 2, 0, 0, 0, 7, 4, 0, 0],
    [0, 4, 9, 2, 0, 6, 0, 0, 7]
]


def solve_sudoku(board):
    pos = get_empty_square(board=board)
    # No empty square left implies sudoku is solved
    if pos == None:
        return True
    row, col = pos

    # Try each number from 1-9 in the empty square and backtrack if we aren't able to solve
    for num in range(1, 10):
        if validate(board=board, num=num, pos=pos):
            board[row][col] = num
            if solve_sudoku(board):
                return True
            board[row][col] = 0

    return False


def validate(board, num, pos):
    row = pos[0]
    col = pos[1]
    # Check no other number is num in the row
    for j in range(0, num_cols):
        if board[row][j] == num and j != col:
            return False

    # Check no other number is num in the col
    for i in range(0, num_rows):
        if board[i][col] == num and i != row:
            return False

    # Check no other number is num in the 3x3 subbox
    subbox_row = row // 3
    subbox_col = col // 3
    for i in range(subbox_row * 3, subbox_row * 3 + 3):
        for j in range(subbox_col * 3, subbox_col * 3 + 3):
            if board[i][j] == num and (i, j) != pos:
                return False

    return True


def get_empty_square(board):
    # Check in each square if it is empty else return None
    for i in range(0, num_rows):
        for j in range(0, num_cols):
            if board[i][j] == 0:
                return (i, j)
    return None


def dashed_lines():
    print("----------------------")


def print_board(board):
    for i in range(0, num_rows):
        if i % 3 == 0 and i != 0:
            dashed_lines()
        for j in range(0, num_cols):
            if j % 3 == 0 and j != 0:
                print('|', end=' ')
            print(board[i][j], end=' ')
        print()


print("Initial Sudoku is \n")
print_board(board=board)
print()
solve_sudoku(board=board)
print("Solution to Sudoku is \n")
print_board(board=board)
end_time = datetime.now()
print('Duration: {}'.format(end_time - start_time))
