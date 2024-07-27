import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Improved4 {
    public static void main(String[] args) {
        connectfour();
    }

    static void connectfour() {
        JFrame frame = new JFrame("Connect Four");
        frame.setSize(480, 380);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel panel = new JPanel(new BorderLayout());
        frame.add(panel);
        JPanel gridPanel = new JPanel(new GridLayout(6, 7));
        panel.add(gridPanel, BorderLayout.CENTER);
        JButton[][] buttons = new JButton[6][7];
        Character[][] board = makeboard();
        String[] players = {"Red", "Yellow"};
        Character[] pieces = {'O', 'X'};
        final int[] turn = {0};
        final int[] counter = {0};
        final int[] outcome = {0};
        final JLabel label = new JLabel("Player " + players[turn[0]] + "'s turn");
        label.setHorizontalAlignment(SwingConstants.CENTER);
        panel.add(label, BorderLayout.SOUTH);
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                buttons[i][j] = new JButton();
                buttons[i][j].setPreferredSize(new Dimension(60, 60));
                gridPanel.add(buttons[i][j]);
                ImageIcon icon1 = new ImageIcon("Pictures/RedPiece1.png");
                ImageIcon icon2 = new ImageIcon("Pictures/YellowPiece1.png");
                Image RED = icon1.getImage().getScaledInstance(buttons[i][j].getWidth()-10, 
                                                               buttons[i][j].getHeight()-10, 
                                                               Image.SCALE_SMOOTH);
                Image BLUE = icon2.getImage().getScaledInstance(buttons[i][j].getWidth()-10, 
                                                                buttons[i][j].getHeight()-10, 
                                                                Image.SCALE_SMOOTH);
                int col = j;
                Image[] pictures = {RED, BLUE};
                buttons[i][j].addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        if (outcome[0] == 0 && counter[0] < 42) {
                            int temp = 5;
                            while (temp >= -1) {
                                if (temp == -1) {
                                    break;
                                }
                                if (board[temp][col] == ' ') {
                                    buttons[temp][col].setIcon(new ImageIcon(pictures[turn[0]]));
                                    board[temp][col] = pieces[turn[0]];
                                    outcome[0] = checkboard(board);
                                    turn[0] = 1 - turn[0];
                                    counter[0]++;
                                    label.setText("Player " + players[turn[0]] + "'s turn");
                                    break;
                                }
                                else {
                                    temp--;
                                }
                            }
                        }
                        if (outcome[0] == 1) {
                            label.setText("Player " + players[1-turn[0]] + " has won!");
                        }
                        else if (counter[0] == 42) {
                            label.setText("It's a draw!");
                        }
                    }
                });
            }
        }
        JPanel rightButtonPanel = new JPanel();
        rightButtonPanel.setLayout(new BoxLayout(rightButtonPanel, BoxLayout.Y_AXIS));
        panel.add(rightButtonPanel, BorderLayout.EAST);
        JButton rightButton = new JButton("Restart");
        rightButtonPanel.add(rightButton);
        rightButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                connectfour();
            }
        });
        frame.setVisible(true);
    }

    static Character[][] makeboard() {
        Character[][] board = new Character[6][7];
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                board[i][j] = ' ';
            }
        }
        return board;
    }

    static int checkboard(Character[][] board) {
        for (int i = 0; i < 7; i++) {
            if (board[0][i].equals(board[1][i]) && 
                board[1][i].equals(board[2][i]) && 
                board[2][i].equals(board[3][i]) && 
                !board[0][i].equals(' ')) {
                return 1;
            }
            else if (board[1][i].equals(board[2][i]) && 
                     board[2][i].equals(board[3][i]) && 
                     board[3][i].equals(board[4][i]) && 
                     !board[1][i].equals(' ')) {
                return 1;
            }
            else if (board[2][i].equals(board[3][i]) && 
                     board[3][i].equals(board[4][i]) && 
                     board[4][i].equals(board[5][i]) && 
                     !board[2][i].equals(' ')) {
                return 1;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (board[i][0].equals(board[i][1]) && 
                board[i][1].equals(board[i][2]) && 
                board[i][2].equals(board[i][3]) && 
                !board[i][0].equals(' ')) {
                return 1;
            }
            else if (board[i][1].equals(board[i][2]) && 
                     board[i][2].equals(board[i][3]) && 
                     board[i][3].equals(board[i][4]) && 
                     !board[i][1].equals(' ')) {
                return 1;
            }
            else if (board[i][2].equals(board[i][3]) && 
                     board[i][3].equals(board[i][4]) && 
                     board[i][4].equals(board[i][5]) && 
                     !board[i][2].equals(' ')) {
                return 1;
            }
            else if (board[i][3].equals(board[i][4]) && 
                     board[i][4].equals(board[i][5]) && 
                     board[i][5].equals(board[i][6]) && 
                     !board[i][3].equals(' ')) {
                return 1;
            }
        }
        int top_right = 6;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[j][i].equals(board[j+1][i+1]) && 
                    board[j+1][i+1].equals(board[j+2][i+2]) && 
                    board[j+2][i+2].equals(board[j+3][i+3]) && 
                    !board[j][i].equals(' ')) {
                    return 1;
                }
                else if (board[j][top_right].equals(board[j+1][top_right-1]) && 
                         board[j+1][top_right-1].equals(board[j+2][top_right-2]) && 
                         board[j+2][top_right-2].equals(board[j+3][top_right-3]) && 
                         !board[j][top_right].equals(' ')) {
                    return 1;
                }
            }
            top_right--;
        }
        int bottom_right = 6;
        for (int i = 0; i < 4; i++) {
            for (int j = 5; j > 2; j--) {
                if (board[j][i].equals(board[j-1][i+1]) && 
                    board[j-1][i+1].equals(board[j-2][i+2]) && 
                    board[j-2][i+2].equals(board[j-3][i+3]) && 
                    !board[j][i].equals(' ')) {
                    return 1;
                }
                else if (board[j][bottom_right].equals(board[j-1][bottom_right-1]) && 
                         board[j-1][bottom_right-1].equals(board[j-2][bottom_right-2]) && 
                         board[j-2][bottom_right-2].equals(board[j-3][bottom_right-3]) && 
                         !board[j][bottom_right].equals(' ')) {
                    return 1;
                }
            }
            bottom_right--;
        }
        return 0;
    }
}