#include "initialize.h"
#include <stdio.h>
#include <stdlib.h>

void InitGame(Game *G){
  ElmtName(*G).Length = 0;
  Life(*G) = 5;
  Money(*G) = 0;
  InitRoom(&(Ruang(*G,1)));
  InitRoom(&(Ruang(*G,2)));
  InitRoom(&(Ruang(*G,3)));
  InitDapur(&(Ruang(*G,4)));
  InitGraph(&(RoomGraph(*G)));
  NextCustomerArr = (rand() % 10);
}

void InitPlayer(Player *P){
  CreateEmptyStack(&(OnHand(*P)));
  CreateEmptyStack(&(OnTray(*P)));
  PlayerTick(*P) = 1;
  PosPlayer(*P) =  MakePOINT(5, 5);
  RoomID(*P) = 1;
}

void InitMap(Room *R, POINT PlPoint){
  MakeMATRIKS(RestoSizeM, RestoSizeN, &(Layout(*R)));
  int i,j,x;
  int tableCount = 4;
  int ingCount = 16;
  for (i = GetFirstIdxBrs(Layout(*R)); i <= GetLastIdxBrs(Layout(*R)); i++) {
    for (j = GetFirstIdxKol(Layout(*R)); j <= GetLastIdxKol(Layout(*R)); j++) {
      if (i == 0 && j == 0){
        MatElmt(Layout(*R), i, j) = '#';
      }else if (EQ(PlPoint,MakePOINT(j, i))) {
        MatElmt(Layout(*R), i, j) = 'P';
      }else{
        MatElmt(Layout(*R), i, j) = '.';
      }
      if (RoomStructID(*R)!=4) { //Bukan Dapur
        for (x = 1; x <= tableCount; x++) {
          if (EQ(PosTable(TableNo(*R, x), 0),MakePOINT(j, i))){
            MatElmt(Layout(*R), i, j) = x + '0';
          }
          int xkursi;
          for (xkursi = 1; xkursi <= Capacity(TableNo(*R, x)); xkursi++) {
            if (EQ(PosTable(TableNo(*R, x), xkursi),MakePOINT(j, i))){
              if (IsOccupied(TableNo(*R, x))) {
                MatElmt(Layout(*R), i, j) = 'C';
              } else {
                MatElmt(Layout(*R), i, j) = 'X';
              }
            }
          }
        }
      } else {
        for (x = 0; x < ingCount; x++) {
          if (EQ(PosIngredients(Ingredient(*R, x)),MakePOINT(j, i))){
            MatElmt(Layout(*R), i, j) = 'M';
          }
        }
        if (EQ(PosTray(*R),MakePOINT(j, i))){
          MatElmt(Layout(*R), i, j) = 'T';
        }
      }
    }
  }
}

void InitGraph(GRAPH *G){
  adrNode R1 = AlokNodeGr(1);
  adrNode R2 = AlokNodeGr(2);
  adrNode R3 = AlokNodeGr(3);
  adrNode R4 = AlokNodeGr(4);

  *G = CreateGraph(R1);
  NextNode(R1) = R2;
  NextNode(R2) = R3;
  NextNode(R3) = R4;

  adrEdgeNode E12 = AlokEdgeNode(*G, MakePOINT(5, RestoSizeM), MakePOINT(2, 1), 2);
  adrEdgeNode E21 = AlokEdgeNode(*G, MakePOINT(2, 1), MakePOINT(5, RestoSizeM), 1);
  adrEdgeNode E23 = AlokEdgeNode(*G, MakePOINT(RestoSizeN, 5), MakePOINT(1, 5), 3);
  adrEdgeNode E32 = AlokEdgeNode(*G, MakePOINT(1, 5), MakePOINT(RestoSizeN, 5), 2);
  adrEdgeNode E34 = AlokEdgeNode(*G, MakePOINT(2, 1), MakePOINT(5, RestoSizeM), 4);
  adrEdgeNode E43 = AlokEdgeNode(*G, MakePOINT(5, RestoSizeM), MakePOINT(2, 1), 3);
  adrEdgeNode E14 = AlokEdgeNode(*G, MakePOINT(RestoSizeN, 5), MakePOINT(1, 5), 4);
  adrEdgeNode E41 = AlokEdgeNode(*G, MakePOINT(1, 5), MakePOINT(RestoSizeN, 5), 1);

  addEdgeNode(&R1, E12);
  addEdgeNode(&R1, E14);
  addEdgeNode(&R2, E21);
  addEdgeNode(&R2, E23);
  addEdgeNode(&R3, E32);
  addEdgeNode(&R3, E34);
  addEdgeNode(&R4, E41);
  addEdgeNode(&R4, E43);
}

