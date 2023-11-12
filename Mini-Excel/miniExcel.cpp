#include <iostream>
#include <vector>
#include <string>

using namespace std;
template <typename T>
class MiniExcel
{
public:
    class Cell
    {

    public:
        string value;
        Cell *left;
        Cell *right;
        Cell *up;
        Cell *down;
        Cell(string value)
        {
            this->value = value;
            left = NULL;
            right = NULL;
            up = NULL;
            down = NULL;
        }
    };

    MiniExcel(int rows = 5, int cols = 5)
    {
        start = nullptr;
        current = nullptr;
        this->rows = rows;
        this->cols = cols;
        initializeGrid(rows, cols, "A");
    }

    void initializeGrid(int rows, int cols, string value)
    { // Create the top-left cell.
        char a = 'A';
        Cell *current_cell = new Cell(value + to_string(0));
        start = current_cell;
        current = current_cell;

        // Create the first row.
        for (int i = 0; i < cols - 1; i++)
        {
            Cell *newCell = new Cell(char(++a) + to_string(0));
            current_cell->right = newCell;
            newCell->left = current_cell;
            current_cell = newCell;
        }
        // Create the remaining rows.
        Cell *firstCellInRow = current;
        for (int i = 1; i < rows; i++) // Fixed the loop limit to create the correct number of rows.
        {
            // int no = i - 1;
            a = 'A';
            Cell *newRowCell = new Cell(char(a++) + to_string(i));
            current = newRowCell;
            firstCellInRow->down = newRowCell;
            newRowCell->up = firstCellInRow;
            current_cell = newRowCell;

            // Create cells in the current row.
            for (int j = 1; j < cols; j++) // Fixed the loop limit to create the correct number of cells in each row.
            {
                Cell *newCell = new Cell(char(a++) + to_string(i));
                current_cell->right = newCell;
                newCell->left = current_cell;
                current_cell = newCell;
                firstCellInRow = firstCellInRow->right; // Move to the right in the first row.
                current_cell->up = firstCellInRow;      // Connect the cell to the cell above it.
                firstCellInRow->down = current_cell;    // Connect the cell above to the current cell.
            }
            firstCellInRow = newRowCell; // Move to the next row.
        }
    }

    void displayGrid()
    {
        Cell *currentCell = start;
        while (currentCell)
        {
            Cell *row_Cell = currentCell;
            while (row_Cell)
            {
                cout << row_Cell->value << "|";
                row_Cell = row_Cell->right;
            }
            cout << endl;
            currentCell = currentCell->down;
        }
    }

    Cell *currentCell()
    {
        return current;
    }

    // Function to insert a row below the current cell
    void InsertRowBelow()
    {

        // Create a new row
        Cell *newRow = nullptr;
        Cell *currentRow = rowStartCell(current);
        Cell *rowBelowCurrent = rowStartCell(current)->down;
        // Initialize newRow with space character
        for (int i = 0; currentRow != nullptr; i++)
        {
            Cell *newRowCell = new Cell("B" + to_string(i + 1));
            newRowCell->left = newRow;
            if (newRow != nullptr)
                newRow->right = newRowCell;

            newRowCell->up = currentRow;
            currentRow->down = newRowCell;
            newRow = newRowCell;
            currentRow = currentRow->right;
        }
        newRow = rowStartCell(newRow);
        for (int i = 0; rowBelowCurrent != nullptr; i++)
        {
            newRow->down = rowBelowCurrent;
            rowBelowCurrent->up = newRow;
            newRow = newRow->right;
            rowBelowCurrent = rowBelowCurrent->right;
        }
        rows++;
    }

    // Function to insert a row above the current cell
    void InsertRowAbove()
    {
        // Create a new row
        Cell *newRow = nullptr;
        Cell *currentRow = rowStartCell(current);
        Cell *rowUpCurrent = rowStartCell(current)->up;
        // Initialize newRow with space character
        for (int i = 0; currentRow != nullptr; i++)
        {
            Cell *newRowCell = new Cell("B" + to_string(i + 1));
            newRowCell->left = newRow;
            if (newRow != nullptr)
                newRow->right = newRowCell;

            newRowCell->down = currentRow;
            currentRow->up = newRowCell;
            newRow = newRowCell;
            currentRow = currentRow->right;
        }

        newRow = rowStartCell(newRow);
        if (!rowUpCurrent)
            start = newRow;

        for (int i = 0; rowUpCurrent != nullptr; i++)
        {
            rowUpCurrent->down = newRow;
            newRow->up = rowUpCurrent;
            rowUpCurrent = rowUpCurrent->right;
            newRow = newRow->right;
        }
        rows++;
    }

