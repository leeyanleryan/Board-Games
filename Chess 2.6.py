from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton, QLabel
from PyQt5.QtGui import QPixmap, QIcon, QPainter
from PyQt5.QtCore import QSize, QTimer, Qt
from time import *
import os

os.chdir("C:/Users/Admin/OneDrive/Projects/Chess/Pictures")

class Chess(QWidget):
    def __init__(self):
        super().__init__()
        begin = time()
        self.players = ["White", "Black"]
        self.turn_pieces = [["P", "N", "B", "R", "Q", "K"], ["p", "n", "b", "r", "q", "k"]]
        self.all_pieces = {"P":"Pawn", "N":"Knight", "B":"Bishop", "R":"Rook", "Q":"Queen", "K":"King",
                           "p":"Pawn", "n":"Knight", "b":"Bishop", "r":"Rook", "q":"Queen", "k":"King"}
        self.square_pos = {"a8":(0, 0), "b8":(0, 1), "c8":(0, 2), "d8":(0, 3), "e8":(0, 4), "f8":(0, 5), "g8":(0, 6), "h8":(0, 7),
                           "a7":(1, 0), "b7":(1, 1), "c7":(1, 2), "d7":(1, 3), "e7":(1, 4), "f7":(1, 5), "g7":(1, 6), "h7":(1, 7),
                           "a6":(2, 0), "b6":(2, 1), "c6":(2, 2), "d6":(2, 3), "e6":(2, 4), "f6":(2, 5), "g6":(2, 6), "h6":(2, 7),
                           "a5":(3, 0), "b5":(3, 1), "c5":(3, 2), "d5":(3, 3), "e5":(3, 4), "f5":(3, 5), "g5":(3, 6), "h5":(3, 7),
                           "a4":(4, 0), "b4":(4, 1), "c4":(4, 2), "d4":(4, 3), "e4":(4, 4), "f4":(4, 5), "g4":(4, 6), "h4":(4, 7),
                           "a3":(5, 0), "b3":(5, 1), "c3":(5, 2), "d3":(5, 3), "e3":(5, 4), "f3":(5, 5), "g3":(5, 6), "h3":(5, 7),
                           "a2":(6, 0), "b2":(6, 1), "c2":(6, 2), "d2":(6, 3), "e2":(6, 4), "f2":(6, 5), "g2":(6, 6), "h2":(6, 7),
                           "a1":(7, 0), "b1":(7, 1), "c1":(7, 2), "d1":(7, 3), "e1":(7, 4), "f1":(7, 5), "g1":(7, 6), "h1":(7, 7)}
        self.pos_square = dict((v, k) for k, v in self.square_pos.items())
        self.turn = 0
        self.board = self.CreateBoard()
        self.move_counter = 0
        self.moves_played = []
        self.selection = [-1, -1]
        self.legal_moves = []
        self.all_legal_moves = []
        self.possible_captures = []
        self.king_white_pos = [-1, -1]
        self.king_white_moved = 0
        self.rook_white_short_moved = 0
        self.rook_white_long_moved = 0
        self.king_black_pos = [-1, -1]
        self.king_black_moved = 0
        self.rook_black_short_moved = 0
        self.rook_black_long_moved = 0
        self.king_piece_pos = [self.king_white_pos, self.king_black_pos]
        self.king_piece_moved = [self.king_white_moved, self.king_black_moved]
        self.rook_piece_short_moved = [self.rook_white_short_moved, self.rook_black_short_moved]
        self.rook_piece_long_moved = [self.rook_white_long_moved, self.rook_black_long_moved]
        self.en_passant = [0, 0]
        self.en_passant_square = [[-1, -1], [-1, -1]]
        self.counter_hashmap = {"P":0, "N":0, "B":[0, 0], "R":0, "Q":0, "K":0,
                                "p":0, "n":0, "b":[0, 0], "r":0, "q":0, "k":0}
        self.position_hashmap = {"".join(map(lambda x: "".join(x), self.board)):1}
        self.game_end = 0
        self.grid = QGridLayout(self)
        self.grid.setSpacing(0)
        self.buttons = [[QPushButton(self) for _ in range(8)] for _ in range(8)]
        self.pawn_p, self.pawn_p_capture = QPixmap("PawnBlack.png"), QPixmap("PawnBlackCapture.png")
        self.pawn_P, self.pawn_P_capture = QPixmap("PawnWhite.png"), QPixmap("PawnWhiteCapture.png")
        self.bishop_b, self.bishop_b_capture = QPixmap("BishopBlack.png"), QPixmap("BishopBlackCapture.png")
        self.bishop_B, self.bishop_B_capture = QPixmap("BishopWhite.png"), QPixmap("BishopWhiteCapture.png")
        self.knight_n, self.knight_n_capture = QPixmap("KnightBlack.png"), QPixmap("KnightBlackCapture.png")
        self.knight_N, self.knight_N_capture = QPixmap("KnightWhite.png"), QPixmap("KnightWhiteCapture.png")
        self.rook_r, self.rook_r_capture = QPixmap("RookBlack.png"), QPixmap("RookBlackCapture.png")
        self.rook_R, self.rook_R_capture = QPixmap("RookWhite.png"), QPixmap("RookWhiteCapture.png")
        self.queen_q, self.queen_q_capture = QPixmap("QueenBlack.png"), QPixmap("QueenBlackCapture.png")
        self.queen_Q, self.queen_Q_capture = QPixmap("QueenWhite.png"), QPixmap("QueenWhiteCapture.png")
        self.king_k, self.king_k_capture = QPixmap("KingBlack.png"), QPixmap("KingBlackCapture.png")
        self.king_K, self.king_K_capture = QPixmap("KingWhite.png"), QPixmap("KingWhiteCapture.png")
        self.legal_move = QPixmap("LegalMove.png")
        self.piece_capture = QPixmap("PieceCapture.png")
        self.piece_pixmap = {"r":self.rook_r, "n":self.knight_n, "b":self.bishop_b, "q":self.queen_q, "k":self.king_k, "p":self.pawn_p,
                             "R":self.rook_R, "N":self.knight_N, "B":self.bishop_B, "Q":self.queen_Q, "K":self.king_K, "P":self.pawn_P,
                             "-":""}
        self.piece_capture_pixmap = {"r":self.rook_r_capture, "n":self.knight_n_capture, "b":self.bishop_b_capture, "q":self.queen_q_capture, "k":self.king_k_capture, "p":self.pawn_p_capture,
                                     "R":self.rook_R_capture, "N":self.knight_N_capture, "B":self.bishop_B_capture, "Q":self.queen_Q_capture, "K":self.king_K_capture, "P":self.pawn_P_capture,
                                     "-":""}
        for i in range(8):
            for j in range(8):
                self.grid.addWidget(self.buttons[i][j], i, j)
                self.buttons[i][j].setFixedSize(100, 100)
                if self.board[i][j] == "k":
                    self.king_black_pos[0] = i
                    self.king_black_pos[1] = j
                elif self.board[i][j] == "K":
                    self.king_white_pos[0] = i
                    self.king_white_pos[1] = j
                if (i + j) % 2 == 0:
                    self.buttons[i][j].setStyleSheet("background-image: url(BoardWhite.png); border: 0")
                else:
                    self.buttons[i][j].setStyleSheet("background-image: url(BoardBlack.png); border: 0")
                icon = QIcon(self.piece_pixmap[self.board[i][j]])
                self.buttons[i][j].setIcon(icon)
                self.buttons[i][j].setIconSize(QSize(100, 100))
                self.buttons[i][j].clicked.connect(lambda checked, row=i, col=j: 
                                                   self.MakeMove(row, col))
        self.setLayout(self.grid)
        self.setWindowTitle("Chess")
        self.move(300, 100)
        print(f"\nMoves Played: {self.moves_played}\n")
        self.BoardPrint()
        print(f"\nTime taken: {time()-begin}s")

    def CreateBoard(self):
        board = [["-" for i in range(8)] for j in range(8)]
        for i in range(8):
            board[1][i] = "p"
            board[6][i] = "P"
        board[7] = ["R","N","B","Q","K","B","N","R"]
        board[0] = list(map(lambda x: x.lower(), board[7]))
        return board

    def BoardPrint(self):
        board = self.board
        for i in range(8):
            print(f"{board[i][0]}|{board[i][1]}|{board[i][2]}|{board[i][3]}|{board[i][4]}|{board[i][5]}|{board[i][6]}|{board[i][7]} {8-i}")
        print("a b c d e f g h")

    def MakeMove(self, row, col):
        if self.game_end == 1:
            return
        begin = time()
        board_pic = ["BoardWhite.png", "BoardBlack.png"]
        selected_piece = self.board[row][col]
        show_move = 0
        hide_move = 0
        make_move = 0
        # Making move
        if (row, col) in self.legal_moves:
            self.buttons[self.selection[0]][self.selection[1]].setStyleSheet(f"background-image: url({board_pic[(self.selection[0] + self.selection[1]) % 2]}); border: 0")
            prev_row = self.selection[0]
            prev_col = self.selection[1]
            self.selection[0] = -1
            self.selection[1] = -1
            hide_move = 1
            make_move = 1
        # Have not selected and selected piece is valid
        elif self.selection[0] == -1 and self.selection[1] == -1 and selected_piece in self.turn_pieces[self.turn]:
            self.buttons[row][col].setStyleSheet("background-image: url(SelectedPiece.png); border: 0")
            self.selection[0] = row
            self.selection[1] = col
            show_move = 1
        # Selected same piece or selected piece is invalid
        elif self.selection[0] == row and self.selection[1] == col or selected_piece not in self.turn_pieces[self.turn]:
            self.buttons[self.selection[0]][self.selection[1]].setStyleSheet(f"background-image: url({board_pic[(self.selection[0] + self.selection[1]) % 2]}); border: 0")
            self.selection[0] = -1
            self.selection[1] = -1
            hide_move = 1
        # Selected different piece and selected piece is valid
        else:
            self.buttons[self.selection[0]][self.selection[1]].setStyleSheet(f"background-image: url({board_pic[(self.selection[0] + self.selection[1]) % 2]}); border: 0")
            self.buttons[row][col].setStyleSheet("background-image: url(SelectedPiece.png); border: 0")
            self.selection[0] = row
            self.selection[1] = col
            hide_move = 1
            show_move = 1
        # Hide legal moves
        if hide_move == 1:
            icon = QIcon()
            for moves in self.legal_moves:
                self.buttons[moves[0]][moves[1]].setIcon(icon)
            for pieces in self.possible_captures:
                enemy_piece = self.board[pieces[0]][pieces[1]]
                icon = QIcon(self.piece_pixmap[enemy_piece])
                self.buttons[pieces[0]][pieces[1]].setIcon(icon)
            self.legal_moves = []
            self.possible_captures = []
        # Show legal moves
        if show_move == 1:
            if selected_piece.lower() == "p":
                self.LegalPawnMovement(row, col, True)
            elif selected_piece.lower() == "n":
                self.LegalKnightMovement(row, col, True)
            elif selected_piece.lower() == "b":
                self.LegalBishopMovement(row, col, True)
            elif selected_piece.lower() == "r":
                self.LegalRookMovement(row, col, True)
            elif selected_piece.lower() == "q":
                self.LegalQueenMovement(row, col, True)
            elif selected_piece.lower() == "k":
                self.LegalKingMovement(row, col, True)
        # Make move
        if make_move == 1:
            if self.board[prev_row][prev_col].lower() == "p":
                self.MovePawn(prev_row, prev_col, row, col)
                self.move_counter = 1
            else:
                self.MovePiece(prev_row, prev_col, row, col)
            self.en_passant[1-self.turn] = 0
            self.en_passant_square[1-self.turn][0] = -1
            self.en_passant_square[1-self.turn][1] = -1
            self.turn = 1 - self.turn
            print(f"\nMoves Played: {self.moves_played}\n")
            self.BoardPrint()
            print(f"\nTime taken: {time()-begin}s")

    def LegalPawnMovement(self, row, col, show_move):
        turn_factor = [-1, 1]
        home_row = [6, 1]
        pawn_turn = ["P", "p"]
        icon_move = QIcon(self.legal_move)
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        ep_square = self.en_passant_square
        # Cannot move forward if piece is in front
        if (self.board[row+1*(turn_factor[self.turn])][col] == "-" and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col, king_row, king_col) == False):
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col))
            if show_move == True:
                self.buttons[row+1*(turn_factor[self.turn])][col].setIcon(icon_move)
        # Home square can move one extra
        if (row == home_row[self.turn] and self.board[row+2*(turn_factor[self.turn])][col] == "-" and
            self.board[row+1*(turn_factor[self.turn])][col] == "-" and
            self.CheckIfPinned(row, col, row+2*(turn_factor[self.turn]), col, king_row, king_col) == False):
            self.legal_moves.append((row+2*(turn_factor[self.turn]), col))
            if show_move == True:
                self.buttons[row+2*(turn_factor[self.turn])][col].setIcon(icon_move)
        # Capture diagonally left
        if (col-1 in range(8) and self.board[row+1*(turn_factor[self.turn])][col-1] in self.turn_pieces[1-self.turn] and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col-1, king_row, king_col) == False):
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col-1))
            if show_move == True:
                icon_capture = QIcon(self.piece_capture_pixmap[self.board[row+1*(turn_factor[self.turn])][col-1]])
                self.buttons[row+1*(turn_factor[self.turn])][col-1].setIcon(icon_capture)
                self.possible_captures.append((row+1*(turn_factor[self.turn]), col-1))
        # Capture diagonally right
        if (col+1 in range(8) and self.board[row+1*(turn_factor[self.turn])][col+1] in self.turn_pieces[1-self.turn] and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col+1, king_row, king_col) == False):
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col+1))
            if show_move == True:
                icon_capture = QIcon(self.piece_capture_pixmap[self.board[row+1*(turn_factor[self.turn])][col+1]])
                self.buttons[row+1*(turn_factor[self.turn])][col+1].setIcon(icon_capture)
                self.possible_captures.append((row+1*(turn_factor[self.turn]), col+1))
        # En passant left
        if (self.en_passant[1-self.turn] == 1 and (ep_square[1-self.turn][0], ep_square[1-self.turn][1]) == (row, col-1) and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col-1, king_row, king_col) == False):
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col-1))
            if show_move == True:
                self.buttons[row+1*(turn_factor[self.turn])][col-1].setIcon(icon_move)
                self.possible_captures.append((row+1*(turn_factor[self.turn]), col-1))
        # En passant right
        if (self.en_passant[1-self.turn] == 1 and (ep_square[1-self.turn][0], ep_square[1-self.turn][1]) == (row, col+1) and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col+1, king_row, king_col) == False):
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col+1))
            if show_move == True:
                self.buttons[row+1*(turn_factor[self.turn])][col+1].setIcon(icon_move)
                self.possible_captures.append((row+1*(turn_factor[self.turn]), col+1))
            
    def LegalKnightMovement(self, row, col, show_move):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        pool = [(row-1, col-2), (row-2, col-1), (row-1, col+2), (row-2, col+1),
                (row+1, col-2), (row+2, col-1), (row+1, col+2), (row+2, col+1)]
        # Check all 8 possible spots
        for pos in pool:
            if pos[0] in range(8) and pos[1] in range(8):
                if self.CheckIfPinned(row, col, pos[0], pos[1], king_row, king_col) == False:
                    if self.board[pos[0]][pos[1]] == "-":
                        self.legal_moves.append((pos[0], pos[1]))
                        if show_move == True:
                            icon = QIcon(self.legal_move)
                            self.buttons[pos[0]][pos[1]].setIcon(icon)
                    elif self.board[pos[0]][pos[1]] in self.turn_pieces[1-self.turn]:
                        self.legal_moves.append((pos[0], pos[1]))
                        if show_move == True:
                            icon = QIcon(self.piece_capture_pixmap[self.board[pos[0]][pos[1]]])
                            self.buttons[pos[0]][pos[1]].setIcon(icon)
                            self.possible_captures.append((pos[0], pos[1]))

    def LegalBishopMovement(self, row, col, show_move):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        # Top Left
        check_row = row - 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row -= 1
            check_col -= 1
        # Top Right
        check_row = row - 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row -= 1
            check_col += 1
        # Bottom Left
        check_row = row + 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row += 1
            check_col -= 1
        # Bottom Right
        check_row = row + 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row += 1
            check_col += 1

    def LegalRookMovement(self, row, col, show_move):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        check_row = row - 1
        check_col = col
        # Up
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and 
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row -= 1
        # Down
        check_row = row + 1
        check_col = col
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and 
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_row += 1
        # Left
        check_row = row
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and 
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_col -= 1
        # Right
        check_row = row
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if (self.board[check_row][check_col] == "-" and
                self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
            elif (self.board[check_row][check_col] in self.turn_pieces[1-self.turn] and 
                  self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False):
                self.legal_moves.append((check_row, check_col))
                if show_move == True:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.possible_captures.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] in self.turn_pieces[self.turn]:
                break
            check_col += 1

    def LegalQueenMovement(self, row, col, show_move):
        self.LegalBishopMovement(row, col, show_move)
        self.LegalRookMovement(row, col, show_move)

    def LegalKingMovement(self, row, col, show_move):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        enemy_king_row = self.king_piece_pos[1-self.turn][0]
        enemy_king_col = self.king_piece_pos[1-self.turn][1]
        home_square = [(7, 4), (0, 4)]
        pool = [(row-1, col-1), (row-1, col), (row-1, col+1),
                (row, col-1),                 (row, col+1),
                (row+1, col-1), (row+1, col), (row+1, col+1)]
        enemy_pool = [(enemy_king_row-1, enemy_king_col-1), (enemy_king_row-1, enemy_king_col), (enemy_king_row-1, enemy_king_col+1),
                      (enemy_king_row, enemy_king_col-1),                                       (enemy_king_row, enemy_king_col+1),
                      (enemy_king_row+1, enemy_king_col-1), (enemy_king_row+1, enemy_king_col), (enemy_king_row+1, enemy_king_col+1)]
        # Surrounding 8 squares
        for pos in pool:
            if pos[0] in range(8) and pos[1] in range(8) and (pos[0], pos[1]) not in enemy_pool:
                if self.CheckIfPinned(row, col, pos[0], pos[1], pos[0], pos[1]) == False:
                    if self.board[pos[0]][pos[1]] == "-":
                        self.legal_moves.append((pos[0], pos[1]))
                        if show_move == True:
                            icon = QIcon(self.legal_move)
                            self.buttons[pos[0]][pos[1]].setIcon(icon)
                    elif self.board[pos[0]][pos[1]] in self.turn_pieces[1-self.turn]:
                        self.legal_moves.append((pos[0], pos[1]))
                        if show_move == True:
                            icon = QIcon(self.piece_capture_pixmap[self.board[pos[0]][pos[1]]])
                            self.buttons[pos[0]][pos[1]].setIcon(icon)
                            self.possible_captures.append((pos[0], pos[1]))
        # Castling
        if (row, col) == home_square[self.turn]:
            icon = QIcon(self.legal_move)
            turn_row = [7, 0]
            turn_rook = ["R", "r"]
            rook_short_home_square = [(7, 7), (0, 7)]
            rook_short_row = rook_short_home_square[self.turn][0]
            rook_short_col = rook_short_home_square[self.turn][1]
            rook_long_home_square = [(7, 0), (0, 0)]
            rook_long_row = rook_long_home_square[self.turn][0]
            rook_long_col = rook_long_home_square[self.turn][1]
            # Short Castles
            if self.board[rook_short_row][rook_short_col] == turn_rook[self.turn]:
                if self.king_piece_moved[self.turn] == 0 and self.rook_piece_short_moved[self.turn] == 0:
                    if (turn_row[self.turn], 5) not in enemy_pool and (turn_row[self.turn], 6) not in enemy_pool:
                        if (self.CheckIfPinned(row, col, turn_row[self.turn], 5, turn_row[self.turn], 5) == False and
                            self.CheckIfPinned(row, col, turn_row[self.turn], 6, turn_row[self.turn], 6) == False):
                            if "".join(self.board[turn_row[self.turn]][5:7]) == "--":
                                self.legal_moves.append((turn_row[self.turn], 6))
                                if show_move == True:
                                    self.buttons[turn_row[self.turn]][6].setIcon(icon)
            # Long Castles
            if self.board[rook_long_row][rook_long_col] == turn_rook[self.turn]:
                if self.king_piece_moved[self.turn] == 0 and self.rook_piece_long_moved[self.turn] == 0:
                    if (turn_row[self.turn], 2) not in enemy_pool and (turn_row[self.turn], 3) not in enemy_pool:
                        if (self.CheckIfPinned(row, col, turn_row[self.turn], 2, turn_row[self.turn], 2) == False and
                            self.CheckIfPinned(row, col, turn_row[self.turn], 3, turn_row[self.turn], 3) == False):
                            if "".join(self.board[turn_row[self.turn]][1:4]) == "---":
                                self.legal_moves.append((turn_row[self.turn], 2))
                                if show_move == True:
                                    self.buttons[turn_row[self.turn]][2].setIcon(icon)

    def FindPawn(self, row, col, piece_name):
        pool_pawn = []
        turn_factor = [1, -1]
        # Left
        if (row+turn_factor[1-self.turn] in range(8) and col-1 in range(8) and
            self.board[row+turn_factor[1-self.turn]][col-1] == piece_name):
            pool_pawn.append((row+turn_factor[1-self.turn], col-1))
        # Right
        elif (row+turn_factor[1-self.turn] in range(8) and col+1 in range(8) and
              self.board[row+turn_factor[1-self.turn]][col+1] == piece_name):
            pool_pawn.append((row+turn_factor[1-self.turn], col+1))
        return pool_pawn

    def FindKnight(self, prev_row, prev_col, row, col, piece_name):
        pool_knight = []
        pool_pos = [(-1, -2), (-2, -1), (-1, 2), (-2, 1),
                    (1, -2), (2, -1), (1, 2), (2, 1)]
        for pos in pool_pos:
            check_row = row + pos[0]
            check_col = col + pos[1]
            if check_row in range(8) and check_col in range(8):
                if self.board[check_row][check_col] == piece_name:
                    if (check_row, check_col) != (prev_row, prev_col):
                        pool_knight.append((check_row, check_col))
        return pool_knight

    def FindBishop(self, prev_row, prev_col, row, col, piece_name):
        pool_bishop = []
        # Top left
        check_row = row - 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_bishop.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row -= 1
            check_col -= 1
        # Top Right
        check_row = row - 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_bishop.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row -= 1
            check_col += 1
        # Bottom Left
        check_row = row + 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_bishop.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row += 1
            check_col -= 1
        # Bottom Right
        check_row = row + 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_bishop.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row += 1
            check_col += 1
        return pool_bishop

    def FindRook(self, prev_row, prev_col, row, col, piece_name):
        pool_rook = []
        check_row = row - 1
        check_col = col
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_rook.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row -= 1
        check_row = row + 1
        check_col = col
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_rook.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_row += 1
        check_row = row
        check_col = col - 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_rook.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_col -= 1
        check_row = row
        check_col = col + 1
        while check_row in range(8) and check_col in range(8) and (check_row, check_col) != (prev_row, prev_col):
            if self.board[check_row][check_col] == piece_name:
                pool_rook.append((check_row, check_col))
                break
            elif self.board[check_row][check_col] != "-":
                break
            check_col += 1
        return pool_rook

    def CheckIfCheck(self, king_row, king_col, turn):
        pool_pawn = self.FindPawn(king_row, king_col, self.turn_pieces[turn][0])
        pool_knight = self.FindKnight(-1, -1, king_row, king_col, self.turn_pieces[turn][1])
        pool_bishop = self.FindBishop(-1, -1, king_row, king_col ,self.turn_pieces[turn][2])
        pool_rook = self.FindRook(-1, -1, king_row, king_col ,self.turn_pieces[turn][3])
        pool_queen1 = self.FindBishop(-1, -1, king_row, king_col ,self.turn_pieces[turn][4])
        pool_queen2 = self.FindRook(-1, -1, king_row, king_col ,self.turn_pieces[turn][4])
        combined_pool = pool_pawn + pool_knight + pool_bishop + pool_rook + pool_queen1 + pool_queen2
        return len(combined_pool) > 0

    def CheckIfPinned(self, prev_row, prev_col, row, col, king_row, king_col):
        temp_piece = self.board[row][col]
        self.board[row][col] = self.board[prev_row][prev_col]
        self.board[prev_row][prev_col] = "-"
        is_pinned = self.CheckIfCheck(king_row, king_col, 1-self.turn)
        self.board[prev_row][prev_col] = self.board[row][col]
        self.board[row][col] = temp_piece
        return is_pinned

    def CheckIfMate(self):
        self.turn = 1-self.turn
        for piece_row in range(8):
            for piece_col in range(8):
                selected_piece = self.board[piece_row][piece_col]
                if selected_piece in self.turn_pieces[self.turn]:
                    if selected_piece.lower() == "p":
                        self.LegalPawnMovement(piece_row, piece_col, False)
                    elif selected_piece.lower() == "n":
                        self.LegalKnightMovement(piece_row, piece_col, False)
                    elif selected_piece.lower() == "b":
                        self.LegalBishopMovement(piece_row, piece_col, False)
                    elif selected_piece.lower() == "r":
                        self.LegalRookMovement(piece_row, piece_col, False)
                    elif selected_piece.lower() == "q":
                        self.LegalQueenMovement(piece_row, piece_col, False)
                    elif selected_piece.lower() == "k":
                        self.LegalKingMovement(piece_row, piece_col, False)
                if selected_piece != "-":
                    if selected_piece.lower() == "b":
                        self.counter_hashmap[selected_piece][(piece_row+piece_col)%2] += 1
                    else:
                        self.counter_hashmap[selected_piece] += 1
        number_of_moves = len(self.legal_moves)
        self.turn = 1-self.turn
        self.legal_moves = []
        return number_of_moves == 0

    def CheckIfDead(self):
        # Having pawn, rook or queen means no draw
        if (self.counter_hashmap["P"] == self.counter_hashmap["p"] == 0 and
            self.counter_hashmap["R"] == self.counter_hashmap["r"] == 0 and
            self.counter_hashmap["Q"] == self.counter_hashmap["q"] == 0):
            knight_config = (self.counter_hashmap["N"], self.counter_hashmap["n"])
            bishop_config = (self.counter_hashmap["B"][0], self.counter_hashmap["b"][0], self.counter_hashmap["B"][1], self.counter_hashmap["b"][1])
            # King vs king
            if (knight_config == (0, 0) and 
                bishop_config == (0, 0, 0, 0)):
                return True
            # King and bishop vs king
            elif (knight_config == (0, 0) and
                 (bishop_config == (1, 0, 0, 0) or bishop_config == (0, 1, 0, 0) or
                  bishop_config == (0, 0, 1, 0) or bishop_config == (0, 0, 0, 1))):
                return True
            # King and knight vs king
            elif ((knight_config == (1, 0) or knight_config == (0, 1)) and
                   bishop_config == (0, 0, 0, 0)):
                return True
            # King and bishop vs king and bishop (both bishop same square colour)
            elif (knight_config == (0, 0) and
                 (bishop_config == (1, 1, 0, 0) or bishop_config == (0, 0, 1, 1))):
                return True
        # Three fold repetition
        new_position = "".join(map(lambda x: "".join(x), self.board))
        if new_position not in self.position_hashmap:
            self.position_hashmap[new_position] = 1
        else:
            self.position_hashmap[new_position] += 1
        if self.position_hashmap[new_position] == 3:
            return True
        self.counter_hashmap = {"P":0, "N":0, "B":[0, 0], "R":0, "Q":0, "K":0,
                                "p":0, "n":0, "b":[0, 0], "r":0, "q":0, "k":0}
        return False

    def MovePawn(self, prev_row, prev_col, row, col):
        move_played = ""
        prev_square = self.pos_square[(prev_row, prev_col)]
        new_square = self.pos_square[(row, col)]
        end_squares = [0, 7]
        pawn_pixmap = [self.pawn_P, self.pawn_p]
        promo_piece_pixmap = [self.queen_Q, self.queen_q]
        promo_piece = ["Q", "q"]
        turn_factor = [1, -1]
        icon_blank = QIcon()
        # promote: yes, capture: no
        if row == end_squares[self.turn] and self.board[row][col] == "-":
            icon = QIcon(promo_piece_pixmap[self.turn])
            self.board[row][col] = promo_piece[self.turn]
            move_played = f"{new_square}={promo_piece[self.turn]}"
        # promote: yes, capture: yes
        elif row == end_squares[self.turn] and self.board[row][col] != "-":
            icon = QIcon(promo_piece_pixmap[self.turn])
            self.board[row][col] = promo_piece[self.turn]
            move_played = f"{prev_square[0]}x{new_square}={promo_piece[self.turn]}"
        # en_passant: yes
        elif (self.en_passant_square[1-self.turn][0], self.en_passant_square[1-self.turn][1]) == (row+turn_factor[self.turn], col):
            icon = QIcon(pawn_pixmap[self.turn])
            self.buttons[self.en_passant_square[1-self.turn][0]][self.en_passant_square[1-self.turn][1]].setIcon(icon_blank)
            self.board[self.en_passant_square[1-self.turn][0]][self.en_passant_square[1-self.turn][1]] = "-"
            self.board[row][col] = self.board[prev_row][prev_col]
            move_played = f"{prev_square[0]}x{new_square}"
        # promote: no, capture: yes
        elif self.board[row][col] != "-":
            icon = QIcon(pawn_pixmap[self.turn])
            self.board[row][col] = self.board[prev_row][prev_col]
            move_played = f"{prev_square[0]}x{new_square}"
        # promote: no, capture: no
        elif self.board[row][col] == "-":
            icon = QIcon(pawn_pixmap[self.turn])
            self.board[row][col] = self.board[prev_row][prev_col]
            move_played = f"{new_square}"
        # check en passant rule
        if abs(row - prev_row) == 2:
            self.en_passant[self.turn] = 1
            self.en_passant_square[self.turn][0] = row
            self.en_passant_square[self.turn][1] = col
        self.buttons[row][col].setIcon(icon)
        self.buttons[prev_row][prev_col].setIcon(icon_blank)
        self.board[prev_row][prev_col] = "-"
        is_mate = self.CheckIfMate()
        is_check = self.CheckIfCheck(self.king_piece_pos[1-self.turn][0], self.king_piece_pos[1-self.turn][1], self.turn)
        is_dead = self.CheckIfDead()
        # Stalemate
        if is_check == False and is_mate == True:
            self.moves_played.append(move_played)
            move_played = "1/2-1/2"
            self.game_end = 1
        # Checkmate
        elif is_check == True and is_mate == True:
            move_played += "#"
            self.game_end = 1
        # Check
        elif is_check == True and is_mate == False:
            move_played += "+"
        self.moves_played.append(move_played)
    
    def MovePiece(self, prev_row, prev_col, row, col):
        piece_name = self.board[prev_row][prev_col]
        move_played = piece_name
        icon_piece = QIcon(self.piece_pixmap[piece_name])
        icon_blank = QIcon()
        castles = 0
        # Same piece different position check
        if piece_name.lower() == "n":
            pool_knight = self.FindKnight(prev_row, prev_col, row, col, piece_name)
            add_row = 0
            add_col = 0
            for pos in pool_knight:
                if pos[0] in range(8) and pos[1] in range(8) and self.board[pos[0]][pos[1]] == piece_name:
                    if pos[1] == prev_col:
                        add_col = 1
                    else:
                        add_row = 1
            if add_row == 1:
                move_played += self.pos_square[(prev_row, prev_col)][0]
            if add_col == 1:
                move_played += self.pos_square[(prev_row, prev_col)][1]
        elif piece_name.lower() == "b":
            pool_bishop = self.FindBishop(prev_row, prev_col, row, col, piece_name)
            if len(pool_bishop) == 1:
                if pool_bishop[0][1] == prev_col:
                    move_played += self.pos_square[(prev_row, prev_col)][1]
                else:
                    move_played += self.pos_square[(prev_row, prev_col)][0]
            elif len(pool_bishop) > 1:
                add_row = 0
                add_col = 0
                for pos in pool_bishop:
                    if pos[0] == prev_row:
                        add_row += 1
                    elif pos[1] == prev_col:
                        add_col += 1
                if add_row == 1:
                    move_played += self.pos_square[(prev_row, prev_col)][0]
                if add_col == 1:
                    move_played += self.pos_square[(prev_row, prev_col)][1]
                if add_row == 0 and add_col == 0:
                    move_played += self.pos_square[(prev_row, prev_col)][0]
        elif piece_name.lower() == "r":
            pool_rook = self.FindRook(prev_row, prev_col, row, col, piece_name)
            short_home_square = [(7, 7), (0, 7)]
            long_home_square = [(7, 0), (0, 0)]
            add_row = 0
            add_col = 0
            for pos in pool_rook:
                if pos[1] == prev_col:
                    add_col = 1
                else:
                    add_row = 1
            if add_col == 1:
                move_played += self.pos_square[(prev_row, prev_col)][1]
            elif add_row == 1:
                move_played += self.pos_square[(prev_row, prev_col)][0]
            if short_home_square[self.turn] == (prev_row, prev_col):
                self.rook_piece_short_moved[self.turn] = 1
            elif long_home_square[self.turn] == (prev_row, prev_col):
                self.rook_piece_long_moved[self.turn] = 1
        elif piece_name.lower() == "q":
            pool_bishop = self.FindBishop(prev_row, prev_col, row, col, piece_name)
            pool_rook = self.FindRook(prev_row, prev_col, row, col, piece_name)
            if len(pool_bishop) > 0:
                if len(pool_bishop) == 1:
                    if pool_bishop[0][1] == prev_col:
                        move_played += self.pos_square[(prev_row, prev_col)][1]
                    else:
                        move_played += self.pos_square[(prev_row, prev_col)][0]
                elif len(pool_bishop) > 1:
                    add_row = 0
                    add_col = 0
                    for pos in pool_bishop:
                        if pos[0] == prev_row:
                            add_row += 1
                        elif pos[1] == prev_col:
                            add_col += 1
                    if add_row == 1:
                        move_played += self.pos_square[(prev_row, prev_col)][0]
                    if add_col == 1:
                        move_played += self.pos_square[(prev_row, prev_col)][1]
                    if add_row == 0 and add_col == 0:
                        move_played += self.pos_square[(prev_row, prev_col)][0]
            elif len(pool_rook) > 0:
                add_row = 0
                add_col = 0
                for pos in pool_rook:
                    if pos[1] == prev_col:
                        add_col = 1
                    else:
                        add_row = 1
                if add_col == 1:
                    move_played += self.pos_square[(prev_row, prev_col)][1]
                elif add_row == 1:
                    move_played += self.pos_square[(prev_row, prev_col)][0]
        elif piece_name.lower() == "k":
            turn_rook = ["R", "r"]
            icon_rook_pixmap = [self.rook_R, self.rook_r]
            icon_rook = QIcon(icon_rook_pixmap[self.turn])
            if prev_col - col == 2 and col == 2:
                self.board[row][col+1] = turn_rook[self.turn]
                self.board[row][0] = "-"
                self.buttons[row][col+1].setIcon(icon_rook)
                self.buttons[row][0].setIcon(icon_blank)
                move_played = "O-O-O"
                castles = 1
            elif col - prev_col == 2 and col == 6:
                self.board[row][col-1] = turn_rook[self.turn]
                self.board[row][7] = "-"
                self.buttons[row][col-1].setIcon(icon_rook)
                self.buttons[row][7].setIcon(icon_blank)
                move_played = "O-O"
                castles = 1
            self.king_piece_pos[self.turn][0] = row
            self.king_piece_pos[self.turn][1] = col
            self.king_piece_moved[self.turn] = 1
        # Moving
        if self.board[row][col] != "-":
            move_played += "x"
            self.move_counter = 1
        elif self.board[row][col] == "-":
            self.move_counter += 1
        if castles == 0:
            move_played += self.pos_square[(row, col)]
        self.buttons[row][col].setIcon(icon_piece)
        self.buttons[prev_row][prev_col].setIcon(icon_blank)
        self.board[row][col] = self.board[prev_row][prev_col]
        self.board[prev_row][prev_col] = "-"
        is_mate = self.CheckIfMate()
        is_check = self.CheckIfCheck(self.king_piece_pos[1-self.turn][0], self.king_piece_pos[1-self.turn][1], self.turn)
        is_dead = self.CheckIfDead()
        # 50 Move Rule
        if self.move_counter == 50:
            self.moves_played.append(move_played)
            move_played = "1/2-1/2"
            self.game_end = 1
        # Stalemate
        elif is_check == False and is_mate == True:
            self.moves_played.append(move_played)
            move_played = "1/2-1/2"
            self.game_end = 1
        # Check and Dead Position
        elif is_check == True and is_dead == True:
            move_played += "+"
            self.moves_played.append(move_played)
            move_played = "1/2-1/2"
            self.game_end = 1
        # Dead position
        elif is_check == False and is_dead == True:
            self.moves_played.append(move_played)
            move_played = "1/2-1/2"
            self.game_end = 1
        # Checkmate
        elif is_check == True and is_mate == True:
            move_played += "#"
            self.game_end = 1
        # Check
        elif is_check == True and is_mate == False:
            move_played += "+"
        self.moves_played.append(move_played)

if __name__ == "__main__":
    app = QApplication([])
    window = Chess()
    window.show()
    app.exec_()
