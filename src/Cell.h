# ifndef _CELL_H_
# define _CELL_H_

# include <cmath>

class Cell {
public:
    static inline int getRow (int _serialNumber, int _colNum, int _bbb, int _stateNum) {
        int cellSerialNumber = std::ceil(double(_serialNumber) / double(_stateNum));
        return std::ceil(double(cellSerialNumber) / double(2 * _bbb + _colNum)) - _bbb;
    }
    static inline int getCol (int _serialNumber, int _colNum, int _bbb, int _stateNum) {
        int cellSerialNumber = std::ceil(double(_serialNumber) / double(_stateNum));
        int tempRem = cellSerialNumber % (2 * _bbb + _colNum);
        return (tempRem)? (tempRem - _bbb):(_bbb + _colNum);
    }
    static inline int getState (int _serialNumber, int _stateNum) { 
        int tempRem = _serialNumber % _stateNum;
        return (tempRem)? tempRem:_stateNum;
    }

    static inline int getSerialNumber (int _row, int _col, int _state, int _colNum, int _bbb, int _stateNum) {
        return ((_bbb + _row - 1) * (_colNum + 2 * _bbb) + (_col + _bbb - 1)) * _stateNum + _state;
    }
};

# endif