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

//class Piece {
//    string name;
//    string color;
//    Square location;
//    bool inPlay;
//
//public:
//    Piece(string name_in, string color_in, char file_in, int rank_in) : name(name_in), color(color_in), location(file_in, rank_in, true, color), inPlay(true) {}
//
//    virtual bool move() = 0;
//
//    virtual bool attack(Piece &victim) = 0;
//
//    char getFile() {
//        return location.getFile();
//    }
//
//    int getRank() {
//        return location.getRank();
//    }
//};
//
//class Knight : public Piece {
//public:
//    Knight(string name_in, string color_in, char file_in, int rank_in) : Piece(name_in, color_in, file_in, rank_in) {}
//
//
//};

int main(int argc, const char * argv[]) {
    int a = 'b' - 'c';
    cout << a << endl;
    return 0;
}
