QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    chess.cpp

HEADERS += \
    chess.h

FORMS += \
    chess.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Board/Brown/Board.png \
    Board/Brown/BoardBlack.png \
    Board/Brown/BoardWhite.png \
    Board/Brown/SelectedPiece.png \
    Pieces/Neo/BishopBlack.png \
    Pieces/Neo/BishopBlackCapture.png \
    Pieces/Neo/BishopWhite.png \
    Pieces/Neo/BishopWhiteCapture.png \
    Pieces/Neo/KingBlack.png \
    Pieces/Neo/KingBlackCapture.png \
    Pieces/Neo/KingWhite.png \
    Pieces/Neo/KingWhiteCapture.png \
    Pieces/Neo/KnightBlack.png \
    Pieces/Neo/KnightBlackCapture.png \
    Pieces/Neo/KnightWhite.png \
    Pieces/Neo/KnightWhiteCapture.png \
    Pieces/Neo/LegalMove.png \
    Pieces/Neo/PawnBlack.png \
    Pieces/Neo/PawnBlackCapture.png \
    Pieces/Neo/PawnWhite.png \
    Pieces/Neo/PawnWhiteCapture.png \
    Pieces/Neo/PieceCapture.png \
    Pieces/Neo/QueenBlack.png \
    Pieces/Neo/QueenBlackCapture.png \
    Pieces/Neo/QueenWhite.png \
    Pieces/Neo/QueenWhiteCapture.png \
    Pieces/Neo/RookBlack.png \
    Pieces/Neo/RookBlackCapture.png \
    Pieces/Neo/RookWhite.png \
    Pieces/Neo/RookWhiteCapture.png

RESOURCES += \
    resources.qrc
