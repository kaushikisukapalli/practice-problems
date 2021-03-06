//
//  main.cpp
//  Chess
//
//  Created by Kaushik Isukapalli on 6/8/21.
//  Copyright © 2021 Kaushik Isukapalli. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

int squareValues[64];

int toLocation(char file_in, int rank_in) {
    return 8 * rank_in + ((int) file_in) - 73;
}

bool isEmpty(char file_in, int rank_in) {
    int location = toLocation(file_in, rank_in);
    return (squareValues[location] == 0);
}

bool isEmpty(int targetSquare) {
    return (squareValues[targetSquare] == 0);
}

void printLines(char startFile, int startRank, char targetFile, int targetRank, bool capture) {
    if (!capture) {
        cout << startFile << startRank << " to " << targetFile << targetRank << endl;
    }
    else {
        cout << startFile << startRank << " captures " << targetFile << targetRank << endl;
    }
}

class Piece {
    int moves;
    int id;
    
    string color;
    string type;
    char file;
    int rank;
    int location;
    bool inPlay;
    
    static Piece *notInPlay;

public:
    static int lastPieceMoved;
    static int whiteKingSquare;
    static int blackKingSquare;
    static Piece *pieces[32];
    
    Piece(int id_in, string type_in, char file_in, int rank_in) : moves(0), id(id_in), type(type_in), file(file_in), rank(rank_in), inPlay(true) {
        if (id <= 16) {
            color = "White";
        }
        else {
            color = "Black";
        }
        location = toLocation(file, rank);
        squareValues[location] = id;
        pieces[id-1] = this;
    }
    
    int getMoves() {
        return moves;
    }
    
    
    int getId() {
        return id;
    }
    
    static Piece** getAllPieces() {
        return pieces;
    }
    
    static Piece* getPiece(int id) {
        return pieces[id-1];
    }
    
    static void changePieces(Piece *newPiece) {
        pieces[newPiece->getId() - 1] = newPiece;
        squareValues[newPiece->getLocation()] = newPiece->getId();
    }
    
    string getColor() {
        return color;
    }
    
    string getType() {
        return type;
    }
    
    void setType(string type_in) {
        type = type_in;
    }
    
    char getFile() {
        return file;
    }
    
    int getRank() {
        return rank;
    }
    
    int getLocation() {
        return location;
    }
    
    static int getLastPieceMoved() {
        return lastPieceMoved;
    }
    
    void setInPlay(bool status) {
        inPlay = status;
        if (status) {
            squareValues[location] = id;
            notInPlay = nullptr;
        }
        else {
            squareValues[location] = 0;
            notInPlay = this;
        }
    }
    
    static Piece* getNotInPlay() {
        return notInPlay;
    }
    
//    static void setNotInPlay(int id) {
//        notInPlay = getPiece(id);
//    }
    
//    void changePlayStatus(bool newStatus) {
//        inPlay = newStatus;
//        if (!newStatus) {
//            pieces[id-1] = nullptr;
//            squareValues[location] = 0;
//        }
//    }
    
//    bool canAnyPieceMove(char target_file, int target_rank) {
//        int targetSquare = toLocation(target_file, target_rank);
//        if (targetSquare < 0 || targetSquare > 63) {
//            return false;
//        }
//       if (!isEmpty(targetSquare)) {
//            return false;
//        }
//        return true;
//    }
    
