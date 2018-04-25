//Shireen Bahadur
//ssb160430@utdalas.edu
//CS 3377.502

#include "prog6.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

int main()
{

  WINDOW        *window;
  CDKSCREEN     *cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix 

  // Remember that matrix starts out at 1,1.    
  // Since arrays start out at 0, the first entries                  
  // below ("R0", and "C0") are just placeholders
  //               
  // Finally... make sure your arrays have enough entries given the 
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.                       

  const char    *rowTitles[] = {" ", "A", "B", "C", "D", "E"};
  const char    *columnTitles[] = {" ", "A", "B", "C", "D", "E"};
  int           boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int           boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*               
   * Initialize the Cdk screen.            
   *                       
   * Make sure the putty terminal is large enough     
   */

  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*                                  
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
                          MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
                          boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*                        
   * Dipslay a message                  
   */

  //Open binary file
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  if (!binInfile) {
    cout << "file could not be found. Please try again later." << endl;
    exit(1);
  }

  //buffer char array
  char buff[100];

  BinaryFileHeader *myH = new BinaryFileHeader();

  //read the binary file and store into the myH variable      
  binInfile.read((char*)myH, sizeof(BinaryFileHeader));

  sprintf(buff, "Magic: 0x%X", myH->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buff);
  sprintf(buff, "Version: %"PRIu32, myH->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buff);
  sprintf(buff, "NumRecords: %"PRIu64, myH->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buff);

  //create 4 variables for the first 4 entries in the binary file
  BinaryFileRecord *one = new BinaryFileRecord();
  BinaryFileRecord *two = new BinaryFileRecord();
  BinaryFileRecord *three = new BinaryFileRecord();
  BinaryFileRecord *four = new BinaryFileRecord();

  //open all the files through the entries
  binInfile.read((char*)one, sizeof(BinaryFileRecord));
  binInfile.read((char*)two, sizeof(BinaryFileRecord));
  binInfile.read((char*)three, sizeof(BinaryFileRecord));
  binInfile.read((char*)four, sizeof(BinaryFileRecord));

  //for first entry to calculate string length
  sprintf(buff, "StrLen: %"PRIu8, one->strLength);                                  
  setCDKMatrixCell(myMatrix, 2,1, buff);

  //for second entry to calculate string length      
  sprintf(buff, "StrLen: %"PRIu8, two->strLength);
  setCDKMatrixCell(myMatrix, 3,1, buff);
  
  //for third entry to calculate string length    
  sprintf(buff, "StrLen: %"PRIu8, three->strLength);
  setCDKMatrixCell(myMatrix, 4,1, buff);

  //for forth entry to calculate string length     
  sprintf(buff, "StrLen: %"PRIu8, four->strLength);
  setCDKMatrixCell(myMatrix, 5,1, buff);

  //first entry to print the string out to the matrix
  sprintf(buff, "%s", one->stringBuffer);                                           
  setCDKMatrixCell(myMatrix, 2,2, buff);

  //second entry to print the string out to the matrix 
  sprintf(buff, "%s", two->stringBuffer);
  setCDKMatrixCell(myMatrix, 3,2, buff);

  //third entry to print the string out to the matrix  
  sprintf(buff, "%s", three->stringBuffer);
  setCDKMatrixCell(myMatrix, 4,2, buff);

  //fourth entry to print the string out to the matrix   
  sprintf(buff, "%s", four->stringBuffer);
  setCDKMatrixCell(myMatrix, 5,2, buff);

  //draw matrix again with the boxes filled in
  drawCDKMatrix(myMatrix, true);  

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  //End the screen and free everything up      
  endCDK();
  free(myH);
  binInfile.close();
}
