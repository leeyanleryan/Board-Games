from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton, QLabel
from PyQt5.QtGui import QPixmap, QIcon, QPainter
from PyQt5.QtCore import QSize, QTimer, Qt
from time import *
import os

os.chdir("C:/Users/Admin/OneDrive/Projects/Chess/Pictures")

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        begin = time()
        self.players = ['White', 'Black']
        self.turn_pieces = [['P', 'N', 'B', 'R', 'Q', 'K'], ['p', 'n', 'b', 'r', 'q', 'k']]
        self.all_pieces = {'P':'Pawn', 'N':'Knight', 'B':'Bishop', 'R':'Rook', 'Q':'Queen', 'K':'King',
                           'p':'Pawn', 'n':'Knight', 'b':'Bishop', 'r':'Rook', 'q':'Queen', 'k':'King'}
        self.square_pos = {'a8':(0, 0), 'b8':(0, 1), 'c8':(0, 2), 'd8':(0, 3), 'e8':(0, 4), 'f8':(0, 5), 'g8':(0, 6), 'h8':(0, 7),
                           'a7':(1, 0), 'b7':(1, 1), 'c7':(1, 2), 'd7':(1, 3), 'e7':(1, 4), 'f7':(1, 5), 'g7':(1, 6), 'h7':(1, 7),
                           'a6':(2, 0), 'b6':(2, 1), 'c6':(2, 2), 'd6':(2, 3), 'e6':(2, 4), 'f6':(2, 5), 'g6':(2, 6), 'h6':(2, 7),
                           'a5':(3, 0), 'b5':(3, 1), 'c5':(3, 2), 'd5':(3, 3), 'e5':(3, 4), 'f5':(3, 5), 'g5':(3, 6), 'h5':(3, 7),
                           'a4':(4, 0), 'b4':(4, 1), 'c4':(4, 2), 'd4':(4, 3), 'e4':(4, 4), 'f4':(4, 5), 'g4':(4, 6), 'h4':(4, 7),
                           'a3':(5, 0), 'b3':(5, 1), 'c3':(5, 2), 'd3':(5, 3), 'e3':(5, 4), 'f3':(5, 5), 'g3':(5, 6), 'h3':(5, 7),
                           'a2':(6, 0), 'b2':(6, 1), 'c2':(6, 2), 'd2':(6, 3), 'e2':(6, 4), 'f2':(6, 5), 'g2':(6, 6), 'h2':(6, 7),
                           'a1':(7, 0), 'b1':(7, 1), 'c1':(7, 2), 'd1':(7, 3), 'e1':(7, 4), 'f1':(7, 5), 'g1':(7, 6), 'h1':(7, 7)}
        self.pos_square = dict((v, k) for k, v in self.square_pos.items())
        self.possible_pieces = ['a8', 'b8', 'c8', 'd8', 'e8', 'f8', 'g8', 'h8', 'a7', 'b7', 'c7', 'd7', 'e7', 'f7', 'g7', 'h7', 'a6', 'b6', 'c6', 'd6', 'e6', 'f6', 'g6', 'h6','a5', 'b5', 'c5', 'd5', 'e5', 'f5', 'g5', 'h5','a4', 'b4', 'c4', 'd4', 'e4', 'f4', 'g4', 'h4','a3', 'b3', 'c3', 'd3', 'e3', 'f3', 'g3', 'h3','a2', 'b2', 'c2', 'd2', 'e2', 'f2', 'g2', 'h2','a1', 'b1', 'c1', 'd1', 'e1', 'f1', 'g1', 'h1',
                                'Ra8', 'Rb8', 'Rc8', 'Rd8', 'Re8', 'Rf8', 'Rg8', 'Rh8', 'Ra7', 'Rb7', 'Rc7', 'Rd7', 'Re7', 'Rf7', 'Rg7', 'Rh7', 'Ra6', 'Rb6', 'Rc6', 'Rd6', 'Re6', 'Rf6', 'Rg6', 'Rh6', 'Ra5', 'Rb5', 'Rc5', 'Rd5', 'Re5', 'Rf5', 'Rg5', 'Rh5', 'Ra4', 'Rb4', 'Rc4', 'Rd4', 'Re4', 'Rf4', 'Rg4', 'Rh4', 'Ra3', 'Rb3', 'Rc3', 'Rd3', 'Re3', 'Rf3', 'Rg3', 'Rh3', 'Ra2', 'Rb2', 'Rc2', 'Rd2', 'Re2', 'Rf2', 'Rg2', 'Rh2', 'Ra1', 'Rb1', 'Rc1', 'Rd1', 'Re1', 'Rf1', 'Rg1', 'Rh1',
                                'Na8', 'Nb8', 'Nc8', 'Nd8', 'Ne8', 'Nf8', 'Ng8', 'Nh8', 'Na7', 'Nb7', 'Nc7', 'Nd7', 'Ne7', 'Nf7', 'Ng7', 'Nh7', 'Na6', 'Nb6', 'Nc6', 'Nd6', 'Ne6', 'Nf6', 'Ng6', 'Nh6', 'Na5', 'Nb5', 'Nc5', 'Nd5', 'Ne5', 'Nf5', 'Ng5', 'Nh5', 'Na4', 'Nb4', 'Nc4', 'Nd4', 'Ne4', 'Nf4', 'Ng4', 'Nh4', 'Na3', 'Nb3', 'Nc3', 'Nd3', 'Ne3', 'Nf3', 'Ng3', 'Nh3', 'Na2', 'Nb2', 'Nc2', 'Nd2', 'Ne2', 'Nf2', 'Ng2', 'Nh2', 'Na1', 'Nb1', 'Nc1', 'Nd1', 'Ne1', 'Nf1', 'Ng1', 'Nh1',
                                'Ba8', 'Bb8', 'Bc8', 'Bd8', 'Be8', 'Bf8', 'Bg8', 'Bh8', 'Ba7', 'Bb7', 'Bc7', 'Bd7', 'Be7', 'Bf7', 'Bg7', 'Bh7', 'Ba6', 'Bb6', 'Bc6', 'Bd6', 'Be6', 'Bf6', 'Bg6', 'Bh6', 'Ba5', 'Bb5', 'Bc5', 'Bd5', 'Be5', 'Bf5', 'Bg5', 'Bh5', 'Ba4', 'Bb4', 'Bc4', 'Bd4', 'Be4', 'Bf4', 'Bg4', 'Bh4', 'Ba3', 'Bb3', 'Bc3', 'Bd3', 'Be3', 'Bf3', 'Bg3', 'Bh3', 'Ba2', 'Bb2', 'Bc2', 'Bd2', 'Be2', 'Bf2', 'Bg2', 'Bh2', 'Ba1', 'Bb1', 'Bc1', 'Bd1', 'Be1', 'Bf1', 'Bg1', 'Bh1',
                                'Qa8', 'Qb8', 'Qc8', 'Qd8', 'Qe8', 'Qf8', 'Qg8', 'Qh8', 'Qa7', 'Qb7', 'Qc7', 'Qd7', 'Qe7', 'Qf7', 'Qg7', 'Qh7', 'Qa6', 'Qb6', 'Qc6', 'Qd6', 'Qe6', 'Qf6', 'Qg6', 'Qh6', 'Qa5', 'Qb5', 'Qc5', 'Qd5', 'Qe5', 'Qf5', 'Qg5', 'Qh5', 'Qa4', 'Qb4', 'Qc4', 'Qd4', 'Qe4', 'Qf4', 'Qg4', 'Qh4', 'Qa3', 'Qb3', 'Qc3', 'Qd3', 'Qe3', 'Qf3', 'Qg3', 'Qh3', 'Qa2', 'Qb2', 'Qc2', 'Qd2', 'Qe2', 'Qf2', 'Qg2', 'Qh2', 'Qa1', 'Qb1', 'Qc1', 'Qd1', 'Qe1', 'Qf1', 'Qg1', 'Qh1',
                                'Ka8', 'Kb8', 'Kc8', 'Kd8', 'Ke8', 'Kf8', 'Kg8', 'Kh8', 'Ka7', 'Kb7', 'Kc7', 'Kd7', 'Ke7', 'Kf7', 'Kg7', 'Kh7', 'Ka6', 'Kb6', 'Kc6', 'Kd6', 'Ke6', 'Kf6', 'Kg6', 'Kh6', 'Ka5', 'Kb5', 'Kc5', 'Kd5', 'Ke5', 'Kf5', 'Kg5', 'Kh5', 'Ka4', 'Kb4', 'Kc4', 'Kd4', 'Ke4', 'Kf4', 'Kg4', 'Kh4', 'Ka3', 'Kb3', 'Kc3', 'Kd3', 'Ke3', 'Kf3', 'Kg3', 'Kh3', 'Ka2', 'Kb2', 'Kc2', 'Kd2', 'Ke2', 'Kf2', 'Kg2', 'Kh2', 'Ka1', 'Kb1', 'Kc1', 'Kd1', 'Ke1', 'Kf1', 'Kg1', 'Kh1',
                                'ra8', 'rb8', 'rc8', 'rd8', 're8', 'rf8', 'rg8', 'rh8', 'ra7', 'rb7', 'rc7', 'rd7', 're7', 'rf7', 'rg7', 'rh7', 'ra6', 'rb6', 'rc6', 'rd6', 're6', 'rf6', 'rg6', 'rh6', 'ra5', 'rb5', 'rc5', 'rd5', 're5', 'rf5', 'rg5', 'rh5', 'ra4', 'rb4', 'rc4', 'rd4', 're4', 'rf4', 'rg4', 'rh4', 'ra3', 'rb3', 'rc3', 'rd3', 're3', 'rf3', 'rg3', 'rh3', 'ra2', 'rb2', 'rc2', 'rd2', 're2', 'rf2', 'rg2', 'rh2', 'ra1', 'rb1', 'rc1', 'rd1', 're1', 'rf1', 'rg1', 'rh1',
                                'na8', 'nb8', 'nc8', 'nd8', 'ne8', 'nf8', 'ng8', 'nh8', 'na7', 'nb7', 'nc7', 'nd7', 'ne7', 'nf7', 'ng7', 'nh7', 'na6', 'nb6', 'nc6', 'nd6', 'ne6', 'nf6', 'ng6', 'nh6', 'na5', 'nb5', 'nc5', 'nd5', 'ne5', 'nf5', 'ng5', 'nh5', 'na4', 'nb4', 'nc4', 'nd4', 'ne4', 'nf4', 'ng4', 'nh4', 'na3', 'nb3', 'nc3', 'nd3', 'ne3', 'nf3', 'ng3', 'nh3', 'na2', 'nb2', 'nc2', 'nd2', 'ne2', 'nf2', 'ng2', 'nh2', 'na1', 'nb1', 'nc1', 'nd1', 'ne1', 'nf1', 'ng1', 'nh1',
                                'ba8', 'bb8', 'bc8', 'bd8', 'be8', 'bf8', 'bg8', 'bh8', 'ba7', 'bb7', 'bc7', 'bd7', 'be7', 'bf7', 'bg7', 'bh7', 'ba6', 'bb6', 'bc6', 'bd6', 'be6', 'bf6', 'bg6', 'bh6', 'ba5', 'bb5', 'bc5', 'bd5', 'be5', 'bf5', 'bg5', 'bh5', 'ba4', 'bb4', 'bc4', 'bd4', 'be4', 'bf4', 'bg4', 'bh4', 'ba3', 'bb3', 'bc3', 'bd3', 'be3', 'bf3', 'bg3', 'bh3', 'ba2', 'bb2', 'bc2', 'bd2', 'be2', 'bf2', 'bg2', 'bh2', 'ba1', 'bb1', 'bc1', 'bd1', 'be1', 'bf1', 'bg1', 'bh1',
                                'qa8', 'qb8', 'qc8', 'qd8', 'qe8', 'qf8', 'qg8', 'qh8', 'qa7', 'qb7', 'qc7', 'qd7', 'qe7', 'qf7', 'qg7', 'qh7', 'qa6', 'qb6', 'qc6', 'qd6', 'qe6', 'qf6', 'qg6', 'qh6', 'qa5', 'qb5', 'qc5', 'qd5', 'qe5', 'qf5', 'qg5', 'qh5', 'qa4', 'qb4', 'qc4', 'qd4', 'qe4', 'qf4', 'qg4', 'qh4', 'qa3', 'qb3', 'qc3', 'qd3', 'qe3', 'qf3', 'qg3', 'qh3', 'qa2', 'qb2', 'qc2', 'qd2', 'qe2', 'qf2', 'qg2', 'qh2', 'qa1', 'qb1', 'qc1', 'qd1', 'qe1', 'qf1', 'qg1', 'qh1',
                                'ka8', 'kb8', 'kc8', 'kd8', 'ke8', 'kf8', 'kg8', 'kh8', 'ka7', 'kb7', 'kc7', 'kd7', 'ke7', 'kf7', 'kg7', 'kh7', 'ka6', 'kb6', 'kc6', 'kd6', 'ke6', 'kf6', 'kg6', 'kh6', 'ka5', 'kb5', 'kc5', 'kd5', 'ke5', 'kf5', 'kg5', 'kh5', 'ka4', 'kb4', 'kc4', 'kd4', 'ke4', 'kf4', 'kg4', 'kh4', 'ka3', 'kb3', 'kc3', 'kd3', 'ke3', 'kf3', 'kg3', 'kh3', 'ka2', 'kb2', 'kc2', 'kd2', 'ke2', 'kf2', 'kg2', 'kh2', 'ka1', 'kb1', 'kc1', 'kd1', 'ke1', 'kf1', 'kg1', 'kh1']
        self.turn = 0
        self.board = self.CreateBoard()
        # self.board = [['r','n','b','q','n','B','-','-'],
        #               ['p','k','p','p','p','p','-','-'],
        #               ['-','-','b','q','-','r','Q','-'],
        #               ['-','-','-','-','N','-','-','-'],
        #               ['-','-','K','-','-','-','-','-'],
        #               ['-','-','-','B','-','-','q','-'],
        #               ['P','P','P','P','P','P','-','-'],
        #               ['R','N','N','Q','N','b','B','-']]
        # self.board = [['r','n','b','q','n','B','-','-'],
        #               ['p','k','p','p','p','B','-','-'],
        #               ['B','-','b','q','-','r','Q','-'],
        #               ['-','-','-','-','N','-','-','-'],
        #               ['-','-','-','-','-','-','-','-'],
        #               ['-','-','K','B','-','-','q','-'],
        #               ['B','P','P','P','P','P','-','-'],
        #               ['R','N','N','Q','N','b','B','-']]
        # self.board = [['r','n','b','q','n','B','-','-'],
        #               ['p','k','p','p','p','B','-','-'],
        #               ['-','-','-','-','-','-','-','-'],
        #               ['-','-','-','R','-','-','-','-'],
        #               ['R','-','-','-','-','-','-','R'],
        #               ['-','-','-','-','R','-','-','-'],
        #               ['B','P','P','P','P','P','-','-'],
        #               ['R','N','N','Q','N','b','B','-']]
        # self.board = [['r','n','b','q','n','B','-','-'],
        #               ['p','k','p','p','p','B','-','-'],
        #               ['-','-','-','-','-','-','-','-'],
        #               ['-','-','-','Q','-','-','-','-'],
        #               ['Q','-','-','-','-','-','-','Q'],
        #               ['-','-','-','-','Q','-','-','-'],
        #               ['B','P','P','P','P','P','-','-'],
        #               ['R','N','N','Q','N','b','B','-']]
        # self.board = [['r','n','b','q','k','b','n','r'], 
        #               ['p','p','p','p','p','p','p','p'], 
        #               ['-','-','-','-','r','-','-','-'], 
        #               ['-','-','-','-','-','-','-','-'], 
        #               ['-','-','-','-','-','-','-','-'], 
        #               ['-','-','-','-','-','p','-','-'], 
        #               ['P','P','P','P','P','P','P','P'], 
        #               ['R','N','B','Q','K','B','N','R']]
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
        self.en_passant = 0
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
                    self.buttons[i][j].setStyleSheet('background-image: url(BoardWhite.png); border: 0')
                else:
                    self.buttons[i][j].setStyleSheet('background-image: url(BoardBlack.png); border: 0')
                icon = QIcon(self.piece_pixmap[self.board[i][j]])
                self.buttons[i][j].setIcon(icon)
                self.buttons[i][j].setIconSize(QSize(100, 100))
                self.buttons[i][j].clicked.connect(lambda checked, row=i, col=j: 
                                                   self.MakeMove(row, col))
        self.setLayout(self.grid)
        self.setWindowTitle('Chess')
        self.move(300, 100)
        print(f'\nMoves Played: {self.moves_played}\n')
        self.BoardPrint()
        print(f'\nTime taken: {time()-begin}s')

    def CreateBoard(self):
        board = [['-' for i in range(8)] for j in range(8)]
        for i in range(8):
            board[1][i] = 'p'
            board[6][i] = 'P'
        board[7] = ['R','N','B','Q','K','B','N','R']
        board[0] = list(map(lambda x: x.lower(), board[7]))
        return board

    def BoardPrint(self):
        board = self.board
        for i in range(8):
            print(f'{board[i][0]}|{board[i][1]}|{board[i][2]}|{board[i][3]}|{board[i][4]}|{board[i][5]}|{board[i][6]}|{board[i][7]} {8-i}')
        print('a b c d e f g h')

    def MakeMove(self, row, col):
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
            self.buttons[row][col].setStyleSheet('background-image: url(SelectedPiece.png); border: 0')
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
            self.buttons[row][col].setStyleSheet('background-image: url(SelectedPiece.png); border: 0')
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
                self.LegalPawnMovement(row, col)
            elif selected_piece.lower() == "n":
                self.LegalKnightMovement(row, col)
            elif selected_piece.lower() == "b":
                self.LegalBishopMovement(row, col)
            elif selected_piece.lower() == "r":
                self.LegalRookMovement(row, col)
            elif selected_piece.lower() == "q":
                self.LegalQueenMovement(row, col)
            elif selected_piece.lower() == "k":
                self.LegalKingMovement(row, col)
        # Make move
        if make_move == 1:
            if self.board[prev_row][prev_col].lower() == "p":
                self.MovePawn(prev_row, prev_col, row, col)
            else:
                self.MovePiece(prev_row, prev_col, row, col)
            print(f'\nMoves Played: {self.moves_played}\n')
            self.BoardPrint()
            self.en_passant = 0
            self.turn = 1 - self.turn
            print(f'\nTime taken: {time()-begin}s')

    def LegalPawnMovement(self, row, col):
        turn_factor = [-1, 1]
        home_row = [6, 1]
        icon = QIcon(self.legal_move)
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        # Cannot move forward if piece is in front
        if (self.board[row+1*(turn_factor[self.turn])][col] == "-" and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col, king_row, king_col) == False):
            self.buttons[row+1*(turn_factor[self.turn])][col].setIcon(icon)
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col))
        # Home square can move one extra
        if (row == home_row[self.turn] and self.board[row+2*(turn_factor[self.turn])][col] == "-" and
            self.board[row+1*(turn_factor[self.turn])][col] == "-" and
            self.CheckIfPinned(row, col, row+2*(turn_factor[self.turn]), col, king_row, king_col) == False):
            self.buttons[row+2*(turn_factor[self.turn])][col].setIcon(icon)
            self.legal_moves.append((row+2*(turn_factor[self.turn]), col))
        # Capture diagonally left
        if (col-1 in range(8) and self.board[row+1*(turn_factor[self.turn])][col-1] in self.turn_pieces[1-self.turn] and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col-1, king_row, king_col) == False):
            icon = QIcon(self.piece_capture_pixmap[self.board[row+1*(turn_factor[self.turn])][col-1]])
            self.buttons[row+1*(turn_factor[self.turn])][col-1].setIcon(icon)
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col-1))
            self.possible_captures.append((row+1*(turn_factor[self.turn]), col-1))
        # Capture diagonally right
        if (col+1 in range(8) and self.board[row+1*(turn_factor[self.turn])][col+1] in self.turn_pieces[1-self.turn] and
            self.CheckIfPinned(row, col, row+1*(turn_factor[self.turn]), col+1, king_row, king_col) == False):
            icon = QIcon(self.piece_capture_pixmap[self.board[row+1*(turn_factor[self.turn])][col+1]])
            self.buttons[row+1*(turn_factor[self.turn])][col+1].setIcon(icon)
            self.legal_moves.append((row+1*(turn_factor[self.turn]), col+1))
            self.possible_captures.append((row+1*(turn_factor[self.turn]), col+1))
        # En passant
        if (self.en_passant == 1):
            pass
            
    def LegalKnightMovement(self, row, col):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        pool = [(row-1, col-2), (row-2, col-1), (row-1, col+2), (row-2, col+1),
                (row+1, col-2), (row+2, col-1), (row+1, col+2), (row+2, col+1)]
        # Check all 8 possible spots
        for pos in pool:
            if pos[0] in range(8) and pos[1] in range(8):
                if self.CheckIfPinned(row, col, pos[0], pos[1], king_row, king_col) == False:
                    if self.board[pos[0]][pos[1]] == "-":
                        icon = QIcon(self.legal_move)
                        self.buttons[pos[0]][pos[1]].setIcon(icon)
                        self.legal_moves.append((pos[0], pos[1]))
                    elif self.board[pos[0]][pos[1]] in self.turn_pieces[1-self.turn]:
                        icon = QIcon(self.piece_capture_pixmap[self.board[pos[0]][pos[1]]])
                        self.buttons[pos[0]][pos[1]].setIcon(icon)
                        self.legal_moves.append((pos[0], pos[1]))
                        self.possible_captures.append((pos[0], pos[1]))

    def LegalBishopMovement(self, row, col):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        # Top Left
        check_row = row - 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row -= 1
            check_col -= 1
        # Top Right
        check_row = row - 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row -= 1
            check_col += 1
        # Bottom Left
        check_row = row + 1
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row += 1
            check_col -= 1
        # Bottom Right
        check_row = row + 1
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row += 1
            check_col += 1

    def LegalRookMovement(self, row, col):
        king_row = self.king_piece_pos[self.turn][0]
        king_col = self.king_piece_pos[self.turn][1]
        check_row = row - 1
        check_col = col
        # Up
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row -= 1
        # Down
        check_row = row + 1
        check_col = col
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_row += 1
        # Left
        check_row = row
        check_col = col - 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_col -= 1
        # Right
        check_row = row
        check_col = col + 1
        while check_row in range(8) and check_col in range(8):
            if self.CheckIfPinned(row, col, check_row, check_col, king_row, king_col) == False:
                if self.board[check_row][check_col] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                elif self.board[check_row][check_col] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[check_row][check_col]])
                    self.buttons[check_row][check_col].setIcon(icon)
                    self.legal_moves.append((check_row, check_col))
                    self.possible_captures.append((check_row, check_col))
                    break
                else:
                    break
            check_col += 1

    def LegalQueenMovement(self, row, col):
        self.LegalBishopMovement(row, col)
        self.LegalRookMovement(row, col)

    def LegalKingMovement(self, row, col):
        pool = [(row-1, col-1), (row-1, col), (row-1, col+1),
                (row, col-1),                   (row, col+1),
                (row+1, col-1), (row+1, col), (row+1, col+1)]
        for pos in pool:
            if pos[0] in range(8) and pos[1] in range(8):
                if self.board[pos[0]][pos[1]] == "-":
                    icon = QIcon(self.legal_move)
                    self.buttons[pos[0]][pos[1]].setIcon(icon)
                    self.legal_moves.append((pos[0], pos[1]))
                elif self.board[pos[0]][pos[1]] in self.turn_pieces[1-self.turn]:
                    icon = QIcon(self.piece_capture_pixmap[self.board[pos[0]][pos[1]]])
                    self.buttons[pos[0]][pos[1]].setIcon(icon)
                    self.legal_moves.append((pos[0], pos[1]))
                    self.possible_captures.append((pos[0], pos[1]))
        # Short Castles
        icon = QIcon(self.legal_move)
        turn_row = [7, 0]
        if self.king_piece_moved[self.turn] == 0 and self.rook_piece_short_moved[self.turn] == 0:
            if "".join(self.board[turn_row[self.turn]][5:7]) == "--":
                self.buttons[turn_row[self.turn]][6].setIcon(icon)
                self.legal_moves.append((turn_row[self.turn], 6))
        # Long Castles
        if self.king_piece_moved[self.turn] == 0 and self.rook_piece_long_moved[self.turn] == 0:
            if "".join(self.board[turn_row[self.turn]][1:4]) == "---":
                self.buttons[turn_row[self.turn]][2].setIcon(icon)
                self.legal_moves.append((turn_row[self.turn], 2))

    def MovePawn(self, prev_row, prev_col, row, col):
        move_played = ""
        prev_square = self.pos_square[(prev_row, prev_col)]
        new_square = self.pos_square[(row, col)]
        end_squares = [0, 7]
        pawn_pixmap = [self.pawn_P, self.pawn_p]
        promo_piece_pixmap = [self.queen_Q, self.queen_q]
        promo_piece = ["Q", "q"]
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
        # promote: no, capture: yes
        elif self.board[row][col] != "-":
            icon = QIcon(pawn_pixmap[self.turn])
            self.board[row][col] = self.board[prev_row][prev_col]
            move_played = f"{prev_square[0]}x{new_square}"
        # promote: no, capture: no
        else:
            icon = QIcon(pawn_pixmap[self.turn])
            self.board[row][col] = self.board[prev_row][prev_col]
            move_played = f"{new_square}"
        # check en passant rule
        if row - prev_row == 2:
            self.en_passant = 1
        self.buttons[row][col].setIcon(icon)
        self.buttons[prev_row][prev_col].setIcon(icon_blank)
        self.board[prev_row][prev_col] = "-"
        if self.CheckIfCheck(self.king_piece_pos[1-self.turn][0], self.king_piece_pos[1-self.turn][1], self.turn) == 1:
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
            # Check all 8 except knight original pos
            for pos in pool_knight:
                if pos[0] in range(8) and pos[1] in range(8) and self.board[pos[0]][pos[1]] == piece_name:
                    if pos[0] == prev_row:
                        add_row = 1
                    elif pos[1] == prev_col:
                        add_col = 1
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
                self.buttons[row][col+1].setIcon(icon_rook)
                self.buttons[row][0].setIcon(icon_blank)
                move_played = "O-O-O"
                castles = 1
            elif col - prev_col == 2 and col == 6:
                self.board[row][col-1] = turn_rook[self.turn]
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
        if castles == 0:
            move_played += self.pos_square[(row, col)]
        self.buttons[row][col].setIcon(icon_piece)
        self.buttons[prev_row][prev_col].setIcon(icon_blank)
        self.board[row][col] = self.board[prev_row][prev_col]
        self.board[prev_row][prev_col] = "-"
        if self.CheckIfCheck(self.king_piece_pos[1-self.turn][0], self.king_piece_pos[1-self.turn][1], self.turn) == 1:
            move_played += "+"
        self.moves_played.append(move_played)

    def FindPawn(self, prev_row, prev_col, row, col, piece_name):
        pool_pawn = []
        return pool_pawn

    def FindKnight(self, prev_row, prev_col, row, col, piece_name):
        pool_knight = []
        pool_pos = [(-1, -2), (-2, -1), (-1, 2), (-2, 1),
                    (1, -2), (2, -1), (1, 2), (2, 1)]
        for pos in pool_pos:
            check_row = row + pos[0]
            check_col = col + pos[1]
            if check_row in range(8) and check_col in range(8) and self.board[check_row][check_col] == piece_name:
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
        pool_pawn = self.FindPawn(-1, -1, king_row, king_col, self.turn_pieces[turn][0])
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

if __name__ == '__main__':
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()
