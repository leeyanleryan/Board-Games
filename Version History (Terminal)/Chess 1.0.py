players = ['White','Black']
pieces = ['R','N','B','Q','K']
all_pieces = ['R','N','B','Q','K','P','r','n','b','q','k','p']
squares = {'a8':(0,0),'b8':(0,1),'c8':(0,2),'d8':(0,3),'e8':(0,4),'f8':(0,5),'g8':(0,6),'h8':(0,7),
           'a7':(1,0),'b7':(1,1),'c7':(1,2),'d7':(1,3),'e7':(1,4),'f7':(1,5),'g7':(1,6),'h7':(1,7),
           'a6':(2,0),'b6':(2,1),'c6':(2,2),'d6':(2,3),'e6':(2,4),'f6':(2,5),'g6':(2,6),'h6':(2,7),
           'a5':(3,0),'b5':(3,1),'c5':(3,2),'d5':(3,3),'e5':(3,4),'f5':(3,5),'g5':(3,6),'h5':(3,7),
           'a4':(4,0),'b4':(4,1),'c4':(4,2),'d4':(4,3),'e4':(4,4),'f4':(4,5),'g4':(4,6),'h4':(4,7),
           'a3':(5,0),'b3':(5,1),'c3':(5,2),'d3':(5,3),'e3':(5,4),'f3':(5,5),'g3':(5,6),'h3':(5,7),
           'a2':(6,0),'b2':(6,1),'c2':(6,2),'d2':(6,3),'e2':(6,4),'f2':(6,5),'g2':(6,6),'h2':(6,7),
           'a1':(7,0),'b1':(7,1),'c1':(7,2),'d1':(7,3),'e1':(7,4),'f1':(7,5),'g1':(7,6),'h1':(7,7)}
            
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

def BoardPrint(game):
    for i in range(len(game)):
        line = ''
        for j in range(len(game[0])):
            line += str(game[i][j])
        print(line)

def BoardTranspose(game):
    T = ZeroMatrix(8,8)
    for i in range(len(game)):
        for j in range(len(game[0])):
            T[j][i] = game[i][j]
    return T

def ChessNotations():
    pass

def LegalRookMove(game,old_pos,new_pos):
    pass

def LegalKnightMove(game,old_pos,new_pos):
    pass

def LegalBishopMove(game,old_pos,new_pos):
    pass

def LegalQueenMove(game,old_pos,new_pos):
    pass

def LegalKingMove(game,old_pos,new_pos):
    pass

def LegalPawnMove(game,old_pos,new_pos):
    pass

def MoveType(move):
    pass

