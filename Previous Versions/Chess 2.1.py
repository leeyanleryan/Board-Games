players = ['White','Black']

turn_pieces = [['R','N','B','Q','K','P'],['r','n','b','q','k','p']]

all_pieces = {'R':'Rook','N':'Knight','B':'Bishop','Q':'Queen','K':'King','P':'Pawn',
              'r':'Rook','n':'Knight','b':'Bishop','q':'Queen','k':'King','p':'Pawn'}

all_pieces_flipped = {'Rook':('R','r'),'Knight':('N','n'),'Bishop':('B','b'),'Queen':('Q','q'),'King':('K','k'),'Pawn':('P','p')}

squares = {'a8':(0,0),'b8':(0,1),'c8':(0,2),'d8':(0,3),'e8':(0,4),'f8':(0,5),'g8':(0,6),'h8':(0,7),
           'a7':(1,0),'b7':(1,1),'c7':(1,2),'d7':(1,3),'e7':(1,4),'f7':(1,5),'g7':(1,6),'h7':(1,7),
           'a6':(2,0),'b6':(2,1),'c6':(2,2),'d6':(2,3),'e6':(2,4),'f6':(2,5),'g6':(2,6),'h6':(2,7),
           'a5':(3,0),'b5':(3,1),'c5':(3,2),'d5':(3,3),'e5':(3,4),'f5':(3,5),'g5':(3,6),'h5':(3,7),
           'a4':(4,0),'b4':(4,1),'c4':(4,2),'d4':(4,3),'e4':(4,4),'f4':(4,5),'g4':(4,6),'h4':(4,7),
           'a3':(5,0),'b3':(5,1),'c3':(5,2),'d3':(5,3),'e3':(5,4),'f3':(5,5),'g3':(5,6),'h3':(5,7),
           'a2':(6,0),'b2':(6,1),'c2':(6,2),'d2':(6,3),'e2':(6,4),'f2':(6,5),'g2':(6,6),'h2':(6,7),
           'a1':(7,0),'b1':(7,1),'c1':(7,2),'d1':(7,3),'e1':(7,4),'f1':(7,5),'g1':(7,6),'h1':(7,7)}

