#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
        Cell *cellLeftCurrent = current->left;
        Cell *cellRightCurrent = current->right;
        Cell *cellUpCurrent = current->up;
        Cell *cellDownCurrent = current->down;
        if (start == currentCell)
            start = cellRightCurrent;

        if (cellLeftCurrent && cellRightCurrent)
        {
            cellLeftCurrent->right = cellRightCurrent;
            cellRightCurrent->left = cellLeftCurrent;
        }

        else if (cellRightCurrent)
        {
            cellRightCurrent->left = nullptr;
        }
        else
        {
            cellLeftCurrent->right = nullptr;
        }
        if (current->right)
            cellRightCurrent = current->right;
        while (cellDownCurrent)
        {
            cellDownCurrent->up = cellRightCurrent;
            if (cellRightCurrent)
            {

                cellRightCurrent->down = cellDownCurrent;
                cellRightCurrent = cellRightCurrent->right;
            }
            cellDownCurrent = cellDownCurrent->right;
        }
        if (current->right)
            cellRightCurrent = current->right;
        while (cellUpCurrent)
        {
            cellUpCurrent->down = cellRightCurrent;
            if (cellRightCurrent)
            {
                cellRightCurrent->up = cellUpCurrent;
                cellRightCurrent = cellRightCurrent->right;
            }
            cellUpCurrent = cellUpCurrent->right;
        }
        cellRightCurrent = current->right;
        if (cellRightCurrent)
            current = current->right;
        else
            current = current->left;
    }
    // Function to delete the current cell and shift cell upwards

    void DeleteCellByUpShift()
    {
        Cell *currentCell = current;
        Cell *cellLeftCurrent = current->left;
        Cell *cellRightCurrent = current->right;
        Cell *cellUpCurrent = current->up;
        Cell *cellDownCurrent = current->down;
        if (start == currentCell)
            start = cellDownCurrent;

        if (cellUpCurrent && cellDownCurrent)
        {
            cellUpCurrent->down = cellDownCurrent;
            cellDownCurrent->up = cellUpCurrent;
        }
        else if (cellUpCurrent)

            cellUpCurrent->down = nullptr;

        else
            cellDownCurrent->up = nullptr;

        if (cellRightCurrent)
            cellRightCurrent = current->right;
        cout << endl;
        while (cellRightCurrent)
        {
            cellRightCurrent->left = cellDownCurrent;
            if (cellDownCurrent)
            {
                if (cellDownCurrent->left && !cellDownCurrent->down)
                {
                    cout << endl
                         << cellDownCurrent->value << " " << cellDownCurrent->left->value << endl;
                    cellRightCurrent->left = cellDownCurrent->left;
                }
                else
                {
                    cellDownCurrent->right = cellRightCurrent;
                    cellDownCurrent = cellDownCurrent->down;
                }
            }
            cellRightCurrent = cellRightCurrent->down;
        }
        if (cellLeftCurrent)
            cellLeftCurrent = current->left;
        cellDownCurrent = current->down;
        while (cellLeftCurrent)
        {
            cellLeftCurrent->right = cellDownCurrent;
            cout << cellLeftCurrent->value << " ";
            if (cellDownCurrent)
            {
                if (cellDownCurrent->right && !cellDownCurrent->down)
                {
                    cout << endl
                         << cellDownCurrent->value << " " << cellDownCurrent->right->value << endl;
                    cellLeftCurrent->right = cellDownCurrent->right;
                }
                else
                {
                    cellDownCurrent->left = cellLeftCurrent;
                    cellDownCurrent = cellDownCurrent->down;
                }
            }

            cellLeftCurrent = cellLeftCurrent->down;
        }

        if (current->down)
            current = current->down;
        else
            current = current->right;
    }

    Cell *getMidCell()
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
};

int main()
{
    MiniExcel excel;
    excel.displayGrid();
}