    // Function to insert a column to left of the current cell
    void InsertColumnToLeft(string val)
    {
        Cell *currentColumn = colStartCell(current);
        cout << currentColumn->value;
        Cell *columnToLeft = currentColumn->left;
        Cell *newCol = nullptr;
        for (int i = 0; currentColumn != nullptr; i++)
        {
            Cell *newCell = new Cell(val + to_string(i));
            newCell->up = newCol;
            if (newCol != nullptr)
                newCol->down = newCell;
            newCell->right = currentColumn;
            currentColumn->left = newCell;
            newCol = newCell;
            currentColumn = currentColumn->down;
        }

        newCol = colStartCell(newCol);
        if (columnToLeft == nullptr)
            start = newCol;
        for (int i = 0; columnToLeft != nullptr; i++)
        {
            columnToLeft->right = newCol;
            newCol->left = columnToLeft;
            columnToLeft = columnToLeft->down;
            newCol = newCol->down;
        }
        cols++;
    }

    // Function to insert a column to right of the current cell
    void InsertColumnToRight(string val)
    {
        Cell *currentColumn = colStartCell(current);
        Cell *columnToRight = currentColumn->right;
        Cell *newCol = nullptr;
        for (int i = 0; currentColumn != nullptr; i++)
        {
            Cell *newCell = new Cell(val + to_string(i));
            newCell->up = newCol;
            if (newCol != nullptr)
                newCol->down = newCell;
            newCell->left = currentColumn;
            currentColumn->right = newCell;
            newCol = newCell;
            currentColumn = currentColumn->down;
        }

        newCol = colStartCell(newCol);

        for (int i = 0; columnToRight != nullptr; i++)
        {
            columnToRight->left = newCol;
            newCol->right = columnToRight;
            columnToRight = columnToRight->down;
            newCol = newCol->down;
        }
        cols++;
    }

    // Function to delete current row
    void DeleteRow()
    {
        Cell *currentRow = rowStartCell(current);
        Cell *rowAboveCurrent = currentRow->up;
        Cell *rowBelowCurrent = currentRow->down;

        for (int i = 0; rowAboveCurrent != nullptr && rowBelowCurrent != nullptr; i++)
        {
            rowAboveCurrent->down = rowBelowCurrent;
            rowBelowCurrent->up = rowAboveCurrent;
            rowAboveCurrent = rowAboveCurrent->right;
            rowBelowCurrent = rowBelowCurrent->right;
        }

        if (!currentRow->up)
        {
            for (int i = 0; rowBelowCurrent != nullptr; i++)
            {
                rowBelowCurrent->up = nullptr;
                rowBelowCurrent = rowBelowCurrent->right;
            }
        }
        if (!currentRow->down)
        {
            for (int i = 0; rowAboveCurrent != nullptr; i++)
            {
                rowAboveCurrent->down = nullptr;
                rowAboveCurrent = rowAboveCurrent->right;
            }
        }
        rows--;
    }

    // Function to delete a current column

    void DeleteColumn()
    {
        Cell *currentCol = colStartCell(current);
        Cell *colToLeft = currentCol->left;
        Cell *colToRight = currentCol->right;

        for (int i = 0; colToLeft != nullptr && colToRight != nullptr; i++)
        {
            colToLeft->right = colToRight;
            colToRight->left = colToLeft;
            colToLeft = colToLeft->down;
            colToRight = colToRight->down;
        }

        if (!currentCol->left)
        {
            start = colToRight;
            while (colToRight != nullptr)
            {
                colToRight->left = nullptr;
                colToRight = colToRight->down;
            }
        }
        if (!currentCol->right)
        {
            while (colToLeft != nullptr)
            {
                colToLeft->right = nullptr;
                colToLeft = colToRight->down;
            }
        }
        cols--;
    }

    // Function to clear a column

    void ClearColumn()
    {
        Cell *currentCol = colStartCell(current);
        while (currentCol)
        {
            currentCol->value = "";
            currentCol = currentCol->down;
        }
    }

    // Function to clear a row

