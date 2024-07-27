##def PieceMovement(game,turn,piece,r_piece,c_piece,move,r_move,c_move,movesplayed):
##    if game[r_move][c_move] == '-':
##        game[r_piece][c_piece] = '-'
##        game[r_move][c_move] = piece[0]
##        movesplayed.append(f'{piece[0]}{move}')
##        turn = 1 - turn
##    elif game[r_move][c_move] in turn_pieces[turn]:
##        print(f'\nIllegal move. Cannot capture own piece.')
##    elif game[r_move][c_move] in turn_pieces[1-turn]:
##        game[r_piece][c_piece] = '-'
##        game[r_move][c_move] = piece[0]
##        movesplayed.append(f'{piece[0]}x{move}')
##        turn = 1 - turn
##    return turn
##
##
##if -1<3<5:
##    print('yes')

from time import *

begin = time()

for i in range(1000000):
    1+1==2

print(time()-begin)