void InitRoom(Room *R){
  PosTable(TableNo(*R, 1), 0) = MakePOINT(3, 3);
  PosTable(TableNo(*R, 2), 0) = MakePOINT(7, 4);
  PosTable(TableNo(*R, 3), 0) = MakePOINT(3, 8);
  PosTable(TableNo(*R, 4), 0) = MakePOINT(7, 7);
  Capacity(TableNo(*R, 1)) = 4;
  Capacity(TableNo(*R, 2)) = 2;
  Capacity(TableNo(*R, 3)) = 4;
  Capacity(TableNo(*R, 4)) = 2;
  IsOccupied(TableNo(*R, 1)) = false;
  IsOccupied(TableNo(*R, 2)) = false;
  IsOccupied(TableNo(*R, 3)) = false;
  IsOccupied(TableNo(*R, 4)) = false;
  PosTable(TableNo(*R, 1), 1) = MakePOINT(2, 3);
  PosTable(TableNo(*R, 1), 2) = MakePOINT(4, 3);
  PosTable(TableNo(*R, 1), 3) = MakePOINT(3, 2);
  PosTable(TableNo(*R, 1), 4) = MakePOINT(3, 4);
  PosTable(TableNo(*R, 2), 1) = MakePOINT(6, 4);
  PosTable(TableNo(*R, 2), 2) = MakePOINT(8, 4);
  PosTable(TableNo(*R, 2), 3) = MakePOINT(7, 3);
  PosTable(TableNo(*R, 2), 4) = MakePOINT(7, 5);
  PosTable(TableNo(*R, 3), 1) = MakePOINT(2, 8);
  PosTable(TableNo(*R, 3), 2) = MakePOINT(4, 8);
  PosTable(TableNo(*R, 3), 3) = MakePOINT(3, 7);
  PosTable(TableNo(*R, 3), 4) = MakePOINT(3, 9);
  PosTable(TableNo(*R, 4), 1) = MakePOINT(6, 7);
  PosTable(TableNo(*R, 4), 2) = MakePOINT(8, 7);
  PosTable(TableNo(*R, 4), 3) = MakePOINT(7, 6);
  PosTable(TableNo(*R, 4), 4) = MakePOINT(7, 8);
  OrderCStatus(CustomerSeat(TableNo(*R, 1))) = '$';
  OrderCStatus(CustomerSeat(TableNo(*R, 2))) = '$';
  OrderCStatus(CustomerSeat(TableNo(*R, 3))) = '$';
  OrderCStatus(CustomerSeat(TableNo(*R, 4))) = '$';
}