    void ClearRow()
    {
        Cell *currentRow = rowStartCell(current);
        while (currentRow)
        {
            currentRow->value = "";
            currentRow = currentRow->right;
        }
    }

    // Function to insert a new cell and shift the current cell to right
    void InsertCellByRightShift(string value)
    {
        Cell *newCell = new Cell(value);
        Cell *currentCell = current;
        Cell *cellUpCurrent = currentCell->up;
        Cell *cellDownCurrent = currentCell->down;
        Cell *cellRightCurrent = currentCell->right;
        Cell *cellLeftCurrent = currentCell->left;
        current = newCell;
        if (start == current)
            start = newCell;
        while (currentCell)
        {
            newCell->right = currentCell;
            if (cellLeftCurrent)
            {
                currentCell->left = newCell;
                newCell->left = cellLeftCurrent;
                cellLeftCurrent->right = newCell;
                cellLeftCurrent = cellLeftCurrent->right;
            }
            newCell = currentCell;
            currentCell = currentCell->right;
        }

        newCell = current;
        while (cellUpCurrent)
        {
            newCell->up = cellUpCurrent;
            cellUpCurrent->down = newCell;
            cellUpCurrent = cellUpCurrent->right;
            newCell = newCell->right;
        }
        newCell = current;
        while (cellDownCurrent)
        {
            newCell->down = cellDownCurrent;
            cellDownCurrent->up = newCell;
            cellDownCurrent = cellDownCurrent->right;
            newCell = newCell->right;
        }
        cols++;
    }

    // Function to insert a new cell and shift the current cell to down
    void InsertCellByDownShift(string value)
    {
        Cell *newCell = new Cell(value);
        Cell *currentCell = current;
        Cell *cellUpCurrent = currentCell->up;
        Cell *cellDownCurrent = currentCell->down;
        Cell *cellLeftCurrent = currentCell->left;
        Cell *cellRightCurrent = currentCell->right;

        current = newCell;
        if (start == current)
            start = newCell;

        while (currentCell)
        {
            newCell->down = currentCell;
            if (cellUpCurrent)
            {
                currentCell->up = newCell;
                cellUpCurrent->down = newCell;
                newCell->up = cellUpCurrent;
                cellUpCurrent = cellUpCurrent->down;
            }
            newCell = currentCell;
            currentCell = currentCell->down;
        }
        newCell = current;
        while (cellLeftCurrent)
        {
            newCell->left = cellLeftCurrent;
            cellLeftCurrent->right = newCell;
            cellLeftCurrent = cellLeftCurrent->down;
            newCell = newCell->down;
        }

        newCell = current;
        while (cellRightCurrent)
        {
            newCell->right = cellRightCurrent;
            cellRightCurrent->left = newCell;
            cellRightCurrent = cellRightCurrent->down;
            newCell = newCell->down;
        }
        rows++;
    }

    // Function to delete the current cell and shift cell leftwards

    void DeleteCellByLeftShift()
    {
        Cell *currentCell = current;
        while (currentCell->right)
        {
            Cell *next = currentCell->right;
            swap(currentCell->value, next->value);
            currentCell = next;
        }
        if (!currentCell->right && currentCell->left)
        {
            currentCell->left->right = nullptr;
        }

        if (currentCell->up)
        {
            currentCell->up->down = nullptr;
        }
        if (currentCell->down)
        {
            currentCell->down->up = nullptr;
        }
    }

    // Function to delete the current cell and shift cell upwards

    void DeleteCellByUpShift()
    {
        Cell *currentCell = current;
        while (currentCell->down)
        {
            Cell *next = currentCell->down;
            swap(currentCell->value, next->value);
            currentCell = next;
        }

        if (!currentCell->down && currentCell->up)
        {
            currentCell->up->down = nullptr;
            if (currentCell->right && !currentCell->left)
            {
                Cell *temp = currentCell->right;
                Cell *upCell = currentCell->up;
                while (temp && upCell)
                {
                    upCell->down = temp;
                    temp->up = upCell;
                    temp = temp->right;
                    upCell = upCell->right;
                }
            }
        }
        if (currentCell->left && currentCell->right)
        {
            currentCell->left->right = currentCell->right;
        }
        if (!current->left && !current->down && current->right)
        {
            current = current->right;
        }
    }

    // Operations Section

    // Function to get range sum of row/column

