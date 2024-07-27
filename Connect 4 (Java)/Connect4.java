import java.util.Scanner;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Connect4 {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Connect Four");
        frame.setSize(420, 360);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JPanel panel = new JPanel();
        frame.add(panel);
        panel.setLayout(new GridLayout(6, 7));
        JButton[][] buttons = new JButton[6][7];
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                buttons[i][j] = new JButton();
                panel.add(buttons[i][j]);
            }
        }
        frame.setVisible(true);
        int turn = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                buttons[i][j].setPreferredSize(new Dimension(60, 60));
                ImageIcon icon1 = new ImageIcon("Pictures/RedPiece1.png");
                ImageIcon icon2 = new ImageIcon("Pictures/YellowPiece1.png");
                Image RED = icon1.getImage().getScaledInstance(buttons[i][j].getWidth()-10, buttons[i][j].getHeight()-10, Image.SCALE_SMOOTH);
                Image BLUE = icon2.getImage().getScaledInstance(buttons[i][j].getWidth()-10, buttons[i][j].getHeight()-10, Image.SCALE_SMOOTH);
                int row = i;
                int col = j;
                Image[] pieces = {RED, BLUE};
                buttons[i][j].addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        buttons[row][col].setIcon(new ImageIcon(pieces[turn]));
                    }
                });
            }
        }
    }

    static void connectfour() {
        Character[][] board = makeboard();
        printboard(board);
        int turn = 0;
        int outcome = 0;
        String[] players = {"Red", "Yellow"};
        Character[] pieces = {'O', 'X'};
        Character[] possible_moves = {'1', '2', '3', '4', '5', '6', '7'};
        int counter = 0;
        while (outcome == 0 && counter < 42) {
            Scanner myObj = new Scanner(System.in);
            System.out.println(players[turn] + ", enter a number to place " + pieces[turn]);
            String player_input = myObj.nextLine();
            boolean check_input = false;
            for (int i = 0; i < 7; i++) {
                if (player_input.charAt(0) == possible_moves[i] && player_input.length() == 1) {
                    check_input = true;
                }
            }
            if (check_input == false) {
                continue;
            }
            int column = Integer.parseInt(player_input) - 1;
            int row = 5;
            while (row >= -1) {
                if (row == -1) {
                    System.out.println("Invalid input, please try again");
                    break;
                }
                if (board[row][column] != ' ') {
                    row--;
                }
                else {
                    board[row][column] = pieces[turn];
                    printboard(board);
                    turn = 1 - turn;
                    outcome = checkboard(board);
                    counter++;
                    break;
                }
            }
        }
        if (outcome == 1) {
            System.out.println(players[1-turn] + ", " + pieces[1-turn] + " has won!");
        }
        else if (counter == 42) {
            System.out.println("It's a draw.");;
        }
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

    static void printboard(Character[][] board) {
        System.out.println("---------------");
        for (int i = 0; i < 6; i++) {
            String output = "|";
            for (int j = 0; j < 7; j++) {
                output += board[i][j] + "|";
            }
            System.out.println(output);
            System.out.println("---------------");
        }
        System.out.println(" 1 2 3 4 5 6 7 ");
    }

    static int checkboard(Character[][] board) {
        for (int i = 0; i < 7; i++) {
            if (board[0][i].equals(board[1][i]) && board[1][i].equals(board[2][i]) && board[2][i].equals(board[3][i]) && !board[0][i].equals(' ')) {
                return 1;
            }
            else if (board[1][i].equals(board[2][i]) && board[2][i].equals(board[3][i]) && board[3][i].equals(board[4][i]) && !board[1][i].equals(' ')) {
                return 1;
            }
            else if (board[2][i].equals(board[3][i]) && board[3][i].equals(board[4][i]) && board[4][i].equals(board[5][i]) && !board[2][i].equals(' ')) {
                return 1;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (board[i][0].equals(board[i][1]) && board[i][1].equals(board[i][2]) && board[i][2].equals(board[i][3]) && !board[i][0].equals(' ')) {
                return 1;
            }
            else if (board[i][1].equals(board[i][2]) && board[i][2].equals(board[i][3]) && board[i][3].equals(board[i][4]) && !board[i][1].equals(' ')) {
                return 1;
            }
            else if (board[i][2].equals(board[i][3]) && board[i][3].equals(board[i][4]) && board[i][4].equals(board[i][5]) && !board[i][2].equals(' ')) {
                return 1;
            }
            else if (board[i][3].equals(board[i][4]) && board[i][4].equals(board[i][5]) && board[i][5].equals(board[i][6]) && !board[i][3].equals(' ')) {
                return 1;
            }
        }
        int top_right = 6;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[j][i].equals(board[j+1][i+1]) && board[j+1][i+1].equals(board[j+2][i+2]) && board[j+2][i+2].equals(board[j+3][i+3]) && !board[j][i].equals(' ')) {
                    return 1;
                }
                else if (board[j][top_right].equals(board[j+1][top_right-1]) && board[j+1][top_right-1].equals(board[j+2][top_right-2]) && board[j+2][top_right-2].equals(board[j+3][top_right-3]) && !board[j][top_right].equals(' ')) {
                    return 1;
                }
            }
            top_right--;
        }
        int bottom_right = 6;
        for (int i = 0; i < 4; i++) {
            for (int j = 5; j > 2; j--) {
                if (board[j][i].equals(board[j-1][i+1]) && board[j-1][i+1].equals(board[j-2][i+2]) && board[j-2][i+2].equals(board[j-3][i+3]) && !board[j][i].equals(' ')) {
                    return 1;
                }
                else if (board[j][bottom_right].equals(board[j-1][bottom_right-1]) && board[j-1][bottom_right-1].equals(board[j-2][bottom_right-2]) && board[j-2][bottom_right-2].equals(board[j-3][bottom_right-3]) && !board[j][bottom_right].equals(' ')) {
                    return 1;
                }
            }
            bottom_right--;
        }
        return 0;
    }
}