void InitDapur(Room *R){
  PosTray(*R) = MakePOINT(10, 1);
  IngName(Ingredient(*R, 0)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 0)).TabKata[1] = 'p';
  IngName(Ingredient(*R, 0)).TabKata[2] = 'i';
  IngName(Ingredient(*R, 0)).TabKata[3] = 'r';
  IngName(Ingredient(*R, 0)).TabKata[4] = 'i';
  IngName(Ingredient(*R, 0)).TabKata[5] = 'n';
  IngName(Ingredient(*R, 0)).TabKata[6] = 'g';
  IngName(Ingredient(*R, 0)).Length = 7;
  PosIngredients(Ingredient(*R, 0)) = MakePOINT(1, 1);

  IngName(Ingredient(*R, 1)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 1)).TabKata[1] = 's';
  IngName(Ingredient(*R, 1)).TabKata[2] = 'e';
  IngName(Ingredient(*R, 1)).TabKata[3] = 'n';
  IngName(Ingredient(*R, 1)).TabKata[4] = 'd';
  IngName(Ingredient(*R, 1)).TabKata[5] = 'o';
  IngName(Ingredient(*R, 1)).TabKata[6] = 'k';
  IngName(Ingredient(*R, 1)).Length = 7;
  PosIngredients(Ingredient(*R, 1)) = MakePOINT(1, 2);

  IngName(Ingredient(*R, 2)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 2)).TabKata[1] = 'g';
  IngName(Ingredient(*R, 2)).TabKata[2] = 'a';
  IngName(Ingredient(*R, 2)).TabKata[3] = 'r';
  IngName(Ingredient(*R, 2)).TabKata[4] = 'p';
  IngName(Ingredient(*R, 2)).TabKata[5] = 'u';
  IngName(Ingredient(*R, 2)).Length = 6;
  PosIngredients(Ingredient(*R, 2)) = MakePOINT(1, 3);

  IngName(Ingredient(*R, 3)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 3)).TabKata[1] = 'e';
  IngName(Ingredient(*R, 3)).TabKata[2] = 's';
  IngName(Ingredient(*R, 3)).TabKata[3] = 'k';
  IngName(Ingredient(*R, 3)).TabKata[4] = 'r';
  IngName(Ingredient(*R, 3)).TabKata[5] = 'i';
  IngName(Ingredient(*R, 3)).TabKata[6] = 'm';
  IngName(Ingredient(*R, 3)).Length = 7;
  PosIngredients(Ingredient(*R, 3)) = MakePOINT(1, 4);

  IngName(Ingredient(*R, 4)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 4)).TabKata[1] = 'n';
  IngName(Ingredient(*R, 4)).TabKata[2] = 'a';
  IngName(Ingredient(*R, 4)).TabKata[3] = 's';
  IngName(Ingredient(*R, 4)).TabKata[4] = 'i';
  IngName(Ingredient(*R, 4)).Length = 5;
  PosIngredients(Ingredient(*R, 4)) = MakePOINT(1, 5);

  IngName(Ingredient(*R, 5)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 5)).TabKata[1] = 'r';
  IngName(Ingredient(*R, 5)).TabKata[2] = 'o';
  IngName(Ingredient(*R, 5)).TabKata[3] = 't';
  IngName(Ingredient(*R, 5)).TabKata[4] = 'i';
  IngName(Ingredient(*R, 5)).Length = 5;
  PosIngredients(Ingredient(*R, 5)) = MakePOINT(1, 6);

  IngName(Ingredient(*R, 6)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 6)).TabKata[1] = 's';
  IngName(Ingredient(*R, 6)).TabKata[2] = 'p';
  IngName(Ingredient(*R, 6)).TabKata[3] = 'a';
  IngName(Ingredient(*R, 6)).TabKata[4] = 'g';
  IngName(Ingredient(*R, 6)).TabKata[5] = 'h';
  IngName(Ingredient(*R, 6)).TabKata[6] = 'e';
  IngName(Ingredient(*R, 6)).TabKata[7] = 't';
  IngName(Ingredient(*R, 6)).TabKata[8] = 't';
  IngName(Ingredient(*R, 6)).TabKata[9] = 'i';
  IngName(Ingredient(*R, 6)).Length = 10;
  PosIngredients(Ingredient(*R, 6)) = MakePOINT(1, 7);

  IngName(Ingredient(*R, 7)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 7)).TabKata[1] = 'p';
  IngName(Ingredient(*R, 7)).TabKata[2] = 'i';
  IngName(Ingredient(*R, 7)).TabKata[3] = 's';
  IngName(Ingredient(*R, 7)).TabKata[4] = 'a';
  IngName(Ingredient(*R, 7)).TabKata[5] = 'n';
  IngName(Ingredient(*R, 7)).TabKata[6] = 'g';
  IngName(Ingredient(*R, 7)).Length = 7;
  PosIngredients(Ingredient(*R, 7)) = MakePOINT(1, 8);

  IngName(Ingredient(*R, 8)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 8)).TabKata[1] = 's';
  IngName(Ingredient(*R, 8)).TabKata[2] = 't';
  IngName(Ingredient(*R, 8)).TabKata[3] = 'r';
  IngName(Ingredient(*R, 8)).TabKata[4] = 'o';
  IngName(Ingredient(*R, 8)).TabKata[5] = 'b';
  IngName(Ingredient(*R, 8)).TabKata[6] = 'e';
  IngName(Ingredient(*R, 8)).TabKata[7] = 'r';
  IngName(Ingredient(*R, 8)).TabKata[8] = 'i';
  IngName(Ingredient(*R, 8)).Length = 9;
  PosIngredients(Ingredient(*R, 8)) = MakePOINT(1, 9);

  IngName(Ingredient(*R, 9)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 9)).TabKata[1] = 't';
  IngName(Ingredient(*R, 9)).TabKata[2] = 'e';
  IngName(Ingredient(*R, 9)).TabKata[3] = 'l';
  IngName(Ingredient(*R, 9)).TabKata[4] = 'u';
  IngName(Ingredient(*R, 9)).TabKata[5] = 'r';
  IngName(Ingredient(*R, 9)).Length = 6;
  PosIngredients(Ingredient(*R, 9)) = MakePOINT(1, 10);

  IngName(Ingredient(*R, 10)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 10)).TabKata[1] = 'a';
  IngName(Ingredient(*R, 10)).TabKata[2] = 'y';
  IngName(Ingredient(*R, 10)).TabKata[3] = 'a';
  IngName(Ingredient(*R, 10)).TabKata[4] = 'm';
  IngName(Ingredient(*R, 10)).TabKata[5] = 'g';
  IngName(Ingredient(*R, 10)).TabKata[6] = 'o';
  IngName(Ingredient(*R, 10)).TabKata[7] = 'r';
  IngName(Ingredient(*R, 10)).TabKata[8] = 'e';
  IngName(Ingredient(*R, 10)).TabKata[9] = 'n';
  IngName(Ingredient(*R, 10)).TabKata[10] = 'g';
  IngName(Ingredient(*R, 10)).Length = 11;
  PosIngredients(Ingredient(*R, 10)) = MakePOINT(4, 3);

  IngName(Ingredient(*R, 11)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 11)).TabKata[1] = 'p';
  IngName(Ingredient(*R, 11)).TabKata[2] = 'a';
  IngName(Ingredient(*R, 11)).TabKata[3] = 't';
  IngName(Ingredient(*R, 11)).TabKata[4] = 't';
  IngName(Ingredient(*R, 11)).TabKata[5] = 'y';
  IngName(Ingredient(*R, 11)).Length = 6;
  PosIngredients(Ingredient(*R, 11)) = MakePOINT(5, 3);

  IngName(Ingredient(*R, 12)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 12)).TabKata[1] = 's';
  IngName(Ingredient(*R, 12)).TabKata[2] = 'o';
  IngName(Ingredient(*R, 12)).TabKata[3] = 's';
  IngName(Ingredient(*R, 12)).TabKata[4] = 'i';
  IngName(Ingredient(*R, 12)).TabKata[5] = 's';
  IngName(Ingredient(*R, 12)).Length = 6;
  PosIngredients(Ingredient(*R, 12)) = MakePOINT(6, 3);

  IngName(Ingredient(*R, 13)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 13)).TabKata[1] = 'b';
  IngName(Ingredient(*R, 13)).TabKata[2] = 'o';
  IngName(Ingredient(*R, 13)).TabKata[3] = 'l';
  IngName(Ingredient(*R, 13)).TabKata[4] = 'o';
  IngName(Ingredient(*R, 13)).TabKata[5] = 'g';
  IngName(Ingredient(*R, 13)).TabKata[6] = 'n';
  IngName(Ingredient(*R, 13)).TabKata[7] = 'e';
  IngName(Ingredient(*R, 13)).TabKata[8] = 's';
  IngName(Ingredient(*R, 13)).TabKata[9] = 'e';
  IngName(Ingredient(*R, 13)).Length = 10;
  PosIngredients(Ingredient(*R, 13)) = MakePOINT(4, 6);

  IngName(Ingredient(*R, 14)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 14)).TabKata[1] = 'c';
  IngName(Ingredient(*R, 14)).TabKata[2] = 'a';
  IngName(Ingredient(*R, 14)).TabKata[3] = 'r';
  IngName(Ingredient(*R, 14)).TabKata[4] = 'b';
  IngName(Ingredient(*R, 14)).TabKata[5] = 'o';
  IngName(Ingredient(*R, 14)).TabKata[6] = 'n';
  IngName(Ingredient(*R, 14)).TabKata[7] = 'a';
  IngName(Ingredient(*R, 14)).TabKata[8] = 'r';
  IngName(Ingredient(*R, 14)).TabKata[9] = 'a';
  IngName(Ingredient(*R, 14)).Length = 10;
  PosIngredients(Ingredient(*R, 14)) = MakePOINT(5, 6);

  IngName(Ingredient(*R, 15)).TabKata[0] = ' ';
  IngName(Ingredient(*R, 15)).TabKata[1] = 'k';
  IngName(Ingredient(*R, 15)).TabKata[2] = 'e';
  IngName(Ingredient(*R, 15)).TabKata[3] = 'j';
  IngName(Ingredient(*R, 15)).TabKata[4] = 'u';
  IngName(Ingredient(*R, 15)).Length = 5;
  PosIngredients(Ingredient(*R, 15)) = MakePOINT(6, 6);
}