    virtual bool canMove(char target_file, int target_rank) {
        if (target_file < 'A' || target_file > 'H' || target_rank < 1 || target_rank > 8) {
            return false;
        }
        if (target_file == getFile() && target_rank == getRank()) {
            return false;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if (!isEmpty(targetSquare)) {
            if (((getPiece(squareValues[targetSquare]))->getColor().compare(this->color)) == 0) {
                return false;
            }
        }
        return true;
    }
    
    void printMoveLines(char target_file, int target_rank) {
        cout << color << ": " << file << rank << " to " << target_file << target_rank << endl;
    }
    
    void printAttackLines(char target_file, int target_rank) {
        cout << color << ": " << file << rank << " captures on " << target_file << target_rank;
    }
    
    void justMove(char target_file, int target_rank) {
        int targetSquare = toLocation(target_file, target_rank);
        squareValues[targetSquare] = id;
        squareValues[location] = 0;
        file = target_file;
        rank = target_rank;
        location = targetSquare;
        moves++;
    }
    
    virtual void move(char target_file, int target_rank) {
        int targetSquare = toLocation(target_file, target_rank);
        if (!isEmpty(targetSquare)) {
            getPiece(squareValues[targetSquare])->setInPlay(false);
        }
        justMove(target_file, target_rank);
    }
    
    virtual void moveBack(char startingFile, int startingRank) {
        int startingSquare = toLocation(startingFile, startingRank);
        squareValues[startingSquare] = id;
        squareValues[location] = 0;
        file = startingFile;
        rank = startingRank;
        location = startingSquare;
        moves--;
        if (type.compare("King") == 0) {
            if (id <= 16) {
                whiteKingSquare = location;
            }
            else {
                blackKingSquare = location;
            }
        }
        if (notInPlay != nullptr) {
            notInPlay->setInPlay(true);
        }
    }
    
//    virtual bool canAttack(char target_file, int target_rank) {
//        int targetSquare = toLocation(target_file, target_rank);
//        if (targetSquare < 0 || targetSquare > 63) {
//            return false;
//        }
//        if (isEmpty(targetSquare)) {
//            return false;
//        }
//        return canMove(target_file, target_rank);
//    }
//
//    virtual void attack(char target_file, int target_rank) {
//        if (!canAttack(target_file, target_rank)) {
//            cout << "Cannot capture on" << target_file << target_rank << endl;
//        }
//        else {
//            int targetLocation = toLocation(target_file, target_rank);
//            int victimID = squareValues[targetLocation];
//            Piece *victim = pieces[victimID-1];
//            delete victim;
//            cout << file << rank << " captures on " << target_file << target_rank;
//        }
//    }
    
    virtual ~Piece() {
        pieces[id-1] = nullptr;
        notInPlay = nullptr;
        
//        squareValues[location] = 0;
    }
};

int Piece::lastPieceMoved = 0;
Piece* Piece::notInPlay = nullptr;
Piece* Piece::pieces[32] = {nullptr};
int Piece::whiteKingSquare = 4;
int Piece::blackKingSquare = 60;


class Knight : public Piece {
public:
    Knight(int id_in, char file_in, int rank_in) : Piece(id_in, "Knight", file_in, rank_in) {}
    
    bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        if ((abs(target_file - getFile()) == 2) && (abs(target_rank - getRank()) == 1)) {
            return true;
        }
        else if ((abs(target_file - getFile()) == 1) && (abs(target_rank - getRank()) == 2)) {
            return true;
        }
        return false;
    }
};

class Rook : public Piece {
public:
    Rook(int id_in, char file_in, int rank_in) : Piece(id_in, "Rook", file_in, rank_in) {}
    
    bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if ((target_file == getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 8; i > targetSquare; i -= 8) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file == getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 8; i < targetSquare; i += 8) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() - 1; i > targetSquare; i--) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() + 1; i < targetSquare; i++) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Bishop : public Piece {
public:
    Bishop(int id_in, char file_in, int rank_in) : Piece(id_in, "Bishop", file_in, rank_in) {}
    
    virtual bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        if ((abs(target_file - getFile())) != (abs(target_rank - getRank()))) {
            return false;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if ((target_file < getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 9; i > targetSquare; i -= 9) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 7; i < targetSquare; i += 7) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 7; i > targetSquare; i -= 7) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 9; i < targetSquare; i += 9) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Queen : public Bishop {
public:
    Queen(int id_in, char file_in, int rank_in) : Bishop(id_in, file_in, rank_in) {
        setType("Queen");
    }
    
    bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        if (Bishop::canMove(target_file, target_rank)) {
            return true;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if ((target_file == getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 8; i > targetSquare; i -= 8) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file == getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 8; i < targetSquare; i += 8) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() - 1; i > targetSquare; i--) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() + 1; i < targetSquare; i++) {
                if (!isEmpty(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Pawn : public Piece {
public:
    Pawn(int id_in, char file_in, int rank_in) : Piece(id_in, "Pawn", file_in, rank_in) {}
    
    bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if (isEmpty(targetSquare)) {
            if (getId() <= 16) {
                if (targetSquare - getLocation() == 8) {
                    return true;
                }
                if ((targetSquare - getLocation() == 16) && (getMoves() == 0)) {
                    return true;
                }
                if ((getRank() == 5) && (target_rank - getRank() == 1) && (abs(target_file - getFile()) == 1)) {
                    if (Piece::lastPieceMoved == 0) {
                        return false;
                    }
                    string lastMoved = getPiece(getLastPieceMoved())->getType();
                    int totalMoves = getPiece(getLastPieceMoved())->getMoves();
                    if ((getLastPieceMoved() == squareValues[targetSquare-8]) && (lastMoved.compare("Pawn")) == 0 && (totalMoves == 1)) {
                        return true;
                    }
                    return false;
                }
                return false;
            }
            else {
                if (targetSquare - getLocation() == -8) {
                    return true;
                }
                if ((targetSquare - getLocation() == -16) && (getMoves() == 0)) {
                    return true;
                }
                if ((getRank() == 4) && (target_rank - getRank() == -1) && (abs(target_file - getFile()) == 1)) {
                    if (Piece::lastPieceMoved == 0) {
                        return false;
                    }
                    string lastMoved = getPiece(getLastPieceMoved())->getType();
                    int totalMoves = getPiece(getLastPieceMoved())->getMoves();
                    if ((getLastPieceMoved() == squareValues[targetSquare+8]) && (lastMoved.compare("Pawn")) == 0 && (totalMoves == 1)) {
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
        else {
            if (getId() <= 16) {
                if ((target_rank - getRank() == 1) && (abs(target_file - getFile()) == 1)) {
                    return true;
                }
                return false;
            }
            else {
                if ((target_rank - getRank() == -1) && (abs(target_file - getFile()) == 1)) {
                    return true;
                }
                return false;
            }
        }
    }
    
    void move(char target_file, int target_rank) override {
        if ((abs(target_file - getFile()) == 1) && (abs(target_rank - getRank()) == 1) && (isEmpty(target_file, target_rank))) {
            int victimSquare = toLocation(target_file, getRank());
            getPiece(squareValues[victimSquare])->setInPlay(false);
//            cout << getColor() << ": " << getFile() << getRank() << " captures on " << target_file << target_rank << " (en passant)" << endl;
//            justMove(target_file, target_rank);
        }
        Piece::move(target_file, target_rank);
//        if (((getId() <= 16) && (getRank() == 8)) || ((getId() >= 17) && (getRank() == 1))) {
//            string newType = "Pawn";
//            cout << "Enter a new piece (Knight, Bishop, Rook, or Queen): ";
//            cin >> newType;
//            cout << endl;
//            while ((newType.compare("Knight") != 0) && (newType.compare("Bishop") != 0) && (newType.compare("Rook") != 0) && (newType.compare("Knight") != 0)) {
//                cout << "Try again (Knight, Bishop, Rook, or Queen): ";
//                cin >> newType;
//                cout << endl;
//            }
//            Piece *newPiece = nullptr;
//            if (newType.compare("Knight") == 0) {
//                newPiece = new Knight(this->getId(), this->getFile(), this->getRank());
//            }
//            else if (newType.compare("Bishop") == 0) {
//                newPiece = new Bishop(this->getId(), this->getFile(), this->getRank());
//            }
//            else if (newType.compare("Rook") == 0) {
//                newPiece = new Rook(this->getId(), this->getFile(), this->getRank());
//            }
//            else {
//                newPiece = new Queen(this->getId(), this->getFile(), this->getRank());
//            }
//            this->setInPlay(false);
//            changePieces(newPiece);
//            cout << newPiece->getColor() << ": Pawn to " << newType << " on " << newPiece->getFile() << newPiece->getRank() << endl;
//        }
    }
};

class King : public Piece {
public:
    King(int id_in, char file_in, int rank_in) : Piece(id_in, "King", file_in, rank_in) {}
    
    bool canMove(char target_file, int target_rank) override {
        if (!Piece::canMove(target_file, target_rank)) {
            return false;
        }
        if ((abs(target_file - getFile()) <= 1) && (abs(target_rank - getRank()) <= 1)) {
            return true;
        }
        if ((getMoves() == 0) && (target_file == 'C') && (target_rank == getRank())) {
            int rookLocation = toLocation('A', getRank());
            Piece *queenRook = getPiece(squareValues[rookLocation]);
            if (queenRook && queenRook->getMoves() == 0 && (queenRook->getId() % 16) == 9) {
                for (int i = rookLocation+1; i <= rookLocation+3; i++) {
                    if (!isEmpty(i)) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        else if ((getMoves() == 0) && (target_file == 'G') && (target_rank == getRank())) {
            int rookLocation = toLocation('H', getRank());
            Piece *kingRook = getPiece(squareValues[rookLocation]);
            if (kingRook && kingRook->getMoves() == 0 && (kingRook->getId() % 16) == 0) {
                for (int i = getLocation()+1; i <= rookLocation-1; i++) {
                    if (!isEmpty(i)) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;
    }
    
    void move(char target_file, int target_rank) override {
        int targetSquare = toLocation(target_file, target_rank);
        if (targetSquare - getLocation() == -2) {
            getPiece(squareValues[toLocation('A', this->getRank())])->justMove('D', getRank());
            justMove(target_file, target_rank);
//            cout << getColor() << ": Queen Side Castle" << endl;
        }
        else if (targetSquare - getLocation() == 2) {
            getPiece(squareValues[toLocation('H', this->getRank())])->justMove('F', getRank());
            justMove(target_file, target_rank);
//            cout << getColor() << ": King Side Castle" << endl;
        }
        else {
            Piece::move(target_file, target_rank);
        }
        if (getId() <= 16) {
            whiteKingSquare = getLocation();
        }
        else {
            blackKingSquare = getLocation();
        }
    }
    
    void moveBack(char startingFile, int startingRank) override {
        int startingSquare = toLocation(startingFile, startingRank);
        if (startingSquare-getLocation() == 2) {
            Piece *queenRook = getPiece(squareValues[getLocation()+1]);
            queenRook->moveBack('A', getRank());
        }
        else if (startingSquare-getLocation() == -2) {
            Piece *kingRook = getPiece(squareValues[getLocation()-1]);
            kingRook->moveBack('H', getRank());
        }
        Piece::moveBack(startingFile, startingRank);
    }
};

class Game {
    string currentPlayer;
    string oppositePlayer;
    bool whiteKingCheck;
    bool blackKingCheck;
    bool mate;
    
public:
    Game() : currentPlayer("White"), oppositePlayer("Black"), whiteKingCheck(false), blackKingCheck(false), mate(false) {
        for (int i = 1; i <= 8; i++) {
            new Pawn(i, (char) (i+64), 2);
        }
        new Rook(9, 'A', 1);
        new Knight(10, 'B', 1);
        new Bishop(11, 'C', 1);
        new Queen(12, 'D', 1);
        new King(13, 'E', 1);
        new Bishop(14, 'F', 1);
        new Knight(15, 'G', 1);
        new Rook(16, 'H', 1);
        for (int i = 1; i <= 8; i++) {
            new Pawn(i+16, (char) (i+64), 7);
        }
        new Rook(25, 'A', 8);
        new Knight(26, 'B', 8);
        new Bishop(27, 'C', 8);
        new Queen(28, 'D', 8);
        new King(29, 'E', 8);
        new Bishop(30, 'F', 8);
        new Knight(31, 'G', 8);
        new Rook(32, 'H', 8);
    }
    
    string getCurrentPlayer() {
        return currentPlayer;
    }
    
    string getOppositePlayer() {
        return oppositePlayer;
    }
    
    void switchPlayer() {
        string temp = currentPlayer;
        currentPlayer = oppositePlayer;
        oppositePlayer = temp;
    }
    
    bool kingCheckStatus(string color) {
        if (color.compare("White") == 0) {
            char kingFile = Piece::getPiece(13)->getFile();
            int kingRank = Piece::getPiece(13)->getRank();
            for (int i = 17; i <= 32; i++) {
                while ((i <= 32) && Piece::getPiece(i) == nullptr) {
                    i++;
                }
                if (Piece::getPiece(i)->canMove(kingFile, kingRank)) {
                    whiteKingCheck = true;
                    return true;
                }
            }
            whiteKingCheck = false;
            return false;
        }
        else {
            char kingFile = Piece::getPiece(29)->getFile();
            int kingRank = Piece::getPiece(29)->getRank();
            for (int i = 1; i <= 16; i++) {
                while ((i <= 16) && Piece::getPiece(i) == nullptr) {
                    i++;
                }
                if (Piece::getPiece(i)->canMove(kingFile, kingRank)) {
                    blackKingCheck = true;
                    return true;
                }
            }
            blackKingCheck = false;
            return false;
        }
    }
    
    void afterMateCheck(int id, int offset, char file, int rank, bool kingCheck) {
        if (offset == 0) {
            whiteKingCheck = kingCheck;
        }
        else {
            blackKingCheck = kingCheck;
        }
        (Piece::getPiece(id))->moveBack(file, rank);
    }
    
    bool getMate() {
        return mate;
    }
    
    bool isMate() {
        int offset = 16;
        bool kingCheck = blackKingCheck;
        if (currentPlayer.compare("White") == 0) {
            offset = 0;
            kingCheck = whiteKingCheck;
        }
        for (int i = 13+offset; i <= 16+offset; i++) {
            while ((i <= 16+offset) && Piece::getPiece(i) == nullptr) {
                if (i == 13+offset) {
                    i = offset;
                }
                else if (i == 12+offset) {
                    i++;
                }
                i++;
            }
            char originalFile = Piece::getPiece(i)->getFile();
            int originalRank = Piece::getPiece(i)->getRank();
            if (Piece::getPiece(i)->getType().compare("Pawn") == 0) {
                for (char j = originalFile - 1; j <= originalFile + 1; j++) {
                    if (Piece::getPiece(i)->canMove(j, originalRank+1)) {
                        Piece::getPiece(i)->move(j, originalRank+1);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                }
            }
            else if (Piece::getPiece(i)->getType().compare("King") == 0) {
                for (char j = originalFile-1; j <= originalFile+1; j++) {
                    for (int k = originalRank-1; k <= originalRank+1; k++) {
                        if (Piece::getPiece(i)->canMove(j, k)) {
                            Piece::getPiece(i)->move(j, k);
                            if (!kingCheckStatus(currentPlayer)) {
                                afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                                mate = false;
                                return false;
                            }
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                        }
                    }
                }
            }
            else if (Piece::getPiece(i)->getType().compare("Rook") == 0) {
                for (int k = 1; k <= 8; k++) {
                    if (Piece::getPiece(i)->canMove(originalFile, k)) {
                        Piece::getPiece(i)->move(originalFile, k);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                }
                for (char j = 'A'; j <= 'H'; j++) {
                    if (Piece::getPiece(i)->canMove(j, originalRank)) {
                        Piece::getPiece(i)->move(j, originalRank);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                }
            }
            else if (Piece::getPiece(i)->getType().compare("Knight") == 0) {
                for (char j = originalFile-1; j <= originalFile+1; j += 2) {
                    for (int k = originalRank-2; k <= originalRank+2; k += 4) {
                        if (Piece::getPiece(i)->canMove(j, k)) {
                            Piece::getPiece(i)->move(j, k);
                            if (!kingCheckStatus(currentPlayer)) {
                                afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                                mate = false;
                                return false;
                            }
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                        }
                    }
                }
                for (char j = originalFile-2; j <= originalFile+2; j += 4) {
                    for (int k = originalRank-1; k <= originalRank+1; k += 2) {
                        if (Piece::getPiece(i)->canMove(j, k)) {
                            Piece::getPiece(i)->move(j, k);
                            if (!kingCheckStatus(currentPlayer)) {
                                afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                                mate = false;
                                return false;
                            }
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                        }
                    }
                }
            }
            else if (Piece::getPiece(i)->getType().compare("Bishop") == 0) {
                int j = 0;
                while (originalFile-j >= 'A' && originalRank-j >= 1) {
                    if (Piece::getPiece(i)->canMove(originalFile-j, originalRank-j)) {
                        Piece::getPiece(i)->move(originalFile-j, originalRank-j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile-j >= 'A' && originalRank+j <= 8) {
                    if (Piece::getPiece(i)->canMove(originalFile-j, originalRank+j)) {
                        Piece::getPiece(i)->move(originalFile-j, originalRank+j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile+j <= 'H' && originalRank-j >= 1) {
                    if (Piece::getPiece(i)->canMove(originalFile+j, originalRank-j)) {
                        Piece::getPiece(i)->move(originalFile+j, originalRank-j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile+j <= 'H' && originalRank+j <= 8) {
                    if (Piece::getPiece(i)->canMove(originalFile+j, originalRank+j)) {
                        Piece::getPiece(i)->move(originalFile+j, originalRank+j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
            }
            else {
                for (int k = 1; k <= 8; k++) {
                    if (Piece::getPiece(i)->canMove(originalFile, k)) {
                        Piece::getPiece(i)->move(originalFile, k);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                }
                for (char j = 'A'; j <= 'H'; j++) {
                    if (Piece::getPiece(i)->canMove(j, originalRank)) {
                        Piece::getPiece(i)->move(j, originalRank);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                }
                int j = 0;
                while (originalFile-j >= 'A' && originalRank-j >= 1) {
                    if (Piece::getPiece(i)->canMove(originalFile-j, originalRank-j)) {
                        Piece::getPiece(i)->move(originalFile-j, originalRank-j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile-j >= 'A' && originalRank+j <= 8) {
                    if (Piece::getPiece(i)->canMove(originalFile-j, originalRank+j)) {
                        Piece::getPiece(i)->move(originalFile-j, originalRank+j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile+j <= 'H' && originalRank-j >= 1) {
                    if (Piece::getPiece(i)->canMove(originalFile+j, originalRank-j)) {
                        Piece::getPiece(i)->move(originalFile+j, originalRank-j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
                j = 0;
                while (originalFile+j <= 'H' && originalRank+j <= 8) {
                    if (Piece::getPiece(i)->canMove(originalFile+j, originalRank+j)) {
                        Piece::getPiece(i)->move(originalFile+j, originalRank+j);
                        if (!kingCheckStatus(currentPlayer)) {
                            afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                            mate = false;
                            return false;
                        }
                        afterMateCheck(i, offset, originalFile, originalRank, kingCheck);
                    }
                    j++;
                }
            }
            if (i == 13+offset) {
                i = offset;
            }
            else if (i == 12+offset) {
                i++;
            }
        }
        mate = true;
        return true;
    }
    
    bool movePiece(char currentFile, int currentRank, char targetFile, int targetRank, bool kingCheck) {
        int currentSquare = toLocation(currentFile, currentRank);
        int targetSquare = toLocation(targetFile, targetRank);
        int offset = 8;
        if (currentPlayer.compare("Black") == 0) {
            offset = 1;
        }
//        if (isMate()) {
//            if (kingCheck) {
//                cout << "Checkmate! " << oppositePlayer << "has won!" << endl;
//            }
//            else {
//                cout << "Stalemate! Game has ended in a draw!" << endl;
//            }
//            return false;
//        }
        
//        if (isEmpty(currentSquare)) {
//            cout << "Choose a square with a piece" << endl;
//            return false;
//        }
//        if ((offset == 0 && squareValues[currentSquare] > 16) || (offset == 56 && squareValues[currentSquare] < 17)) {
//            cout << "Choose a " << currentPlayer << " piece" << endl;
//            return false;
//        }
        if (!(Piece::getPiece(squareValues[currentSquare]))->canMove(targetFile, targetRank)) {
            cout << "Cannot move from " << currentFile << currentRank << " to " << targetFile << targetRank << endl;
            return false;
        }
        if (kingCheck && (squareValues[currentSquare] % 16 == 13) && (abs(targetSquare-currentSquare) == 2)) {
            cout << "Cannot castle on a Check" << endl;
            return false;
        }
        int id = squareValues[currentSquare];
        Piece::getPiece(squareValues[currentSquare])->move(targetFile, targetRank);
        if (kingCheckStatus(currentPlayer)) {
            Piece::getPiece(squareValues[targetSquare])->moveBack(currentFile, currentRank);
            cout << "Cannot place King under Check" << endl;
            return false;
        }
        else {
            Piece::lastPieceMoved = id;
        }
        
        if ((Piece::lastPieceMoved % 16 == 13) && (abs(targetFile-currentFile) == 2)) {
            if (abs(targetFile-currentFile) == -2) {
                cout << getCurrentPlayer() << ": Queen Side Castle" << endl;
            }
            else if (abs(targetFile-currentFile) == 2) {
                cout << getCurrentPlayer() << ": King Side Castle" << endl;
            }
        }
        else if (Piece::getNotInPlay() != nullptr) {
            printLines(currentFile, currentRank, targetFile, targetRank, true);
            delete Piece::getNotInPlay();
        }
        else {
            printLines(currentFile, currentRank, targetFile, targetRank, false);
        }
        for (char j = 'A'; j <= 'H'; j++) {
            int i = toLocation(j, offset);
            if (Piece::getPiece(squareValues[toLocation(j, offset)]) && Piece::getPiece(squareValues[toLocation(j, offset)])->getType().compare("Pawn") == 0) {
                Piece *currentPawn = Piece::getPiece(squareValues[toLocation(j, offset)]);
                string newType = "Pawn";
                cout << "Enter a new piece (Knight, Bishop, Rook, or Queen): ";
                cin >> newType;
                while ((newType.compare("Knight") != 0) && (newType.compare("Bishop") != 0) && (newType.compare("Rook") != 0) && (newType.compare("Knight") != 0)) {
                    cout << "Try again (Knight, Bishop, Rook, or Queen): ";
                    cin >> newType;
                }
                Piece *newPiece = nullptr;
                if (newType.compare("Knight") == 0) {
                    newPiece = new Knight(currentPawn->getId(), currentPawn->getFile(), i/8 + 1);
                }
                else if (newType.compare("Bishop") == 0) {
                    newPiece = new Bishop(currentPawn->getId(), currentPawn->getFile(), i/8 + 1);
                }
                else if (newType.compare("Rook") == 0) {
                    newPiece = new Rook(currentPawn->getId(), currentPawn->getFile(), i/8 + 1);
                }
                else {
                    newPiece = new Queen(currentPawn->getId(), currentPawn->getFile(), i/8 + 1);
                }
                delete currentPawn;
                Piece::changePieces(newPiece);
                cout << newPiece->getColor() << ": Pawn to " << newType << " on " << newPiece->getFile() << newPiece->getRank() << endl;
            }
        }
        return true;
    }
    
    ~Game() {
        for (int i = 1; i <= 32; i++) {
            if (Piece::getPiece(i) != nullptr) {
                delete Piece::getPiece(i);
            }
        }
        for (int j = 0; j < 64; j++) {
            squareValues[j] = 0;
        }
    }
};

int main(int argc, const char * argv[]) {
    Game chess;
    bool gameOver = false;
    bool kingCheck = false;
    while (!gameOver) {
        bool acceptedMove = false;
        while (!acceptedMove) {
            string startingSquare = "";
            cout << chess.getCurrentPlayer() << ": Enter a starting square: ";
            bool acceptedStartingSquare = false;
            char startfile = '0';
            int startrank = 0;
            while (!acceptedStartingSquare) {
                cin >> startingSquare;
                while (startingSquare.length() != 2 || startingSquare[0] < 'A' || startingSquare[0] > 'H' || startingSquare[1] < '1' || startingSquare[1] > '8') {
                    cout << "Choose a valid starting square: ";
                    cin >> startingSquare;
                }
                startfile = startingSquare[0];
                startrank = ((int) startingSquare[1]) - 48;
                int startSquare = toLocation(startfile, startrank);
                if (isEmpty(startSquare) || (squareValues[startSquare] > 16 && chess.getCurrentPlayer().compare("White") == 0) || (squareValues[startSquare] < 17 && chess.getCurrentPlayer().compare("Black") == 0)) {
                    cout << "Choose a square with a " << chess.getCurrentPlayer() << " piece: ";
                    acceptedStartingSquare = false;
                }
                else {
                    acceptedStartingSquare = true;
                }
            }
            string endSquare = "";
            cout << chess.getCurrentPlayer() << ": Enter a square to move to: ";
            char endFile = '0';
            int endRank = 0;
            cin >> endSquare;
            if (endSquare.length() != 2 || endSquare[0] < 'A' || endSquare[0] > 'H' || endSquare[1] < '1' || endSquare[1] > '8') {
                cout << "Not a valid square" << endl;
                acceptedMove = false;
            }
            else {
                endFile = endSquare[0];
                endRank = ((int) endSquare[1]) - 48;
                acceptedMove = chess.movePiece(startfile, startrank, endFile, endRank, kingCheck);
            }
        }
        chess.switchPlayer();
        kingCheck = chess.kingCheckStatus(chess.getCurrentPlayer());
        bool mate = chess.isMate();
        if (mate) {
            if (kingCheck) {
                cout << "Checkmate! " << chess.getOppositePlayer() << " has won!" << endl;
            }
            else {
                cout << "Stalemate! Game has ended in a draw!" << endl;
            }
        }
        if (kingCheck) {
            cout << "Check!" << endl;
        }
        gameOver = mate;
    }
    return 0;
}
