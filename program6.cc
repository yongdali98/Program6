/*
  Yongda Li
  yxl161830@utdallas.edu
  CS3377.502
*/

#include "program6.h"

using namespace std;

int main(int argc, char **argv)
{
  WINDOW    *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries below ("R0", and "C0") are just placeholders
  // Finally... make sure your arrays have enough entries given the values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT above.

  const char *rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char *columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /* Initialize the Cdk screen */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /* Create the matrix.  Need to manually cast (const char**) to (char **) */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  char temp[100];
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binaryInfile ("cs3377.bin", ios::in | ios:: binary);

  /* If file is not open, print error and exit*/
  if(!binaryInfile.is_open())
    {
      cout << "ERROR, Cannot open the file!" << endl;
      exit(1);
    }

  /* Read the binary file and setup the matrix*/
  binaryInfile.read((char*) myHeader, sizeof(BinaryFileHeader));
  sprintf(temp, "Magic: %s", convertIntToHex(myHeader->magicNumber));
  setCDKMatrixCell(myMatrix, 1, 1, temp);
  sprintf(temp, "Version: %u", (unsigned int)myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, temp);
  sprintf(temp, "Version: %u", (unsigned int)myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, temp);

  BinaryFileRecord *myRecord = new BinaryFileRecord();

  /* Read the binary file and setup the matrix*/
  for(unsigned int i = 0; i < myHeader->numRecords && i < 4; i++)
    {
      binaryInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
      sprintf(temp, "strlen: %u", (unsigned int)myRecord->strLength);
      setCDKMatrixCell(myMatrix, i + 2, 1, temp);
      setCDKMatrixCell(myMatrix, i + 2, 2, myRecord->stringBuffer);
    }

  /* Dipslay a message */
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* close ifstream*/
  binaryInfile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  /* Cleanup screen */
  endCDK();

  return 0;
}
