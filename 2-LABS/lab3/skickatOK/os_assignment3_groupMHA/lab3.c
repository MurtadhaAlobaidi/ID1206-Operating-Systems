/* LAB3 Operating Systems ID1206
 *  Group MHA
 */
#include <stdio.h>
#include <string.h>

struct Address
{
  int logicalAddress;
  int physicalAddress;
};

struct Memmory
{
  int memory[256 * 256];
  int currentFrame;
};

struct Memmory addToMemory(struct Memmory testMem, char buffer[])
{

  for (int i = 0; i < 256; i++)
  {
    testMem.memory[(testMem.currentFrame * 256) + i] = buffer[i];
  }
  testMem.currentFrame = testMem.currentFrame + 1;

  return testMem;
};

struct TLB
{
  struct Address array[16];
  int pointer;
};

struct TLB addToTLB(struct TLB TLB_cashe, struct Address address)
{
  if (TLB_cashe.pointer == 16)
  {
    TLB_cashe.pointer = 0;
  }

  TLB_cashe.array[TLB_cashe.pointer] = address;
  TLB_cashe.pointer++;

  return TLB_cashe;
};

int searchTLB(struct TLB TLB_cashe, int logical)
{
  for (int i = 0; i < 16; i++)
  {
    if (TLB_cashe.array[i].logicalAddress != 2147483647 &&
        TLB_cashe.array[i].logicalAddress == logical)
    {
      return TLB_cashe.array[i].physicalAddress;
    }
  }

  return -1;
};

int main()
{
  int pages[256];          // pages
  signed char buffer[256]; // store the information from the binstore to the buffer
  int allAddresses[256];   // we will store all addresses from addresees.txt
  int tr;
  int pointerReadAddresses = 0;
  double pageFaultRate = 0;
  double tlbHitRate = 0;

  struct Memmory myMemmory; // Memmory
  myMemmory.currentFrame = 0;

  struct TLB TLBtest; // TLB
  TLBtest.pointer = 0;

  struct Address test; // test
  test.logicalAddress = 1000;
  test.physicalAddress = 2000;

  for (int i = 0; i < 16; i++)
  {
    TLBtest.array[i].logicalAddress = 2147483647;
  }

  for (int i = 0; i < 256; i++)
  {
    pages[i] = -1;
  }

  // TLBtest = addToTLB(TLBtest, test);
  FILE *aRead = fopen("data/addresses.txt", "r");      // Läsa från filen
  FILE *bRead = fopen("data/BACKING_STORE.bin", "rb"); // Läsa från filen

  if (aRead == NULL)
  {
    printf("Error open the file.\n");
    return 1;
  }
  else
  {
    while ((fscanf(aRead, "%d", &tr) == 1) && pointerReadAddresses < 256)
    {
      allAddresses[pointerReadAddresses] = tr;
      pointerReadAddresses++;
    }

    fclose(aRead);
  }

  // extract the pageNumber and offset
  for (int i = 0; i < 256; i++)
  {
    int pageNumber;
    int pysicl;
    int offset;

    pageNumber = (allAddresses[i] >> 8) & 0x00ff;
    offset = allAddresses[i] & 0xff;

    int resultTLB = searchTLB(TLBtest, pageNumber); // check the tlb first

    if (resultTLB == -1)
    {
      if (pages[pageNumber] == -1)
      {
        // here we want to chnage
        fseek(bRead, (pageNumber * 256), SEEK_SET);
        fread(buffer, 1, 256, bRead);
        pysicl = (myMemmory.currentFrame);
        myMemmory = addToMemory(myMemmory, buffer);
        pages[pageNumber] = pysicl;
        struct Address tempAddress;
        tempAddress.logicalAddress = pageNumber;
        tempAddress.physicalAddress = pysicl;
        TLBtest = addToTLB(TLBtest, tempAddress);
        pageFaultRate++;
      }
      else
      {
        pysicl = pages[pageNumber];
        struct Address tempAddress1;
        tempAddress1.logicalAddress = pageNumber;
        tempAddress1.physicalAddress = pysicl;
        TLBtest = addToTLB(TLBtest, tempAddress1);
      }
    }
    else
    {
      pysicl = resultTLB;
      tlbHitRate++;
    }

    int realAddress = ((pysicl & 0xff)) << 8 | offset;
    signed int value = myMemmory.memory[realAddress];

    printf("Virtual address: %d ", allAddresses[i]);
    printf("Physical address: %d ", realAddress);
    printf("Value: %d\n", value);
  }

  printf("TLB Hit: %f\n", (tlbHitRate / 256) * 100);
  printf("Miss: %f\n", (pageFaultRate / 256) * 100);
  return 0;
}
