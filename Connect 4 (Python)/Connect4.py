def makeboard():
    return [[" " for j in range(7)] for i in range(6)]

def printboard(board):
    print("---------------")
    for i in range(len(board)):
        output = "|"
        for j in range(len(board[i])):
            output += board[i][j] + "|"
        print(output)
        print("---------------")
    print(" 1 2 3 4 5 6 7 ")

def checkboard(board):
    for i in range(7):
        if board[0][i] == board[1][i] == board[2][i] == board[3][i] and board[0][i] != " ":
            return 1
        elif board[1][i] == board[2][i] == board[3][i] == board[4][i] and board[1][i] != " ":
            return 1
        elif board[2][i] == board[3][i] == board[4][i] == board[5][i] and board[2][i] != " ":
            return 1
    for i in range(6):
        if board[i][0] == board[i][1] == board[i][2] == board[i][3] and board[i][0] != " ":
            return 1
        elif board[i][1] == board[i][2] == board[i][3] == board[i][4] and board[i][1] != " ":
            return 1
        elif board[i][2] == board[i][3] == board[i][4] == board[i][5] and board[i][2] != " ":
            return 1
        elif board[i][3] == board[i][4] == board[i][5] == board[i][6] and board[i][3] != " ":
            return 1
    top_right = 6
    for i in range(4):
        for j in range(3):
            if board[j][i] == board[j+1][i+1] == board[j+2][i+2] == board[j+3][i+3] and board[j][i] != " ":
                return 1
            elif board[j][top_right] == board[j+1][top_right-1] == board[j+2][top_right-2] == board[j+3][top_right-3] and board[j][top_right] != " ":
                return 1
        top_right -= 1
    bottom_right = 6
    for i in range(4):
        for j in range(5, 2, -1):
            if board[j][i] == board[j-1][i+1] == board[j-2][i+2] == board[j-3][i+3] and board[j][i] != " ":
                return 1
            elif board[j][bottom_right] == board[j-1][bottom_right-1] == board[j-2][bottom_right-2] == board[j-3][bottom_right-3] and board[j][bottom_right] != " ":
                return 1
        bottom_right -= 1
    return 0

def connectfour():
    board = makeboard()
    printboard(board)
    turn = 0
    outcome = 0
    players = ["Red", "Yellow"]
    pieces = ["O", "X"]
    possible_moves = ["1", "2", "3", "4", "5", "6", "7"]
    counter = 0
    while outcome == 0 and counter < 42:
        player_input = input(f"{players[turn]}, enter a number to place {pieces[turn]}: ")
        if player_input == "EXIT":
            break
        while player_input not in possible_moves:
            player_input = input(f"{players[turn]}, enter a number to place a piece {pieces[turn]}: ")
        column = int(player_input) - 1
        row = 5
        while row >= -1:
            if row == -1:
                print("Invalid input, please try again")
                break
            if board[row][column] != " ":
                row -= 1
            else:
                board[row][column] = pieces[turn]
                printboard(board)
                turn = 1 - turn
                outcome = checkboard(board)
                counter += 1
                break
    if outcome == 1:
        print(f"{players[1-turn]}, {pieces[1-turn]} has won!")
    elif counter == 42:
        print("It's a draw.")
    replay = input("Enter R to replay or Q to quit: ")
    if replay.upper() == "R":
        connectfour()

def menu():
    choice = input("Please type A to begin: ")
    if choice.upper() == "A":
        connectfour()

if __name__ == "__main__":
    menu()