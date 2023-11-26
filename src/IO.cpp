# include "IO.h"
# include "Cell.h"
# include "AuxFuncs.h"
# include "TetrisData.h"

std::string IO::varStringforPrinting   (int _serialNumber,
                                        int _colNum,
                                        int _bbb, 
                                        int _stateNum, 
                                        const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed) 
{
    char block = AuxFuncs::getBlockAndRelativeIndexByStateIndex (Cell::getState (_serialNumber, _stateNum),  _rotationStateNumIsUsed).first;
    char relativeIndex = AuxFuncs::getBlockAndRelativeIndexByStateIndex (Cell::getState (_serialNumber, _stateNum),  _rotationStateNumIsUsed).second;
    int rotationState = std::ceil(double(relativeIndex) / 4.0);
    int cellIndexInBlock = (relativeIndex % 4 == 0)?4:(relativeIndex % 4);
    std::string varStringforPrinting = "a[" + std::to_string(Cell::getRow(_serialNumber, _colNum, _bbb, _stateNum)) + ", " + std::to_string(Cell::getCol(_serialNumber, _colNum, _bbb, _stateNum)) + "].(" + block + char(int('0') + rotationState) + char(int('0') + cellIndexInBlock) + ")";
    return varStringforPrinting ;
}

void IO::printClause   (const std::vector<int>& _clauseNegArr, 
                        int _colNum, 
                        int _bbb, 
                        int _stateNum, 
                        const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed) 
{
    bool notPrintOrSign = true;
    for (int i = 0; i < _clauseNegArr.size(); ++i) {
        if (_clauseNegArr[i] != -1) {
            if (notPrintOrSign) {
                std::cout << varStringforPrinting(i+1, _colNum, _bbb, _stateNum, _rotationStateNumIsUsed) << ((_clauseNegArr[i])?"":"\'");
                notPrintOrSign = false;
            }
            else {
                std::cout << " + " << varStringforPrinting(i+1, _colNum, _bbb, _stateNum, _rotationStateNumIsUsed) << ((_clauseNegArr[i])?"":"\'");
            }
        }
    }
    std::cout << std::endl;
} 

void IO::charBoardForPrinting (std::vector<std::vector<char> >& _charBoard, 
                               const std::vector<int>& _varValueIfSAT, 
                               int _rowNum,
                               int _colNum, 
                               int _bbb, 
                               int _stateNum, 
                               const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed) 
{
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = 1; col <= _colNum; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                if (_varValueIfSAT[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] == 1) {
                    char blockType = AuxFuncs::getBlockAndRelativeIndexByStateIndex (state, _rotationStateNumIsUsed).first;
                    _charBoard[row - 1][col - 1] = blockType;
                }
            }
        }
    }
}

void IO::printBoard(const std::vector<int>& _varValueIfSAT, 
                    int _rowNum,
                    int _colNum,
                    int _bbb,
                    int _stateNum,
                    const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed) 
{
    std::vector<std::vector<char> > charBoard(_rowNum, std::vector<char>(_colNum, ' '));
    charBoardForPrinting(charBoard, _varValueIfSAT, _rowNum, _colNum, _bbb, _stateNum, _rotationStateNumIsUsed);
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = 1; col <= _colNum; ++col) {
            std::cout << charBoard[row - 1][col - 1];
        }
        std::cout << std::endl;
    }
}

void IO::printBoardPNG (const std::vector<int>& _varValueIfSAT, 
                        int _rowNum,
                        int _colNum, 
                        int _bbb, 
                        int _stateNum, 
                        const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed) 
{
    const unsigned cellWidth = 100;
    const unsigned borderWidth = 20;
    const unsigned width = (cellWidth + borderWidth) * _colNum + borderWidth;
    const unsigned height = (cellWidth + borderWidth) * _rowNum + borderWidth;

    // Create a vector to store pixel values (RGBA)
    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    // charBoard
    std::vector<std::vector<char> > charBoard(_rowNum, std::vector<char>(_colNum, ' '));
    charBoardForPrinting(charBoard, _varValueIfSAT, _rowNum, _colNum, _bbb, _stateNum, _rotationStateNumIsUsed);
    
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            size_t index = 4 * (y * width + x);
            if (width - x <= borderWidth || height - y <= borderWidth) {
                for (int i = 0; i < 3; ++i) image[index + i] = 0;
                image[index + 3] = 255;
            }
            else {
                int col = x / (cellWidth + borderWidth) + 1;
                int row = y / (cellWidth + borderWidth) + 1;
                char blockType = charBoard[row - 1][col - 1];
                if (x % (cellWidth + borderWidth) < borderWidth || y % (cellWidth + borderWidth) <= borderWidth) {
                    for (int i = 0; i < 3; ++i) image[index + i] = 0;
                    image[index + 3] = 255;
                }
                else {
                    for (int i = 0; i < 3; ++i) image[index + i] = TetrisData::getBlockColor()[blockType][i];
                    image[index + 3] = 255;
                }
            }  
        }
    }

    // Save the image to a file
    if (lodepng::encode("outputs/output.png", image, width, height) == 0) { 
        std::cout << "| Board layout saved in /outputs.         |" << std::endl;
    } else {
        std::cerr << "Error saving image." << std::endl;
    }
}