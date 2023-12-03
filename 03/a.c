#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DYN_LABEL_IMPL(NAME, LINE) NAME##LINE
#define DYN_LABEL(NAME, LINE) DYN_LABEL_IMPL(NAME, LINE)
#define GET_CHAR_AT_POS(OUT, X, Y)                          \
  getCharAtPos_row = (Y);                                   \
  getCharAtPos_col = (X);                                   \
  pGetCharAtPos_retAddr = &&DYN_LABEL(gcap_ret_, __LINE__); \
  goto get_char_at_pos;                                     \
  DYN_LABEL(gcap_ret_, __LINE__) : OUT = getCharAtPos_ret;

#define ADD_AND_ERASE_NUMBER(X, Y)                              \
  addAndEraseNumber_row = (Y);                                  \
  addAndEraseNumber_col = (X);                                  \
  pAddAndEraseNumber_retAddr = &&DYN_LABEL(gcap_ret, __LINE__); \
  goto add_and_erase_number;                                    \
  DYN_LABEL(gcap_ret, __LINE__) :

int main(int argc, char **pArgv)
{
  char *aLines[200];
  memset(aLines, 0, sizeof(aLines));

  int lineLen = 0;
  int numLines = 0;

  int totalPartNumbers = 0;

  goto real_main;

// Functions
get_char_at_pos:
  int getCharAtPos_row;
  int getCharAtPos_col;
  char getCharAtPos_ret = '.';
  void *pGetCharAtPos_retAddr;

  void *aIsInvalidAddrJumpTable[] = {&&get_symbol_at_pos_do_read, pGetCharAtPos_retAddr};
  goto *aIsInvalidAddrJumpTable[(getCharAtPos_row < 0) || (getCharAtPos_row >= numLines) || (getCharAtPos_col < 0) || (getCharAtPos_col >= lineLen)];

get_symbol_at_pos_do_read:
  getCharAtPos_ret = aLines[getCharAtPos_row][getCharAtPos_col];
  goto *pGetCharAtPos_retAddr;
end_get_char_at_pos:
  goto end_get_char_at_pos;

add_and_erase_number:
  int addAndEraseNumber_row;
  int addAndEraseNumber_col;
  void *pAddAndEraseNumber_retAddr;

add_and_erase_number_move_left:
  char leftChar = 0;
  GET_CHAR_AT_POS(leftChar, addAndEraseNumber_col - 1, addAndEraseNumber_row);

  void *aFoundStartOfNumberJumpTable[] = {&&add_and_erase_number_still_searching, &&add_and_erase_number_found_start};
  goto *aFoundStartOfNumberJumpTable[isdigit(leftChar) == 0];
add_and_erase_number_still_searching:
  addAndEraseNumber_col -= 1;
  goto add_and_erase_number_move_left;

add_and_erase_number_found_start:
  int numFound = 0;
  int numLen = 0;
  (void)sscanf(&aLines[addAndEraseNumber_row][addAndEraseNumber_col], "%d%n", &numFound, &numLen);
  memset(aLines[addAndEraseNumber_row] + addAndEraseNumber_col, '.', numLen);
  totalPartNumbers += numFound;
  goto *pAddAndEraseNumber_retAddr;

end_add_and_erase_number:
  goto end_add_and_erase_number;

real_main:
  FILE *pInput = fopen(pArgv[1], "r");

  size_t bufSize = 0;

read_all_lines:
read_next_line:
  bufSize = 0;
  int getlineResult = getline(&aLines[numLines++], &bufSize, pInput);

  void *aEofJumpTable[] = {&&erase_newline, &&end_of_file};
  goto *aEofJumpTable[getlineResult < 0];

erase_newline:
  aLines[numLines - 1][getlineResult - 1] = '\0';
  goto read_next_line;

end_of_file:
  numLines -= 1;
  lineLen = strlen(aLines[0]);
  int row = 0;
  int col = 0;

search_for_symbol:
  void *aIsSymbolJumpTable[] = {&&symbol_not_found, &&symbol_found};
  goto *aIsSymbolJumpTable[(aLines[row][col] != '.') && (!isdigit(aLines[row][col]))];

symbol_not_found:
  col += 1;
  row += col / lineLen;
  col %= lineLen;
  void *aIsEndOfInputJumpTable[] = {&&search_for_symbol, &&end_of_input};
  goto *aIsEndOfInputJumpTable[row == numLines];

symbol_found:

#define CHECK_CELL(dirName, nextDirName, col, row)                                                               \
  char dirName = 0;                                                                                              \
  GET_CHAR_AT_POS(dirName, col, row);                                                                            \
  void *aHandle##dirName##JumpTable[] = {&&symbol_found_check_##nextDirName, &&symbol_found_##dirName##_is_num}; \
  goto *aHandle##dirName##JumpTable[isdigit(dirName) != 0];                                                      \
  symbol_found_##dirName##_is_num : ADD_AND_ERASE_NUMBER(col, row);                                              \
  symbol_found_check_##nextDirName:

  CHECK_CELL(upLeft, up, col - 1, row - 1);
  CHECK_CELL(up, upRight, col, row - 1);
  CHECK_CELL(upRight, left, col + 1, row - 1);
  CHECK_CELL(left, right, col - 1, row);
  CHECK_CELL(right, downLeft, col + 1, row);
  CHECK_CELL(downLeft, down, col - 1, row + 1);
  CHECK_CELL(down, downRight, col, row + 1);
  CHECK_CELL(downRight, none, col + 1, row + 1);

  goto symbol_not_found;

end_of_input:
  printf("%d\n", totalPartNumbers);

  return 0;
}