possible_pieces = ['a8', 'b8', 'c8', 'd8', 'e8', 'f8', 'g8', 'h8','a7', 'b7', 'c7', 'd7', 'e7', 'f7', 'g7', 'h7','a6', 'b6', 'c6', 'd6', 'e6', 'f6', 'g6', 'h6','a5', 'b5', 'c5', 'd5', 'e5', 'f5', 'g5', 'h5','a4', 'b4', 'c4', 'd4', 'e4', 'f4', 'g4', 'h4','a3', 'b3', 'c3', 'd3', 'e3', 'f3', 'g3', 'h3','a2', 'b2', 'c2', 'd2', 'e2', 'f2', 'g2', 'h2','a1', 'b1', 'c1', 'd1', 'e1', 'f1', 'g1', 'h1',
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

possible_events = {'none':'', '+':'Check! ', '#':'Checkmate! ', '1/2-1/2':'Draw.', '1/2+1/2':'Stalemate.'}

def ZeroMatrix(r,c):
    return [['-' for i in range(c)] for j in range(r)]

def CreateGame():
    game = ZeroMatrix(8,8)
    for i in range(8):
        game[1][i] = 'p'
        game[6][i] = 'P'
    game[7] = ['R','N','B','Q','K','B','N','R']
    game[0] = list(map(lambda x: x.lower(),game[7]))
    return game

def StartingItems():
    return 0, -1, '', [], 'none', [0,0], [0,0], [0,0]

def Options():
    print('Welcome to Chess!\n\nType "Play" to start a new game.\nType "Notations" to see the different kinds of moves.\nType "Exit" to stop playing.')
    possible_choices = ['Play','Notations','Exit']
    choice = input("\nPlease enter an option: ")
    while choice not in possible_choices:
        choice = input("Please enter a valid option: ")
    if choice == 'Play':
        return PlayChess()
    elif choice == 'Notations':
        return ChessNotations()
    elif choice == 'Exit':
        return None

def ChessNotations():
    print('\nSome examples of notations in chess are:\nd4, exd5, Nf3, O-O, Qb7#, Bc5+, b8=Q#, etc.\n\nHowever, the notations used in this version are slightly different.\n\nYou will be presented with two texts.\nChoose a piece:\nMove to:')
    print('\nFor the first line, you are choosing a piece to move.\nSome examples are Ng1, e2, ra8, ke8, Bc1, etc.')
    print('\nFor the second line, you are choosing the place for the piece to move to.\nSome examples are e4, h8, a1, b5, c2, etc.')
    print('\nYou do not need to indicate if you are capturing, giving a check, etc.\nThose are automatically accounted for.')
    print('\nFor Castling, you choose the King, then the spot it will move to after castling.\nFor example, Ke1 g1 will do short castles O-O.')
    print('\nType "More" to see all possible notations.')
    print('Type "Back" to go back.')
    possible_choices = ['More','Back']
    choice = input('\nPlease enter an option: ')
    while choice not in possible_choices:
        choice = input('\nPlease enter a valid option: ')
    print("")
    if choice == 'More':
        print(f'Choose a piece: {possible_pieces}')
        print(f'\nMove to: {list(squares.keys())}')
        choice = input('\nType "Back" to go back: ')
        while choice not in ['Back']:
            choice = input('Type "Back" to go back: ')
        ChessNotations()
    else:
        Options()

def BoardPrint(game):
    for i in range(8):
        print(f'{game[i][0]}|{game[i][1]}|{game[i][2]}|{game[i][3]}|{game[i][4]}|{game[i][5]}|{game[i][6]}|{game[i][7]} {8-i}')
    print('a b c d e f g h')

def CheckEvent(event,players,turn):
    if event == '+':
        print(f'\n{possible_events[event]}{players[turn]} to move.')
        return 0
    elif event == '#':
        print(f'\n{possible_events[event]}{players[1-turn]} wins!')
        return 1
    elif event == '1/2-1/2':
        print(f'\n{possible_events[event]}')
        return 1
    else:
        print(f'\n{possible_events[event]}{players[turn]} to move.')
        return 0

def GetPieceAndMove():
    piece = input("Choose a piece: ")
    if piece == "Undo":
        return piece, move, 1, 0
    while piece not in possible_pieces:
        piece = input("Choose a piece: ")
        if piece == "Undo":
            return piece, move, 1, 0
    move = input("Move to: ")
    if move == "Redo":
        return piece, move, 0, 1
    while move not in squares.keys():
        move = input("Move to: ")
        if move == "Redo":
            return piece, move, 0, 1
    return piece, move, 0, 0

def MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,capture,promo,movesplayed):
    if game[r_move][c_move] == turn_pieces[1-turn][-2]:
        print("\nIllegal move. The King cannot be eaten.")
        return turn
    game[r_piece][c_piece] = '-'
    game[r_move][c_move] = pawn
    if capture == 0 and promo == 0:
        movesplayed.append(move)
    elif capture == 1 and promo == 0:
        movesplayed.append(f'{piece[0]}x{move}')
    elif capture == 0 and promo == 1:
        movesplayed.append(f'{move}={pawn}')
    elif capture == 1 and promo == 1:
        movesplayed.append(f'{piece[0]}x{move}={promo}')
    turn = 1 - turn
    return turn

def PawnMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,en_passant,ep_square,movesplayed):
    starting_square, negative_side = [6,1], [1,-1]
    side, other_side = negative_side[turn], negative_side[1-turn]
    pawn, other_pawn = all_pieces_flipped['Pawn'][turn], all_pieces_flipped['Pawn'][1-turn]
    if c_piece - c_move == 0:
        if side*(r_piece - r_move) > 2:
            print("\nIllegal move. Pawns can't move more than two squares even if starting at home square.")
        elif side*(r_piece - r_move) < 0:
            print("\nIllegal move. Pawns can't move backwards.")
        elif r_piece == starting_square[turn]:
            if side*(r_piece - r_move) == 2:
                if game[r_piece+(1*other_side)][c_piece] != '-' or game[r_move][c_move] != '-':
                    print(f'\nIllegal move. There is a piece blocking the way.')
                else:
                    turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,0,0,movesplayed)
                    if (c_move-1 < 0 and game[r_move][c_move+1] == other_pawn) or (c_move+1 > 7 and game[r_move][c_move-1] == other_pawn):
                        en_passant = c_move
                        ep_square = move
                    elif 0 < c_move < 7 and (game[r_move][c_move+1] == other_pawn or game[r_move][c_move-1] == other_pawn):
                        en_passant = c_move
                        ep_square = move
            if side*(r_piece - r_move) == 1:
                if game[r_move][c_move] != '-':
                    print(f'\nIllegal move. There is a piece blocking the way.')
                else:
                    turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,0,0,movesplayed)
        elif r_piece != starting_square[turn]:
            if game[r_move][c_move] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
            else:
                if r_move == starting_square[1-turn]-(1*side):
                    promo = input("Promote to: ")
                    while promo not in turn_pieces[turn] or promo == turn_pieces[turn][-2] or promo == turn_pieces[turn][-1]:
                        promo = input("Promote to: ")
                    turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,promo,0,1,movesplayed)
                else:
                    turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,0,0,movesplayed)
    else:
        if side*(r_piece - r_move) < 0:
            print("\nIllegal move. Pawns can't move backwards.")
        elif side*(r_piece - r_move) == 0 and abs(c_piece - c_move) >= 1:
            print(f'\nIllegal move. Pawns cannot move sideways.')
        elif en_passant != -1 and c_move == en_passant and game[r_move+(1*side)][c_move] == other_pawn:
            if movesplayed[-1] != ep_square:
                print(f'\nIllegal move. The window for En Passant has ended.')
            elif movesplayed.count(ep_square) > 1:
                print(f'\nIllegal move. Cannot En Passant a pawn that moved one square.')
            else:
                turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,1,0,movesplayed)
                game[r_move+(1*side)][c_move] = '-'
            en_passant = -1
            ep_square = ''
        elif game[r_move][c_move] == '-':
            print(f'\nIllegal move. There is no piece to capture.')
        elif r_move == starting_square[1-turn]-(1*side) and game[r_move][c_move] in turn_pieces[1-turn] and game[r_move][c_move] != turn_pieces[1-turn][-2]:
            promo = input("Promote to: ")
            while promo not in turn_pieces[turn] or promo == turn_pieces[turn][-2] or promo == turn_pieces[turn][-1]:
                promo = input("Promote to: ")
            turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,promo,1,1,movesplayed)
        elif game[r_move][c_move] in turn_pieces[turn]:
            print(f'\nIllegal move. Cannot capture own piece.')
        elif game[r_move][c_move] in turn_pieces[1-turn]:
            turn = MovePawn(game,turn,piece,r_piece,c_piece,move,r_move,c_move,pawn,1,0,movesplayed)
    return turn, en_passant, ep_square

