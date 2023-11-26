# ifndef _IO_H_
# define _IO_H_
# include "lodepng/lodepng.h"
# include <iostream>
# include <iomanip>
# include <vector>
# include <unordered_map>
# include <utility>
# include <string>
# include <cmath>

class IO {
public:
    static std::string varStringforPrinting(int _serialNumber, 
                                            int _colNum, 
                                            int _bbb, 
                                            int _stateNum, 
                                            const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed);
    static void printClause(const std::vector<int>& _clauseNegArr, 
                            int _colNum, 
                            int _bbb, 
                            int _stateNum, 
                            const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed);
    static void charBoardForPrinting (std::vector<std::vector<char> >& _charBoard, 
                                      const std::vector<int>& _varValueIfSAT, 
                                      int _rowNum,
                                      int _colNum, 
                                      int _bbb, 
                                      int _stateNum, 
                                      const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed);
    static void printBoard (const std::vector<int>& _varValueIfSAT, 
                            int _rowNum,
                            int _colNum, 
                            int _bbb, 
                            int _stateNum, 
                            const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed);
    static void printBoardPNG  (const std::vector<int>& _varValueIfSAT, 
                                int _rowNum,
                                int _colNum, 
                                int _bbb, 
                                int _stateNum, 
                                const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed);

    static inline void handleInput (int& _rowNum, int& _colNum, std::string& _blockUsed) {
        const char* boldOn = "\033[1m";
        const char* boldOff = "\033[0m";
        const char* greenColor = "\033[1;32m"; 
        const char* blueColor = "\033[1;34m";
        const char* redColor = "\033[1;31m"; 
        const char* resetColor = "\033[0m";  
        std::cout << "+-----------------------------------------+\n";
        std::cout << boldOn << "|      Tetris Filling Problem Solver      |\n" << boldOff;
        std::cout << "+-----------------------------------------+\n";
        std::cout << "| Creator:       B10901016 Yan Sheng Qiu  |\n";
        std::cout << "| Last Modified: 20231126                 |\n";
        std::cout << "+-----------------------------------------+\n";
        while (true) {
            std::cout << "\nEnter board size.\nRow number => ";
            std::cin >> _rowNum;
            std::cout << "Column number => ";
            std::cin >> _colNum;
            if ((_rowNum * _colNum) % 4 != 0) {
                std::cout << boldOn << redColor << "\nTotal cell number is not a multiple of 4. Please re-enter.\n" << resetColor << boldOff;
            }
            else break;
        }
        std::cout << "\nUsing block: (e.g. All, I, TS, SZ, ...)\n=> ";
        std::cin >> _blockUsed;
        std::cout << boldOn << blueColor << "\nComputing...Please wait...\n\n" << resetColor << boldOff;
    }
    static inline void handleOutput (bool _isSAT, 
                                     const std::vector<int>& _varValueIfSAT, 
                                     int _rowNum, 
                                     int _colNum, 
                                     int _bbb, 
                                     int _stateNum, 
                                     const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed, 
                                     int _varNum, 
                                     int _clauseNum, 
                                     std::chrono::microseconds& _duration) {
        const char* boldOn = "\033[1m";
        const char* boldOff = "\033[0m";
        const char* greenColor = "\033[1;32m"; 
        const char* blueColor = "\033[1;34m";
        const char* redColor = "\033[1;31m"; 
        const char* resetColor = "\033[0m";  
        std::cout << "+-----------------------------------------+\n";
        std::cout << boldOn << "|                Statistics               |\n" << boldOff;
        std::cout << "+-----------------------------------------+\n";
        std::cout << "| Number of variables: " << std::setw(10) << std::left << _varNum << "         |\n";
        std::cout << "| Number of clauses: " << std::setw(10) << std::left << _clauseNum << "           |\n";
        std::cout << "|                                         |\n";
        
        if (_isSAT) {
            //IO::printBoard(varValueIfSAT, rowNum, colNum, bbb, stateNum, rotationStateNumIsUsed);
            std::cout << "| Tetris Blocks " << greenColor << "CAN" << resetColor << " fill the board!       |\n";
            IO::printBoardPNG(_varValueIfSAT, _rowNum, _colNum, _bbb, _stateNum, _rotationStateNumIsUsed);
        }
        else {
            std::cout << "| Tetris Blocks " << redColor << "CANNOT" << resetColor << " fill the board!    |\n";
        }
        std::cout << "|                                         |\n";
        std::cout << "| Total Running Time (ms): " << std::setw(10) << std::left << _duration.count()/1000 << "     |\n";
        std::cout << "+-----------------------------------------+\n";
    }
};

# endif 