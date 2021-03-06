#include "src\snipper.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

void foo(){
  // Creates a hidden popup window, sets global variables etc.
  Snipper snipper;

  // Pointer that'll point to pixel array
  const RGBQUAD* snipPixels;

  /* Takes the screenshot of window after 2 seconds and paints it in window, makes the user take a snipshot
  and returns the array of snipshot's pixels.
  snipshot's width and height are accessible via snipper.width and snipper.height
  NOTE: If user presses ESC key instead of taking a snipshot, return values is NULL*/

  snipPixels=snipper.TakeASnip(2000);

  /* Write the rgb pixel array to the file*/
  vector<unsigned char> pixels;
  ofstream stream("testData",ofstream::binary);
  
  for(int i=0;i<snipper.height;i++){
    for(int j=0;j<snipper.width;j++){
      pixels.push_back(snipPixels[snipper.width*i+j].rgbRed);
      pixels.push_back(snipPixels[snipper.width*i+j].rgbGreen);
      pixels.push_back(snipPixels[snipper.width*i+j].rgbBlue);
    }
  }

  stream.write((char*)pixels.data(),pixels.size());
  stream.close();
}

int main(){

  // hiding the console window (not necessary)
  ShowWindow(GetConsoleWindow(), SW_HIDE);

  thread myThread(foo);
  myThread.join();
  
  return 0;
}