    int GetRangeSum(Cell *rangeStart, Cell *rangeEnd)
    {
        bool column = whetherRoworColumn(rangeStart, rangeEnd);
        int sum = 0;
        if (!column)
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->right)
            {
                // As the value is mix of string and integer so (stoi) will help to distinguish between them
                try
                {
                    int cellValue = stoi(temp->value);
                    sum += cellValue;
                }
                catch (const invalid_argument &e)
                {
                }
                temp = temp->right;
            }
            Cell *cell = new Cell(to_string(sum));
            insertCellAtRow(rangeStart, cell);
        }
        else
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->down)
            {
                try
                {
                    int cellValue = stoi(temp->value);
                    sum += cellValue;
                }
                catch (const invalid_argument &e)
                {
                }
                temp = temp->down;
            }
            Cell *cell = new Cell(to_string(sum));
            insertCellAtCol(rangeStart, cell);
        }
        return sum;
    }

    // Function to get range sum of row/column

    int GetRangeAverage(Cell *rangeStart, Cell *rangeEnd)
    {
        bool column = whetherRoworColumn(rangeStart, rangeEnd);
        int sum = 0;
        int nos = 0;
        if (!column)
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->right)
            {
                try
                {
                    int cellValue = stoi(temp->value);
                    sum += cellValue;
                    nos++;
                }
                catch (const invalid_argument &e)
                {
                }
                temp = temp->right;
            }
            Cell *cell = new Cell(to_string(sum / nos));
            insertCellAtRow(rangeStart, cell);
        }
        else
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->down)
            {
                try
                {
                    int cellValue = stoi(temp->value);
                    sum += cellValue;
                    nos++;
                }
                catch (const invalid_argument &e)
                {
                }
                temp = temp->down;
            }
            Cell *cell = new Cell(to_string(sum / nos));
            insertCellAtCol(rangeStart, cell);
        }
        return sum / nos;
    }

    // Function to find minimum number from a particular range
    int GetRangeMin(Cell *rangeStart, Cell *rangeEnd)
    {
        bool column = whetherRoworColumn(rangeStart, rangeEnd);
        int minNo = INT_MAX;
        if (!column)
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->right)
            {
                if (temp->right && temp)
                {
                    try
                    {
                        int cellValue = stoi(temp->value);
                        minNo = min(minNo, cellValue);
                    }
                    catch (const invalid_argument &e)
                    {
                        // Handle non-integer cell values if necessary
                    }
                }
                temp = temp->right;
            }
            Cell *cell = new Cell(to_string(minNo));
            insertCellAtRow(rangeStart, cell);
        }
        else
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->down)
            {
                if (temp->down && temp)
                {
                    try
                    {
                        int cellValue = stoi(temp->value);
                        minNo = min(minNo, cellValue);
                    }
                    catch (const invalid_argument &e)
                    {
                        // Handle non-integer cell values if necessary
                    }
                }
                temp = temp->down;
            }
            Cell *cell = new Cell(to_string(minNo));
            insertCellAtCol(rangeStart, cell);
        }
        return minNo;
    }
    // Function to find maximum number from a particular range
    int GetRangeMax(Cell *rangeStart, Cell *rangeEnd)
    {
        bool column = whetherRoworColumn(rangeStart, rangeEnd);
        int maxNo = INT_MIN;
        if (!column)
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->right)
            {
                if (temp->right && temp)
                    try
                    {
                        int cellValue = stoi(temp->value);
                        maxNo = max(maxNo, cellValue);
                    }
                    catch (const invalid_argument &e)
                    {
                        // Handle non-integer cell values if necessary
                    }
                temp = temp->right;
            }
            Cell *cell = new Cell(to_string(maxNo));
            insertCellAtRow(rangeStart, cell);
        }
        else
        {
            Cell *temp = rangeStart;
            while (temp != rangeEnd->down)
            {
                if (temp->down && temp)
                    try
                    {
                        int cellValue = stoi(temp->value);
                        maxNo = max(maxNo, cellValue);
                    }
                    catch (const invalid_argument &e)
                    {
                        // Handle non-integer cell values if necessary
                    }
                temp = temp->down;
            }
            Cell *cell = new Cell(to_string(maxNo));
            insertCellAtCol(rangeStart, cell);
        }
        return maxNo;
    }

    // Function to copy the contents from particular range

    vector<T> Copy(Cell *startRange, Cell *endRange)
    {
        vector<T> new_range;
        bool column = whetherRoworColumn(startRange, endRange);
        if (!column)
        {
            Cell *temp = startRange;
            while (temp != endRange->right)
            {
                new_range.push_back(temp->value);
                temp = temp->right;
            }
        }
        else
        {
            Cell *temp = startRange;
            while (temp != endRange->down)
            {
                new_range.push_back(temp->value);
                temp = temp->down;
            }
        }
        return new_range;
    }
    // Function to cut the contents from particular range

    vector<T> Cut(Cell *startRange, Cell *endRange)
    {
        vector<T> new_range;
        bool column = whetherRoworColumn(startRange, endRange);
        if (!column)
        {
            Cell *temp = startRange;
            while (temp != endRange->right)
            {
                new_range.push_back(temp->value);
                temp->value = " ";
                temp = temp->right;
            }
        }
        else
        {
            Cell *temp = startRange;
            while (temp != endRange->down)
            {
                new_range.push_back(temp->value);
                temp->value = " ";
                temp = temp->down;
            }
        }
        return new_range;
    }

    // Function to paste the data of cut/copied cells

    void Paste(vector<T> &data, string rowOrCol)
    {
        int dataIndex = 0; // Index to access the data vector
        Cell *currentCell = current;

        if (rowOrCol == "row")
        {
            currentCell = rowStartCell(current);
            while (dataIndex < data.size())
            {
                currentCell->value = data[dataIndex];
                dataIndex++;
                if (dataIndex < data.size())
                {
                    if (currentCell->right)
                    {
                        currentCell = currentCell->right;
                    }
                    else
                    {
                        // setCurrent(temp);
                        Cell *newCell = new Cell(" ");
                        currentCell->right = newCell;
                        newCell->left = currentCell;
                        currentCell = newCell;
                    }
                }
            }
        }
        else
        {
            currentCell = colStartCell(current);
            while (dataIndex < data.size())
            {
                if (dataIndex < data.size())

                {
                    currentCell->value = data[dataIndex];
                    dataIndex++;
                    if (currentCell->down)
                    {
                        currentCell = currentCell->down;
                    }
                    else
                    {
                        Cell *newCell = new Cell(" ");
                        currentCell->down = newCell;
                        newCell->up = currentCell;
                        currentCell = newCell;
                    }
                }
            }
        }
    }

    Cell *
    getMidCell()
    {
        int midRow = rows / 2;
        int midCol = cols / 2;
        Cell *midCell = start;
        for (int i = 0; i < midRow; i++)
        {
            midCell = midCell->down;
        }
        for (int i = 0; i < midCol; i++)
        {
            midCell = midCell->right;
        }
        return midCell;
    }

    Cell *getCell(int rowIndex, int columnIndex)
    {
        Cell *startCell = start;

        for (int i = 0; i < rowIndex; i++)
        {
            startCell = startCell->down;
        }
        for (int j = 0; j < columnIndex; j++)
        {
            startCell = startCell->right;
        }

        return startCell;
    }

    void setCurrent(Cell *current)
    {
        this->current = current;
    }

