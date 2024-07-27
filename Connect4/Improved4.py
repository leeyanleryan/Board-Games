from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton
from PyQt5.QtGui import QPixmap, QIcon
from PyQt5.QtCore import QSize

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.grid = QGridLayout(self)
        self.buttons = [[QPushButton(self) for _ in range(7)] for _ in range(6)]
        self.colours = [[None for _ in range(7)] for _ in range(6)]
        self.red_piece = QPixmap("RedPiece1.png")
        self.yellow_piece = QPixmap("YellowPiece1.png")
        self.board = [[" " for j in range(7)] for i in range(6)]
        self.turn = 0
        self.outcome = 0
        self.players = ["Red", "Yellow"]
        self.pieces = ["O", "X"]
        self.counter = 0
        for i in range(6):
            for j in range(7):
                self.grid.addWidget(self.buttons[i][j], i, j)
                self.buttons[i][j].setFixedSize(50, 50)
                self.buttons[i][j].clicked.connect(lambda checked, row=i, col=j: 
                                                   self.connectfour(row, col))
        self.setLayout(self.grid)
        self.setWindowTitle('Connect 4')

    def printboard(self):
        for i in range(len(self.board)):
            print("".join(self.board[i]))

    def connectfour(self, row, col):
        size = self.buttons[row][col].size()
        self.red_piece = self.red_piece.scaled(size)
        self.yellow_piece = self.yellow_piece.scaled(size)
        if self.outcome == 0:
            row = 5
            while row >= -1:
                if row == -1:
                    break
                if self.board[row][col] != " ":
                    row -= 1
                else:
                    self.board[row][col] = self.pieces[self.turn]
                    if self.turn == 0:
                        icon = QIcon(self.red_piece)
                    else:
                        icon = QIcon(self.yellow_piece)
                    self.buttons[row][col].setIcon(icon)
                    self.buttons[row][col].setIconSize(QSize(40, 40))
                    self.turn = 1 - self.turn
                    self.outcome = self.checkboard(self.board)
                    self.counter += 1
                    break
        if self.outcome == 1:
            print(f"{self.players[1-self.turn]}, {self.pieces[1-self.turn]} has won!")
        elif self.counter == 42:
            print("It's a draw.")

    def checkboard(self, board):
        for i in range(7):
            if (board[0][i] == board[1][i] ==
                board[2][i] == board[3][i] and 
                board[0][i] != " "):
                return 1
            elif (board[1][i] == board[2][i] == 
                  board[3][i] == board[4][i] and 
                  board[1][i] != " "):
                  return 1
            elif (board[2][i] == board[3][i] == 
                  board[4][i] == board[5][i] and 
                  board[2][i] != " "):
                  return 1
        for i in range(6):
            if (board[i][0] == board[i][1] == 
                board[i][2] == board[i][3] and 
                board[i][0] != " "):
                return 1
            elif (board[i][1] == board[i][2] == 
                  board[i][3] == board[i][4] and 
                  board[i][1] != " "):
                  return 1
            elif (board[i][2] == board[i][3] == 
                  board[i][4] == board[i][5] and 
                  board[i][2] != " "):
                  return 1
            elif (board[i][3] == board[i][4] == 
                  board[i][5] == board[i][6] and 
                  board[i][3] != " "):
                  return 1
        top_right = 6
        for i in range(4):
            for j in range(3):
                if (board[j][i] == board[j+1][i+1] == 
                    board[j+2][i+2] == board[j+3][i+3] and 
                    board[j][i] != " "):
                    return 1
                elif (board[j][top_right] == board[j+1][top_right-1] == 
                      board[j+2][top_right-2] == board[j+3][top_right-3] and 
                      board[j][top_right] != " "):
                      return 1
            top_right -= 1
        bottom_right = 6
        for i in range(4):
            for j in range(5, 2, -1):
                if (board[j][i] == board[j-1][i+1] == 
                    board[j-2][i+2] == board[j-3][i+3] and 
                    board[j][i] != " "):
                    return 1
                elif (board[j][bottom_right] == board[j-1][bottom_right-1] == 
                      board[j-2][bottom_right-2] == board[j-3][bottom_right-3] and 
                      board[j][bottom_right] != " "):
                      return 1
            bottom_right -= 1
        return 0


if __name__ == '__main__':
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()