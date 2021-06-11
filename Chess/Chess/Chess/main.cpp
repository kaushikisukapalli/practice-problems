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



class Square {
    char file;
    int rank;
    static bool squaresOccupied[64];
    bool occupied;
    string pieceColor;
    string pieceType;
    int location;
    
public:
    Square(char f_in, int r_in, bool o_in, string c_in, string t_in) : file(f_in), rank(r_in), occupied(o_in), pieceColor(c_in), pieceType(t_in) {
        location = 8 * rank + ((int) file) - 73;
    }
    
    void setOccupiedValue(bool value) {
        occupied = value;
        squaresOccupied[location] = value;
        if (!value) {
            setPieceColor("None");
            setPieceType("None");
        }
    }
    
    bool getOccupiedValue() {
        return occupied;
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
    
    void setPieceColor(string color_in) {
        pieceColor = color_in;
    }
    
    string getPieceColor() {
        return pieceColor;
    }
    
    void setPieceType(string type_in) {
        pieceType = type_in;
    }
    
    string getPieceType() {
        return pieceType;
    }
    
    void movePiece(Square &target) {
        target.setPieceColor(pieceColor);
        target.setPieceType(pieceType);
        target.setOccupiedValue(true);
        this->setOccupiedValue(false);
        cout << target.getPieceColor() << ": " << this->getFile() << this->getRank() << " to " << target.getFile() << target.getRank() << endl;
    }
    
    bool rookCanMove(Square &target) {
        if (target.getFile() == this->getFile() && target.getRank() < this->getRank()) {
            for (int i = this->getLocation() - 8; i >= target.getLocation(); i -= 8) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getFile() == this->getFile() && target.getRank() > this->getRank()) {
            for (int i = this->getLocation() + 8; i <= target.getLocation(); i += 8) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getRank() == this->getRank() && ((int) target.getFile() < (int) this->getRank())) {
            for (int i = this->getLocation() - 1; i >= target.getLocation(); i--) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getRank() == this->getRank() && ((int) target.getFile() > (int) this->getRank())) {
            for (int i = this->getLocation() + 1; i <= target.getLocation(); i++) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    
    bool bishopCanMove(Square &target) {
        if (abs(target.getFile() - this->getFile()) != abs(target.getRank() - this->getRank())) {
            return false;
        }
        if (target.getFile() > this->getFile() && target.getRank() > this->getRank()) {
            for (int i = this->getLocation() + 9; i <= target.getLocation(); i += 9) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getFile() > this->getFile() && target.getRank() < this->getRank()) {
            for (int i = this->getLocation() - 7; i >= target.getLocation(); i -= 7) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getFile() < this->getFile() && target.getRank() > this->getRank()) {
            for (int i = this->getLocation() + 7; i <= target.getLocation(); i += 7) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        else if (target.getFile() < this->getFile() && target.getRank() < this->getRank()) {
            for (int i = this->getLocation() - 9; i >= target.getLocation(); i -= 9) {
                if (squaresOccupied[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    
    bool canMove(Square &target) {
        if (!occupied) {
            return false;
        }
        if (target.location < 0 || target.location > 63) {
            return false;
        }
        if (target.getOccupiedValue()) {
            return false;
        }
        
        if (pieceType.compare("Pawn") == 0) {
            if (pieceColor.compare("White") == 0) {
                if (target.getLocation() - this->getLocation() == 8) {
                    return true;
                }
                else if (target.getLocation() - this->getLocation() == 16 && this->getLocation() > 7 && this->getLocation() < 16) {
                    return true;
                }
                return false;
            }
            else {
                if (target.getLocation() - this->getLocation() == -8) {
                    return true;
                }
                else if (target.getLocation() - this->getLocation() == -16 && this->getLocation() > 47 && this->getLocation() < 56) {
                    return true;
                }
                return false;
            }
        }
        
        if (pieceType.compare("Knight") == 0) {
            if (abs(((int) this->getFile()) - ((int) target.getFile())) == 1 && (abs(this->getRank() - target.getRank()) == 2)) {
                return true;
            }
            else if (abs(((int) this->getFile()) - ((int) target.getFile())) == 2 && (abs(this->getRank() - target.getRank()) == 1)) {
                return true;
            }
            return false;
        }
        
        if (pieceType.compare("Rook") == 0) {
            return rookCanMove(target);
        }
        
        if (pieceType.compare("Bishop") == 0) {
            return bishopCanMove(target);
        }
        
        if (pieceType.compare("Queen")) {
            return rookCanMove(target) || bishopCanMove(target);
        }
        return true;
    }

};

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
//string toFileRank(int location) {
//
//}

class Piece {
    int moves;
    int id;
    static Piece *pieces[32];
    string color;
    string type;
    char file;
    int rank;
    int location;
    static int lastPieceMoved;
    //bool inPlay;

public:
    Piece(int id_in, string type_in, char file_in, int rank_in) : moves(0), id(id_in), type(type_in), file(file_in), rank(rank_in) {
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
    
    Piece* getPiece(int id) {
        return pieces[id-1];
    }
    
    void changePieces(Piece *newPiece) {
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
    
    int getLastPieceMoved() {
        return lastPieceMoved;
    }
    
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
        int targetSquare = toLocation(target_file, target_rank);
        if (targetSquare < 0 || targetSquare > 63) {
            return false;
        }
        if (squareValues[targetSquare] != 0) {
            if (((pieces[squareValues[targetSquare]-1]->getColor()).compare(this->color)) == 0) {
                return false;
            }
        }
        return true;
    }
    
    virtual void move(char target_file, int target_rank) {
//        if (!canMove(target_file, target_rank)) {
//            cout << "Cannot move " << color << " " << type << " to " << target_file << " " << target_rank << endl;
//            return;
//        }
        int targetSquare = toLocation(target_file, target_rank);
        if (squareValues[targetSquare] != 0) {
            delete pieces[squareValues[targetSquare]-1];
            cout << file << rank << " captures on " << target_file << target_rank;
        }
        else {
            cout << file << rank << " to " << target_file << target_rank << endl;
        }
        squareValues[targetSquare] = id;
        squareValues[location] = 0;
        file = target_file;
        rank = target_rank;
        location = targetSquare;
        moves++;
        lastPieceMoved = id;
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
        squareValues[location] = 0;
    }
    
};

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
            for (int i = getLocation() - 8; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file == getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 8; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() - 1; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() + 1; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
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
        if (abs(target_file - getFile()) != abs(target_rank - getRank())) {
            return false;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if ((target_file < getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 9; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 7; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 7; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 9; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
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
        if (Bishop::canMove(target_file, target_rank)) {
            return true;
        }
        int targetSquare = toLocation(target_file, target_rank);
        if ((target_file == getFile()) && (target_rank < getRank())) {
            for (int i = getLocation() - 8; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file == getFile()) && (target_rank > getRank())) {
            for (int i = getLocation() + 8; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file < getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() - 1; i > targetSquare; i--) {
                if (squareValues[i] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((target_file > getFile()) && (target_rank == getRank())) {
            for (int i = getLocation() + 1; i < targetSquare; i++) {
                if (squareValues[i] != 0) {
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
        if (squareValues[targetSquare] == 0) {
        if (getId() <= 16) {
            if (targetSquare - getLocation() == 8) {
                return true;
            }
            if ((targetSquare - getLocation() == 16) && (getMoves() == 0)) {
                return true;
            }
            if ((getRank() == 5) && (target_rank - getRank() == 1) && (abs(target_file - getFile()) == 1)) {
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
        int targetSquare = toLocation(target_file, target_rank);
        if ((abs(target_file - getFile()) == 1) && (abs(target_rank - getRank()) == 1) && (squareValues[targetSquare] == 0)) {
            int victimSquare = toLocation(target_file, getRank());
            delete getPiece(squareValues[victimSquare]);
        }
        Piece::move(target_file, target_rank);
        if (((getId() <= 16) && (getRank() == 8)) || ((getId() >= 17) && (getRank() == 1))) {
            string newType = "Pawn";
            cout << "Enter a new piece (Knight, Bishop, Rook, or Queen): ";
            cin >> newType;
            cout << endl;
            while ((newType.compare("Knight") != 0) && (newType.compare("Bishop") != 0) && (newType.compare("Rook") != 0) && (newType.compare("Knight") != 0)) {
                cout << "Try again (Knight, Bishop, Rook, or Queen): ";
                cin >> newType;
                cout << endl;
            }
            Piece *newPiece;
            if (newType.compare("Knight") == 0) {
                newPiece = new Knight(this->getId(), this->getFile(), this->getRank());
            }
            else if (newType.compare("Bishop") == 0) {
                newPiece = new Bishop(this->getId(), this->getFile(), this->getRank());
            }
            else if (newType.compare("Rook") == 0) {
                newPiece = new Rook(this->getId(), this->getFile(), this->getRank());
            }
            else {
                newPiece = new Queen(this->getId(), this->getFile(), this->getRank());
            }
            delete this;
            changePieces(newPiece);
            cout << "Pawn to " << newType << " on " << newPiece->getFile() << newPiece->getRank() << endl;
        }
    }
};

class King : public Piece {
public:
    King(int id_in, char file_in, int rank_in) : Piece(id_in, "King", file_in, rank_in) {}
    
    bool canMove(char target_file, int target_rank) override {
        if ((abs(target_file - getFile()) <= 1) && (abs(target_rank - getRank()) <= 1)) {
            return true;
        }
        if ((getMoves() == 0) && (target_file == 'C') && (target_rank == getRank())) {
            int rookLocation = toLocation('A', getRank());
            if (getPiece(squareValues[rookLocation])->getMoves() == 0) {
                for (int i = rookLocation+1; i <= rookLocation+3; i++) {
                    if (squareValues[i] != 0) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        else if ((getMoves() == 0) && (target_file == 'G') && (target_rank == getRank())) {
            int rookLocation = toLocation('H', getRank());
            if (getPiece(squareValues[rookLocation])->getMoves() == 0) {
                for (int i = getLocation()+1; i <= rookLocation-1; i++) {
                    if (squareValues[i] != 0) {
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
        if (targetSquare - getLocation() == -3) {
            getPiece(squareValues[toLocation('A', this->getRank())])->move('D', getRank());
        }
        else if (targetSquare - getLocation() == 2) {
            getPiece(squareValues[toLocation('H', this->getRank())])->move('F', getRank());
        }
        Piece::move(target_file, target_rank);
    }
};

int main(int argc, const char * argv[]) {
    int a = 'f' - 'c';
    cout << a << endl;
    return 0;
}