def PlayChess():
    game = CreateGame()
    turn = 0
    movesplayed = []
    print("Welcome to Chess!")
    while True:
        print("")
        print(f'Moves Played: {movesplayed}\n')
        BoardPrint(game)
        move = input(f'\n{players[turn]} to move: ')
        if move == 'Restart':
            print("")
            PlayChess()
        if turn == 0:
            if move[:2] in squares.keys(): # -------------------- PAWN MOVEMENT WHITE -------------------- #
                if '+' not in move and '=' not in move and '#' not in move:
                    gameT = BoardTranspose(game)
                    try:
                        pos = gameT[squares[move][1]].index('P')
                    except ValueError:
                        print("\nThere is no pawn to move. Please try again.")
                        continue
                    if game[squares[move][0]][squares[move][1]] != '-':
                        print("\nIllegal move. Please make a different move.")
                        continue
                    if pos == 6:
                        if pos - squares[move][0] > 2:
                            print("\nIllegal move. Pawn can't move more than two squares even if starting at home square.")
                            continue
                        elif pos - squares[move][0] == 0:
                            print("\nPlease try again.")
                            continue
                        elif pos - squares[move][0] < 0:
                            print("\nIllegal move. Pawns can't move backwards.")
                            continue
                        else:
                            game[pos][squares[move][1]] = '-'
                            game[squares[move][0]][squares[move][1]] = 'P'
                            movesplayed.append(move)
                            turn = 1 - turn
                            continue
                    else:
                        if pos - squares[move][0] > 1:
                            print("\nIllegal move. Pawn can't move more than one square forward after leaving home square.")
                            continue
                        elif pos - squares[move][0] == 0:
                            print("\nPlease try again.")
                            continue
                        elif pos - squares[move][0] < 0:
                            print("\nIllegal move. Pawns can't move backwards.")
                            continue
                        else:
                            game[pos][squares[move][1]] = '-'
                            game[squares[move][0]][squares[move][1]] = 'P'
                            movesplayed.append(move)
                            turn = 1 - turn
                            continue # -------------------- END OF PAWN MOVEMENT WHITE -------------------- #
            elif move[0] == 'R': # -------------------- ROOK MOVEMENT WHITE -------------------- #
                if move[1:3] in squares.keys():
                    if '+' not in move and '#' not in move:
                        pass
            elif 'x' in move: # -------------------- PAWN CAPTURE WHITE -------------------- #
                if '+' not in move and '#' not in move and '=' not in move:
                    if move[0] not in pieces:
                        if game[squares[move[2:]][0]][squares[move[2:]][1]] == '-':
                            print("\nIllegal move. There is nothing to capture.")
                            continue
                        elif game[squares[move[2:]][0]][squares[move[2:]][1]] in pieces:
                            print("\nThat is not an enemy piece. Please try again.")
                            continue
                        else:
                            current_pos = move[0]+str(int(move[-1])-1)
                            if game[squares[current_pos][0]][squares[current_pos][1]] != 'P':
                                print(f"\nIllegal move. There is no pawn on {current_pos}.")
                                continue
                            else:
                                game[squares[current_pos][0]][squares[current_pos][1]] = '-'
                                game[squares[move[2:]][0]][squares[move[2:]][1]] = 'P'
                                movesplayed.append(move)
                                turn = 1 - turn
                                continue # -------------------- END OF PAWN CAPTURE WHITE -------------------- #
            elif move[1:3] in squares.keys():
                if 'x' not in move and '+' not in move:
                    game[squares[move[1:]][0]][squares[move[1:]][1]] = move[0]
                    turn = 1 - turn
                    movesplayed.append(move)
                    continue
        elif turn == 1:
            if move[:2] in squares.keys(): # -------------------- PAWN MOVEMENT BLACK -------------------- #
                if '+' not in move and '=' not in move and '#' not in move:
                    gameT = BoardTranspose(game)
                    try:
                        pos = gameT[squares[move][1]].index('p')
                    except ValueError:
                        print("\nThere is no pawn to move. Please try again.")
                        continue
                    if game[squares[move][0]][squares[move][1]] != '-':
                        print("\nIllegal move. Please make a different move.")
                        continue
                    if pos == 1:
                        if squares[move][0] - pos > 2:
                            print("\nIllegal move. Pawn can't move more than two squares even if starting at home square.")
                            continue
                        elif squares[move][0] - pos == 0:
                            print("\nPlease try again.")
                            continue
                        elif squares[move][0] - pos < 0:
                            print("\nIllegal move. Pawns can't move backwards.")
                            continue
                        else:
                            game[pos][squares[move][1]] = '-'
                            game[squares[move][0]][squares[move][1]] = 'p'
                            turn = 1 - turn
                            movesplayed.append(move)
                            continue
                    else:
                        if squares[move][0] - pos > 2:
                            print("\nIllegal move. Pawn can't move more than two squares even if starting at home square.")
                            continue
                        elif squares[move][0] - pos == 0:
                            print("\nPlease try again.")
                            continue
                        elif squares[move][0] - pos < 0:
                            print("\nIllegal move. Pawns can't move backwards.")
                            continue
                        else:
                            game[pos][squares[move][1]] = '-'
                            game[squares[move][0]][squares[move][1]] = 'p'
                            turn = 1 - turn
                            movesplayed.append(move)
                            continue # -------------------- END OF PAWN MOVEMENT BLACK -------------------- #
            elif 'x' in move: # -------------------- PAWN CAPTURE BLACK -------------------- #
                if '+' not in move and '#' not in move and '=' not in move:
                    if move[0] not in pieces:
                        if game[squares[move[2:]][0]][squares[move[2:]][1]] == '-':
                            print("\nIllegal move. There is nothing to capture.")
                            continue
                        else:
                            current_pos = move[0]+str(int(move[-1])+1)
                            if game[squares[current_pos][0]][squares[current_pos][1]] != 'p':
                                print(f"\nIllegal move. There is no pawn on {current_pos}.")
                                continue
                            elif game[squares[move[2:]][0]][squares[move[2:]][1]] in pieces:
                                print("\nThat is not an enemy piece. Please try again.")
                                continue
                            else:
                                game[squares[current_pos][0]][squares[current_pos][1]] = '-'
                                game[squares[move[2:]][0]][squares[move[2:]][1]] = 'p'
                                movesplayed.append(move)
                                turn = 1 - turn
                                continue # -------------------- END OF PAWN CAPTURE BLACK -------------------- #
            elif move[1:3] in squares.keys():
                if 'x' not in move and '+' not in move:
                    game[squares[move[1:]][0]][squares[move[1:]][1]] = move[0]
                    turn = 1 - turn
                    movesplayed.append(move)
                    continue
                
PlayChess()