def MovePiece(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
    if game[r_move][c_move] == '-':
        game[r_piece][c_piece] = '-'
        game[r_move][c_move] = piece[0]
        movesplayed.append(f'{piece[0]}{move}')
        turn = 1 - turn
    elif game[r_move][c_move] in turn_pieces[turn]:
        print(f'\nIllegal move. Cannot capture own piece.')
    elif game[r_move][c_move] == turn_pieces[1-turn][-2]:
        print("\nIllegal move. The King cannot be eaten.")
        return turn
    elif game[r_move][c_move] in turn_pieces[1-turn]:
        game[r_piece][c_piece] = '-'
        game[r_move][c_move] = piece[0]
        movesplayed.append(f'{piece[0]}x{move}')
        turn = 1 - turn
    return turn

def LegalBishopMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
    if r_move - r_piece == c_move - c_piece and r_move - r_piece < 0:
        for i in range(1,abs(r_move - r_piece)):
            if game[r_piece-i][c_piece-i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece == c_move - c_piece and r_move - r_piece > 0:
        for i in range(1,abs(r_move - r_piece)):
            if game[r_piece+i][c_piece+i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece == -(c_move - c_piece) and r_move - r_piece < 0:
        for i in range(1,abs(r_move - r_piece)):
            if game[r_piece-i][c_piece+i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece == -(c_move - c_piece) and r_move - r_piece > 0:
        for i in range(1,abs(r_move - r_piece)):
            if game[r_piece+i][c_piece-i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    else:
        print(f'\nIllegal move. The {all_pieces[piece[0]]} cannot move like that.')
        return 0
    return 1

def LegalRookMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
    if r_move - r_piece != 0 and c_move - c_piece == 0 and r_move - r_piece < 0:
        for i in range(1,max(abs(r_move - r_piece),abs(c_move - c_piece))):
            if game[r_piece-i][c_piece] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece != 0 and c_move - c_piece == 0 and r_move - r_piece > 0:
        for i in range(1,max(abs(r_move - r_piece),abs(c_move - c_piece))):
            if game[r_piece+i][c_piece] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece == 0 and c_move - c_piece != 0 and c_move - c_piece < 0:
        for i in range(1,max(abs(r_move - r_piece),abs(c_move - c_piece))):
            if game[r_piece][c_piece-i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    elif r_move - r_piece == 0 and c_move - c_piece != 0 and c_move - c_piece > 0:
        for i in range(1,max(abs(r_move - r_piece),abs(c_move - c_piece))):
            if game[r_piece][c_piece+i] != '-':
                print(f'\nIllegal move. There is a piece blocking the way.')
                return 0
    else:
        print(f'\nIllegal move. The {all_pieces[piece[0]]} cannot move like that.')
        return 0
    return 1

def KnightMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
    if (abs(r_move-r_piece) == 2 and abs(c_move-c_piece) == 1) or (abs(r_move-r_piece) == 1 and abs(c_move-c_piece) == 2):
        turn = MovePiece(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
    else:
        print(f'\nIllegal move. The {all_pieces[piece[0]]} cannot move like that.')
    return turn

def BishopMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
    if LegalBishopMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed) == 1:
        turn = MovePiece(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
    return turn

def RookMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,rook1moves,rook2moves,movesplayed):
    rook1, rook2 = ['a1','a8'], ['h1','h8']
    if LegalRookMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed) == 1:
        turn = MovePiece(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
        if game[squares[rook1[turn]][0]][squares[rook1[turn]][1]] != turn_pieces[turn][0]:
            rook1moves[turn] = 1
        elif game[squares[rook2[turn]][0]][squares[rook2[turn]][1]] != turn_pieces[turn][0]:
            rook2moves[turn] = 1
    return turn, rook1moves, rook2moves

def QueenMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,rook1moves,rook2moves,movesplayed):
    if (r_move - r_piece == 0 and c_move - c_piece != 0) or (r_move - r_piece != 0 and c_move - c_piece == 0):
        turn, rook1moves, rook2moves = RookMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,rook1moves,rook2moves,movesplayed)
    elif abs(r_move - r_piece) == abs(c_move - c_piece):
        turn = BishopMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
    else:
        print(f'\nIllegal move. The {all_pieces[piece[0]]} cannot move like that.')
    return turn

def KingMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,kingmoves,rook1moves,rook2moves,movesplayed):
    side, rook1, rook2 = [7,0], ['a1','a8'], ['h1','h8']
    if r_move - r_piece >= -1 and r_move - r_piece <= 1 and c_move - c_piece >= -1 and c_move - c_piece <= 1:
        kingmoves[turn] = 1
        turn = MovePiece(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
    elif r_move - r_piece == 0 and c_move - c_piece == 2:
        if game[side[turn]][4] != all_pieces_flipped['King'][turn]:
            print(f'\nIllegal move. The King cannot move like that.')
        elif kingmoves[turn] != 0:
            print(f'\nIllegal move. The King has already moved.')
        elif rook2moves[turn] != 0:
            print(f'\nIllegal move. The Rook has already moved.')
        elif game[r_piece][c_piece+3] != all_pieces_flipped['Rook'][turn]:
            print(f'\nIllegal move. Cannot castle as there is no Rook on {rook2[turn]}.')
        elif kingmoves[turn] == 0 and rook2moves[turn] == 0 and game[r_piece][c_piece+1] == '-' and game[r_piece][c_piece+2] == '-' and game[r_piece][c_piece+3] == all_pieces_flipped['Rook'][turn]:
            game[r_piece][c_piece] = '-'
            game[r_piece][c_piece+3] = '-'
            game[r_move][c_move] = piece[0]
            game[r_move][c_move-1] = all_pieces_flipped['Rook'][turn]
            movesplayed.append('O-O')
            turn = 1 - turn
        else:
            print(f'\nIllegal move. Cannot castle as there are pieces in the way, and/or there is no Rook on {rook2[turn]}.')
    elif r_move - r_piece == 0 and c_move - c_piece == -2:
        if game[side[turn]][4] != all_pieces_flipped['King'][turn]:
            print(f'\nIllegal move. The King cannot move like that.')
        elif kingmoves[turn] != 0:
            print(f'\nIllegal move. The King has already moved.')
        elif rook1moves[turn] != 0:
            print(f'\nIllegal move. The Rook has already moved.')
        elif game[r_piece][c_piece-4] != all_pieces_flipped['Rook'][turn]:
            print(f'\nIllegal move. Cannot castle as there is no Rook on {rook1[turn]}.')
        elif kingmoves[turn] == 0 and rook1moves[turn] == 0 and game[r_piece][c_piece-1] == '-' and game[r_piece][c_piece-2] == '-' and game[r_piece][c_piece-3] == '-' and game[r_piece][c_piece-4] == all_pieces_flipped['Rook'][turn]:
            game[r_piece][c_piece] = '-'
            game[r_piece][c_piece-4] = '-'
            game[r_move][c_move] = piece[0]
            game[r_move][c_move+1] = all_pieces_flipped['Rook'][turn]
            movesplayed.append('O-O-O')
            turn = 1 - turn
        else:
            print(f'\nIllegal move. Cannot castle as there are pieces in the way, and/or there is no Rook on {rook1[turn]}')
    else:
        print(f'\nIllegal move. The {all_pieces[piece[0]]} cannot move like that.')
    return turn, kingmoves

def OwnKingInCheck(game):
    pass

def CheckEnemyKing(game):
    pass

def PlayChess():
    game = CreateGame()
    turn, en_passant, ep_square, movesplayed, event, kingmoves, rook1moves, rook2moves = StartingItems()
    while True:
        print(f'\nMoves Played: {movesplayed}\n')
        BoardPrint(game)
        if CheckEvent(event,players,turn) == 1:
            break
        piece, move, undo, redo = GetPieceAndMove()
        if undo == 1:
            continue
        if redo == 1:
            continue
        r_move = squares[move][0]
        c_move = squares[move][1]
        if len(piece) == 2: # ------------- PAWN MOVEMENT ------------- #
                r_piece = squares[piece][0]
                c_piece = squares[piece][1]
                if r_move - r_piece == 0 and c_move - c_piece == 0:
                    print(f'\nNo movement made.')
                    continue
                if game[r_piece][c_piece] not in turn_pieces[turn]:
                    print(f'\nThere is no pawn on {piece}. Please try again.')
                    continue
                turn, en_passant, ep_square = PawnMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,en_passant,ep_square,movesplayed)
        elif len(piece) == 3: # ------------- PIECE MOVEMENT ------------- #
            r_piece = squares[piece[1:]][0]
            c_piece = squares[piece[1:]][1]
            if r_move - r_piece == 0 and c_move - c_piece == 0:
                print(f'\nNo movement made.')
                continue
            if piece[0] not in turn_pieces[turn]:
                print(f'\nThere is no such piece on {piece[1:]}. Please try again.')
                continue
            elif piece[0] in turn_pieces[turn] and game[r_piece][c_piece] != piece[0]:
                print(f'\nThere is no {all_pieces[piece[0]]} on {piece[1:]}. Please try again.')
                continue
            elif piece[0] == turn_pieces[turn][0]: # ------------- ROOK MOVEMENT ------------- #
                turn,rook1moves,rook2moves = RookMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,rook1moves,rook2moves,movesplayed)
            elif piece[0] == turn_pieces[turn][1]: # ------------- KNIGHT MOVEMENT ------------- #
                turn = KnightMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
            elif piece[0] == turn_pieces[turn][2]: # ------------- BISHOP MOVEMENT ------------- #
                turn = BishopMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed)
            elif piece[0] == turn_pieces[turn][3]: # ------------- QUEEN MOVEMENT ------------- #
                turn = QueenMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,rook1moves,rook2moves,movesplayed)
            elif piece[0] == turn_pieces[turn][4]: # ------------- KING MOVEMENT ------------- #
                turn,kingmoves = KingMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,kingmoves,rook1moves,rook2moves,movesplayed)
                    
Options()
