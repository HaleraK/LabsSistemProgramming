#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

// 7.3
void displayNum(unsigned int num);

// 7.4 v8
unsigned int cycleShiftBits(unsigned int value, short shiftRight);

// 7.5.1
int packDate(unsigned int moth, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);

// 7.5.2
unsigned int[] unPackDate(unsigned int packedDate);

// 7.6
unsigned char[] getCountOnes();

// 7.6
unsigned char[] getCountZeros();

// 7.6 v8
short countZerosBits1(unsigned int input);
short countZerosBits2(unsigned int input);

int main() {

  unsigned int num;
  unsigned int[5] nums;
  unsigned char bitsMasOnes[256];
  unsigned char bitsMasZeros[256];

  cout << "7.3 output num and in binary form\n" << endl;
  displayNum(2000000000);
  cout << "\n--------------------------------\n\n" << endl;

  cout << "7.4 v8 shift bits right\n" << endl;
  displayNum(cycleShiftBits(2000000000, 3));
  cout << "\n--------------------------------\n\n" << endl;

  cout << "7.5.1 input and pack moth, day, hour, min, sec\n" << endl;
  cout << "moth" << displayNum(1);
  cout << "day" << displayNum(1);
  cout << "hour" << displayNum(1);
  cout << "min" << displayNum(1);
  cout << "sec" << displayNum(1);
  num = packDate(1, 1, 1, 1, 1);
  displayNum(num);
  cout << "\n--------------------------------\n\n" << endl;

  cout << "7.5.2 unpack date data\n" << endl;
  nums = unPackDate(num);
  cout << "moth" << displayNum(nums[0]);
  cout << "day" << displayNum(nums[1]);
  cout << "hour" << displayNum(nums[2]);
  cout << "min" << displayNum(nums[3]);
  cout << "sec" << displayNum(nums[4]);
  cout << "--------------------------------\n\n" << endl;

  cout << "7.6 get array of count ones\n" << endl;
  bitsMasOnes = getCountOnes();
  for (short i = 0; i<bitsMasOnes.length; i++) {
    cout << i << " " << end;
    displayNum(bitsMasOnes[i]);
    cout << endl;
  }
  cout << "--------------------------------\n\n" << endl;

  cout << "7.6 get array of count zeros\n" << endl;
  bitsMasZeros = getCountZeros();
  for (short i = 0; i<bitsMasZeros.length; i++) {
    cout << i << " " << end;
    displayNum(bitsMasZeros[i]);
    cout <<  endl;
  }
  cout << "--------------------------------\n\n" << endl;

  cout << "7.6.8 v8 count zeros variant1\n" << endl;
  displayNum(2000000000);
  cout << "\n" << endl;
  displayNum(countZerosBits1(2000000000));
  cout << "\n--------------------------------\n\n" << endl;

  cout << "7.6.8 v8 count zeros variant2\n" << endl;
  displayNum(2000000000);
  cout << "\n" << endl;
  displayNum(countZerosBits2(2000000000));
  cout << "\n--------------------------------\n\n" << endl;

  system("PAUSE");
  return 0;
}

// 7.3
void displayNum(unsigned int num) {
  cout << num << " = ";
  unsigned int mask = 1 << 31;

  for (short i = 0; i<32; i++) {
    cout << (num & mask);
    mask >>= 1;
  }

  cout << endl;
};

// 7.4 v8
unsigned int cycleShiftBits(unsigned int value, short shiftRight) {

  unsigned int tmp = 0;
  unsigned int tmp2 = 0;
  unsigned int mask = 1;

  //InitialValuePrint(value);
  for (short i =1; i<=shiftRight;i++) {
	 if (value & mask) {
	  tmp = value >> 1;
    tmp2 = value << 31;
		value = tmp | tmp2;

	 } else {
		value >>= 1;
	 }
  }

	//DisplayBits(value);
	return value;

}

// 7.5.1
int packDate(unsigned int moth, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second) {

  unsigned int tmp = 0;
  unsigned int displayMask = 1 << 31;
  unsigned int value = 0;

  value = second;
  value |= minute << 6;
  value |= hour << 12;
  value |= day << 17;
  value |= moth << 22;

  return value;

}

// 7.5.2
unsigned int[] unPackDate(unsigned int packedDate) {

  unsigned int mask = 0;
  unsigned int[5] arr;

  mask = 63;
  unsigned int second = packedDate & mask;
  arr[4] = second;

  mask = 63;
  unsigned int minute = (packedDate >> 6) & mask;
  arr[3] = minute;

  mask = 31;
  unsigned int hour = (packedDate >> 12) & mask;
  arr[2] = hour;

  mask = 31;
  unsigned int day = (packedDate >> 17) & mask;
  arr[1] = day;

  mask = 15;
  unsigned int moth = (packedDate >> 22) & mask;
  arr[0] = moth;

  return arr;
}

// 7.6
unsigned char[] getCountOnes() {

  short tmp,tmp2;
  unsigned char bitsMas[256];

  for (short i = 0; i<256; i++) {

    tmp = i;
    for (short i = 0; i<8 i++){
      tmp2 += (tmp >> i) & 1;
    }
    bitsMas[i] = tmp2;

  }

  return bitsMas;
}

// 7.6
unsigned char[] getCountZeros() {

  short tmp,tmp2;
  unsigned char bitsMas[256];

  for (short i = 0; i<256; i++) {

    tmp = i ^ 0b11111111;
    for (short i = 0; i<8 i++){
      tmp2 += (tmp >> i) & 1;
    }
    bitsMas[i] = tmp2;

  }

  return bitsMas;
}

// 7.6 v8 version1
short countZerosBits1(unsigned int input) {

  int tmp;
  short countZeros;

  tmp = input ^ 4294967295;
  for (short i = 0; i<32 i++) {
    countZeros += (tmp >> i) & 1;
    //можно сдвигать конечноже маску, но тут сдвигаю само число
  }

  return countZeros;
}

// 7.6 v8 version2
short countZerosBits2(unsigned int input) {

  int tmp, j;
  short countZeros = 0;

  unsigned char bitsMas[256] = getCountZeros();

  tmp = input ^ 4294967295;
  for (short i = 0; i<4 i++) {
    j = (tmp >> (i*8)) & 0b11111111;
    countZeros += bitsMas[j];
  }

  return countZeros;
}