private:
    Cell *start;
    Cell *current;
    int rows;
    int cols;
    vector<vector<Cell *>> grid;

    Cell *rowStartCell(Cell *current)
    {
        Cell *currentCell = current;
        while (currentCell->left)
        {
            currentCell = currentCell->left;
        }
        return currentCell;
    }
    Cell *colStartCell(Cell *current)
    {
        Cell *currentCell = current;
        while (currentCell->up)
        {
            currentCell = currentCell->up;
        }
        return currentCell;
    }
    bool whetherRoworColumn(Cell *rangeStart, Cell *rangeEnd)
    {
        Cell *temp = rangeStart;
        while (temp != nullptr)
        {
            if (temp == rangeEnd)
                return true;
            temp = temp->down;
        }
        return false;
    }

    void insertCellAtRow(Cell *current, Cell *cell)
    {
        Cell *temp = current;
        while (temp->right)
            temp = temp->right;
        temp->right = cell;
        cell->left = temp;
    }
    void insertCellAtCol(Cell *current, Cell *cell)
    {
        Cell *temp = current;
        while (temp->down)
            temp = temp->down;
        temp->down = cell;
        cell->up = temp;
    }

    void setCellValue(int rowIndex, int colIndex, T value)
    {
        Cell *cell = getCell(rowIndex, colIndex);
        cell->value = value;
    }
};

int main()
{
    MiniExcel<string> excel;
    excel.displayGrid();
}