void InitKataCommand(){
  KataGU.TabKata[0] = 'G';
  KataGU.TabKata[1] = 'U';
  KataGU.Length = 2;

  KataGD.TabKata[0] = 'G';
  KataGD.TabKata[1] = 'D';
  KataGD.Length = 2;

  KataGL.TabKata[0] = 'G';
  KataGL.TabKata[1] = 'L';
  KataGL.Length = 2;

  KataGR.TabKata[0] = 'G';
  KataGR.TabKata[1] = 'R';
  KataGR.Length = 2;

  KataORDER.TabKata[0] = 'O';
  KataORDER.TabKata[1] = 'R';
  KataORDER.TabKata[2] = 'D';
  KataORDER.TabKata[3] = 'E';
  KataORDER.TabKata[4] = 'R';
  KataORDER.Length = 5;

  KataPUT.TabKata[0] = 'P';
  KataPUT.TabKata[1] = 'U';
  KataPUT.TabKata[2] = 'T';
  KataPUT.Length = 3;

  KataTAKE.TabKata[0] = 'T';
  KataTAKE.TabKata[1] = 'A';
  KataTAKE.TabKata[2] = 'K';
  KataTAKE.TabKata[3] = 'E';
  KataTAKE.Length = 4;

  KataCH.TabKata[0] = 'C';
  KataCH.TabKata[1] = 'H';
  KataCH.Length = 2;

  KataCT.TabKata[0] = 'C';
  KataCT.TabKata[1] = 'T';
  KataCT.Length = 2;

  KataPLACE.TabKata[0] = 'P';
  KataPLACE.TabKata[1] = 'L';
  KataPLACE.TabKata[2] = 'A';
  KataPLACE.TabKata[3] = 'C';
  KataPLACE.TabKata[4] = 'E';
  KataPLACE.Length = 5;

  KataGIVE.TabKata[0] = 'G';
  KataGIVE.TabKata[1] = 'I';
  KataGIVE.TabKata[2] = 'V';
  KataGIVE.TabKata[3] = 'E';
  KataGIVE.Length = 4;

  KataRECIPE.TabKata[0] = 'R';
  KataRECIPE.TabKata[1] = 'E';
  KataRECIPE.TabKata[2] = 'C';
  KataRECIPE.TabKata[3] = 'I';
  KataRECIPE.TabKata[4] = 'P';
  KataRECIPE.TabKata[5] = 'E';
  KataRECIPE.Length = 6;

  KataSAVE.TabKata[0] = 'S';
  KataSAVE.TabKata[1] = 'A';
  KataSAVE.TabKata[2] = 'V';
  KataSAVE.TabKata[3] = 'E';
  KataSAVE.Length = 4;

  KataLOAD.TabKata[0] = 'L';
  KataLOAD.TabKata[1] = 'O';
  KataLOAD.TabKata[2] = 'A';
  KataLOAD.TabKata[3] = 'D';
  KataLOAD.Length = 4;

  KataEXIT.TabKata[0] = 'E';
  KataEXIT.TabKata[1] = 'X';
  KataEXIT.TabKata[2] = 'I';
  KataEXIT.TabKata[3] = 'T';
  KataEXIT.Length = 4;
}
