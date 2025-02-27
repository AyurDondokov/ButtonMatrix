# ButtonMatrix
## How the program works:
- Configuring pins:
Strings (FIRST_ROW and SECOND_ROW) are configured as outputs.
The columns (FIRST_COL and SECOND_COL) are configured as pull-up inputs.
- Scanning buttons:
The program sequentially sets rows to different states (0 or 1) and checks if there is a closure between the row and column.
If there is a short circuit, then the corresponding button is pressed.
- Output of the result:
If at least one button was pressed, the program displays the message "Pressed button(s):" and the numbers of the pressed buttons separated by a space.
